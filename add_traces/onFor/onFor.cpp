#include "onFor.hpp"
#include "FunctionDefinitionPred.hpp"
#include "FunctionCallsPred.hpp"
#include <stdlib.h>
#include "hlt/hlt-common.hpp"
#include "tl-omp.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include "regex.h"


#include <bits/basic_string.h>

using namespace TL;
using namespace TL::HLT;
using namespace std;



AddTracesOnForPhase::AddTracesOnForPhase() : PragmaCustomCompilerPhase("omp") {
    //    register_new_directive("pragma","acpa","1","0");
    //register_construct("acpa");
    _initialized =0;
    _groupInside = 0;
    

    register_construct("acpa");
    register_directive("var");
    register_directive("iter");
    //register_directive("iter");

    on_directive_post["acpa"].connect(functor(&AddTracesOnForPhase::pragma_postorder, *this));
    //on_directive_post["check"].connect(functor(&AddTracesOnForPhase::pragma_postorder, *this));
    
    
}

void AddTracesOnForPhase::run(DTO& dto) {
    _dto=dto;
    //vector<string> keys;
    //keys =dto.get_keys();
    
    //_translation_unit = dto["translation_unit"];
    _scope_link = dto["scope_link"];  
    PragmaCustomCompilerPhase::run(dto);  
}


void AddTracesOnForPhase::pragma_postorder(PragmaCustomConstruct construct) {
    PragmaCustomClause block_clause = construct.get_clause("block");
    _file_tree = construct.get_statement().get_ast().get_enclosing_global_tree();
    string pragmaInstruction = construct.get_pragma_line().prettyprint(false);
    FunctionDefinition function_def = construct.get_enclosing_function();
    Symbol function_sym = function_def.get_function_symbol();
    ScopeLink functionScopeLink = construct.get_enclosing_function().get_scope_link();
    Scope functionScope = function_def.get_function_body().get_scope();
    Scope globalScope = function_def.get_scope();
    cout<<"OMP("<<pragmaInstruction<<" in: "<<function_sym.get_name()<<") ->" <<construct.get_ast().get_line()<<endl;
    if (!block_clause.is_defined()) {
    
//    cin.get();
    int block_line = get_real_line(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(), construct.get_ast(),0,0,1);
    _construct_inside_bucle =  is_inside_bucle(construct.get_ast(),functionScopeLink,block_line,1);
  
    _construct_num_loop = _for_num;
    _construct_loop = _for_ast;
    Source commented_loop;
    
    cout<<"Analyzing vars Clause"<<endl;
    PragmaCustomClause var_clause = construct.get_clause("var");
    ObjectList<Expression> shared_arguments;
    if (var_clause.is_defined()) {
        commented_loop
                << "// Arguments found in shared clausule: \n";
        cout << "// Arguments found in shared clausule: " << endl;
        shared_arguments = var_clause.get_expression_list();
        for (ObjectList<Expression>::iterator it = shared_arguments.begin(); it != shared_arguments.end(); it++) {
            Expression argument(*it);
            commented_loop << "//  - " << argument.prettyprint() << "\n";
            cout << "//  - " << argument.prettyprint() << endl;
        }
    } else {
        cerr<<"Var clause needed on #pragma acpa"<<endl;
        exit(-1);
    }
    
    cout<<"Analyzing iter Clause"<<endl;
    PragmaCustomClause iter_clause = construct.get_clause("iter");
    ObjectList<Expression> iter_arguments;
    if (iter_clause.is_defined()) {
        commented_loop
                << "// Arguments found in iter clausule: \n";
        cout << "// Arguments found in iter clausule: " << endl;
        iter_arguments = iter_clause.get_expression_list();
        for (ObjectList<Expression>::iterator it = iter_arguments.begin(); it != iter_arguments.end(); it++) {
            Expression argument(*it);
            commented_loop << "//  - " << argument.prettyprint() << "\n";
            cout << "//  - " << argument.prettyprint() << endl;
        }
    } else {
        cerr<<"Iter clause needed on #pragma acpa"<<endl;
        exit(-1);
    }
    Source newdeclaration;
    int varsToInclude = shared_arguments.size();
    for(int y = 0; y<shared_arguments.size();++y) {
        for(int x = 0; x<_declaredVars.size();++x) {
            if(_declaredVars[x].compare(shared_arguments[y].prettyprint())==0) {
                varsToInclude--;
                break;
            }
        }
    }
   
    if(varsToInclude>0) {
//        newdeclaration << "mem_trace_enable(1);\n";
        for(int i = 0; i< shared_arguments.size();++i){
            string name = shared_arguments[i].prettyprint();
            int finded = 0;
            for(int x = 0; x<_declaredVars.size();++x) {
                if(_declaredVars[x].compare(name)==0)
                    finded = 1;
            }
            if(!finded) {
                Symbol findedS = functionScope.get_symbol_from_name(name);
                if(findedS.is_valid()) {
                    cout<< findedS.get_name()<<endl;
                    string declaration;
                    string sizeS, maxS;
                    string n2find = " "+name;
                    if(!findedS.is_valid()){
                        findedS = globalScope.get_symbol_from_name(name);
                        if(findedS.is_valid()){
                            
                            declaration = std::string(findedS.get_type().get_declaration(globalScope,name));
                            // cout<<"d1:"<<declaration<<endl;
                            declaration = declaration.substr(0, declaration.find(n2find));
                            //cout<<"d1:"<<declaration<<endl;
                        }
                    } else {
                        declaration = std::string(findedS.get_type().get_declaration(functionScope,name));
                        
                        //cout<<"d2:"<<declaration<<endl;
                        declaration = declaration.substr(0, declaration.find(n2find));
                        //cout<<"d2:"<<declaration<<endl;
                    }
                    ObjectList<string> sizeOfArray;
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
                            
                            while(declaratrionS.find_first_of("[")>=0 && declaratrionS.find_first_of("[")<declaratrionS.length()) {
                                std::string actIterator = declaratrionS.substr(declaratrionS.find_first_of("[")+1,declaratrionS.length());
                                actIterator = actIterator.substr(0,actIterator.find("]"));
                                std::cout<< name << "-> "<< actIterator <<" on  ("<<declaratrionS<<")"<<std::endl;
                                //                                    
                                
                                sizeOfArray.push_back(actIterator);
                                declaratrionS = declaratrionS.substr(declaratrionS.find("]")+1, declaratrionS.length());
                            }
                            
                            
                        }
                    }
                    //cout<< "FS1: -"<<declaration<<"-"<<endl;
                    declaration = cleanWhiteSpaces(declaration);
                    if(sizeOfArray.size()>0) {
                        newdeclaration << "mem_trace_def_array"<<sizeOfArray.size()<<"d(\""<<name<<"\"";
                        for(int s = 0; s<sizeOfArray.size();++s) {
                            newdeclaration << ", "<<sizeOfArray[s];
                        }
                        newdeclaration <<");\n";
                    }
                    newdeclaration<< "mem_trace_def_mem(\""<<name<<"\", &"<<name<<", sizeof("<<declaration<<"), sizeof("<<name<<"));\n";
                    
                    
                    _declaredVars.push_back(name);
                    
                }
            }
        }
//        newdeclaration << "mem_trace_enable(0);\n\n";
        
        
    }
     
//    cout<< construct.get_ast()<<endl;
//    cout<<construct.get_statement().get_ast().prettyprint()<<endl;
//    cin.get();
     construct.get_ast().replace(construct.get_statement().get_ast());
//    cout<< construct.get_ast()<<endl;
//    cout<<"HI"<<endl;
//    cin.get();
    //cout<<std::string(newdeclaration)<<endl;
    AST_t ast2append;
    if(!_initialized) {
        if(_groupInside) {
            ast2append = _groupAST;
        } else if(_construct_inside_bucle) {
            cout<<"Inside loop"<<endl;
            ast2append = _construct_loop;
            //        cout<<_construct_loop<<endl;
        } else {
            cout<<"Outside loop"<<endl;
            ast2append = construct.get_ast();

        }
        _initialized =1;
        _initializationAST = newdeclaration.parse_statement(functionScope,functionScopeLink);
        cout<<ast2append.prettyprint()<<endl;
         ast2append.prepend(_initializationAST);
    } else {
        ast2append = _initializationAST;
        ast2append.append(newdeclaration.parse_statement(functionScope,functionScopeLink));
    }
   
    
    completeLoopsInAST(construct.get_ast(), functionScopeLink);
    Source newASTSource;
    newASTSource = transformConstructAST(construct,functionScopeLink,functionScope, shared_arguments);
    construct.get_ast().replace(newASTSource.parse_statement(functionScope,functionScopeLink));
    
    for(int y=0;y<iter_arguments.size();++y) {
        string principalIt = iter_arguments[y].prettyprint();
        if(!putIteratedVarsOfInterest(principalIt, construct.get_ast(), functionScopeLink)) {
            Source newBodySource;
                newBodySource << "mem_trace_iter_start(\""<<principalIt<<"\", "<<principalIt<<");"
                        << construct.get_ast().prettyprint()
                        << "mem_trace_iter_end(\""<<principalIt<<"\", "<<principalIt<<");";
            construct.get_ast().replace(newBodySource.parse_statement(functionScope,functionScopeLink));
        }
    }
//    cout<<construct.get_ast()<<endl;
//    cin.get();
    } else {
         TraverseASTFunctor4LocateBucle expr_traverse(construct.get_scope_link());
         ObjectList<AST_t> expr_list = construct.get_statement().get_ast().depth_subtrees(expr_traverse);
         string newPragma = "#pragma omp " 
                 +construct.get_pragma_line().prettyprint().substr(0, construct.get_pragma_line().prettyprint().find("block")) 
                 + "\n";
         cout<<newPragma<<endl;
         cin.get();
         construct.get_ast().replace(construct.get_statement().get_ast());
         _groupInside = 1;
         _groupAST = construct.get_ast();
         ObjectList<PragmaCustomConstruct> constructList;
          for (int l=0; l<expr_list.size();l++) {   
            Expression expr(expr_list[l], construct.get_scope_link());
            PragmaCustomConstruct test(expr.get_ast(),expr.get_scope_link());


                Source newSource;
                newSource << newPragma << construct.prettyprint();
                expr.get_ast().replace(newSource.parse_statement(functionScope,functionScopeLink));
                constructList.push_back(test);
                        
            
            int n =0;
              
          }
           //            std::cout<<"num constructs: "<<constructList.size()<<endl;
                for(int a =0; a<constructList.size();++a) {    
                    pragma_postorder(constructList[a]);
                }
                
                AST_t translation_unit = _dto["translation_unit"];  
//                cout<<translation_unit.prettyprint()<<endl;
                _groupInside = 0;
    }
}

int AddTracesOnForPhase::putIteratedVarsOfInterest(string principalIt,  AST_t astWhereSearch, ScopeLink scopeL) {
    
    TraverseASTFunctor4LocateBucle expr_traverseBucle(scopeL);
    ObjectList<AST_t> expr_listBucle = astWhereSearch.depth_subtrees(expr_traverseBucle);
    int lF = 0;
    int finded = 0;
    for (ObjectList<AST_t>::iterator it = expr_listBucle.begin();it != expr_listBucle.end(); it++, lF++) { 
        string inductionVar;
        if(ForStatement::predicate(expr_listBucle[lF])) {
            ForStatement fS(expr_listBucle[lF],scopeL);
            inductionVar = fS.get_induction_variable().prettyprint();
            if(inductionVar.compare(principalIt) == 0) {
                Source newBodySource;
                newBodySource << "{mem_trace_iter_start(\""<<principalIt<<"\", "<<principalIt<<");"
                        << fS.get_loop_body().get_ast().prettyprint()
                        << "mem_trace_iter_end(\""<<principalIt<<"\", "<<principalIt<<");}";
                fS.get_loop_body().get_ast().replace(newBodySource.parse_statement(astWhereSearch,scopeL));
                finded = 1;
            } else if(putIteratedVarsOfInterest(principalIt, fS.get_loop_body().get_ast(), scopeL)) {
                        return 1;
            }
        } 
        
        
    }
    
    return finded;
}
string AddTracesOnForPhase::cleanWhiteSpaces(string toClean) {
    if(!toClean.empty()) {
        while(std::string(toClean).find_first_of(" ")==0){                       
            toClean = std::string(toClean).substr(1,std::string(toClean).length());
        }
        while(std::string(toClean).find_last_of(" ")==std::string(toClean).length()-1){
            toClean = std::string(toClean).substr(0,std::string(toClean).length()-1);
        }
    }
    return toClean;
}

int AddTracesOnForPhase::is_inside_bucle(AST_t ast2check, ScopeLink scopeL, int exprLine, int searching_construct) {
    
    TraverseASTFunctor4LocateBucle expr_traverseFor(scopeL);
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
            
//            cout <<"nF: -"<<nameF<<"- vs nI: -"<<nameI<<"-"<<endl;
            if (nameF.compare(nameI)==0){
//                cout<<"******************************\nFOR: "<<exprF.prettyprint()<<endl;
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
                    
                    _for_min_line = get_real_line(loopAst, scopeL, exprI.get_ast(), 0, searching_construct,searching_construct);
                    //cout<<"LS: "<<_for_min_line<<"***********************"<<endl;
                    if(_for_min_line>=0) {
                        _for_internal_ast_last = get_last_ast(loopAst, scopeL);
                        _for_internal_ast_first = get_first_ast(loopAst, scopeL);
                        loopAst = loopAst.get_enclosing_function_definition_declaration();
                        _for_min_line = get_real_line(loopAst, scopeL, exprI.get_ast(), 0, searching_construct,searching_construct);
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
    //    cout<<exprLine<<" vs. "<<_for_min_line<<endl;
    //    cin.get();
    if(_for_min_line==exprLine){
        _for_num = num_for;
        return 1;
    }else{
        _for_num = -1;
        return 0;
    }
}

int AddTracesOnForPhase::get_real_line(AST_t asT, ScopeLink scopeL, AST_t actLineAST, int update, int searching_construct, int initialConstruct) {
    std::string actLine;
    actLine= actLineAST.prettyprint();
    
    TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = asT.depth_subtrees(expr_traverse);
    int line=-1;
    int l=0; 
    if(update) {
        _pragma_lines=0;
        
    }
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        Expression expr(expr_list[l], scopeL);
        std::string ppExpr;
        ppExpr=expr.prettyprint();
        if(actLine.compare(ppExpr)==0) {
            
            
            line = l;
            
            if(actLineAST.get_line() == expr_list[l].get_line() || searching_construct || actLineAST.get_line()==1){
                
                if(initialConstruct){
                    PragmaCustomConstruct test(actLineAST,scopeL);
                    if(test.is_construct()){
                        
                        TraverseASTFunctor4LocateUse expr_traverse2(scopeL);
                        
                        ObjectList<AST_t> expr_list2 = test.get_statement().get_ast().depth_subtrees(expr_traverse2);
                        //            if(searching_construct) {
                        //                            cout<<actLineAST.prettyprint()<<endl;
                        //                            if(expr_list2.size()>1) {
                        //                                line+=expr_list2.size();
                        cout<<line<<endl;
                        
                        //                        cout<<line<<endl;
                        //                        line+=(_num_transformed_blocks);
                        //                        cout<<line<<endl;
                        //                        line-=(_num_non_trasformed_blocks);
                        //                        cout<<line<<endl;
                        //                        cin.get();
                        //                                cout<<"Incrementing line in: "<<expr_list2.size()<<endl;
                        
                        //            }
                        //                            }
                        
                    }
                }
                //                cout<<line<<endl;
                //                cin.get();
                it = expr_list.end();
                break;
            }
        }  
    }
    return line;
    //return line+_num_transformed_blocks;
}

AST_t AddTracesOnForPhase::get_last_ast(AST_t ast, ScopeLink scopeL){
    TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    return expr_list[expr_list.size()-1];
}

AST_t AddTracesOnForPhase::get_first_ast(AST_t ast, ScopeLink scopeL){
    TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    return expr_list[0];
}

void AddTracesOnForPhase::completeLoopsInAST(AST_t ast, ScopeLink scopeL){
    TraverseASTFunctor4LocateBucle expr_traverseFor(scopeL);
    ObjectList<AST_t> expr_listFor = ast.depth_subtrees(expr_traverseFor);
    int lF=0;
    AST_t loopAst;
    AST_t fullLoopAst;
    for (ObjectList<AST_t>::iterator it = expr_listFor.begin();it != expr_listFor.end(); it++, lF++) {
        //completeLoopsInAST(loopAst,scopeL);
        if(ForStatement::predicate(expr_listFor[lF])) {
            ForStatement fS(expr_listFor[lF], scopeL);
            loopAst = fS.get_loop_body().get_ast();
            fullLoopAst = fS.get_enclosing_statement().get_ast();
            
        }
        
        if(WhileStatement::predicate(expr_listFor[lF])) {
            WhileStatement wS(expr_listFor[lF],scopeL);
            loopAst = wS.get_body().get_ast();
            fullLoopAst = wS.get_enclosing_statement().get_ast();
            
        }
        if(DoWhileStatement::predicate(expr_listFor[lF])) {
            DoWhileStatement dWS(expr_listFor[lF],scopeL);
            loopAst = dWS.get_body().get_ast();
            fullLoopAst = dWS.get_enclosing_statement().get_ast();
        }
        
        if(loopAst.prettyprint().find("{")!=0){
            Source loopAstWithKeys;
            loopAstWithKeys << "{"<<loopAst.prettyprint()<<"}";
            //            cout<<"1: "<<loopAst.prettyprint()<<endl;
            loopAst.replace_with(loopAstWithKeys.parse_statement(ast,scopeL));
            //            cout<<"2: "<<loopAst.prettyprint()<<endl;
            //
        }
        if(!loopAst.prettyprint().empty()) {
            //            cout<<"Continue with: "<<loopAst.prettyprint()<<endl;
            //            cout<<"Or Continue with: "<<fullLoopAst.prettyprint()<<endl;
            completeLoopsInAST(loopAst,scopeL);
        }
    }
    //    cout<<"C:" <<ast.prettyprint()<<endl;
    //
    
    
}

string AddTracesOnForPhase::transformConstructAST(PragmaCustomConstruct construct, ScopeLink scopeL, Scope sC, ObjectList<Expression> sh){
    Source astPrettyprint;
//    astPrettyprint<< "mem_trace_enable(1);\n";
    AST_t construct_ast = construct.get_ast();
    
    TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = construct_ast.depth_subtrees(expr_traverse);
    int l = 0;
    vector<string> newVariables;
    vector<Source> copyVariables;
    int hasArraysWriteOrRead = 0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        int hasChanges = 0;
        string line;
        line =  expr_list[l].prettyprint();
//        cout<<line<<endl;
//        cin.get();
        Source newLineSource;
        if(expr_list[l].prettyprint().find_first_of("=")>= 0 && expr_list[l].prettyprint().find_first_of("=")<expr_list[l].prettyprint().length()) {
            
            ObjectList<Source> operands, operators;
            string firstO, secondO;
            
            firstO = expr_list[l].prettyprint().substr(0,expr_list[l].prettyprint().find_first_of("="));
            secondO = expr_list[l].prettyprint().substr(expr_list[l].prettyprint().find_first_of("=")+1, expr_list[l].prettyprint().length());
            
            //            cout<<"---------------------------"<<endl;
            //            cout<<expr_list[l].prettyprint()<<endl;
            //            cout<<"1srt: "<<firstO<<endl;
            //            cout<<"2nd: "<<secondO<<endl;   
            line = replaceAll(line, " ", "");
            string op = expr_list[l].prettyprint().substr(expr_list[l].prettyprint().find_first_of("="), expr_list[l].prettyprint().length());
            //            cout<<"1: "<<firstO<< endl;
            //            cout<<"2: "<<secondO<<endl;
            //            cout<<"o: "<<op<<endl;
            
            
            
            operands = splitMathExpression(sC, secondO, 1);
            switch(expr_list[l].prettyprint()[expr_list[l].prettyprint().find_first_of("=")-1]) {
                case '+':
                case '-':
                case '/':
                case '*':
                    string newOP = firstO;
                    if(newOP.find_last_of("]")>=0 && newOP.find_last_of("]")<firstO.length()) {
                        newOP = newOP.substr(0, newOP.find_last_of("]")+1);
                    }
                    firstO = newOP;
                    operands.push_back(newOP);
                    break;
            }
            int hasC = 0;
            if(firstO.find_first_of("[")>= 0 && firstO.find_first_of("[")<firstO.length()) {
                hasArraysWriteOrRead=1;
                Source dimensions;
                string actArg = firstO.substr(0,firstO.find_first_of("["));
                //                                    cout<<actArg<<endl;
                //                                    cin.get();
                string iterators = firstO.substr(firstO.find_first_of("[")+1, firstO.length());
                actArg = cleanWhiteSpaces(actArg);
                if(is_studied_var(actArg,sh)) {
                    newLineSource<< "mem_trace_write(\"";
                    newLineSource<<actArg<<"\"";
                    hasC = 1;
                }
            } else {
                if(is_studied_var(firstO,sh)) {
                    newLineSource<< "mem_trace_write(\"";
                    newLineSource<<firstO<<"\"";
                    hasC = 1;
                }
                
            }
            if(hasC) {
                newLineSource <<", &"<<firstO<<");\n";
                hasChanges = 1;
            }
            
            for (int e=0;e<operands.size();e++){ //second Operand
                int hasC = 0;
                if(std::string(operands[e]).find_first_of(";")> 0 && std::string(operands[e]).find_first_of(";")<std::string(operands[e]).length()) {
                 operands[e] = std::string(operands[e]).substr(0,std::string(operands[e]).find_first_of(";"));
                }
                if(std::string(operands[e]).find_first_of("[")>= 0 && std::string(operands[e]).find_first_of("[")<std::string(operands[e]).length()) {
                    hasArraysWriteOrRead=1;
                    string firstIterator; 
                    
                    string actArg = std::string(operands[e]).substr(0,std::string(operands[e]).find_first_of("["));
                    string iterators = std::string(operands[e]).substr(std::string(operands[e]).find_first_of("[")+1, std::string(operands[e]).length());
                    actArg = cleanWhiteSpaces(actArg);
                    if(is_studied_var(actArg,sh)) {
                        newLineSource<< "mem_trace_read(\"";
                        newLineSource<<actArg<<"\"";
                        hasC = 1;
                    }
                } else {
                    if(is_studied_var(operands[e],sh)) {
                         newLineSource<< "mem_trace_read(\"";
                         newLineSource<<operands[e]<<"\"";
                         hasC = 1;
                    }
                }
                if(hasC) {
                    newLineSource<< ", &"<<operands[e]<<");\n";
                    hasChanges = 1;
                }    
            }
        } else if((expr_list[l].prettyprint().find_first_of("++")>= 0 && expr_list[l].prettyprint().find_first_of("++")<expr_list[l].prettyprint().length()) 
                || (expr_list[l].prettyprint().find_first_of("--")>= 0 && expr_list[l].prettyprint().find_first_of("--")<expr_list[l].prettyprint().length())){
            string exprString =  expr_list[l].prettyprint();
            
            string operatorAS;
            int p = 0;
            int hasC = 0;
            if(exprString.find(";")>=0 && exprString.find(";")<exprString.length())
                exprString = exprString.substr(0,exprString.find(";"));
            if(exprString.find("++")==0) {
                exprString = exprString.substr(2,exprString.length());
                operatorAS = "++";
            } else if(exprString.find("++")==(exprString.length()-2)) {
                exprString = exprString.substr(0,exprString.length()-2);
                p = 1;
                operatorAS = "++";
            } else if(exprString.find("--")==0) {
                exprString = exprString.substr(2,exprString.length());
                operatorAS = "--";
            } else if(exprString.find("--")==(exprString.length()-2)) {
                exprString = exprString.substr(0,exprString.length()-2);
                p = 1;
                operatorAS = "--";
            }
            Source lR,lW;
                
                if(std::string(exprString).find_first_of("[")>= 0 
                        && std::string(exprString).find_first_of("[")<std::string(exprString).length()) {
                    
                    string firstIterator; 
                    
                    string actArg = std::string(exprString).substr(0,std::string(exprString).find_first_of("["));
                    string iterators = std::string(exprString).substr(std::string(exprString).find_first_of("[")+1, std::string(exprString).length());
                    actArg = cleanWhiteSpaces(actArg);
                     if(is_studied_var(actArg,sh)) {
                        lR<< "mem_trace_read(\"";
                        lW<< "mem_trace_write(\"";
                        newLineSource<<actArg<<"\"";
                        hasC = 1;
                     }
                } else {
                    if(is_studied_var(exprString,sh)) {
                        lR<< "mem_trace_read(\"";
                        lW<< "mem_trace_write(\"";
                        newLineSource<<exprString<<"\"";
                        hasC =1;
                    }
                }
            if(hasC) {
                lR <<", &"<<exprString<<");\n";
                lW <<", &"<<exprString<<");\n";
                newLineSource<<lR<<lW;
                hasChanges = 1;
            }
        }
         if(line.find_first_of(";")>= 0 && line.find_first_of(";")<line.length())
                    line = line.substr(0,line.find_first_of(";"));    
        Source nL;
        if(hasChanges) {
           // cout<<std::string(newLineSource)<<endl;
            nL <<  newLineSource <<"("<<line<<")"<<";";
            expr_list[l].replace_with(nL.parse_statement(sC,scopeL));
        } else if(hasArraysWriteOrRead) {
            nL <<  "("<<line<<")"<<";";
            expr_list[l].replace_with(nL.parse_statement(sC,scopeL));
        }
    }
    
    

    astPrettyprint<< construct_ast.prettyprint();
    
    return std::string(astPrettyprint);
}
int AddTracesOnForPhase::is_studied_var(string name, ObjectList<Expression> sh) {
    for (int i= 0; i<sh.size();++i) {
        string studiedVarName =  sh[i].prettyprint();
        if(!studiedVarName.compare(name)) 
            return 1;
    }
    return 0;
}
ObjectList<Source> AddTracesOnForPhase::splitMathExpression(Scope sC,std::string secondO, int includeIterators)
{
    //    std::cout<<"Second Operator: "<<secondO<<endl;
    ObjectList<Source> operators;
    int numElem=0;
    Source empty;
    string math[11] = {"+","*","/","-","<",">","=","?",":","&","|"};
    operators.clear();
    operators.push_back(empty);
    int isInsideIndex = 0;
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
            for(int x=0; x<11;++x){
                if(std::string(actChar).compare(math[x])==0) {
                    find=1; 
                }
                if(math[x].compare("<")==0 || math[x].compare(">")==0) {
                    if(nextChar.compare("=")==0)
                        i++;
                    
                }
                if(math[x].compare("&")==0) {
                    if(nextChar.compare("&")==0)
                        i++;
                    
                }
                if(math[x].compare("|")==0 ) {
                    if(nextChar.compare("|")==0)
                        i++;
                    
                }
                if(math[x].compare("<")==0) {
                    if(nextChar.compare("<")==0) {
                        i++;
                    }
                    
                }
                if(math[x].compare("-")==0) {
                    if(nextChar.compare(">")==0) {
                        //                        cout<<"HI!"<<endl;
                        i++;
                        find = 0;
                    }
                    
                }
                
            }
            if(includeIterators){
                if(std::string(actChar).compare("[")==0) {
                    isInsideIndex++;
                }
                if(std::string(actChar).compare("]")==0) {
                    isInsideIndex--;
                }
                //                cout<<"F: "<< find <<" inside: "<<isInsideIndex<<endl;
            } else {
                if(std::string(actChar).compare("[")==0 || std::string(actChar).compare("]")==0) {
                    find =1;
                }
            }
            if(!find || isInsideIndex>0){
                Source actElem;
                actElem = operators[numElem];
                actElem<<actChar;
                operators.pop_back();
                operators.push_back(actElem);
                //                cout<<std::string(actElem)<<endl;
                //                
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
        } else if(std::string(actChar).compare(")")==0 && std::string(operators[numElem]).compare(std::string(empty))!=0 && (isInsideIndex==0 || !includeIterators)){
            operators.push_back(empty);
            numElem++;           
            operators[numElem]=empty;
        } else if(isInsideIndex>0 && includeIterators && std::string(actChar).compare(" ")!=0) {
            Source actElem;
            actElem = operators[numElem];
            actElem<<actChar;
            operators.pop_back();
            operators.push_back(actElem);
        }
        
    }
    if(std::string(operators[0]).compare("")==0) {
        operators.clear();
    }
    return operators;
}
string AddTracesOnForPhase::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
//*********************

EXPORT_PHASE(AddTracesOnForPhase);

