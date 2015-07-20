#ifndef ADDTRACESONFOR_PHASE_HPP
#define ADDTRACESONFOR_PHASE_HPP

#include <tl-compilerphase.hpp>
#include <hlt/hlt-inline.hpp>
#include <hlt/hlt-common.hpp>
#include <tl-ast.hpp>
#include <tl-scopelink.hpp>
#include <tl-langconstruct.hpp>
#include <tl-symbol.hpp>
#include "tl-pragmasupport.hpp"
#include <cxx-utils.h>
#include <uniquestr.h>
#include <tl-source.hpp>
#include <tl-datareference.hpp>

#include "tl-omp.hpp"
#include <unordered_map>
#include "hlt/hlt-outline.hpp"

//#include "printTraverse.hpp"
using namespace TL;
using namespace TL::HLT;
using namespace std;


class AddTracesOnForPhase : public PragmaCustomCompilerPhase {
public:
    AddTracesOnForPhase();
    virtual void run(DTO &dto);
private:
    void pragma_postorder(PragmaCustomConstruct construct);
    DTO _dto;
    AST_t _translation_unit, _loopSub;
    ScopeLink _scope_link;
    ObjectList<string> _declaredVars;
    string cleanWhiteSpaces(string toClean);
    int is_inside_bucle(AST_t ast2check, ScopeLink scopeL, int exprLine, int searching_construct);
    int get_real_line(AST_t asT, ScopeLink scopeL, AST_t actLineAST, int update, int searching_construct, int initialConstruct);
    AST_t get_last_ast(AST_t ast, ScopeLink scopeL);
    AST_t get_first_ast(AST_t ast, ScopeLink scopeL);
    void completeLoopsInAST(AST_t ast, ScopeLink scopeL);
    string transformConstructAST(PragmaCustomConstruct construct, ScopeLink scopeL, Scope sC, ObjectList<Expression> sh);
    int putIteratedVarsOfInterest(string principalIt,  AST_t astWhereSearch, ScopeLink scopeL);
    int is_studied_var(string name, ObjectList<Expression> sh);
    ObjectList<Source> splitMathExpression(Scope sC,std::string secondO, int includeIterators);
    string replaceAll(std::string str, const std::string& from, const std::string& to);
    class TraverseASTFunctor4Malloc : public TraverseASTFunctor {
    private:
        ScopeLink _slM;
    public:
        
        TraverseASTFunctor4Malloc(ScopeLink sl) : _slM(sl) {};
        virtual ASTTraversalResult do_(const TL::AST_t &a) const
        {
            
            if (Expression::predicate(a)) {
                Expression expr(a, _slM);
                bool retBool = false;
                bool is_assigment =expr.is_assignment();
                if(is_assigment){
                    retBool = true;
                }
                return ast_traversal_result_helper(retBool,false);
            }
            return ast_traversal_result_helper(false, true);
        };
    };
    class TraverseASTFunctor4LocateBucle : public TraverseASTFunctor {
    private:
        ScopeLink _slLF;
    public:
        
        TraverseASTFunctor4LocateBucle(ScopeLink sl) : _slLF(sl) {};
        virtual ASTTraversalResult do_(const TL::AST_t &a) const
        {
            bool retBool = false;
            //std::cout<<"********************+"<<a.prettyprint()<<std::endl;
            if(ForStatement::predicate(a)) {
                
                retBool =true;
                return ast_traversal_result_helper(retBool,false);
            }
            if(WhileStatement::predicate(a)) {
                retBool =true;
                return ast_traversal_result_helper(retBool,false);
            }
            if(DoWhileStatement::predicate(a)) {
                retBool =true;
                return ast_traversal_result_helper(retBool,false);
            }
            if(IfStatement::predicate(a)) {
                retBool =true;
                return ast_traversal_result_helper(retBool,false);
            }
            return ast_traversal_result_helper(false, true);
        };
    };
    class TraverseASTFunctor4LocateUse : public TraverseASTFunctor {
    private:
        ScopeLink _slLU;
        bool _f_defined;
        bool _a_defined;
        
    public:
        
        TraverseASTFunctor4LocateUse(ScopeLink sl) : _slLU(sl) {};
        virtual ASTTraversalResult do_(const TL::AST_t &a) const
        {
            
            bool retBool = false;

//                cout<<"---------------------------------"<<endl;
//                cout<<a.prettyprint()<<endl;
//                cout<<a.prettyprint().find("++")<<endl;
//                cout<<a.prettyprint().length()-3<<endl;
//                cin.get();
            if(a.prettyprint().find("MPI_")>= 0 && a.prettyprint().find("MPI_")<a.prettyprint().length()){
                std::istringstream f(a.prettyprint());
                std::string line;    
                int lines=0;
                while (std::getline(f, line)) {
                    lines++;
                }
                
                if(lines==1){
//                    cout<<a.prettyprint()<<endl;
//                    cin.get();
                    retBool = true;
                    return ast_traversal_result_helper(retBool,false);
                }
                
            }
            if (Expression::predicate(a)) {
                Expression expr(a, _slLU);
//                cout<<"as. "<<a.prettyprint()<<endl;
//                cin.get();
                if(expr.is_assignment()){
                    retBool = true;
                }
                if(expr.is_function_call()){
//                    cout<<expr.prettyprint()<<endl;
                    retBool = true;
//                    cin.get();
                }
                
                if(expr.is_operation_assignment()){
                    retBool = true;
                }
                if(a.prettyprint().find("++")==0 || a.prettyprint().find("++")==a.prettyprint().length()-3
                    || a.prettyprint().find("--")==0 || a.prettyprint().find("--")<a.prettyprint().length()-3) {
                        retBool = true;
                }
                
                return ast_traversal_result_helper(retBool,false);
            } else {
                std::istringstream f(a.prettyprint());
                std::string line;    
                int lines=0;
                while (std::getline(f, line)) {
                    lines++;
                }
                
                if(lines==1){
                    retBool = true;
                    return ast_traversal_result_helper(retBool,false);
                } else {
                    PragmaCustomConstruct test(a,_slLU);
                    if(test.is_construct()){
                        retBool = true;
                        return ast_traversal_result_helper(retBool,false);
                    } 
                }
            }
            return ast_traversal_result_helper(false, true);
        };
    };
    class TraverseASTFunctor4LocateOMP : public TraverseASTFunctor {
    private:
        ScopeLink _sl;
    public:
        
        TraverseASTFunctor4LocateOMP(ScopeLink sl) : _sl(sl) {};
        virtual ASTTraversalResult do_(const TL::AST_t &a) const
        {
            
            bool retBool = false;
            if (!Expression::predicate(a)) {
                std::istringstream f(a.prettyprint());
                std::string line;    
                int lines=0;
                while (std::getline(f, line)) {
                    lines++;
                }
                if(lines>1){
                    PragmaCustomConstruct test(a,_sl);
                    if(test.is_construct()){
                        retBool = true;
                        return ast_traversal_result_helper(retBool,false);
                    } 
                }
            }
            return ast_traversal_result_helper(false, true);
        };
    };
    int _for_min_line;
    AST_t _file_tree, _for_ast, _for_internal_ast_last, _for_internal_ast_first, _construct_loop, _last_construct, _initializationAST, _groupAST;
    
    int _for_num, _construct_num_loop, _last_construct_num_loop, _groupInside, _numLoop;
    int _notOutlined, _initialized;
    int _pragma_lines;
    int _construct_inside_bucle;
    
};



#endif // OMP_TO_MPI_PHASE

