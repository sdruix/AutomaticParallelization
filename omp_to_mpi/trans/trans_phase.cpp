#include "trans_phase.hpp"
#include "FunctionDefinitionPred.hpp"
#include "FunctionCallsPred.hpp"
#include <stdlib.h>
#include "hlt/hlt-common.hpp"
#include "tl-omp.hpp"
#include <iostream>
#include <fstream>
#include "regex.h"


#include <bits/basic_string.h>

using namespace TL;
using namespace TL::HLT;
using namespace std;

TransPhase::TransPhase() : PragmaCustomCompilerPhase("omp") {
    
    register_construct("parallel");
    register_construct("for");
    register_directive("check");
    register_directive("for check");
    register_directive("for private");
    
    on_directive_post["parallel"].connect(functor(&TransPhase::pragma_postorder, *this));
    
    
}

void TransPhase::run(DTO& dto) {
    _dto=dto;
    vector<string> keys;
    keys =dto.get_keys();
    
    
    _translation_unit = dto["translation_unit"];
    _scope_link = dto["scope_link"];  
    PragmaCustomCompilerPhase::run(dto);
    finalize();
    
}
void TransPhase::pragma_postorder(PragmaCustomConstruct construct) {
    
    
    string pragmaInstruction = construct.get_pragma_line().prettyprint(false);
    FunctionDefinition function_def = construct.get_enclosing_function();
    Symbol function_sym = function_def.get_function_symbol();
    Scope functionScope = function_def.get_function_body().get_scope();
    Scope globalScope = function_def.get_scope();
    cout<<"OMP("<<pragmaInstruction<<" in: "<<function_sym.get_name()<<endl;
    TL::PragmaCustomClause check_clause = construct.get_clause("check");
    if(check_clause.is_defined()) {
        if(checkFor(construct)) {
            _file_tree = construct.get_statement().get_ast().get_enclosing_global_tree();
            Statement statement = construct.get_statement();
            _ioVars.clear();
            int block_line = get_real_line(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(), construct.get_ast(),1,0);
            TL::HLT::Outline outlineAux(construct.get_enclosing_function().get_scope_link(), statement, block_line);
            ObjectList<Symbol> prmters;
            prmters = outlineAux.get_parameter_list();
            AST_t prevAST;
            AST_t last_ast = fill_smart_use_table(construct.get_enclosing_function().get_ast(), function_def.get_function_body().get_scope_link(), construct.get_enclosing_function().get_scope_link().get_scope(statement.get_ast()), block_line, prmters,2,0, prevAST);
            for (Mymap::const_iterator it = _smart_use_table.begin(); 
                    it != _smart_use_table.end(); ++it) {
                
                if(it->second.row_last_read_cpu.row!=0) 
                    std::cout<<it->first<< "LR(CPU)("<<it->second.row_last_read_cpu.for_num<<"): "<<it->second.row_last_read_cpu.row<<" -> "<<it->second.row_last_read_cpu.ast.prettyprint()<<endl;
                if(it->second.row_last_write_cpu.row!=0) 
                    std::cout<<it->first<< "LW(CPU)("<<it->second.row_last_write_cpu.for_num<<"): "<<it->second.row_last_write_cpu.row<<" -> "<<it->second.row_last_write_cpu.ast.prettyprint()<<endl;
                if(it->second.row_first_read_cpu.row!=0) 
                    std::cout<<it->first<< "FR(CPU)("<<it->second.row_first_read_cpu.for_num<<"): "<<it->second.row_first_read_cpu.row<<" -> "<<it->second.row_first_read_cpu.ast.prettyprint()<<endl;
                if(it->second.row_first_write_cpu.row!=0) 
                    std::cout<<it->first<< "FW(CPU)("<<it->second.row_first_write_cpu.for_num<<"): "<<it->second.row_first_write_cpu.row<<" -> "<<it->second.row_first_write_cpu.ast.prettyprint()<<endl;
                std::cout<<"---------------------------"<<endl;
            }
            _ioParams = outlineAux.get_parameter_io(construct.get_scope());
            Source commented_loop;
            PragmaCustomClause red_clause = construct.get_clause("reduction");
            PragmaCustomClause static_clause = construct.get_clause("static");
            if(_lastFunctionName.compare(function_sym.get_name())!=0) {
                _initialized = 0;
                _lastFunctionName = function_sym.get_name();
            }
            int staticC = 0;
            if(static_clause.is_defined()) {
                staticC = 1;
                cout<< "Static Transformation"<<endl;
            } else {
                cout<< "Dynamic Transformation"<<endl;
            }
            Source arg;
            
            
            _reducedVarsIndexStart = _reducedVars.size();
            _reducedVars.clear();
            Source emptySource,emptySourceVar;
            if(!_initialized) {
                _initialized = 1;
                emptySource<<
                        "MPI_Status stat;"
                        "int size, myid;"
                        "int *n1;"
                        "char *** n2;"
                        "MPI_Init(n1,n2);"
                        "MPI_Comm_size(MPI_COMM_WORLD,&size);"
                        "MPI_Comm_rank(MPI_COMM_WORLD,&myid);"
                        "const int FTAG = 0;"
                        "const int ATAG = 1;"
                        ;
            }
            //Initialization Common in all
            TL::Statement function_body = function_def.get_function_body();
            Source mpiFixStructurePart1, mpiFixStructurePart2, constructASTS;
            Source mpiVariantStructurePart1, mpiVariantStructurePart2, mpiVariantStructurePart3;
            mpiFixStructurePart1 << "if(myid == 0) {\n ";
            ForStatement fS(construct.get_statement());
            AST_t pragma2mpi = fS.get_loop_body().get_ast();
            construct.get_ast().replace_with(pragma2mpi);
            Expression iterating = fS.get_iterating_expression();
            Expression condition = fS.get_iterating_condition();
            AST_t init = fS.get_iterating_init();
            Expression exprInit(init, fS.get_scope_link());
            Source initVar, initValue, initS;
            initS << exprInit.prettyprint();
            if (red_clause.is_defined()) {
                cout<< "Reduction"<<endl;
                ObjectList<std::string> red_args = red_clause.get_arguments();
                for (ObjectList<std::string>::iterator it = red_args.begin(); it != red_args.end(); it++) {
                    string argument(*it);
                    string act, operation;
                    while(argument.find_first_of(":")>=0 && argument.find_first_of(":")<argument.length()) {
                        operation = argument.substr(0,argument.find_first_of(":"));
                        //std::cout <<"n: "<<num<<std::endl;
                        if(argument.find_first_of(",")>=0 && argument.find_first_of(",")<argument.length()) {
                            act = argument.substr(argument.find_first_of(":")+1,argument.find_first_of(",")-1);
                            argument = argument.substr(argument.find_first_of(",")+1,argument.length());
                        } else {
                            act = argument.substr(argument.find_first_of(":")+1,argument.length());
                            argument = argument.substr(argument.find_first_of(":")+1,argument.length());
                        }
                        infoVar newR;
                        newR.name << act;
                        newR.operation << operation;
                        // cout << "N: -"<< std::string(newR.name) <<"- O: -"<< std::string(newR.operation) <<"-"<< endl;
                        Symbol findedS = functionScope.get_symbol_from_name(newR.name);
                        string declaration;
                        if(!findedS.is_valid()){
                            findedS = globalScope.get_symbol_from_name(newR.name);
                            if(findedS.is_valid()){
                                declaration = std::string(findedS.get_type().get_declaration(globalScope,newR.name));
                                declaration = declaration.substr(0, declaration.find(newR.name));
                            }
                        } else {
                            declaration = std::string(findedS.get_type().get_declaration(functionScope,newR.name));
                            declaration = declaration.substr(0, declaration.find(newR.name));
                        }
                        declaration = cleanWhiteSpaces(declaration);
                        
                        //cout<< "FS: -"<<declaration<<"-"<<endl;
                        newR.type <<  declaration;
                        _reducedVars.push_back(newR);
                        
                        
                    }
                    
                }
                
                PragmaCustomClause shared_clause = construct.get_clause("shared");
                if (shared_clause.is_defined()) {
                    commented_loop
                            << "// Arguments found in shared clausule: \n";
                    cout << "// Arguments found in shared clausule: " << endl;
                    ObjectList<Expression> shared_arguments = shared_clause.get_expression_list();
                    for (ObjectList<Expression>::iterator it = shared_arguments.begin(); it != shared_arguments.end(); it++) {
                        Expression argument(*it);
                        commented_loop
                        << "//  - " << argument.prettyprint() << "\n";
                        cout << "//  - " << argument.prettyprint() << endl;
                    }
                }
                
                
                
                
                for(int i = 0; i<_reducedVars.size(); ++i){
                    emptySource<< _reducedVars[i].type <<" work"<<_reducedVarsIndexStart+i<<";";  
                }
                
                TraverseASTFunctor4LocateUse expr_traverse(_scope_link);
                ObjectList<AST_t> expr_list = function_body.get_ast().depth_subtrees(expr_traverse);
                AST_t emptyAst = emptySource.parse_statement(function_body.get_ast(), function_body.get_scope_link());
                //                cout<< emptyAst.prettyprint()<<endl;
                expr_list[0].prepend(emptyAst);
                
                
                
                // Master Code
                
                
                if(staticC){
                    mpiVariantStructurePart1 <<"for("<<std::string(initS)<<condition.get_ast().prettyprint()<<";" <<iterating.get_ast().prettyprint()<<")"
                            "{\n"
                            "int index = (i%(size-1))+1;"
                            "MPI_Send(&i, 1 , MPI_INT, index, ATAG, MPI_COMM_WORLD);"
                            "}\n"
                            "for(int node = 1; node < size; ++node)"
                            "{"
                            "MPI_Send(&node,1,MPI_INT,i,FTAG,MPI_COMM_WORLD);";
                    
                    for(int i = 0; i<_reducedVars.size(); ++i){
                        
                        string upperType = std::string(_reducedVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1<< "MPI_Recv(&work"<<_reducedVarsIndexStart+i<<", 1, MPI_"<<upperType<<", i, MPI_ANY_TAG, MPI_COMM_WORLD,&stat);";
                        mpiVariantStructurePart1<< _reducedVars[i].name<<" "<<_reducedVars[i].operation<<"= work"<<_reducedVarsIndexStart+i<<";";
                    }
                    mpiVariantStructurePart1<<"}";
                    
                    
                    
                    
                    
                } else {
                    mpiVariantStructurePart1<<"for(int node = 1; node < size; ++node)"
                            "{"
                            "int index = node-1;"
                            "MPI_Send(&index,1,MPI_INT,node,ATAG,MPI_COMM_WORLD);"
                            "}"
                            "int followIN = size-1; while(1){";
                    
                    for(int i = 0; i<_reducedVars.size(); ++i){
                        string upperType = std::string(_reducedVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1<< "MPI_Recv(&work"<<_reducedVarsIndexStart+i<<", 1, MPI_"<<upperType<<", node, MPI_ANY_TAG, MPI_COMM_WORLD,&stat);";
                        mpiVariantStructurePart1<< _reducedVars[i].name<<" "<<_reducedVars[i].operation<<"= work"<<_reducedVarsIndexStart+i<<";";
                    }
                    
                    string conditionToWork = condition.prettyprint();
                    //                cout<<conditionToWork<<endl;
                    if(conditionToWork.find_first_of("=")>=0 && conditionToWork.find_first_of("=")<conditionToWork.length()){
                        conditionToWork = conditionToWork.substr(conditionToWork.find_first_of("=")+1,conditionToWork.length());
                    }
                    if(conditionToWork.find_first_of("<")>=0 && conditionToWork.find_first_of("<")<conditionToWork.length()){
                        conditionToWork =conditionToWork.substr(conditionToWork.find_first_of("<")+1,conditionToWork.length());
                    }
                    if(conditionToWork.find_first_of(">")>=0 && conditionToWork.find_first_of(">")<conditionToWork.length()){
                        conditionToWork =conditionToWork.substr(conditionToWork.find_first_of(">")+1,conditionToWork.length());
                    }
                    conditionToWork = cleanWhiteSpaces(conditionToWork);
                    mpiVariantStructurePart1<<"if(followIN<"<<conditionToWork<<"){"
                            "MPI_Send(&followIN,1,MPI_INT,stat.MPI_source,ATAG,MPI_COMM_WORLD);"
                            "} else {"
                            "MPI_Send(&followIN,1,MPI_INT,stat.MPI_source,FTAG,MPI_COMM_WORLD);"
                            "}"
                            "followIN++;"
                            "if(followIN>="<<conditionToWork<<"+size-1) {"
                            "break;"
                            "}"
                            "}";
                    
                }
                
                mpiFixStructurePart1 <<mpiVariantStructurePart1<< "}";
                //pragma2mpi.prepend(ASTmpiFixStructurePart1);
                AST_t ASTmpiFixStructurePart1 = mpiFixStructurePart1.parse_statement(function_body.get_ast(), function_body.get_scope_link());
                construct.get_ast().prepend(ASTmpiFixStructurePart1);
                
                //Slave Code
                constructASTS << construct.get_ast().prettyprint(); 
                mpiFixStructurePart2 << "if(myid !=0){ "
                        "int i=0; "
                        "while(1) {"
                        "MPI_Recv(&i,1, MPI_INT, 0 , MPI_ANI_TAG, MPI_COMM_WORLD, &stat);"
                        "if(stat.MPI_TAG == ATAG) {";
                if(!staticC) {
                    for(int i = 0; i<_reducedVars.size(); ++i){
                        string upperType = std::string(_reducedVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart2<< "MPI_Send(&work"<<_reducedVarsIndexStart+i<<", 1, MPI_"<<upperType<<", 0, 0, MPI_COMM_WORLD);";
                        
                    }   
                }    
                mpiFixStructurePart2<<constructASTS<<mpiVariantStructurePart2<<"} else if(stat.MPI_TAG == FTAG) {";
                if(staticC)  {  
                    for(int i = 0; i<_reducedVars.size(); ++i){
                        string upperType = std::string(_reducedVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart3<< "MPI_Send(&sum, 1, MPI_"<<upperType<<", 0, 0, MPI_COMM_WORLD);";
                    }
                } 
                
                mpiFixStructurePart2<<mpiVariantStructurePart3<<"break;}"
                        "}"
                        "}";
                AST_t ASTmpiFixStructurePart2 = mpiFixStructurePart2.parse_statement(function_body.get_ast(), function_body.get_scope_link());
                construct.get_ast().replace_with(ASTmpiFixStructurePart2);
                _lastAST.push_back(construct.get_ast());
                _lastFunctionNameList.push_back(function_sym.get_name());
                
                
                
                //            cout<<function_def.get_function_body().get_ast().prettyprint(false)<<endl;
                
                
            } else {
                cout<< "Array"<<endl;
                
                typedef std::unordered_map <std::string,AST_t> iter4io; 
                int l=0;
                for (iter4io::const_iterator it = _ioParams.begin(); it != _ioParams.end(); ++it, ++l) {
                    infoVar newR;
                    newR.name << it->first;
                    newR.iterVar = findPrincipalIterator(it->second, it->first);
                    Symbol findedS = functionScope.get_symbol_from_name(newR.name);
                    string declaration;
                    string sizeS, maxS;
                    if(!findedS.is_valid()){
                        findedS = globalScope.get_symbol_from_name(newR.name);
                        if(findedS.is_valid()){
                            declaration = std::string(findedS.get_type().get_declaration(globalScope,newR.name));
                            declaration = declaration.substr(0, declaration.find(newR.name));
                        }
                    } else {
                        declaration = std::string(findedS.get_type().get_declaration(functionScope,newR.name));
                        declaration = declaration.substr(0, declaration.find(newR.name));
                    }
                    if(findedS.is_valid()) {
                        if(findedS.get_type().is_pointer()) {
                            AST_t allocateAst;
                            TraverseASTFunctor4Malloc expr_traverse(_scope_link);
                            ObjectList<AST_t> asts = allocateAst.depth_subtrees(expr_traverse);
                            int l=0;
                            for (ObjectList<AST_t>::iterator it = asts.begin();it != asts.end();it++,l++) {
                                Expression expr(asts[l], _scope_link);
                                std::string firstOperand;
                                firstOperand = expr.get_first_operand().prettyprint();
                                size_t arrayAcces;
                                arrayAcces = firstOperand.find("[");
                                if(arrayAcces < 0 || arrayAcces>firstOperand.length()) {
                                    //cout<<"3"<<endl;
                                    Symbol sym = expr.get_first_operand().get_symbol();
                                    if(sym.get_type().is_pointer()) {
                                        std::string mallocExpr, mallocString;
                                        mallocExpr = expr.prettyprint();
                                        size_t findMalloc;
                                        findMalloc = mallocExpr.find("malloc");
                                        if(findMalloc > 0 && findMalloc<mallocExpr.length()) {
                                            sizeS = mallocExpr.substr(findMalloc+6,mallocExpr.length());
                                        }
                                    }
                                } 
                            } 
                        } else if(findedS.get_type().is_array()) {
                            string declaratrionS = findedS.get_point_of_declaration().prettyprint();
                            newR.size = get_size_of_array(newR.name, declaratrionS);
                            
                        }
                    }
                    
                    
                    declaration = cleanWhiteSpaces(declaration);
                    
                    //cout<< "FS: -"<<declaration<<"-"<<endl;
                    newR.type <<  declaration;
                    _ioVars.push_back(newR);
                    
                    
                    
                    
                }
                int maxS = 0;
                for(int i = 0; i<_ioVars.size(); ++i){
                    if(_ioVars[i].size>maxS)
                        maxS=_ioVars[i].size;
                }
                emptySource << "int partSize = "<<maxS<<"/ (size-1), offset;";
                
                
                TraverseASTFunctor4LocateUse expr_traverse(_scope_link);
                ObjectList<AST_t> expr_list = function_body.get_ast().depth_subtrees(expr_traverse);
                AST_t emptyAst = emptySource.parse_statement(function_body.get_ast(), function_body.get_scope_link());
                //                cout<< emptyAst.prettyprint()<<endl;
                expr_list[0].prepend(emptyAst);
                if(staticC) {
                    mpiVariantStructurePart1 << "for (int to=1;to<size;++to) {"
                            "if(to!=size-1) {";
                    
                    mpiVariantStructurePart1 << "partSize = "<<maxS<<"/ (size-1);"
                            << "offset = partSize * (to-1);"
                            << "} else {"
                            << "partSize = "<<maxS<<"/ (size-1) + "<<maxS <<"%"<<"(size-1) ;"
                            << "offset = " << maxS << "/ (size-1) * (to-1);"
                            << "}";
                    for(int i = 0; i<_ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1 << "MPI_Send(&"<<_ioVars[i].name<<"[offset], partSize, MPI_"<<upperType<<",to,ATAG,MPI_COMM_WORLD);";
                    }
                    mpiVariantStructurePart1 << "}"
                            << "for(int from = 1; from<size;++from) {"
                            << "if(from!=size-1) {"
                            << "partSize = "<<maxS<<"/ (size-1);"
                            << "offset = partSize * (from-1);" 
                            << "} else {"
                            << "partSize = "<<maxS<<"/ (size-1) + "<<maxS <<"%"<<"(size-1) ;"
                            << "offset = " << maxS << "/ (size-1) * (from-1);"
                            << "}";
                    for(int i = 0; i<_ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1 << "MPI_Recv(&"<<_ioVars[i].name<<"[offset], partSize, MPI_"<<upperType<<",from,MPI_ANY_TAG,MPI_COMM_WORLD, &stat);";
                    }
                    string upperType = std::string(_ioVars[0].type);
                    std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                    mpiVariantStructurePart1 << "}"
                            << "for (int s = 0; s <size; ++s) {"
                            << " MPI_Send(&s, 1, MPI_"<<upperType<<", s,FTAG,MPI_COMM_WORLD);"
                            <<"}";
                    
                    
                } else {
                    
                    mpiVariantStructurePart1 << "int followIN = 0; int killed = 0;"
                            << "for (int to=1; to<size; ++to) {"
                            << "MPI_Send(&followIN, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);"
                            << "MPI_Send(&partSize, 1, MPI_INT, to, ATAG, MPI_COMM_WORLD);";
                    for(int i=0; i< _ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[0].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1 << "MPI_Send(&"<<_ioVars[i].name<<"[followIN], partSize, MPI_"<<upperType<<",to,ATAG,MPI_COMM_WORLD);";
                    }
                    mpiVariantStructurePart1 << "followIN += partSize;"
                            << "}"
                            << " while(1){"
                            << "MPI_Recv(&offset, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);"
                            << "int source = stat.MPI_SOURCE;"
                            << "MPI_Recv(&partSize, 1, MPI_INT, 0, source, MPI_COMM_WORLD, &stat);";
                    for(int i = 0; i<_ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1 << "MPI_Recv(&"<<_ioVars[i].name<<"[offset], partSize, MPI_"<<upperType<<",source,MPI_ANY_TAG,MPI_COMM_WORLD, &stat);";
                    }
                    mpiVariantStructurePart1 << "if ((followIN+partSize) <"<<maxS<<") {"
                            << "MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);"
                            << "MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);";
                    for(int i = 0; i<_ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1 << "MPI_Send(&"<<_ioVars[i].name<<"[followIN], partSize, MPI_"<<upperType<<",source,ATAG,MPI_COMM_WORLD);";
                    }
                    mpiVariantStructurePart1 << "} else if(("<<maxS<<"-followIN)< partSize && ("<<maxS<<"-followIN)>0) {"
                            << "partSize ="<<maxS <<"-followIN;"
                            << "MPI_Send(&followIN, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);"
                            << "MPI_Send(&partSize, 1, MPI_INT, source, ATAG, MPI_COMM_WORLD);";
                    for(int i = 0; i<_ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart1 << "MPI_Send(&"<<_ioVars[i].name<<"[followIN], partSize, MPI_"<<upperType<<",source,ATAG,MPI_COMM_WORLD);";
                    }
                    mpiVariantStructurePart1 << "}";
                    mpiVariantStructurePart1 << "if((followIN+partSize) > "<<maxS<<") {"
                            << "MPI_Send(&offset, 1, MPI_INT, source, FTAG, MPI_COMM_WORLD);"
                            << "killed++;"
                            << " }"
                            << "followIN+=partSize;"
                            << "if(killed==size-1) {"
                            << "break; }"
                            <<"}";
                }   
                mpiFixStructurePart1 <<mpiVariantStructurePart1;
                
                mpiFixStructurePart1 <<"}";
                //pragma2mpi.prepend(ASTmpiFixStructurePart1);
                
                AST_t ASTmpiFixStructurePart1 = mpiFixStructurePart1.parse_statement(function_body.get_ast(), function_body.get_scope_link());
                construct.get_ast().prepend(ASTmpiFixStructurePart1);
                constructASTS << construct.get_ast().prettyprint(); 
                Source mpiVariantStructurePart4, mpiVariantStructurePart5, mpiVariantStructurePart6;
                
                
                if(staticC) {
                    mpiVariantStructurePart4 <<"if(myid!=size-1) {"
                            << "partSize = "<<maxS<<"/ (size-1);"
                            << "offset = partSize * (myid-1);"
                            <<" } else {"
                            << "partSize = "<<maxS<<"/ (size-1) + "<<maxS <<"%"<<"(size-1) ;"
                            << "offset = " << maxS << "/ (size-1) * (myid-1);"
                            << "}";
                    
                } else {
                    mpiVariantStructurePart4<<"while(1){"
                            "MPI_Recv(&offset, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);";
                    mpiVariantStructurePart6 << "MPI_Recv(&partSize, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD);";
                    for(int i = 0; i<_ioVars.size(); ++i){
                        string upperType = std::string(_ioVars[i].type);
                        std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                        mpiVariantStructurePart6<<"MPI_Recv(&"<<_ioVars[i].name<<"[offset], partSize, MPI_"<<upperType<<", 0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);";
                    }
                    mpiVariantStructurePart2 << "MPI_Send(&offset, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);"
                            "MPI_Send(&partSize,1, MPI_INT, 0, 0, MPI_COMM_WORLD);";
                    
                }
                
                mpiFixStructurePart2 << "if(myid !=0){ "
                        <<mpiVariantStructurePart4
                        <<"if(stat.MPI_TAG == ATAG) {"
                        <<mpiVariantStructurePart6
                        <<"for(int "<<_ioVars[_ioVars.size()-1].iterVar<<" = offset; "<<_ioVars[_ioVars.size()-1].iterVar<<"<offset+partSize;++"<<_ioVars[_ioVars.size()-1].iterVar<<")"
                        <<constructASTS<<mpiVariantStructurePart2;
                for(int i = 0; i<_ioVars.size(); ++i){
                    string upperType = std::string(_ioVars[i].type);
                    std::transform(upperType.begin(), upperType.end(),upperType.begin(), ::toupper);
                    mpiFixStructurePart2<<"MPI_Send(&"<<_ioVars[i].name<<"[offset], partSize, MPI_"<<upperType<<", 0, 0, MPI_COMM_WORLD);";
                }
                
                mpiFixStructurePart2 <<"} else if(stat.MPI_TAG == FTAG) {";
                if(!staticC){
                    mpiVariantStructurePart5 << "}";
                }
                mpiFixStructurePart2<<mpiVariantStructurePart3<<"break;}"
                        "}"
                        <<mpiVariantStructurePart5;
                AST_t ASTmpiFixStructurePart2 = mpiFixStructurePart2.parse_statement(function_body.get_ast(), function_body.get_scope_link());
                construct.get_ast().replace_with(ASTmpiFixStructurePart2);
                _lastAST.push_back(construct.get_ast());
                _lastFunctionNameList.push_back(function_sym.get_name());
                
            }
        } else {
            AST_t new_block;
            Source new_blockS;
            int preHMPPstart=0;
            string clauses;
            std::string fixedS,checkS;
            clauses =  construct.get_pragma_line().prettyprint();
            if(clauses.find("check")>=0 && clauses.find("check")<clauses.length()) {
                checkS=" check";
                preHMPPstart=1;
            }
            if(clauses.find("fixed")>=0 && clauses.find("fixed")<clauses.length()) {
                fixedS= clauses.substr(clauses.find("fixed"), clauses.find_last_of(")"));
                preHMPPstart=1;
            }
            if(preHMPPstart) {
                construct.get_ast().replace(construct.get_statement().get_ast());
                TraverseASTFunctor4LocateOMP expr_traverse(construct.get_scope_link());
                ObjectList<AST_t> expr_list = construct.get_ast().depth_subtrees(expr_traverse);
                int l=0;
                ObjectList<PragmaCustomConstruct> constructList;
                for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
                    
                    Expression expr(expr_list[l], construct.get_scope_link());
                    PragmaCustomConstruct test(expr.get_ast(),expr.get_scope_link());
                    
                    
                    if(test.is_construct()){
                        constructList.push_back(test);
                        Statement statement = test.get_statement();
                        clauses =  test.get_pragma_line().prettyprint();
                        string checkSinside,fixedSinside;
                        if(clauses.find("check")>=0 && clauses.find("check")<clauses.length()) {
                            if(fixedS.empty())
                                checkSinside=" check";    
                            clauses  = clauses.substr(0,clauses.find("check")-1);
                        }
                        if(clauses.find("fixed")>=0 && clauses.find("fixed")<clauses.length()) {
                            //                    if(!preHMPPstart)
                            fixedSinside= clauses.substr(clauses.find("fixed"), clauses.find_last_of(")"));
                            clauses  = clauses.substr(0,clauses.find("fixed")-1);
                        }
                        int outline_line = get_real_line(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(), construct.get_ast(),1,0);
                        TL::HLT::Outline outlineAux(statement.get_scope_link(), statement,outline_line);
                        Source sharedVars,privateVars, s,sep,f;
                        s<<"shared(";
                        sep <<", ";
                        f <<") ";
                        sharedVars = outlineAux.get_parameter_io(statement.get_scope(),s,sep,f);
                        sharedVars = std::string(sharedVars).substr(std::string(sharedVars).find(", s")+1,std::string(sharedVars).length());
                        std::string astText= expr.get_ast().prettyprint(true);
                        //                std::cout<<"a: "<<astText<<std::endl;
                        //                cin.get();
                        int num = 0;
                        size_t forIndx=-1;
                        if(clauses.find("private")<0 || clauses.find("private")>clauses.length()) {
                            privateVars << "private(";
                            while(astText.find("for")>=0 && astText.find("for")<astText.length()){
                                astText = astText.substr(astText.find("for")+4,astText.length());
                                size_t spaces;
                                Source stringSpaces;
                                spaces = astText.substr(0,astText.find("(")).length();
                                for(int s=0;s<(int)spaces;s++){
                                    stringSpaces <<" ";
                                }
                                if(astText.substr(0,astText.find_first_of("(")).compare(std::string(stringSpaces))==0){
                                    astText = astText.substr(astText.find_first_of("(")+1,astText.length());
                                    
                                    std::string express;
                                    express = astText.substr(0,astText.find("="));
                                    // std::cout<<"0: "<<express<<std::endl;
                                    while(express.find(" ")==0) {
                                        express = express.substr(express.find(" ")+1,express.length());
                                        //  std::cout<<"1: "<<express<<std::endl;
                                    }
                                    while(express.find_last_of(" ")==express.length()-1){
                                        express = express.substr(0,express.find_last_of(" "));
                                        //  std::cout<<"2: "<<express<<std::endl;
                                    }
                                    
                                    if(express.find_last_of(" ")>0 && express.find_last_of(" ")<express.length()) {
                                        express= express.substr(express.find_last_of(" ")+1,express.length());
                                        //   std::cout<<"3: "<<express<<std::endl;
                                    }
                                    
                                    if(num==0)
                                        privateVars << express;
                                    else
                                        privateVars <<", "<<express;
                                    num++;
                                }
                            }
                            
                            
                            
                            privateVars<<")";
                        }
                        //                std::cout<<"Shared: "<<std::string(sharedVars)<<endl;
                        Source newSource;
                        if(fixedSinside.empty() && checkSinside.empty()) {
                            newSource<<"#pragma omp parallel "<<clauses<<sharedVars<<privateVars<<fixedS<<checkS<<"\n"<<statement.prettyprint()<<"\n";
                        }
                        if(!fixedSinside.empty() && checkSinside.empty()) {
                            newSource<<"#pragma omp parallel "<<clauses<<sharedVars<<privateVars<<fixedSinside<<"\n"<<statement.prettyprint()<<"\n";
                        }
                        if(fixedSinside.empty() && !checkSinside.empty()) {
                            newSource<<"#pragma omp parallel "<<clauses<<sharedVars<<privateVars<<checkSinside<<"\n"<<statement.prettyprint()<<"\n";
                        }

                        AST_t newAst = newSource.parse_statement(construct.get_ast(), construct.get_enclosing_function().get_scope_link());
                        expr.get_ast().replace(newAst);

                    }
                }
                int n =0;
                for(ObjectList<PragmaCustomConstruct>::iterator itC = constructList.begin(); itC!=constructList.end();itC++,n++) {    
                    pragma_postorder(constructList[n]);
                }

                AST_t translation_unit = _dto["translation_unit"]; 

            } else {
                construct.get_ast().replace(construct.get_statement().get_ast());               
                TraverseASTFunctor4LocateOMP expr_traverse(construct.get_scope_link());
                ObjectList<AST_t> expr_list = construct.get_ast().depth_subtrees(expr_traverse);
                int l=0;
                ObjectList<PragmaCustomConstruct> constructList;

                for (int l=0; l<expr_list.size();l++) {
                    
                    Expression expr(expr_list[l], construct.get_scope_link());
                    PragmaCustomConstruct test(expr.get_ast(),expr.get_scope_link());

                    if(test.is_construct()){
                        Statement statement = test.get_statement();
                        //                cout<<"Statement: "<<statement.prettyprint()<<endl;
                        clauses =  test.get_pragma_line().prettyprint();
                        //                cout<<"Clauses: "<<clauses<<endl;
                        //                cin.get();
                        
                        string checkSinside,fixedSinside;
                        int inside = 0;
                        if(clauses.find("check")>=0 && clauses.find("check")<clauses.length()) {
                            clauses  = clauses.substr(0,clauses.find("check")-1);
                            inside =1;
                        }
                        if(clauses.find("fixed")>=0 && clauses.find("fixed")<clauses.length()) {
                            fixedSinside= clauses.substr(clauses.find("fixed"), clauses.find_last_of(")"));
                            clauses  = clauses.substr(0,clauses.find("fixed")-1);
                            inside=1;
                        }
                        if(inside) {
                            constructList.push_back(test);
                        }
                        int outline_line = get_real_line(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(), construct.get_ast(),1,0);
                        TL::HLT::Outline outlineAux(statement.get_scope_link(), statement,outline_line);
                        Source sharedVars,privateVars, s,sep,f;
                        s<<"shared(";
                        sep <<", ";
                        f <<") ";
                        sharedVars = outlineAux.get_parameter_io(statement.get_scope(),s,sep,f);
                        sharedVars = std::string(sharedVars).substr(std::string(sharedVars).find(", s")+1,std::string(sharedVars).length());
                        std::string astText= expr.get_ast().prettyprint(true);
                        //                std::cout<<"a: "<<astText<<std::endl;
                        //                cin.get();
                        int num = 0;
                        size_t forIndx=-1;
                        if(clauses.find("private")<0 || clauses.find("private")>clauses.length()) {
                            privateVars << "private(";
                            while(astText.find("for")>=0 && astText.find("for")<astText.length()){
                                forIndx = astText.find("for");
                                //std::cout<<"aC: "<<astText<<std::endl;
                                //std::cout <<astText.substr(astText.find_first_of(" for"),astText.find_first_of(" for")+4)<<std::endl;
                                astText = astText.substr(astText.find("for")+4,astText.length());
                                size_t spaces;
                                Source stringSpaces;
                                spaces = astText.substr(0,astText.find("(")).length();
                                for(int s=0;s<(int)spaces;s++){
                                    stringSpaces <<" ";
                                }
                                if(astText.substr(0,astText.find_first_of("(")).compare(std::string(stringSpaces))==0){
                                    astText = astText.substr(astText.find_first_of("(")+1,astText.length());
                                    
                                    std::string express;
                                    express = astText.substr(0,astText.find("="));
                                    // std::cout<<"0: "<<express<<std::endl;
                                    while(express.find(" ")==0) {
                                        express = express.substr(express.find(" ")+1,express.length());
                                        //  std::cout<<"1: "<<express<<std::endl;
                                    }
                                    while(express.find_last_of(" ")==express.length()-1){
                                        express = express.substr(0,express.find_last_of(" "));
                                        //  std::cout<<"2: "<<express<<std::endl;
                                    }
                                    
                                    if(express.find_last_of(" ")>0 && express.find_last_of(" ")<express.length()) {
                                        express= express.substr(express.find_last_of(" ")+1,express.length());
                                        //   std::cout<<"3: "<<express<<std::endl;
                                    }
                                    
                                    if(num==0)
                                        privateVars << express;
                                    else
                                        privateVars <<", "<<express;
                                    num++;
                                }
                            }
                            privateVars<<")";
                        }
                        Source newSource;
                        if(fixedSinside.empty() && checkSinside.empty()) {
                            newSource<<"#pragma omp parallel "<<clauses<<sharedVars<<privateVars<<"\n"<<statement.prettyprint()<<"\n";
                        }
                        if(!fixedSinside.empty() && checkSinside.empty()) {
                            newSource<<"#pragma omp parallel "<<clauses<<sharedVars<<privateVars<<fixedSinside<<"\n"<<statement.prettyprint()<<"\n";
                        }
                        if(fixedSinside.empty() && !checkSinside.empty()) {
                            newSource<<"#pragma omp parallel "<<clauses<<sharedVars<<privateVars<<checkSinside<<"\n"<<statement.prettyprint()<<"\n";
                        }
                        AST_t newAst = newSource.parse_statement(construct.get_ast(), construct.get_enclosing_function().get_scope_link());
                        expr.get_ast().replace(newAst);
                    }
                    
                }
                int n =0;
                //            std::cout<<"num constructs: "<<constructList.size()<<endl;
                for(int a =0; a<constructList.size();++a) {    
                    pragma_postorder(constructList[a]);
                }

                AST_t translation_unit = _dto["translation_unit"];  
            }
        }
    }
    
    
    
    
    
}
Source TransPhase::findPrincipalIterator(AST_t varUse, string name) {
    regex_t expEqual; //Our compiled expression
    stringstream equal;
    string sizeS = "1";
    equal << "\\("<<name<<"\\s*"<<"\\["<<"\\s*"<<"[a-z]*"<<"\\s*"<<"\\]"<<"\\)";
    
    //cout <<varUse.prettyprint() <<endl;
    if (regcomp(&expEqual, equal.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    size_t     nmatch = 2;
    regmatch_t matchesEqual[2]; //A list of the matches in the string (a list of 1)
    
    if (regexec(&expEqual, varUse.prettyprint().c_str(), nmatch, matchesEqual, 0) == 0){
        sizeS = varUse.prettyprint().substr(matchesEqual[0].rm_so + name.length()+1, varUse.prettyprint().length());
        sizeS = sizeS.substr(0, sizeS.find_first_of("]"));
    }
    Source iteratorS;
    iteratorS << sizeS;
    return iteratorS;
}
int TransPhase::get_size_of_array(string name, string declaration) {
    regex_t expEqual; //Our compiled expression
    stringstream equal;
    string sizeS = "1";
    equal << "\\("<<name<<"\\s*"<<"\\["<<"\\s*"<<"[0-9]*"<<"\\s*"<<"\\]"<<"\\)";
    //cout <<declaration <<endl;
    if (regcomp(&expEqual, equal.str().c_str(), 0) != 0) {
        exit(EXIT_FAILURE);
    }
    size_t     nmatch = 2;
    regmatch_t matchesEqual[2]; //A list of the matches in the string (a list of 1)
    
    if (regexec(&expEqual, declaration.c_str(), nmatch, matchesEqual, 0) == 0){
        sizeS = declaration.substr(matchesEqual[0].rm_so + name.length()+1, declaration.length());
        sizeS = sizeS.substr(0, sizeS.find_first_of("]"));
    }
    return atoi((const char *)sizeS.c_str());
}
bool TransPhase::checkFor(PragmaCustomConstruct construct) {
    PragmaCustomClause for_clause = construct.get_clause("for");
    bool for_clau = false;
    if (for_clause.is_defined()) {
        for_clau = true;
    }
    return for_clau;
}
void TransPhase::finalize() {
    Source fin;
    fin << "MPI_Finalize();";
    AST_t finAST = fin.parse_statement(_translation_unit,_scope_link);
    for (int i=0; i < _lastAST.size(); ++i) {
        if(i+1<_lastAST.size()) {
            if(_lastFunctionNameList[i].compare(_lastFunctionNameList[i+1])!=0) {
                _lastAST[i].append(finAST);
            }
        } else {
            _lastAST[i].append(finAST);
        }
    } 
}

string TransPhase::cleanWhiteSpaces(string toClean) {
    while(std::string(toClean).find_first_of(" ")==0){                       
        toClean = std::string(toClean).substr(1,std::string(toClean).length());
    }
    while(std::string(toClean).find_first_of(" ")<std::string(toClean).length()){
        toClean = std::string(toClean).substr(0,std::string(toClean).length()-1);
    }
    return toClean;
}


//*********************

AST_t TransPhase::fill_smart_use_table(AST_t asT, ScopeLink scopeL, Scope sC, int outline_num_line, ObjectList<Symbol> prmters , int hmppOrig, int offset, AST_t prevAST){
    int l=0;
    int line=0;
    //std::cout<<"Working Line: "<<outline_num_line<<endl;
    
    int k=0;
    int f=0;
    int maxLine=offset;
    std::istringstream allAST(asT.prettyprint(false));
    std::string lineActAst;    
    Source workingSource,lastSource;
    int q =0;
    AST_t actAst, workingAst,lastAst;
    while (std::getline(allAST, lineActAst)) {
        maxLine++;
        if(q!=0)
            workingSource << lineActAst <<"\n";
        lastSource << lineActAst <<"\n";
        q++;
    }
    int inside =0;
    if(hmppOrig!=2 && hmppOrig!=3) {       
        actAst =asT;
        workingAst=workingSource.parse_statement(sC,scopeL);
    } else {
        workingAst = asT;
        
        if(hmppOrig==3) {
            inside = 1;
        }
    }
    // std::cout<<"Working Ast: "<<workingAst.prettyprint()<<endl;
    std::string actWord;
    TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = workingAst.depth_subtrees(expr_traverse);
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        
        f=0; 
        Expression expr(expr_list[l], scopeL);
        
        std::string ppExpr = expr.prettyprint();
        std::cout<<"Working Expr: "<<ppExpr<<endl;
        lastAst = expr.get_ast();
        if(hmppOrig!=2 && hmppOrig!=3) {
            line = offset;
        } else if(hmppOrig!=3){
            actAst = expr_list[l];
            line = offset+l;
        } else {
            line = offset;
            hmppOrig=1;
            actAst = prevAST;              
        }
        
        //Check if is inside Bucle
        
        if(line!=outline_num_line) {
            if((expr.is_assignment() || expr.is_operation_assignment()) && f==0) {
                f=1; 
                if(hmppOrig == 2) 
                    _inside_loop=is_inside_bucle(expr_list[l],scopeL, line, 0);
                Expression firstOperand = expr.get_first_operand();
                
                Expression secondOperand = expr.get_second_operand();
                
                
                size_t EndPart1 = std::string(firstOperand.prettyprint()).find_first_of("[");
                if(EndPart1>0 && EndPart1<std::string(firstOperand.prettyprint()).length()) {
                    Source cutParam;
                    cutParam << std::string(std::string(firstOperand.prettyprint()).substr(0, EndPart1));
                    while(std::string(cutParam).find_first_of(" ")==0)
                        std::string(cutParam) = std::string(cutParam).substr(1,std::string(cutParam).length());
                    while(std::string(cutParam).find_first_of(" ")<std::string(cutParam).length())
                        std::string(cutParam) = std::string(cutParam).substr(0,std::string(cutParam).length()-1);
                    //Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                    Symbol findedS = sC.get_symbol_from_name(std::string(cutParam));
                    if(!findedS.is_invalid()) {
                        actWord = findedS.get_name();
                        
                        //                    std::cout<<"(ass)Var use "<< findedS.get_name()<<" in "<<line<<endl;
                        if(line<outline_num_line) {
                            if(!hmppOrig || hmppOrig == 2) {
                                if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                    _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                                }
                            } else {
                                
                                if(inside) {
                                    if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                        _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                                    }
                                }
                            }
                        } else {
                            if(!hmppOrig || hmppOrig == 2) {
                                if(_smart_use_table[actWord].row_first_write_cpu.row > line || _smart_use_table[actWord].row_first_write_cpu.row == 0) {
                                    _smart_use_table[actWord].row_first_write_cpu = fill_use(line,actAst);    
                                }
                            } 
                            
                        }
                    }
                    
                } 
                ObjectList<Source> operands;
                operands = splitMathExpression(sC, secondOperand.prettyprint());
                
                for (int e=0;e<operands.size();e++){
                    //                    std::cout<<std::string(operands[e])<<endl;
                    EndPart1 = std::string(operands[e]).find_first_of("[");
                    if(EndPart1>0 && EndPart1<std::string(operands[e]).length()) {
                        Source cutParam;
                        cutParam << std::string(std::string(operands[e]).substr(0, EndPart1));
                        //  std::cout<<"-"<<std::string(cutParam)<<"-"<<endl;
                        while(std::string(cutParam).find_first_of(" ")==0){                       
                            cutParam = std::string(cutParam).substr(1,std::string(cutParam).length());
                            //      std::cout<<"-"<<std::string(cutParam)<<"-"<<endl;
                        }
                        
                        while(std::string(cutParam).find_first_of(" ")<std::string(cutParam).length()){
                            cutParam = std::string(cutParam).substr(0,std::string(cutParam).length()-1);
                            //     std::cout<<"-"<<std::string(cutParam)<<"-"<<endl;
                        }
                        //Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                        Symbol findedS = sC.get_symbol_from_name(std::string(cutParam));
                        if(!findedS.is_invalid()) {
                            actWord = findedS.get_name();
                            if(line<outline_num_line) {
                                if(!hmppOrig || hmppOrig == 2) {
                                    if(_smart_use_table[actWord].row_last_read_cpu.row < line || _smart_use_table[actWord].row_last_read_cpu.row == 0) {
                                        _smart_use_table[actWord].row_last_read_cpu = fill_use(line,actAst);
                                    }
                                }  
                            } else {
                                if(!hmppOrig || hmppOrig == 2) {
                                    if(_smart_use_table[actWord].row_first_read_cpu.row > line || _smart_use_table[actWord].row_first_read_cpu.row == 0) {
                                        _smart_use_table[actWord].row_first_read_cpu = fill_use(line,actAst);
                                    }
                                } 
                                
                            }
                        }
                        
                    } 
                }
                //                cin.get();
                
            }
            
            PragmaCustomConstruct test(expr.get_ast(),expr.get_scope_link());
            if(test.is_construct() && f==0 && outline_num_line !=line){
                f=1;
                if(hmppOrig == 2) 
                    _inside_loop=is_inside_bucle(expr_list[l],scopeL, line, 0);
                
                
                
                std::istringstream actASTtext(test.prettyprint());
                std::string lineAct;    
                signed int maxLinePragma=line+offset;
                Source workingSource;
                int h=0;
                while (std::getline(actASTtext, lineAct)) {
                    if(h>0)
                        workingSource <<lineAct<<"\n";
                    maxLinePragma++;
                    h++;
                }
                //                std::cout<<line<<endl;
                TL::PragmaCustomClause shared_clause = test.get_clause("shared");
                TL::PragmaCustomClause private_clause = test.get_clause("private");
                TL::PragmaCustomClause red_clause = test.get_clause("reduction");
                TL::PragmaCustomClause check_clause = test.get_clause("check");
                TL::PragmaCustomClause fixed_clause = test.get_clause("fixed");
                int hmpp=0;
                if(shared_clause.is_defined()) {
                    ObjectList<Expression> shared_arguments = shared_clause.get_expression_list();
                    for (ObjectList<Expression>::iterator it = shared_arguments.begin(); it != shared_arguments.end(); it++) {
                        Expression argument(*it);
                        actWord = argument.prettyprint();
                        //                        cout << "//  S: " << argument.prettyprint() << endl;
                        if(!hmpp && hmppOrig!=1) {
                            if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                            }
                            if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                                
                            }
                            
                        } else {
                            if(inside) {
                                if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                    _smart_use_table[actWord].row_first_write_cpu = fill_use(maxLinePragma,actAst);
                                }
                            }
                            
                            
                        }
                    }
                }
                if(private_clause.is_defined()) {
                    ObjectList<Expression> private_arguments = private_clause.get_expression_list();
                    for (ObjectList<Expression>::iterator it = private_arguments.begin(); it != private_arguments.end(); it++) {
                        Expression argument(*it);
                        actWord = argument.prettyprint();
                        //                        cout << "//  P: " << argument.prettyprint() << endl;
                        if(!hmpp && hmppOrig!=1) {
                            
                            if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                                
                            }
                            if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                            }
                            
                        } else {
                            if(inside) {
                                if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                    _smart_use_table[actWord].row_first_write_cpu = fill_use(maxLinePragma,actAst);
                                    
                                }
                            }
                            
                        }
                    }
                }
                if(red_clause.is_defined()) {
                    ObjectList<std::string> red_args = red_clause.get_arguments();
                    for (ObjectList<std::string>::iterator it = red_args.begin(); it != red_args.end(); it++) {
                        string argument(*it);
                        string actArgList;
                        while(argument.find(":")>=0 && argument.find(":")<argument.length()){
                            actArgList=argument.substr(argument.find_first_of(":")+1,argument.length());
                            argument = actArgList;
                            string actArg;
                            while(actArgList.find(",")>=0 && actArgList.find(",")<actArgList.length()) {
                                actArg=actArgList.substr(0,actArgList.find_first_of(","));
                                actArgList = actArgList.substr(actArgList.find_first_of(",")+1,actArgList.length());
                                while(actArg.find_first_of(" ")==0)
                                    actArg = actArg.substr(1,actArg.length());
                                while(actArg.find_first_of(" ")<actArg.length())
                                    actArg = actArg.substr(0,actArg.length()-1);
                                //                                cout << "//  R1:  " << actArg << endl;
                                actWord=actArg;
                                if(!hmpp && hmppOrig!=1) {
                                    if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                        _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                                        
                                    }
                                    if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                        _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                                    }
                                    
                                } else {
                                    if(inside) {
                                        if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                            _smart_use_table[actWord].row_first_write_cpu = fill_use(maxLinePragma,actAst);
                                        }
                                    }
                                    
                                }
                            }
                            actArg=actArgList;
                            while(actArg.find_first_of(" ")==0)
                                actArg = actArg.substr(1,actArg.length());
                            while(actArg.find_first_of(" ")<actArg.length())
                                actArg = actArg.substr(0,actArg.length()-1);
                            //                            cout << "//  R2:  " << actArg << endl;
                            actWord=actArg;
                            if(!hmpp && hmppOrig!=1) {
                                if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                    _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                                }
                                if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                    _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                                }
                                
                            } else {
                                if(inside) {
                                    if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                        _smart_use_table[actWord].row_first_write_cpu = fill_use(maxLinePragma,actAst);
                                    }
                                }
                                
                            }
                        }
                        
                    }
                }
                
                AST_t nouse =fill_smart_use_table(test.get_ast(), scopeL, sC, outline_num_line, prmters, hmpp, line, actAst);
            }
            
            
            stringstream equal;
            equal<<"[^<>][=][^=]";
            regex_t expEqual; //Our compiled expression
            int rev = regcomp(&expEqual, equal.str().c_str(), REG_EXTENDED);
            if (rev != 0) {
                printf("regcomp failed with %d\n", rev);
            }
            regmatch_t matchesEqual[1]; //A list of the matches in the string (a list of 1)
            
            if (f==0 && regexec(&expEqual, ppExpr.c_str(), 1, matchesEqual, 0) == 0){
                if(hmppOrig == 2)  
                    _inside_loop=is_inside_bucle(expr_list[l],scopeL, line, 0);
                f=1;
                if(prmters.size()>0){
                    k=0;
                    vector<string> sub_strings;
                    for (ObjectList<Symbol>::iterator it = prmters.begin();it != prmters.end(); it++,k++) {
                        if(prmters[k].get_type().is_array() || (prmters[k].get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && prmters[k].get_point_of_declaration().prettyprint(true).find_first_of("[")<prmters[k].get_point_of_declaration().prettyprint(true).length())) {
                            stringstream pattern, pattern2;
                            pattern<<"[^a-zA-Z0-9]"<<prmters[k].get_name()<<"[ \r\t\n\f]*[\r\t\n\f]*[\[]+";
                            pattern2<<prmters[k].get_name()<<"\\s*\\[[\\d+]*[a-z]*\\]";
                            //                            std::cout<<"P: "<<pattern.str()<<endl;
                            int rv;
                            regex_t exp, exp2; //Our compiled expression
                            
                            rv = regcomp(&exp, pattern.str().c_str(), REG_EXTENDED);
                            if (rv != 0) {
                                printf("regcomp failed with %d\n", rv);
                            }
                            rv = regcomp(&exp2, pattern2.str().c_str(), REG_EXTENDED);
                            if (rv != 0) {
                                printf("regcomp failed with %d\n", rv);
                            }
                            regmatch_t matches[1]; //A list of the matches in the string (a list of 1)
                            if(regexec(&exp, ppExpr.c_str(), 1, matches, 0) == 0 || regexec(&exp2, ppExpr.c_str(), 1, matches, 0) == 0) {
                                std::string actWord = prmters[k].get_name();
                                
                                if(ppExpr.find(prmters[k].get_name())<ppExpr.find("=")) {
                                    
                                    if(line<outline_num_line) {
                                        if(!hmppOrig || hmppOrig==2){
                                            if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                                _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst); 
                                            }
                                        } else {
                                            
                                            if(inside) {
                                                if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                                    _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst); 
                                                }
                                            }
                                        }
                                    } else {
                                        if(!hmppOrig || hmppOrig==2){
                                            if(_smart_use_table[actWord].row_first_write_cpu.row > line || _smart_use_table[actWord].row_first_write_cpu.row == 0) {
                                                _smart_use_table[actWord].row_first_write_cpu = fill_use(line,actAst);
                                            }
                                        } 
                                    }
                                } else {
                                    //                                    std::cout<<"(read)"<<prmters[k].get_name()<<endl;
                                    if(line<outline_num_line) {
                                        if(!hmppOrig || hmppOrig==2){
                                            if(_smart_use_table[actWord].row_last_read_cpu.row < line || _smart_use_table[actWord].row_last_read_cpu.row == 0) {
                                                _smart_use_table[actWord].row_last_read_cpu = fill_use(line,actAst);
                                            }
                                        } else {
                                            if(inside) {
                                                if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                                    _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                                                }
                                            }
                                        }
                                    } else {
                                        if(!hmppOrig || hmppOrig==2){
                                            if(_smart_use_table[actWord].row_first_read_cpu.row > line || _smart_use_table[actWord].row_first_read_cpu.row == 0) {
                                                _smart_use_table[actWord].row_first_read_cpu = fill_use(line,actAst);
                                                
                                            }
                                        } 
                                    }
                                }
                                
                            }
                            
                        }
                        
                    }
                } 
                
            }
            if(inside){
                hmppOrig=3;
            }
            
        }
    }
    
    for (Mymap::iterator itSm = _smart_use_table.begin(); 
            itSm != _smart_use_table.end(); ++itSm) {
        if(itSm->second.row_first_read_cpu.row==0) {
            itSm->second.row_first_read_cpu.ast=asT; 
            itSm->second.row_first_read_cpu.inside_loop=0; 
            itSm->second.row_first_read_cpu.for_num=-1; 
            itSm->second.row_first_read_cpu.for_ast = NULL;
        }
        if(itSm->second.row_first_write_cpu.row==0) {
            itSm->second.row_first_write_cpu.ast=asT; 
            itSm->second.row_first_write_cpu.inside_loop=0; 
            itSm->second.row_first_write_cpu.for_num=-1; 
            itSm->second.row_first_write_cpu.for_ast = NULL;
        }
    }
    return lastAst;
}

ObjectList<Source> TransPhase::splitMathExpression(Scope sC,std::string secondO)
{
    //    std::cout<<"Second Operator: "<<secondO<<endl;
    ObjectList<Source> operators;
    int numElem=0;
    Source empty;
    string math[4] = {"+","*","/","-"};
    operators.clear();
    operators.push_back(empty);
    for (int i=0;i<secondO.length();++i){
        std::string actChar,nextChar;
        actChar = (secondO[i]);
        int l = i+1;
        while(l < secondO.length()-1){
            if(secondO[l] != 32) {
                nextChar = secondO[l];
                l=secondO.length();
            } else {
                l++;
            }
        }
        int find=0;
        if(!(std::string(actChar).compare(")")==0 || std::string(actChar).compare(" ")==0  || std::string(actChar).compare("(")==0)) {
            for(int x=0; x<4;++x){
                if(std::string(actChar).compare(math[x])==0) {
                    find=1; 
                }
            }
            if(!find){
                Source actElem;
                actElem = operators[numElem];
                actElem<<actChar;
                operators.pop_back();
                operators.push_back(actElem);
                
                Symbol findedS = sC.get_symbol_from_name(std::string(operators[numElem]));
                
                if(!findedS.is_invalid()) {
                    if(findedS.is_function()) {
                        if(nextChar.compare("(")==0) {
                            //                                std::cout<<std::string(operators[numElem])<<" discarted is function!!"<<endl;
                            operators[numElem]=empty;
                        }
                    }
                }
                
            }else if(std::string(operators[numElem]).compare(std::string(empty))!=0){
                operators.push_back(empty);
                numElem++;           
                operators[numElem]=empty;
                
            }
        } else if(std::string(actChar).compare(")")==0 && std::string(operators[numElem]).compare(std::string(empty))!=0){
            operators.push_back(empty);
            numElem++;           
            operators[numElem]=empty;
        }
        
    }
    if(std::string(operators[0]).compare("")==0) {
        operators.clear();
    }
    return operators;
}

TransPhase::use TransPhase::fill_use(int line, AST_t actAst){
    use actUse;
    actUse.row=line;
    actUse.ast=actAst;
    actUse.inside_loop = _inside_loop;
    actUse.for_num = _for_num;
    actUse.for_ast = _for_ast;
    actUse.for_internal_ast_last = _for_internal_ast_last;
    return actUse;
    
}

int TransPhase::is_inside_bucle(AST_t ast2check, ScopeLink scopeL, int exprLine, int searching_construct) {
    
    TraverseASTFunctor4LocateFor expr_traverseFor(scopeL);
    ObjectList<AST_t> expr_listFor = _file_tree.depth_subtrees(expr_traverseFor);
    _for_min_line =-1;
    int lF=0;
    int num_for=-1;
    for (ObjectList<AST_t>::iterator it = expr_listFor.begin();it != expr_listFor.end(); it++, lF++) {
        
        Expression exprI(ast2check, scopeL);
        
        if(expr_listFor[lF].is_valid()) {
            Expression exprF(expr_listFor[lF], scopeL);
            
            FunctionDefinition fdF(exprF.get_enclosing_function());
            FunctionDefinition fdI(exprI.get_enclosing_function());
            
            string nameF = fdF.get_function_name().get_symbol().get_name();
            string nameI = fdI.get_function_name().get_symbol().get_name();
            
            //cout <<"nF: -"<<nameF<<"- vs nI: -"<<nameI<<"-"<<endl;
            if (nameF.compare(nameI)==0){
                //cout<<"******************************\nFOR: "<<exprF.prettyprint()<<endl;
                AST_t loopAst;
                Statement s(expr_listFor[lF],scopeL);
                if(ForStatement::predicate(expr_listFor[lF])) {
                    ForStatement fS(s);
                    loopAst = fS.get_loop_body().get_ast();
                    
                }
                
                if(WhileStatement::predicate(expr_listFor[lF])) {
                    WhileStatement wS(expr_listFor[lF],scopeL);
                    loopAst = wS.get_body().get_ast();
                    
                }
                if(DoWhileStatement::predicate(expr_listFor[lF])) {
                    DoWhileStatement dWS(expr_listFor[lF],scopeL);
                    loopAst = dWS.get_body().get_ast();
                }
                if(loopAst.prettyprint().compare("")!=0 && _for_min_line==-1){
                    
                    _for_min_line = get_real_line(loopAst, scopeL, exprI.get_ast(), 0, searching_construct);
                    //cout<<"LS: "<<_for_min_line<<"***********************"<<endl;
                    if(_for_min_line>=0) {
                        _for_internal_ast_last = get_last_ast(loopAst, scopeL);
                        _for_internal_ast_first = get_first_ast(loopAst, scopeL);
                        loopAst = loopAst.get_enclosing_function_definition_declaration();
                        _for_min_line = get_real_line(loopAst, scopeL, exprI.get_ast(), 0, searching_construct);
                        if(searching_construct) {
                            _for_min_line-=_notOutlined;
                            _for_min_line-=_pragma_lines;
                        }
                        num_for= expr_listFor[lF].get_line();
                        _for_ast = expr_listFor[lF];
                    }
                }
            }
        }
        
        
    }
    if(_for_min_line==exprLine){
        _for_num = num_for;
        return 1;
    }else{
        _for_num = -1;
        return 0;
    }
}

int TransPhase::get_real_line(AST_t asT, ScopeLink scopeL, AST_t actLineAST, int update, int searching_construct) {
    std::string actLine;
    actLine= actLineAST.prettyprint();
    
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = asT.depth_subtrees(expr_traverse);
    int line=-1;
    int l=0; 
    if(update) {
        _pragma_lines=0;
        p_l_s.clear();
    }
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        Expression expr(expr_list[l], scopeL);
        std::string ppExpr;
        ppExpr=expr.prettyprint();
        if(update) {
            if(ppExpr.find("#pragma hmpp ")>=0 && ppExpr.find("#pragma hmpp ")<ppExpr.length()){
                if(ppExpr.find(" group")>0 && ppExpr.find(" group")<ppExpr.length()){
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                if(ppExpr.find(" mapbyname,")>0 && ppExpr.find(" mapbyname,")<ppExpr.length()){
                    //                        cout<<ppExpr<<endl;
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                if(ppExpr.find(" advancedload,")>0 && ppExpr.find(" advancedload,")<ppExpr.length()){
                    
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                if(ppExpr.find(" delegatedstore,")>0 && ppExpr.find(" delegatedstore,")<ppExpr.length()){
                    //                        cout<<ppExpr<<endl;
                    _pragma_lines++; 
                    p_l_s.push_back(ppExpr);
                }
                
                if(ppExpr.find(" synchronize")>0 && ppExpr.find(" synchronize")<ppExpr.length()){
                    //                        cout<<ppExpr<<endl;
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                
                if(ppExpr.find(" release")>0 && ppExpr.find(" release")<ppExpr.length()){
                    //                        cout<<ppExpr<<endl;
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
            }
        }
        if(actLine.compare(ppExpr)==0) {
            line = l;
            if(actLineAST.get_line() == expr_list[l].get_line() || searching_construct || actLineAST.get_line()==1){
                it = expr_list.end();
                break;
            }
        }  
    }
    return line;
}

AST_t TransPhase::get_last_ast(AST_t ast, ScopeLink scopeL){
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    return expr_list[expr_list.size()-1];
}

AST_t TransPhase::get_first_ast(AST_t ast, ScopeLink scopeL){
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    return expr_list[0];
}
//*********************

EXPORT_PHASE(TransPhase);

