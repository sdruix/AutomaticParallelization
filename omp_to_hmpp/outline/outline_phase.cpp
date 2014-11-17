#include "outline_phase.hpp"
#include "hlt/hlt-common.hpp"
#include "hlt/hlt-unroll.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "cxx-parameters.h"
#include "math.h"
#include <cstring>

#include "regex.h"
using namespace TL;
using namespace std;

OutlinePhase::OutlinePhase() : PragmaCustomCompilerPhase("omp") {
    _notOutlined =0;
    register_construct("parallel");
    register_construct("for");
    register_directive("hmpp");
    register_directive("fixed");
    register_directive("check");
    register_directive("for check");
    register_directive("for fixed");
    register_directive("for private");
    
    on_directive_post["parallel"].connect(functor(&OutlinePhase::pragma_postorder, *this));
    
    
}


void OutlinePhase::run(DTO& dto) {
    _dto=dto;
    std::ofstream groupIN,numGroup;
    groupIN.open("inGroup.data", std::ios::trunc);
    groupIN <<0;
    groupIN.close();
    
    PragmaCustomCompilerPhase::run(dto);
}


void OutlinePhase::pragma_postorder(PragmaCustomConstruct construct) {
    
    
    ifstream outFun("numTransform.data");
    string num;
    getline(outFun, num);
    _numTransform = atoi(num.c_str());
    outFun.close();
    TL::PragmaCustomClause for_clause = construct.get_clause("for");
    if(for_clause.is_defined()) {
        struct generator {
            int cod;
            int call;
            int transfer;
            int *lvl1;
            int *lvl2;
        };
        generator kindofOutline;
        
        kindofOutline.lvl1 = new int[4];
        kindofOutline.lvl2 = new int[2];
        memset(kindofOutline.lvl1, 0, 4*sizeof(int));
        memset(kindofOutline.lvl2, 0, 2*sizeof(int));
        
        string pragmaInstruction = construct.get_pragma_line().prettyprint(false);
        Source original_enclosing_function_ast = construct.get_enclosing_function().get_ast().prettyprint();
        
        size_t fixed_inst = pragmaInstruction.find("fixed");
        int start_outlining=0;
        TL::PragmaCustomClause check_clause = construct.get_clause("check");
        TL::PragmaCustomClause fixed_clause = construct.get_clause("fixed");
        char *buf = new char[10];
        
        if(check_clause.is_defined()) {
            start_outlining=1;
            ofstream params;
            ifstream inFile("csv.data");
            string line;
            getline(inFile, line);
            istringstream linestream(line);
            string item;
            getline(linestream, item, ',');
            strcpy(buf, item.c_str());
            int lvl1BeforeBin = atoi(buf);
            
            getline(linestream, item, ',');
            strcpy(buf, item.c_str());
            int lvl2BeforeBin = atoi(buf);
            
            getline(linestream, item, ',');
            strcpy(buf, item.c_str());
            kindofOutline.transfer = atoi(buf);
            binary(lvl1BeforeBin, 3,kindofOutline.lvl1, 4); 
            binary(lvl2BeforeBin, 1,kindofOutline.lvl2, 2);
            cout<<"Check: "<<lvl1BeforeBin<<","<<lvl2BeforeBin<<","<<kindofOutline.transfer<<endl;
            
        } else if(fixed_clause.is_defined()){
            start_outlining=1;    
            string fixedFun =pragmaInstruction.substr(fixed_inst+std::string("fixed").length(),pragmaInstruction.length());
            fixedFun =fixedFun.substr(fixedFun.find_first_of("(")+1,fixedFun.length());
            fixedFun =fixedFun.substr(0,fixedFun.find_first_of(")"));
            
            istringstream linestream(fixedFun);
            string item;
            getline(linestream, item, ',');
            strcpy(buf, item.c_str());
            int lvl1BeforeBin = atoi(buf);
            
            getline(linestream, item, ',');
            strcpy(buf, item.c_str());
            int lvl2BeforeBin = atoi(buf);
            
            getline(linestream, item, ',');
            strcpy(buf, item.c_str());
            kindofOutline.transfer = atoi(buf);
            
            binary(lvl1BeforeBin, 3,kindofOutline.lvl1, 4); 
            binary(lvl2BeforeBin, 1,kindofOutline.lvl2, 2);
            cout<<"Fixed: "<<lvl1BeforeBin<<","<<lvl2BeforeBin<<","<<kindofOutline.transfer<<endl;
            
        }
        
        delete []buf;
        if(start_outlining){
            _smart_use_table.clear();
            _file_tree = construct.get_statement().get_ast().get_enclosing_global_tree();
            Source commented_loop;
            commented_loop
                    << "// Suitable \"#pragma omp\" found.\n";
            if(checkFor(construct, commented_loop)) {
                Statement statement = construct.get_statement();
                
                
                AST_t statement_tree = statement.get_ast();
                if (!ForStatement::predicate(statement_tree)) {
                    cerr << statement.get_ast().get_locus() << ": (error): #pragma omp doesn't have a \"for\" loop " << endl;
                    return;
                }
                
                
                
                
                
                Source argRed;
                std::cout << "--------------------------------------"<<endl;
                
                cout << "// Suitable \"#pragma omp\" found." << endl;
                std::cout << "--------------------------------------"<<endl;
                commented_loop
                        << statement.prettyprint();
                //Call substitution
                
                ObjectList<std::string> unchanged;
                ObjectList<Symbol> prmters;
                Source groupName;
                std::ifstream inGroup("inGroup.data");
                std::string line;
                getline(inGroup, line);
                int inGroupV = atoi(line.c_str());
                inGroup.close();
                if(!inGroupV && (kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                    std::ofstream groupIN;
                    groupIN.open("inGroup.data", std::ios::trunc);
                    groupIN <<1;
                    groupIN.close();
                    inGroupV = 0;
                    _false_group = 1;
                }
                
                
                int outline_line = get_real_line(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(), construct.get_ast(),1,0);
                
                TL::HLT::Outline outlineAux(construct.get_enclosing_function().get_scope_link(), statement, outline_line);
                prmters = outlineAux.get_parameter_list();
                
                system("clear");
                
                AST_t prevAST;
                
                AST_t lastAst=fill_smart_use_table(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_enclosing_function().get_scope_link(), construct.get_enclosing_function().get_scope_link().get_scope(statement.get_ast()), outline_line, prmters,2,0, prevAST);
                Source groupS, mapbynameS;
                
                
                for (Mymap::const_iterator it = _smart_use_table.begin(); 
                        it != _smart_use_table.end(); ++it) {
                    
                    if(it->second.row_first_read_cpu.row==0) {
                        unchanged.push_back(it->first);
                    }
                }
                
                outline_line-=_notOutlined;
                outline_line-=_pragma_lines;
                
                if(!(kindofOutline.lvl1[0] && kindofOutline.lvl2[1])){
                    unchanged.clear();
                }
                
                TL::HLT::Outline outline(construct.get_enclosing_function().get_scope_link(), statement, unchanged, outline_line);
                outline.set_unchanged_vars(unchanged);
                Source name;
                name <<"_instr_for"<< _numTransform;
                outline.set_outline_name(std::string(name));
                outline.set_outline_num_line(outline_line);
                
                prmters = outline.get_parameter_list();
                Source privateS;
                checkShared(construct, commented_loop);
                privateS =  checkPrivate(construct, commented_loop);
                argRed=checkReduction(construct, commented_loop);
                outline.set_reduction(argRed);
                
                if(kindofOutline.lvl1[0]) {
                    kindofOutline.cod = 1 ;
                } else if(decimal(kindofOutline.lvl1,4)==0) {
                    kindofOutline.cod = 0;
                } else {
                    kindofOutline.cod = -1;
                }
                
                
                outline.set_cod_trans(kindofOutline.cod, kindofOutline.transfer);
                if (findName(outline.get_outline_name())) {
                    
                    
                    
                    ofstream funOut;
                    funOut.open("./fun2Outline.data",ios::app);
                    //Create file for inline phase and check pragmas
                    funOut << outline.get_outline_name()<<"\n";
                    funOut.close();    
                    
                    AST_t commented_loop_tree = commented_loop.parse_statement(construct.get_ast(), construct.get_scope_link());
                    construct.get_ast().replace_with(commented_loop_tree);
                    TL::Source source_outline;
                    
                    source_outline = outline.operator Source();
                    Source pragma_instruction, final_call, allocate;
                    //Pragma instruction
                    Source arg_list,sizeS;
                    
                    
                    //Allocate
                    if(outline.get_num_dynamic_var(statement.get_scope())>0 && kindofOutline.lvl1[1]) {
                        pragma_instruction << "#pragma hmpp "
                                << outline.get_outline_name() << " callsite" << allocate <<"\n";
                        AST_t allocateAst;
                        allocateAst=construct.get_enclosing_function().get_ast();
                        outline.set_allocate(allocateAst,construct.get_enclosing_function().get_scope_link());
                        allocate = outline.get_dynamic_var(statement.get_scope());
                        
                    } else if(kindofOutline.lvl1[1]){
                        exit(-1);
                    }
                    
                    Source noUp;
                    
                    if(std::string(privateS).compare("")==0) {
                        pragma_instruction << "#pragma hmpp " <<groupName
                                << outline.get_outline_name() << " callsite"<<noUp ;
                    } else {
                        pragma_instruction << "#pragma hmpp " <<groupName
                                << outline.get_outline_name() << " callsite, "<<privateS <<noUp;
                    }
                    
                    for (Mymap::const_iterator it = _smart_use_table.begin(); 
                            it != _smart_use_table.end(); ++it) {
                        if(it->second.row_last_read_gpu.row!=0)
                            std::cout<<it->first<< "LR(GPU)("<<it->second.row_last_read_gpu.for_num<<"): "<<it->second.row_last_read_gpu.row<<" -> "<<it->second.row_last_read_gpu.ast.prettyprint()<<endl;
                        if(it->second.row_last_write_gpu.row!=0) 
                            std::cout<<it->first<< "LW(GPU)("<<it->second.row_last_write_gpu.for_num<<"): "<<it->second.row_last_write_gpu.row<<" -> "<<it->second.row_last_write_gpu.ast.prettyprint()<<endl;
                        if(it->second.row_last_read_cpu.row!=0) 
                            std::cout<<it->first<< "LR(CPU)("<<it->second.row_last_read_cpu.for_num<<"): "<<it->second.row_last_read_cpu.row<<" -> "<<it->second.row_last_read_cpu.ast.prettyprint()<<endl;
                        if(it->second.row_last_write_cpu.row!=0) 
                            std::cout<<it->first<< "LW(CPU)("<<it->second.row_last_write_cpu.for_num<<"): "<<it->second.row_last_write_cpu.row<<" -> "<<it->second.row_last_write_cpu.ast.prettyprint()<<endl;
                        if(it->second.row_first_read_gpu.row!=0) 
                            std::cout<<it->first<< "FR(GPU)("<<it->second.row_first_read_gpu.for_num<<"): "<<it->second.row_first_read_gpu.row<<" -> "<<it->second.row_first_read_gpu.ast.prettyprint()<<endl;
                        if(it->second.row_first_write_gpu.row!=0) 
                            std::cout<<it->first<< "FW(GPU)("<<it->second.row_first_write_gpu.for_num<<"): "<<it->second.row_first_write_gpu.row<<" -> "<<it->second.row_first_write_gpu.ast.prettyprint()<<endl;
                        if(it->second.row_first_read_cpu.row!=0) 
                            std::cout<<it->first<< "FR(CPU)("<<it->second.row_first_read_cpu.for_num<<"): "<<it->second.row_first_read_cpu.row<<" -> "<<it->second.row_first_read_cpu.ast.prettyprint()<<endl;
                        if(it->second.row_first_write_cpu.row!=0) 
                            std::cout<<it->first<< "FW(CPU)("<<it->second.row_first_write_cpu.for_num<<"): "<<it->second.row_first_write_cpu.row<<" -> "<<it->second.row_first_write_cpu.ast.prettyprint()<<endl;
                        std::cout<<"---------------------------"<<endl;
                    }
                    
                    Source param_list,pragmaTemp;
                    
                    param_list = get_Params(construct, statement, kindofOutline.cod, kindofOutline.transfer, outline);
                    pragmaTemp << outline.get_outline_name() << "(" << std::string(param_list) << ")" << ";\n";
                    
                    construct.get_ast().replace(pragmaTemp.parse_statement(construct.get_ast(), construct.get_scope_link()));
                    _construct_inside_bucle = is_inside_bucle(construct.get_ast(),construct.get_enclosing_function().get_scope_link(),outline_line, 1);
                    
                    _construct_num_loop = _for_num;
                    int markForcedDelegate=0;
                    AST_t astForcedDelegate;
                    Source forced_delegate_store;
                    int forcedDelegateLine = -1;
                    if(kindofOutline.lvl1[0] && kindofOutline.lvl2[1]) {
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"NoUpdate!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        cout<<"---------------------------------------------------------------------------------------"<<endl;
                        
                        int n=0;
                        ObjectList<Symbol> pass_param = outline.get_parameter_list();
                        int j = 0;
                        mapbynameSvector.clear();
                        Source emptyS;
                        forced_delegate_store = emptyS;
                        for (ObjectList<Symbol>::iterator it = pass_param.begin();
                                it != pass_param.end();
                                it++, j++) {
                            string real_name;
                            real_name = pass_param[j].get_name();
                            Symbol noUpdateCandidateSymbol = construct.get_scope().get_symbol_from_name(real_name);
                            if(!noUpdateCandidateSymbol.is_invalid()) {
                                int lwGPU,lwCPU, lrGPU, fwCPU, frGPU;
                                
                                var_use actVarUse;
                                actVarUse=_smart_use_table[real_name];
                                lwGPU = actVarUse.row_last_write_gpu.row;
                                lwCPU = actVarUse.row_last_write_cpu.row;
                                lrGPU = actVarUse.row_last_read_gpu.row;
                                fwCPU = actVarUse.row_first_write_cpu.row;
                                frGPU = actVarUse.row_first_read_gpu.row;
                                
                                if((lwGPU>= lwCPU || (lwGPU == 0 && lwCPU <= lrGPU) || (actVarUse.row_last_write_cpu.for_num!=_construct_num_loop && _construct_inside_bucle))
                                        && (noUpdateCandidateSymbol.get_type().is_array() || 
                                        (noUpdateCandidateSymbol.get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 
                                        && noUpdateCandidateSymbol.get_point_of_declaration().prettyprint(true).find_first_of("[")<noUpdateCandidateSymbol.get_point_of_declaration().prettyprint(true).length()))){
                                    
                                    if((actVarUse.row_first_write_cpu.for_num!=_construct_num_loop) || !_construct_inside_bucle) {
                                        
                                        if(n==0) {
                                            noUp<<", args["<<pass_param[j].get_name();
                                        } else {       
                                            noUp<<", "<<pass_param[j].get_name();
                                        }
                                        if(!pass_param[j].get_name().empty()) {
                                            mapbynameSvector.push_back(pass_param[j].get_name());
                                            n++;
                                        }
                                        Source specificOut,start,separation,final;
                                        vector<string> spec;
                                        spec.clear();
                                        spec.push_back(real_name);
                                        specificOut = outline.get_parameter_io_specific(statement.get_scope(),start,separation,final,spec, 1);
                                        if(actVarUse.row_first_read_cpu.for_num==_construct_num_loop && !specificOut.empty()) {
                                            //Force To Delegate
                                            Source outv2;
                                            start<<"args[";
                                            separation<<",";
                                            final<<"]";
                                            forced_delegate_store << "#pragma hmpp "<<groupName
                                                    << outline.get_outline_name() 
                                                    << " delegatedstore"
                                                    << outv2
                                                    << "\n";
                                            
                                            outv2 = outline.get_parameter_io_specific(statement.get_scope(),start,separation,final, spec, 1);
                                            markForcedDelegate = 1;
                                            if(std::string(outv2).compare("")!=0){
                                                astForcedDelegate = actVarUse.row_first_read_cpu.ast;
                                                _forcedDelegate.push_back(pass_param[j].get_name());
                                                forcedDelegateLine=actVarUse.row_last_read_cpu.row;
                                            }
                                        } else if(actVarUse.row_last_read_cpu.for_num==_construct_num_loop && !specificOut.empty()) {
                                            //Force To Delegate
                                            Source outv2;
                                            start<<"args[";
                                            separation<<",";
                                            final<<"]";
                                            forced_delegate_store << "#pragma hmpp "<<groupName
                                                    << outline.get_outline_name() 
                                                    << " delegatedstore"
                                                    << outv2
                                                    << "\n";
                                            
                                            outv2 = outline.get_parameter_io_specific(statement.get_scope(),start,separation,final, spec, 1);
                                            markForcedDelegate = 1;
                                            if(std::string(outv2).compare("")!=0){
                                                astForcedDelegate = actVarUse.row_first_read_cpu.for_internal_ast_last;
                                                _forcedDelegate.push_back(pass_param[j].get_name());
                                                forcedDelegateLine=actVarUse.row_last_read_cpu.row;
                                            }
                                        }
                                        
                                    }
                                } else {
                                    if(lwGPU==0 && (noUpdateCandidateSymbol.get_type().is_array() || 
                                            (noUpdateCandidateSymbol.get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 
                                            && noUpdateCandidateSymbol.get_point_of_declaration().prettyprint(true).find_first_of("[")<noUpdateCandidateSymbol.get_point_of_declaration().prettyprint(true).length()))) {
                                        if(n==0) {
                                            noUp<<", args["<<pass_param[j].get_name();
                                        } else {       
                                            noUp<<", "<<pass_param[j].get_name();
                                        }
                                        if(!pass_param[j].get_name().empty()) {
                                            mapbynameSvector.push_back(pass_param[j].get_name());
                                            n++;
                                        }
                                        
                                    }
                                }
                                
                            }
                            //                            cin.get();
                            
                        }
                        
                        if(n>0) {
                            noUp<<"].noupdate=true";
                        } else {
                            if(_false_group>0)
                                _false_group++;
                        }
                        //                        cin.get();
                    }
                    if(inGroupV){
                        ifstream groupFileW("numGroup.data");
                        getline(groupFileW, line);
                        int numG = atoi(line.c_str());
                        groupFileW.close();
                        groupName << "<group"<<numG<<"_"<<_numTransform<<"> ";
                    } else if((kindofOutline.lvl1[0] && kindofOutline.lvl2[1])){
                        if(_false_group >=3) {
                            _false_group=0; 
                            ifstream groupFileR("numGroup.data");
                            getline(groupFileR, line);
                            int numG = atoi(line.c_str());
                            groupFileR.close();
                            numG=numG+1;
                            groupName << "<group"<<numG<<"_"<<_numTransform<<"> ";
                            std::ofstream groupFile;
                            groupFile.open("numGroup.data", std::ios::trunc);
                            groupFile <<numG;
                            groupFile.close();
                        } else if(_false_group <3) {
                            ifstream groupFileR("numGroup.data");
                            getline(groupFileR, line);
                            int numG = atoi(line.c_str());
                            groupFileR.close();
                            if(!noUp.empty()) {
                                _false_group=0;
                            } else {
                                numG=numG+1;
                                std::ofstream groupFile;
                                groupFile.open("numGroup.data", std::ios::trunc);
                                groupFile <<numG;
                                groupFile.close();
                            }
                            
                            groupName << "<group"<<numG<<"_"<<_numTransform<<"> ";
                        }  
                    } 
                    
                    if(!groupName.empty()) {
                        groupS <<"#pragma hmpp "<<groupName<<"group, target=CUDA";
                    }
                    
                    if(!groupName.empty()) {
                        TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(construct.get_scope_link());
                        ObjectList<AST_t> expr_list =  construct.get_enclosing_function().get_function_body().get_ast().depth_subtrees(expr_traverse);
                        if(expr_list[0].prettyprint().compare(std::string(groupS))!=0) {
                            expr_list[0].prepend(groupS.parse_statement(construct.get_ast(), construct.get_scope_link()));
                            if(mapbynameSvector.size()>0) {
                                mapbynameS<<"#pragma hmpp "<<groupName<<"mapbyname,";
                                for(int u=0;u<(int)mapbynameSvector.size();++u){
                                    if(u==0) {
                                        mapbynameS<<mapbynameSvector[u]<<" ";
                                    } else {
                                        mapbynameS<<","<<mapbynameSvector[u]<<" ";
                                    }
                                    if(u==(int)mapbynameSvector.size()-1) {
                                        mapbynameS<<"\n";
                                    }
                                }
                                expr_list[0].prepend(mapbynameS.parse_statement(construct.get_ast(), construct.get_scope_link()));
                            }
                        } else if(mapbynameSvector.size()>0) {
                            Source secondLine;
                            secondLine<<  expr_list[1].prettyprint()<<"\n";
                            if(std::string(secondLine).find(" mapbyname,")>0 && std::string(secondLine).find(" mapbyname,")<std::string(secondLine).length()) {
                                std::string mapWithArgs;
                                mapWithArgs = std::string(secondLine).substr(0, std::string(secondLine).find("\n"));
                                mapbynameS<<mapWithArgs;
                                int n=0;
                                for(int u=0;u<(int)mapbynameSvector.size();++u){
                                    
                                    Source caseFirst;
                                    caseFirst << "," << mapbynameSvector[u]<<" ";
                                    size_t caseFind1 = std::string(secondLine).find(std::string(caseFirst));
                                    bool constrain1= (caseFind1 < 0 || caseFind1 > std::string(secondLine).length());
                                    if(constrain1) {
                                        mapbynameS<<","<<mapbynameSvector[u]<<" ";
                                        n++;
                                    }
                                }
                                mapbynameS<<"\n";
                                expr_list[1].replace(mapbynameS.parse_statement(construct.get_ast(), construct.get_scope_link()));
                            } else {
                                expr_list[0].append(mapbynameS.parse_statement(construct.get_ast(), construct.get_scope_link()));
                            }
                        }
                        
                    }
                    int markAsQuickSync=0;
                    AST_t synAst;
                    AST_t ast2substituteRelease,ast2substituteSync;
                    Source synSource;
                    int lineMinSync=-1;
                    if(kindofOutline.lvl1[0] && kindofOutline.lvl2[0]) {
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"Asyn!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        //synchronize
                        
                        synSource << "#pragma hmpp "<<groupName
                                << outline.get_outline_name() << " synchronize\n";
                        
                        
                        var_use synUse;
                        for (Mymap::const_iterator it = _smart_use_table.begin(); 
                                it != _smart_use_table.end(); ++it) {
                            for(unsigned int u=0;u<prmters.size();++u){
                                if(it->first.compare(prmters[u].get_name())==0) {
                                    if((it->second.row_first_read_cpu.row<lineMinSync || lineMinSync==-1) && it->second.row_first_read_cpu.row>0) {
                                        lineMinSync=it->second.row_first_read_cpu.row;
                                        if(it->second.row_first_read_cpu.inside_loop && it->second.row_first_read_cpu.for_num!=_construct_num_loop) {
                                            ast2substituteSync=it->second.row_first_read_cpu.for_ast;
                                        } else {
                                            ast2substituteSync=it->second.row_first_read_cpu.ast;
                                        }
                                        synUse = it->second;
                                    }
                                    if((it->second.row_first_read_gpu.row<lineMinSync || lineMinSync==-1) && it->second.row_first_read_gpu.row>0) {
                                        lineMinSync=it->second.row_first_read_gpu.row;
                                        if(it->second.row_first_read_gpu.inside_loop && it->second.row_first_read_gpu.for_num!=_construct_num_loop) {
                                            ast2substituteSync=it->second.row_first_read_gpu.for_ast;
                                        } else {
                                            ast2substituteSync=it->second.row_first_read_gpu.ast;
                                        }
                                        synUse = it->second;
                                    }
                                    
                                    
                                    if(_construct_inside_bucle){
                                        if((synUse.row_first_read_gpu.row == lineMinSync && synUse.row_first_read_gpu.for_num!=_construct_num_loop) 
                                                || (synUse.row_first_read_cpu.row == lineMinSync && synUse.row_first_read_cpu.for_num!=_construct_num_loop)) {
                                            if(it->second.row_last_read_cpu.for_num == _construct_num_loop && it->second.row_last_read_cpu.row<lineMinSync) {
                                                lineMinSync=it->second.row_last_read_cpu.row;
                                                ast2substituteSync=it->second.row_last_read_cpu.for_internal_ast_last;
                                            }
                                            if(it->second.row_last_read_gpu.for_num == _construct_num_loop && it->second.row_last_read_gpu.row<lineMinSync) {
                                                lineMinSync=it->second.row_last_read_gpu.row;
                                                ast2substituteSync=it->second.row_last_read_gpu.for_internal_ast_last;
                                                
                                            }
                                        }
                                        
                                    }
                                }
                            }
                        }
                        
                        
                        if(!_red_string.empty()) {
                            markAsQuickSync = 1;
                            lineMinSync = outline_line+1;
                        } else if(lineMinSync!=-1 && lineMinSync>outline_line){
                            ast2substituteSync.prepend(synSource.parse_statement(construct.get_ast(), construct.get_scope_link()));
                        } else {
                            
                            if((lastAst.prettyprint().find("return")>=0 && lastAst.prettyprint().find("return")<lastAst.prettyprint().length() )
                                    || (lastAst.prettyprint().find("hmpp")>=0 && lastAst.prettyprint().find("hmpp")<lastAst.prettyprint().length())){
                                lastAst.prepend(synSource.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                
                            } else {
                                lastAst.append(synSource.parse_statement(construct.get_ast(), construct.get_scope_link()));
                            }
                        }
                        
                        pragma_instruction << ", asynchronous";
                        
                    } 
                    if(markAsQuickSync && kindofOutline.lvl1[0] && kindofOutline.lvl2[0]) {
                        synAst=construct.get_ast();
                        construct.get_ast().append(synSource.parse_statement(construct.get_ast(), construct.get_scope_link()));
                    }
                    if(markForcedDelegate && lineMinSync>=forcedDelegateLine) {
                        synAst = get_syn_ast(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(),synSource);
                        synAst.append(forced_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                        
                    }else {
                        astForcedDelegate.prepend(forced_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                    }
                    
                    
                    //Call instruction
                    Source adNup;
                    if (kindofOutline.lvl1[0]) {
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"AdvLoad!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        Source intv; 
                        Source start, separation, final, outv;
                        start<<"args[";
                        separation<<",";
                        final<<"]";
                        Source concatStart, concatFinal; 
                        concatStart <<"";
                        concatFinal <<"";
                        fill_where_put_aL(prmters, outline, kindofOutline.lvl2[1]);
                        
                        for (Mymap2::const_iterator it = _where_put_aL.begin(); 
                                it != _where_put_aL.end(); ++it) {
                            if(it->first>0 && it->second.size()>0){
                                Source new_advanced_load;
                                new_advanced_load << "#pragma hmpp "<<groupName
                                        << outline.get_outline_name() 
                                        << " advancedload"
                                        << intv 
                                        ;
                                intv = outline.get_parameter_in_specific(statement.get_scope(), start, separation, concatFinal,it->second,( kindofOutline.lvl1[0] && kindofOutline.lvl2[1]));
                                if(!intv.empty())
                                    intv<<final;
                                new_advanced_load << "\n";
                                adNup << intv;
                                
                                if(std::string(outv).compare("")!=0 || std::string(intv).compare("")!=0){
                                    if(_smart_use_table[it->second[0]].row_last_write_cpu.row == it->first) {
                                        if(_smart_use_table[it->second[0]].row_last_write_cpu.inside_loop && _smart_use_table[it->second[0]].row_last_write_cpu.for_num!=_construct_num_loop) {
                                            if(_construct_inside_bucle && !( kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                                                construct.get_ast().prepend(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                            } else {
                                                _smart_use_table[it->second[0]].row_last_write_cpu.for_ast.append(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                            }
                                        } else {
                                            if(_construct_inside_bucle && !( kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                                                construct.get_ast().prepend(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                            } else {
                                                _smart_use_table[it->second[0]].row_last_write_cpu.ast.append(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                            }
                                        }
                                    } else if(_smart_use_table[it->second[0]].row_last_write_gpu.row == it->first && !( kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                                        if(_smart_use_table[it->second[0]].row_last_write_gpu.inside_loop && _smart_use_table[it->second[0]].row_last_write_gpu.for_num!=_construct_num_loop) {
                                            _smart_use_table[it->second[0]].row_last_write_gpu.for_ast.append(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                        } else {
                                            _smart_use_table[it->second[0]].row_last_write_gpu.ast.append(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link())); 
                                        }
                                    }
                                }
                            } else if(it->first==0 && it->second.size()>0){
                                Source new_advanced_load;
                                new_advanced_load << "#pragma hmpp "<<groupName
                                        << outline.get_outline_name() 
                                        << " advancedload"
                                        << intv 
                                        ;
                                intv = outline.get_parameter_in_specific(statement.get_scope(), start, separation, concatFinal,it->second,( kindofOutline.lvl1[0] && kindofOutline.lvl2[1]));
                                if(!intv.empty())
                                    intv<<final;
                                new_advanced_load << "\n";
                                adNup << intv ;
                                
                                if(std::string(outv).compare("")!=0 || std::string(intv).compare("")!=0){
                                    construct.get_ast().prepend(new_advanced_load.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                }
                            }
                        }
                        _where_put_aL.clear();
                        
                        
                    } 
                    pragma_instruction << "\n";  
                    
                    if(kindofOutline.lvl1[3]) {
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"Delegate!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                        
                        Source start, separation, final;
                        start<<"args[";
                        separation<<",";
                        final<<"]";
                        fill_where_put_dS(prmters, outline, kindofOutline.lvl2[1]);
                        int l = 0;
                        for (Mymap2::const_iterator it = _where_put_dS.begin(); 
                                it != _where_put_dS.end(); ++it, ++l) {
                            if(it->first>0 && it->second.size()>0){
                                vector<string> aux;
                                for(int i=0;i<(int)it->second.size();++i){
                                    if(!is_forced_delegate(it->second[i]))
                                        aux.push_back(it->second[i]);
                                }
                                if(aux.size()>0) {
                                    Source new_delegate_store,outv2;
                                    new_delegate_store << "#pragma hmpp "<<groupName
                                            << outline.get_outline_name() 
                                            << " delegatedstore"
                                            << outv2
                                            << "\n";
                                    
                                    outv2 = outline.get_parameter_io_specific(statement.get_scope(),start,separation,final, aux, ( kindofOutline.lvl1[0] && kindofOutline.lvl2[1]));
                                    if(std::string(outv2).compare("")!=0){
                                        if(lineMinSync>=it->first) {
                                            synAst = get_syn_ast(construct.get_enclosing_function().get_ast(), construct.get_enclosing_function().get_scope_link(),synSource);
                                            synAst.append(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                        }else if(it->first == _smart_use_table[aux[0]].row_first_read_cpu.row) {
                                            if(_smart_use_table[aux[0]].row_first_read_cpu.inside_loop && _smart_use_table[aux[0]].row_first_read_cpu.for_num!=_construct_num_loop) {
                                                _smart_use_table[aux[0]].row_first_read_cpu.for_ast.prepend(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                            } else {
                                                if(_construct_inside_bucle && ((_smart_use_table[aux[0]].row_first_read_cpu.for_num!=_construct_num_loop && _smart_use_table[aux[0]].row_last_read_cpu.for_num==_construct_num_loop) || (_smart_use_table[aux[0]].row_first_read_cpu.for_num!=_construct_num_loop && _smart_use_table[aux[0]].row_last_read_gpu.for_num==_construct_num_loop)) && !( kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                                                    construct.get_ast().append(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                                } else {
                                                    std::string ppExpr = _smart_use_table[aux[0]].row_first_read_cpu.ast.prettyprint();
                                                    if(ppExpr.find(" synchronize")>0 && ppExpr.find(" synchronize")<ppExpr.length()) {
                                                        _smart_use_table[aux[0]].row_first_read_cpu.ast.append(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                                    } else {
                                                        _smart_use_table[aux[0]].row_first_read_cpu.ast.prepend(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));    
                                                    }
                                                }
                                            }
                                        } else if (_smart_use_table[aux[0]].row_first_read_gpu.row == it->first && !( kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                                            if(_smart_use_table[aux[0]].row_first_read_gpu.inside_loop && _smart_use_table[it->second[0]].row_first_read_gpu.for_num!=_construct_num_loop) {
                                                _smart_use_table[aux[0]].row_first_read_gpu.for_ast.prepend(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                            } else {
                                                if(_construct_inside_bucle && ((_smart_use_table[aux[0]].row_first_read_cpu.for_num!=_construct_num_loop && _smart_use_table[aux[0]].row_last_read_cpu.for_num==_construct_num_loop) || (_smart_use_table[aux[0]].row_first_read_cpu.for_num!=_construct_num_loop && _smart_use_table[aux[0]].row_last_read_gpu.for_num==_construct_num_loop)) && !( kindofOutline.lvl1[0] && kindofOutline.lvl2[1])) {
                                                    construct.get_ast().append(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                                } else {
                                                    
                                                    std::string ppExpr = _smart_use_table[aux[0]].row_first_read_gpu.ast.prettyprint();
                                                    if(ppExpr.find(" synchronize")>0 && ppExpr.find(" synchronize")<ppExpr.length()) {
                                                        _smart_use_table[aux[0]].row_first_read_gpu.ast.append(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                                    } else {
                                                        _smart_use_table[aux[0]].row_first_read_gpu.ast.prepend(new_delegate_store.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                                    }
                                                }
                                            }
                                        }
                                    } 
                                    else {
                                        std::cout<<"Not necessary to delegateS this vars"<<endl;
                                    }
                                }
                            }
                            
                        }
                    }
                    _forcedDelegate.clear();   
                    _where_put_dS.clear();
                    
                    if (kindofOutline.lvl1[2] && !groupName.empty()) {
                        if(!is_released(groupName)) {
                            
                            Source releaseS;
                            int lineMax=-1;
                            for (Mymap::const_iterator it = _smart_use_table.begin(); 
                                    it != _smart_use_table.end(); ++it) {
                                for(unsigned int u=0;u<prmters.size();++u){
                                    if(it->first.compare(prmters[u].get_name())==0) {
                                        if(it->second.row_first_read_cpu.row>lineMax) {
                                            lineMax=it->second.row_first_read_cpu.row;
                                            if(it->second.row_first_read_cpu.inside_loop) {
                                                ast2substituteRelease=it->second.row_first_read_cpu.for_ast;
                                            } else {
                                                ast2substituteRelease=it->second.row_first_read_cpu.ast;
                                            }
                                        }
                                    }
                                }
                            }
                            releaseS << "#pragma hmpp "<< groupName << " release\n";
                            
                            if(lineMax<=0) {
                                
                                if(lastAst.prettyprint().find("return")>=0 && lastAst.prettyprint().find("return")<lastAst.prettyprint().length()){
                                    lastAst.prepend(releaseS.parse_statement(construct.get_ast(), construct.get_scope_link()));
                                } else {
                                    lastAst.append(releaseS.parse_statement(construct.get_ast(), construct.get_scope_link()));   
                                }
                                
                            } else {
                                ast2substituteRelease.append(releaseS.parse_statement(construct.get_ast(), construct.get_scope_link()));
                            }
                            _released_groups.push_back(std::string(groupName));
                        }
                    }
                    _smart_use_table.clear();
                    
                    if(markAsQuickSync){
                        Source reducedToDelegate;
                        reducedToDelegate << "#pragma hmpp "<<groupName
                                << outline.get_outline_name() 
                                << " delegatedstore, args[";   
                        
                        std::string aux,strTowork;
                        strTowork=outline.red_string;
                        int numR=0;
                        while(strTowork.find_first_of(":")>=0 && strTowork.find_first_of(":")<strTowork.length()) {
                            if(strTowork.find_first_of(",")>=0 && strTowork.find_first_of(",")<strTowork.length()) {
                                aux = strTowork.substr(strTowork.find_first_of(":")+1,strTowork.find_first_of(",")-1);
                                strTowork = strTowork.substr(strTowork.find_first_of(",")+1,strTowork.length());
                            } else {
                                aux = strTowork.substr(strTowork.find_first_of(":")+1,strTowork.length());
                                strTowork = "";
                            }
                            std::stringstream actSS;
                            actSS << aux << "_reduced";
                            if(numR>0)
                                reducedToDelegate<<",";
                            reducedToDelegate<<actSS.str();
                            numR++;
                        }
                        
                        reducedToDelegate<<"]";
                        strTowork=_red_string;
                        numR=0;
                        
                        while(strTowork.find_first_of(":")>=0 && strTowork.find_first_of(":")<strTowork.length()) {
                            if(strTowork.find_first_of(",")>=0 && strTowork.find_first_of(",")<strTowork.length()) {
                                aux = strTowork.substr(strTowork.find_first_of(":")+1,strTowork.find_first_of(",")-1);
                                strTowork = strTowork.substr(strTowork.find_first_of(",")+1,strTowork.length());
                            } else {
                                aux = strTowork.substr(strTowork.find_first_of(":")+1,strTowork.length());
                                strTowork = "";
                            }
                            std::stringstream actSS;
                            actSS << aux << "_reduced";
                            reducedToDelegate<<", args["<<actSS.str()<<"].addr=\""<<"&"<<aux<<"\"";
                            numR++;
                        }
                        
                        synAst.append(reducedToDelegate.parse_statement(construct.get_ast(), construct.get_scope_link()));
                    }
                    
                    Source emptyStr;
                    emptyStr<< "";
                    _red_string = emptyStr;
                    outline.clear_reduction();
                    ofstream inlineFile;
                    inlineFile.open("outlinedFunctions.data",ios::app);
                    //Create file for inline phase and check pragmas
                    if(check_clause.is_defined()) {
                        inlineFile << outline.get_outline_name() <<"- check\n";
                    } else if(fixed_clause.is_defined()){
                        inlineFile << outline.get_outline_name() <<"- fixed\n";
                    }
                    inlineFile.close();
                    construct.get_ast().prepend(pragma_instruction.parse_statement(outline._outline_statements[0].get_ast(), outline._sl));
                    
                } else { 
                    if(check_clause.is_defined()){ 
                        
                        Statement statement = construct.get_statement();
                        
                        string clauses =  construct.get_pragma_line().prettyprint();
                        clauses  = clauses.substr(0,clauses.find("check")-1);
                        Source newSource;
                        newSource<<"#pragma omp "<<clauses<<"\n"<<statement.get_ast().prettyprint()<<"\n";
                        AST_t newAst = newSource.parse_statement(construct.get_ast(), construct.get_scope_link());
                        construct.get_ast().replace(newAst);
                        _notOutlined--;
                        
                    }
                    
                }
                
            }
        }
        delete kindofOutline.lvl1;
        delete kindofOutline.lvl2;
        
        
    } 
    else {
        std::ifstream groupFileR("numGroup.data");
        std::string lineF;
        getline(groupFileR, lineF);
        int numG = atoi(lineF.c_str());
        groupFileR.close();
        std::ofstream groupFile;
        groupFile.open("numGroup.data", std::ios::trunc);
        groupFile <<numG+1;
        groupFile.close();
        std::ofstream groupIN;
        groupIN.open("inGroup.data", std::ios::trunc);
        groupIN <<1;
        groupIN.close();
        _false_group=0;
        
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
                    int num = 0;
                    size_t forIndx=-1;
                    if(clauses.find("private")<0 || clauses.find("private")>clauses.length()) {
                        privateVars << "private(";
                        while(astText.find("for")>=0 && astText.find("for")<astText.length()){
                            forIndx = astText.find("for");
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
                                while(express.find(" ")==0) {
                                    express = express.substr(express.find(" ")+1,express.length());
                                }
                                while(express.find_last_of(" ")==express.length()-1){
                                    express = express.substr(0,express.find_last_of(" "));
                                }
                                
                                if(express.find_last_of(" ")>0 && express.find_last_of(" ")<express.length()) {
                                    express= express.substr(express.find_last_of(" ")+1,express.length());
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
            
            groupIN.open("inGroup.data", std::ios::trunc);
            groupIN <<0;
            groupIN.close();
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
                    clauses =  test.get_pragma_line().prettyprint();
                    
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
                    int num = 0;
                    size_t forIndx=-1;
                    if(clauses.find("private")<0 || clauses.find("private")>clauses.length()) {
                        privateVars << "private(";
                        while(astText.find("for")>=0 && astText.find("for")<astText.length()){
                            forIndx = astText.find("for");
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
                                while(express.find(" ")==0) {
                                    express = express.substr(express.find(" ")+1,express.length());
                                }
                                while(express.find_last_of(" ")==express.length()-1){
                                    express = express.substr(0,express.find_last_of(" "));
                                }
                                
                                if(express.find_last_of(" ")>0 && express.find_last_of(" ")<express.length()) {
                                    express= express.substr(express.find_last_of(" ")+1,express.length());
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
            for(int a =0; a<constructList.size();++a) {
                
                pragma_postorder(constructList[a]);
            }
            
            groupIN.open("inGroup.data", std::ios::trunc);
            groupIN <<0;
            groupIN.close();
            AST_t translation_unit = _dto["translation_unit"]; 
            
            
        }
        
    }
    
} 

AST_t OutlinePhase::get_syn_ast(AST_t asT, ScopeLink scopeL,Source synS) {
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = asT.depth_subtrees(expr_traverse);
    int l=0;
    std::string synS_noInto;
    synS_noInto = std::string(synS).substr(0,std::string(synS).length()-1);
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        Expression expr(expr_list[l], scopeL);
        std::string ppExpr;
        ppExpr=expr.prettyprint();
        if(synS_noInto.compare(ppExpr)==0) {
            return expr_list[l];
        }
    }
    return NULL;
}

int OutlinePhase::is_released(Source groupName) {
    int f=0;
    for(int i=0;i<(int)_released_groups.size();++i) {
        if(_released_groups[i].compare(std::string(groupName))==0)
            f=1;
    }
    return f;
}
int OutlinePhase::is_forced_delegate(std::string name)  {
    int f=0;
    for(int i=0;i<(int)_forcedDelegate.size();++i) {
        if(_forcedDelegate[i].compare(name)==0)
            f=1;
    }
    return f;
}
int OutlinePhase::get_real_line(AST_t asT, ScopeLink scopeL, AST_t actLineAST, int update, int searching_construct) {
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
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                if(ppExpr.find(" advancedload,")>0 && ppExpr.find(" advancedload,")<ppExpr.length()){
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                if(ppExpr.find(" delegatedstore,")>0 && ppExpr.find(" delegatedstore,")<ppExpr.length()){
                    _pragma_lines++; 
                    p_l_s.push_back(ppExpr);
                }
                
                if(ppExpr.find(" synchronize")>0 && ppExpr.find(" synchronize")<ppExpr.length()){
                    _pragma_lines++;
                    p_l_s.push_back(ppExpr);
                }
                
                if(ppExpr.find(" release")>0 && ppExpr.find(" release")<ppExpr.length()){
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
int OutlinePhase::is_inside_bucle(AST_t ast2check, ScopeLink scopeL, int exprLine, int searching_construct) {
    TL::HLT::Outline::TraverseASTFunctor4LocateFor expr_traverseFor(scopeL);
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
            
            if (nameF.compare(nameI)==0){
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
                    if(_for_min_line>=0) {
                        _for_internal_ast_last = get_last_ast(loopAst, scopeL);
                        _for_internal_ast_first = get_first_ast(loopAst, scopeL);
                        loopAst = loopAst.get_enclosing_function_definition_declaration();
                        _for_min_line = get_real_line(loopAst, scopeL, exprI.get_ast(), 0, searching_construct);
                        if(searching_construct) {
                            _for_min_line-=_notOutlined;
                            _for_min_line-=_pragma_lines;
                        }
                        num_for=expr_listFor[lF].get_line();
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
AST_t OutlinePhase::get_last_ast(AST_t ast, ScopeLink scopeL){
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    return expr_list[expr_list.size()-1];
}

AST_t OutlinePhase::get_first_ast(AST_t ast, ScopeLink scopeL){
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    return expr_list[0];
}
AST_t OutlinePhase::get_real_ast(AST_t ast2find,AST_t ast2search, ScopeLink scopeL, int exprLine){
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = ast2search.depth_subtrees(expr_traverse);
    int line=0;
    int l=0; 
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        Expression expr(expr_list[l], scopeL);
        std::string ppExpr;
        ppExpr=expr.prettyprint();
        if(ppExpr.find("#pragma hmpp ")>=0 && ppExpr.find("#pragma hmpp ")<ppExpr.length()){
            if(ppExpr.find(" group")>0 && ppExpr.find(" group")<ppExpr.length()){
                line--;
            }
            if(ppExpr.find(" mapbyname,")>0 && ppExpr.find(" mapbyname,")<ppExpr.length()){
                line--;
            }
            if(ppExpr.find(" advancedload,")>0 && ppExpr.find(" advancedload,")<ppExpr.length()){
                line--;
            }
            if(ppExpr.find(" delegatedstore,")>0 && ppExpr.find(" delegatedstore,")<ppExpr.length()){
                line--; 
            }
            
            if(ppExpr.find(" synchronize")>0 && ppExpr.find(" synchronize")<ppExpr.length()){
                line--;
            }
            if(ppExpr.find(" release")>0 && ppExpr.find(" release")<ppExpr.length()){
                line--;
            }
        }
        if(ast2find.prettyprint().compare(ppExpr)==0) {
            line +=l;
            line -=_notOutlined;
            if(exprLine==line) {
                return expr_list[l];
            }
        } 
    }
    return NULL;
    
}
AST_t OutlinePhase::fill_smart_use_table(AST_t asT, ScopeLink scopeL, Scope sC, int outline_num_line, ObjectList<Symbol> prmters , int hmppOrig, int offset, AST_t prevAST){
    int l=0;
    int line=0;
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
    
    std::string actWord;
    TL::HLT::Outline::TraverseASTFunctor4LocateUse expr_traverse(scopeL);
    ObjectList<AST_t> expr_list = workingAst.depth_subtrees(expr_traverse);
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        
        f=0; 
        Expression expr(expr_list[l], scopeL);
        
        std::string ppExpr = expr.prettyprint();
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
                    Symbol findedS = sC.get_symbol_from_name(std::string(cutParam));
                    if(!findedS.is_invalid()) {
                        actWord = findedS.get_name();
                        
                        if(line<outline_num_line) {
                            if(!hmppOrig || hmppOrig == 2) {
                                if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                    _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                                }
                            } else {
                                if(_smart_use_table[actWord].row_last_write_gpu.row < line || _smart_use_table[actWord].row_last_write_gpu.row == 0) {
                                    _smart_use_table[actWord].row_last_write_gpu = fill_use(line,actAst);
                                }
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
                            } else {
                                if(_smart_use_table[actWord].row_first_write_gpu.row > line || _smart_use_table[actWord].row_first_write_gpu.row == 0) {
                                    _smart_use_table[actWord].row_first_write_gpu = fill_use(line,actAst);
                                }
                            }
                            
                        }
                    }
                    
                } 
                ObjectList<Source> operands;
                operands = splitMathExpression(sC, secondOperand.prettyprint());
                
                for (int e=0;e<operands.size();e++){
                    EndPart1 = std::string(operands[e]).find_first_of("[");
                    if(EndPart1>0 && EndPart1<std::string(operands[e]).length()) {
                        Source cutParam;
                        cutParam << std::string(std::string(operands[e]).substr(0, EndPart1));
                        while(std::string(cutParam).find_first_of(" ")==0){                       
                            cutParam = std::string(cutParam).substr(1,std::string(cutParam).length());
                        }
                        
                        while(std::string(cutParam).find_first_of(" ")<std::string(cutParam).length()){
                            cutParam = std::string(cutParam).substr(0,std::string(cutParam).length()-1);
                        }
                        Symbol findedS = sC.get_symbol_from_name(std::string(cutParam));
                        if(!findedS.is_invalid()) {
                            actWord = findedS.get_name();
                            if(line<outline_num_line) {
                                if(!hmppOrig || hmppOrig == 2) {
                                    if(_smart_use_table[actWord].row_last_read_cpu.row < line || _smart_use_table[actWord].row_last_read_cpu.row == 0) {
                                        _smart_use_table[actWord].row_last_read_cpu = fill_use(line,actAst);
                                    }
                                }  else {
                                    if(_smart_use_table[actWord].row_last_read_gpu.row < line || _smart_use_table[actWord].row_last_read_gpu.row == 0) {
                                        _smart_use_table[actWord].row_last_read_gpu = fill_use(line,actAst);
                                    }
                                }
                            } else {
                                if(!hmppOrig || hmppOrig == 2) {
                                    if(_smart_use_table[actWord].row_first_read_cpu.row > line || _smart_use_table[actWord].row_first_read_cpu.row == 0) {
                                        _smart_use_table[actWord].row_first_read_cpu = fill_use(line,actAst);
                                    }
                                } else{
                                    if(_smart_use_table[actWord].row_first_read_gpu.row > line || _smart_use_table[actWord].row_first_read_gpu.row == 0) {
                                        _smart_use_table[actWord].row_first_read_gpu = fill_use(line,actAst);
                                    }
                                }
                                
                            }
                        }
                        
                    } 
                }
                
            }
            
            
            
            if(ppExpr.find("#pragma hmpp ")>=0 && ppExpr.find("#pragma hmpp ")<ppExpr.length() && f==0){
                f=1;
                
                if(hmppOrig == 2) 
                    _inside_loop=is_inside_bucle(expr_list[l],scopeL, line, 0);
                
                if(ppExpr.find(" advancedload,")>0 && ppExpr.find(" advancedload,")<ppExpr.length()){
                    int lineAdv=line;
                    //                    std::cout<<"advancedload : "<<ppExpr<<std::endl;
                    while(ppExpr.find("[")>0 && ppExpr.find("[")<ppExpr.length()) {
                        ppExpr = ppExpr.substr(ppExpr.find_first_of("[")+1,ppExpr.length());
                        std::string args = ppExpr.substr(0,ppExpr.find_first_of("]"));
                        //                        std::cout<<"List of args: "<<args<<endl;
                        while(args.find_first_of(",")>0 && args.find_first_of(",")<args.length()){
                            actWord = args.substr(0,args.find_first_of(","));
                            while(actWord.find_first_of(" ")==0)
                                actWord = actWord.substr(1,actWord.length());
                            while(actWord.find_first_of(" ")<actWord.length())
                                actWord = actWord.substr(0,actWord.length()-1);
                            
                            if((_smart_use_table[actWord].row_last_read_gpu.row < lineAdv || _smart_use_table[actWord].row_last_read_gpu.row == 0)&& lineAdv < outline_num_line) {
                                _smart_use_table[actWord].row_last_read_gpu = fill_use(lineAdv,actAst);
                            }
                            
                            
                            args = args.substr(args.find_first_of(",")+1,args.length());
                        }
                        actWord = args;
                        while(actWord.find_first_of(" ")==0)
                            actWord = actWord.substr(1,actWord.length());
                        while(actWord.find_first_of(" ")<actWord.length())
                            actWord = actWord.substr(0,actWord.length()-1);
                        
                        if((_smart_use_table[actWord].row_last_read_gpu.row < lineAdv  || _smart_use_table[actWord].row_last_read_gpu.row == 0)&& lineAdv < outline_num_line) {
                            _smart_use_table[actWord].row_last_read_gpu = fill_use(lineAdv,actAst);
                        }
                    }
                    
                    
                }
                if(ppExpr.find(" delegatedtore,")>0 && ppExpr.find(" delegatedstore,")<ppExpr.length()){
                    ppExpr = ppExpr.substr(ppExpr.find_first_of("[")+1,ppExpr.length());
                    std::string args = ppExpr.substr(0,ppExpr.find_first_of("]"));
                    while(args.find_first_of(",")>0 && args.find_first_of(",")<args.length()){
                        actWord = args.substr(0,args.find_first_of(","));
                        while(actWord.find_first_of(" ")==0)
                            actWord = actWord.substr(1,actWord.length());
                        while(actWord.find_first_of(" ")<actWord.length())
                            actWord = actWord.substr(0,actWord.length()-1);
                        args = args.substr(args.find_first_of(",")+1,args.length());
                        if((_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0)&& line < outline_num_line) {
                            _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                        }
                        if((_smart_use_table[actWord].row_last_write_gpu.row < line || _smart_use_table[actWord].row_last_write_gpu.row == 0)&& line < outline_num_line) {
                            _smart_use_table[actWord].row_last_write_gpu = fill_use(line,actAst);
                        }
                        
                    }
                    actWord = args;
                    while(actWord.find_first_of(" ")==0)
                        actWord = actWord.substr(1,actWord.length());
                    while(actWord.find_first_of(" ")<actWord.length())
                        actWord = actWord.substr(0,actWord.length()-1);
                    if((_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0)&& line < outline_num_line) {
                        _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                    }
                    if((_smart_use_table[actWord].row_last_write_gpu.row < line || _smart_use_table[actWord].row_last_write_gpu.row == 0)&& line < outline_num_line) {
                        _smart_use_table[actWord].row_last_write_gpu = fill_use(line,actAst);
                    }
                    
                }
                if(ppExpr.find(" synchronize")>0 && ppExpr.find(" synchronize")<ppExpr.length()){
                    string codName;
                    string allAST= actAst.get_enclosing_statement().prettyprint();
                    if(allAST.find(">")>0&&allAST.find(">")<actAst.prettyprint().length()) {
                        allAST = allAST.substr(allAST.find(">")+1,allAST.length());
                    }  else {
                        allAST = allAST.substr(allAST.find(" hmpp ")+6,allAST.length());
                    }
                    
                    codName = allAST.substr(0,allAST.find(" synchronize"));
                    codName = codName.substr(1,codName.length());
                    while(codName.find_first_of(" ")<codName.length())
                        codName = actWord.substr(0,codName.length()-1);
                    allAST = actAst.get_enclosing_statement().prettyprint();
                    ObjectList<AST_t> expr_listAfterHMPP = actAst.get_enclosing_statement().depth_subtrees(expr_traverse);
                    int u=0;
                    string exprS;
                    Symbol sym;
                    for (ObjectList<AST_t>::iterator it1 = expr_list.begin();it1 != expr_list.end(); it1++, u++) {
                        Expression expr(expr_list[u], scopeL);
                        string advAST= expr.prettyprint();
                        if(advAST.find(codName)>=0 && advAST.find(codName)<advAST.length() && advAST.find("(")>=0 && advAST.find("(")<advAST.length()) {
                            exprS = advAST;
                            
                            std::string symName;
                            symName = expr.prettyprint().substr(0,expr.prettyprint().find("("));
                            sym = scopeL.get_scope(expr_list[u]).get_symbol_from_name(symName);
                        }
                    }
                    AST_t defTree;
                    if(!sym.is_invalid()) {
                        defTree=sym.get_definition_tree();
                        FunctionDefinition funct_def(defTree, scopeL);
                        AST_t nouse =fill_smart_use_table(funct_def.get_function_body().get_ast(), scopeL, sC, outline_num_line, prmters, 3, line, actAst);
                    }
                }
                
                if(ppExpr.find(" callsite")>0 && ppExpr.find(" callsite")<ppExpr.length() && line < outline_num_line){
                    
                    string codName;
                    string allAST= actAst.get_enclosing_statement().prettyprint();
                    if(allAST.compare("")==0)
                        allAST= actAst.prettyprint();
                    if(allAST.find(">")>0&&allAST.find(">")<actAst.prettyprint().length()) {
                        allAST = allAST.substr(allAST.find(">")+1,allAST.length());
                    }  else {
                        allAST = allAST.substr(allAST.find(" hmpp ")+6,allAST.length());
                    }
                    
                    codName = allAST.substr(0,allAST.find(" callsite"));
                    while(codName.find_first_of(" ")==0)
                        codName = codName.substr(1,codName.length());
                    while(codName.find_first_of(" ")<codName.length())
                        codName = codName.substr(0,codName.length()-1);
                    allAST = actAst.get_enclosing_statement().prettyprint();
                    ObjectList<AST_t> expr_listAfterHMPP = actAst.get_enclosing_statement().depth_subtrees(expr_traverse);
                    int u=0;
                    AST_t advLoadAST;
                    Symbol sym;
                    int codLine=0;
                    ScopeLink actScope;
                    
                    for (ObjectList<AST_t>::iterator it1 = expr_list.begin();it1 != expr_list.end(); it1++, u++) {
                        Expression expr(expr_list[u], scopeL);
                        string advAST= expr.prettyprint();
                        if(advAST.find(codName)>=0 && advAST.find(codName)<advAST.length() && advAST.find("(")>=0 && advAST.find("(")<advAST.length()) {
                            std::string symName;
                            symName = expr.prettyprint().substr(0,expr.prettyprint().find("("));
                            sym = scopeL.get_scope(expr_list[u]).get_symbol_from_name(symName);
                            codLine=u;
                            advLoadAST = expr.get_ast();
                        }
                    }
                    
                    AST_t defTree;
                    if(!sym.is_invalid()) {
                        defTree=sym.get_definition_tree();
                        FunctionDefinition funct_def(defTree, scopeL);
                        AST_t nouse =fill_smart_use_table(funct_def.get_function_body().get_ast(), scopeL, sC, outline_num_line, prmters, 3, codLine-_notOutlined, advLoadAST);
                        std::cout<<codLine-_notOutlined<<": "<<sym.get_name()<<endl;
                    }
                }
            }
            
            PragmaCustomConstruct test(expr.get_ast(),expr.get_scope_link());
            if(test.is_construct() && f==0 && outline_num_line !=line){
                f=1;
                if(hmppOrig == 2) {
                    _inside_loop=is_inside_bucle(expr_list[l],scopeL, line, 0);
                }
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
                TL::PragmaCustomClause shared_clause = test.get_clause("shared");
                TL::PragmaCustomClause private_clause = test.get_clause("private");
                TL::PragmaCustomClause red_clause = test.get_clause("reduction");
                TL::PragmaCustomClause check_clause = test.get_clause("check");
                TL::PragmaCustomClause fixed_clause = test.get_clause("fixed");
                int hmpp=hmppOrig;
                Source hmppFunName;
                hmppFunName<<"_instr_for"<<_numTransform<<"__ol_"<<line+1<<"_"<<test.get_enclosing_function().get_function_name();
                
                if((check_clause.is_defined()  || fixed_clause.is_defined())&& findName(hmppFunName)){
                    hmpp=1;
                } else {
                    hmpp=0;
                }
                if(shared_clause.is_defined()) {
                    ObjectList<Expression> shared_arguments = shared_clause.get_expression_list();
                    for (ObjectList<Expression>::iterator it = shared_arguments.begin(); it != shared_arguments.end(); it++) {
                        Expression argument(*it);
                        actWord = argument.prettyprint();
                        if(!hmpp && hmppOrig!=1) {
                            if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                            }
                            if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                                
                            }
                            
                        } else {
                            if(_smart_use_table[actWord].row_first_read_gpu.row>offset || _smart_use_table[actWord].row_first_read_gpu.row == 0){
                                _smart_use_table[actWord].row_first_read_gpu = fill_use(offset,actAst);         
                            }
                            if(_smart_use_table[actWord].row_first_write_gpu.row>offset || _smart_use_table[actWord].row_first_write_gpu.row == 0){
                                _smart_use_table[actWord].row_first_write_gpu = fill_use(maxLinePragma,actAst);
                            }
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
                        if(!hmpp && hmppOrig!=1) {
                            
                            if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                                
                            }
                            if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                            }
                            
                        } else {
                            if(_smart_use_table[actWord].row_first_read_gpu.row>offset|| _smart_use_table[actWord].row_first_read_gpu.row == 0){
                                _smart_use_table[actWord].row_first_read_gpu = fill_use(offset,actAst);
                            }
                            if(_smart_use_table[actWord].row_first_write_gpu.row>offset || _smart_use_table[actWord].row_first_write_gpu.row == 0){
                                _smart_use_table[actWord].row_first_write_gpu = fill_use(maxLinePragma,actAst);
                            }
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
                                actWord=actArg;
                                if(!hmpp && hmppOrig!=1) {
                                    if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                        _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                                        
                                    }
                                    if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                        _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                                    }
                                    
                                } else {
                                    if(_smart_use_table[actWord].row_first_read_gpu.row>offset|| _smart_use_table[actWord].row_first_read_gpu.row == 0){
                                        _smart_use_table[actWord].row_first_read_gpu = fill_use(offset,actAst);
                                    }
                                    if(_smart_use_table[actWord].row_first_write_gpu.row>offset || _smart_use_table[actWord].row_first_write_gpu.row == 0){
                                        _smart_use_table[actWord].row_first_write_gpu = fill_use(maxLinePragma,actAst);
                                    }
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
                            actWord=actArg;
                            if(!hmpp && hmppOrig!=1) {
                                if(_smart_use_table[actWord].row_first_read_cpu.row>offset || _smart_use_table[actWord].row_first_read_cpu.row == 0){
                                    _smart_use_table[actWord].row_first_read_cpu = fill_use(offset,actAst);
                                }
                                if(_smart_use_table[actWord].row_first_write_cpu.row>offset || _smart_use_table[actWord].row_first_write_cpu.row == 0){
                                    _smart_use_table[actWord].row_first_write_cpu = fill_use(offset,actAst);
                                }
                                
                            } else {
                                if(_smart_use_table[actWord].row_first_read_gpu.row>offset|| _smart_use_table[actWord].row_first_read_gpu.row == 0){
                                    _smart_use_table[actWord].row_first_read_gpu = fill_use(offset,actAst);
                                }
                                if(_smart_use_table[actWord].row_first_write_gpu.row>offset || _smart_use_table[actWord].row_first_write_gpu.row == 0){
                                    _smart_use_table[actWord].row_first_write_gpu = fill_use(maxLinePragma,actAst);
                                    
                                }
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
            if(expr.is_function_call()&& f==0){
                f=1;
                if(hmppOrig == 2) 
                    _inside_loop=is_inside_bucle(expr_list[l],scopeL, line, 0);
                Source instN;
                instN <<"_instr_for"<<_numTransform;
                if (expr.prettyprint().find(std::string(instN))<0 || expr.prettyprint().find(std::string(instN))>expr.prettyprint().length()) {
                    
                    std::string exprS =expr.prettyprint();
                    exprS = exprS.substr(exprS.find_first_of("(")+1, exprS.length());
                    exprS = exprS.substr(0,exprS.find_last_of(")"));
                    std::string actWord;
                    while(exprS.find_first_of(",")>0 && exprS.find_first_of(",")<exprS.length()){
                        actWord = exprS.substr(0,exprS.find_first_of(","));
                        if((exprS.find_first_of("\"")<0 || exprS.find_first_of("\"")>exprS.length()) && actWord.compare("")!=0) {
                            while(actWord.find_first_of(" ")==0)
                                actWord = actWord.substr(1,actWord.length());
                            while(actWord.find_first_of(" ")<actWord.length())
                                actWord = actWord.substr(0,actWord.length()-1);
                            if(line<outline_num_line) {
                                if(!hmppOrig || hmppOrig == 2) {
                                    if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                        _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst);
                                    }
                                    if(_smart_use_table[actWord].row_last_read_cpu.row < line || _smart_use_table[actWord].row_last_read_cpu.row == 0) {
                                        _smart_use_table[actWord].row_last_read_cpu = fill_use(line,actAst);
                                    }
                                } else {
                                    if(_smart_use_table[actWord].row_last_write_gpu.row < line || _smart_use_table[actWord].row_last_write_gpu.row == 0) {
                                        _smart_use_table[actWord].row_last_write_gpu = fill_use(line,actAst);
                                    }
                                    if(_smart_use_table[actWord].row_last_read_gpu.row < line || _smart_use_table[actWord].row_last_read_gpu.row == 0) {
                                        _smart_use_table[actWord].row_last_read_gpu = fill_use(line,actAst);
                                    }
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
                                    if(_smart_use_table[actWord].row_first_read_cpu.row > line || _smart_use_table[actWord].row_first_read_cpu.row == 0) {
                                        _smart_use_table[actWord].row_first_read_cpu = fill_use(line,actAst);    
                                    }
                                } else {
                                    if(_smart_use_table[actWord].row_first_write_gpu.row > line || _smart_use_table[actWord].row_first_write_gpu.row == 0) {
                                        _smart_use_table[actWord].row_first_write_gpu = fill_use(line,actAst);    
                                        
                                    }
                                    if(_smart_use_table[actWord].row_first_read_gpu.row > line || _smart_use_table[actWord].row_first_read_gpu.row == 0) {                                     
                                        _smart_use_table[actWord].row_first_read_gpu = fill_use(line,actAst);            
                                        
                                    }
                                    if(inside) {
                                        if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                            _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst); 
                                        }
                                    }
                                }
                            }
                        }
                        exprS = exprS.substr(exprS.find_first_of(",")+1,exprS.length());
                    }
                    actWord = exprS;
                    if((exprS.find("\"")<0 || exprS.find_first_of("\"")>exprS.length()) && actWord.compare("")!=0){
                        while(actWord.find_first_of(" ")==0)
                            actWord = actWord.substr(1,actWord.length());
                        while(actWord.find_first_of(" ")<actWord.length())
                            actWord = actWord.substr(0,actWord.length()-1);
                        if(line<outline_num_line) {
                            if(!hmppOrig || hmppOrig == 2) {
                                if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                    _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst); 
                                }
                                if(_smart_use_table[actWord].row_last_read_cpu.row < line || _smart_use_table[actWord].row_last_read_cpu.row == 0) {
                                    _smart_use_table[actWord].row_last_read_cpu = fill_use(line,actAst); 
                                }
                            } else {
                                if(_smart_use_table[actWord].row_last_write_gpu.row < line || _smart_use_table[actWord].row_last_write_gpu.row == 0) {
                                    _smart_use_table[actWord].row_last_write_gpu = fill_use(line,actAst); 
                                }
                                if(_smart_use_table[actWord].row_last_read_gpu.row < line || _smart_use_table[actWord].row_last_read_gpu.row == 0) {
                                    _smart_use_table[actWord].row_last_read_gpu = fill_use(line,actAst); 
                                } 
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
                                if(_smart_use_table[actWord].row_first_read_cpu.row > line || _smart_use_table[actWord].row_first_read_cpu.row == 0) {
                                    _smart_use_table[actWord].row_first_read_cpu = fill_use(line,actAst); 
                                }
                            } else {
                                if(_smart_use_table[actWord].row_first_write_gpu.row > line || _smart_use_table[actWord].row_first_write_gpu.row == 0) {
                                    _smart_use_table[actWord].row_first_write_gpu = fill_use(line,actAst); 
                                    
                                }
                                if(_smart_use_table[actWord].row_first_read_gpu.row > line || _smart_use_table[actWord].row_first_read_gpu.row == 0) {                                     
                                    _smart_use_table[actWord].row_first_read_gpu = fill_use(line,actAst); 
                                }
                                if(inside) {
                                    if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                        _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst); 
                                    }
                                }
                            }
                        }
                    }
                    
                    
                }
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
                            stringstream pattern;
                            pattern<<"[^a-zA-Z0-9]"<<prmters[k].get_name()<<"[ \r\t\n\f]*[\r\t\n\f]*[\[]+";
                            int rv;
                            regex_t exp; 
                            rv = regcomp(&exp, pattern.str().c_str(), REG_EXTENDED);
                            if (rv != 0) {
                                printf("regcomp failed with %d\n", rv);
                            }
                            regmatch_t matches[1]; 
                            if(regexec(&exp, ppExpr.c_str(), 1, matches, 0) == 0) {
                                std::string actWord = prmters[k].get_name();
                                
                                if(ppExpr.find(prmters[k].get_name())<ppExpr.find("=")) {
                                    
                                    if(line<outline_num_line) {
                                        if(!hmppOrig || hmppOrig==2){
                                            if(_smart_use_table[actWord].row_last_write_cpu.row < line || _smart_use_table[actWord].row_last_write_cpu.row == 0) {
                                                _smart_use_table[actWord].row_last_write_cpu = fill_use(line,actAst); 
                                            }
                                        } else {
                                            if(_smart_use_table[actWord].row_last_write_gpu.row < line || _smart_use_table[actWord].row_last_write_gpu.row == 0) {
                                                _smart_use_table[actWord].row_last_write_gpu = fill_use(line,actAst); 
                                            }
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
                                        } else {
                                            if(_smart_use_table[actWord].row_first_write_gpu.row > line || _smart_use_table[actWord].row_first_write_gpu.row == 0) {
                                                _smart_use_table[actWord].row_first_write_gpu = fill_use(line,actAst);
                                            }
                                        }
                                    }
                                } else {
                                    if(line<outline_num_line) {
                                        if(!hmppOrig || hmppOrig==2){
                                            if(_smart_use_table[actWord].row_last_read_cpu.row < line || _smart_use_table[actWord].row_last_read_cpu.row == 0) {
                                                _smart_use_table[actWord].row_last_read_cpu = fill_use(line,actAst);
                                            }
                                        } else {
                                            if(_smart_use_table[actWord].row_last_read_gpu.row < line || _smart_use_table[actWord].row_last_read_gpu.row == 0) {
                                                _smart_use_table[actWord].row_last_read_gpu = fill_use(line,actAst);
                                            }
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
                                        } else {
                                            if(_smart_use_table[actWord].row_first_read_gpu.row > line || _smart_use_table[actWord].row_first_read_gpu.row == 0) {
                                                _smart_use_table[actWord].row_first_read_gpu = fill_use(line,actAst);
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

OutlinePhase::use OutlinePhase::fill_use(int line, AST_t actAst){
    use actUse;
    actUse.row=line;
    actUse.ast=actAst;
    actUse.inside_loop = _inside_loop;
    actUse.for_num = _for_num;
    actUse.for_ast = _for_ast;
    actUse.for_internal_ast_last = _for_internal_ast_last;
    return actUse;
    
}
int OutlinePhase::decimal(int *array, int size) {
    int power = size-1;
    int num = 0;
    for(int i=0;i<size;++i,--power){
        if(array[i]==1)
            num+=pow(2,power) ;
    }
    return num;
}
void OutlinePhase::fill_where_put_aL(ObjectList<Symbol> prmters, HLT::Outline outline, int nup){
    if(prmters.size()>0){         
        int o=0;
        for (ObjectList<Symbol>::iterator it = prmters.begin();it != prmters.end(); it++,o++) {
            //            cout<<prmters[o].get_name()<<endl;
            if(prmters[o].get_type().is_array() || (prmters[o].get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && prmters[o].get_point_of_declaration().prettyprint(true).find_first_of("[")<prmters[o].get_point_of_declaration().prettyprint(true).length())) {
                int line2put = _smart_use_table[prmters[o].get_name()].row_last_write_cpu.row;
                int lwCPU=line2put, lrGPU =_smart_use_table[prmters[o].get_name()].row_last_read_gpu.row, lwGPU = _smart_use_table[prmters[o].get_name()].row_last_write_gpu.row, lrCPU = _smart_use_table[prmters[o].get_name()].row_last_read_cpu.row;
                if(nup){
                    if(lwGPU>= lwCPU || (_smart_use_table[prmters[o].get_name()].row_last_write_cpu.for_num!=_construct_num_loop && _construct_inside_bucle)) {
                        if((_smart_use_table[prmters[o].get_name()].row_first_write_cpu.for_num!=_construct_num_loop) || !_construct_inside_bucle){
                            if(lrCPU+1>lrGPU && (lwCPU!=lwGPU||lwGPU==0)) {
                                _where_put_aL[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                            }
                        }
                    } else if(lwGPU == 0 && lwCPU == 0) {
                        if(line2put>_smart_use_table[prmters[o].get_name()].row_last_write_gpu.row) {
                            _where_put_aL[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                        } else {
                            line2put = _smart_use_table[prmters[o].get_name()].row_last_write_gpu.row;
                            _where_put_aL[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                        }
                    } else if(lwGPU == 0 && lwCPU > 0) {
                        _where_put_aL[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                    }
                    
                } else {
                    if(line2put>_smart_use_table[prmters[o].get_name()].row_last_write_gpu.row) {
                        _where_put_aL[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                    } else {
                        line2put = _smart_use_table[prmters[o].get_name()].row_last_write_gpu.row;
                        _where_put_aL[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                    }
                }
            }
            
        }
    }
    //    cin.get();
    //    cin.get();
}
void OutlinePhase::fill_where_put_dS(ObjectList<Symbol> prmters, HLT::Outline outline, int nup){
    if(prmters.size()>0){
        int o=0;
        for (ObjectList<Symbol>::iterator it = prmters.begin();it != prmters.end(); it++,o++) {
            if(prmters[o].get_type().is_array() || (prmters[o].get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && prmters[o].get_point_of_declaration().prettyprint(true).find_first_of("[")<prmters[o].get_point_of_declaration().prettyprint(true).length())) {
                int line2put = _smart_use_table[prmters[o].get_name()].row_first_read_cpu.row;
                if(nup){
                    _where_put_dS[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                } else {
                    if((line2put<=_smart_use_table[prmters[o].get_name()].row_first_read_gpu.row && line2put!=0)  || (line2put>_smart_use_table[prmters[o].get_name()].row_first_read_gpu.row && _smart_use_table[prmters[o].get_name()].row_first_read_gpu.row==0)) {
                        _where_put_dS[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                    } else {
                        line2put = _smart_use_table[prmters[o].get_name()].row_first_read_gpu.row;
                        _where_put_dS[line2put].push_back(outline._correspondence_table[prmters[o].get_name()].get_name());
                    }
                }
            }
        }
    }
}
int OutlinePhase::dec2dec(int number, int indx,int *array, int size) {
    binary(number, indx, array, size);
    int num = decimal(array,size);
    return num;
}
void OutlinePhase::binary(int number, int indx,int *array, int size) {
    int remainder;
    if(number <= 1) {
        array[indx]=number;
        return;
    }
    
    
    remainder = number%2;
    binary(number >> 1,indx-1, array, size);
    array[indx]=remainder;
}

bool OutlinePhase::findName(Source name) {
    ifstream inFile("toTransform.data");
    string line;
    
    while(getline(inFile, line)){
        size_t fin = std::string(line).find("- fixed");
        size_t cin = std::string(line).find("- check");
        bool is_fixed = fin<std::string(line).length() && fin>0;
        bool is_checked = cin<std::string(line).length() && cin>0;
        
        if(is_fixed){
            line = line.substr(0,fin);
        }
        if(is_checked){
            line = line.substr(0,cin);
        }
        stringstream funName;
        funName << std::string(name).substr(0,10);
        funName << std::string(name).substr(std::string(name).find("_ol_"),std::string(name).length());
        
        if(std::string(line).compare("all")==0) {
            return true;
        } else {
            stringstream funGenericName;
            funGenericName << line.substr(0,10);
            funGenericName << line.substr(line.find("_ol_"),line.length());
            if(funName.str().compare(funGenericName.str())==0) {
                return true;
            }
        }
    }
    return false;
}



/**
 *
 * @param construct Pragma Sentence
 * @param commented_loop Source
 */
void OutlinePhase::checkShared(PragmaCustomConstruct construct, Source& commented_loop) {
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
    
}

Source OutlinePhase::checkReduction(PragmaCustomConstruct construct, Source& commented_loop) {
    PragmaCustomClause red_clause = construct.get_clause("reduction");
    Source arg;
    if (red_clause.is_defined()) {
        commented_loop
                << "// Arguments found in reduction clausule: \n";
        cout << "// Arguments found in reduction clausule: " << endl;
        ObjectList<std::string> red_args = red_clause.get_arguments();
        for (ObjectList<std::string>::iterator it = red_args.begin(); it != red_args.end(); it++) {
            string argument(*it);
            commented_loop
            << "//  - " << argument << "\n";
            cout << "//  - " << argument << endl;
            
            arg << argument;
            
        }
    }
    _red_string = arg;
    return arg;
}

bool OutlinePhase::checkFor(PragmaCustomConstruct construct, Source& commented_loop) {
    PragmaCustomClause for_clause = construct.get_clause("for");
    bool for_clau = false;
    if (for_clause.is_defined()) {
        for_clau = true;
    }
    return for_clau;
}


/**
 * 
 * @param construct Pragma Sentence
 * @param commented_loop Source
 */
Source OutlinePhase::checkPrivate(PragmaCustomConstruct construct, Source& commented_loop) {
    Source privateS;
    PragmaCustomClause private_clause = construct.get_clause("private");
    if (private_clause.is_defined()) {
        commented_loop
                << "// Arguments found in private clausule: \n";
        cout << "// Arguments found in private clausule: " << endl;
        ObjectList<Expression> private_arguments = private_clause.get_expression_list();
        int n=0;
        for (ObjectList<Expression>::iterator it = private_arguments.begin(); it != private_arguments.end(); it++, n++) {
            Expression argument(*it);
            if(n==0)
                privateS << "private=["<<argument.prettyprint();
            else
                privateS << ", "<<argument.prettyprint();
            commented_loop
            << "//  - " << argument.prettyprint() << "\n";
            cout << "//  - " << argument.prettyprint() << endl;
        }
        if(n>0)
            privateS<<"]";
    }
    Source empty;
    return empty;
    //    return privateS;
}

Source OutlinePhase::get_Params(PragmaCustomConstruct construct, Statement statement,  int cod, int transfer, TL::HLT::Outline outlineAux) {
    Source param_list;
    ObjectList<Symbol> pass_param = outlineAux.get_parameter_list();
    int j = 0;
    for (ObjectList<Symbol>::iterator itu = pass_param.begin();
            itu != pass_param.end();
            itu++, j++) {
        if (pass_param[j].get_type().is_array()) {
            param_list << pass_param[j].get_name();
        } else {
            if(outlineAux.is_reduced(pass_param[j].get_name())){
                param_list<<"&"<<pass_param[j].get_name();
                
            } else
                param_list << pass_param[j].get_name();
        }
        if (itu + 1 != pass_param.end())
            param_list << ",";
        
    }
    return param_list;
}

ObjectList<Source> OutlinePhase::splitMathExpression(Scope sC,std::string secondO)
{
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


EXPORT_PHASE(OutlinePhase);
