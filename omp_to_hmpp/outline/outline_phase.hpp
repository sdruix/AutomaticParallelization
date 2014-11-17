#ifndef OUTLINE_PHASE_HPP
#define OUTLINE_PHASE_HPP

#include "tl-compilerphase.hpp"
#include "tl-omp.hpp"
#include "hlt/hlt-outline.hpp"
using namespace TL;
class OutlinePhase : public PragmaCustomCompilerPhase
{
public:
    OutlinePhase();
    virtual void run(DTO &dto);
//    virtual void pre_run(DTO &dto);
private: 
    int _numTransform;
    int _notOutlined;
    int _pragma_lines;
    std::vector<std::string> p_l_s;
    std::vector<std::string> mapbynameSvector;
    std::vector<std::string> _forcedDelegate;
    std::vector<std::string> _released_groups;
    int _inside_loop;
    int _for_min_line;
    int _for_num;
    int _construct_inside_bucle;
    int _construct_num_loop;
    int _outline_line;
    std::vector<int> _jumped_outline_line;
    AST_t _for_ast;
    AST_t _file_tree;
    AST_t _for_internal_ast_last;
    AST_t _for_internal_ast_first;
    int _false_group;
    DTO _dto;
    Source _red_string;
    struct use{
        int row;
        AST_t ast;
        ScopeLink sl;
        int inside_loop;
        int for_num;
        AST_t for_ast;
        AST_t for_internal_ast_last;
        AST_t for_internal_ast_first;
    };
    struct var_use{
        use row_last_write_gpu;
        use row_last_write_cpu;
        use row_last_read_gpu;
        use row_last_read_cpu;
        use row_first_write_gpu;
        use row_first_write_cpu;
        use row_first_read_gpu;
        use row_first_read_cpu;
    }; 
    struct for_info {
        AST_t ast;
        int lineS;
        int lineF;
    };
    typedef std::unordered_map <std::string, var_use> Mymap; 
    typedef std::unordered_map <int, std::vector<std::string> > Mymap2; 
    std::unordered_map <std::string, var_use> _smart_use_table;
    std::unordered_map <std::vector<std::string>,  for_info> _list_of_for;
    std::unordered_map <int, std::vector<std::string> > _where_put_aL;
    std::unordered_map <int, std::vector<std::string> > _where_put_dS;
    //bool is_reduced(std::string);
    void pragma_postorder(PragmaCustomConstruct construct);
    AST_t get_last_ast(AST_t ast, ScopeLink scopeL);
    AST_t get_first_ast(AST_t ast, ScopeLink scopeL);
    use fill_use(int line, AST_t actAst);
    int is_forced_delegate(std::string name);
    int is_released(Source groupName);
    int is_inside_bucle(AST_t ast2check, ScopeLink scopeL, int exprLine, int searching_construct);
    AST_t get_real_ast(AST_t ast2find,AST_t ast2search, ScopeLink scopeL, int exprLine);
    AST_t get_syn_ast(AST_t asT, ScopeLink scopeL,Source synS);
    void checkShared(PragmaCustomConstruct construct,Source& commented_loop);
    Source checkPrivate(PragmaCustomConstruct construct,Source& commented_loop);
    bool checkFor(PragmaCustomConstruct construct,Source& commented_loop);
    void checkGlobalV(PragmaCustomConstruct construct,Source& commented_loop);
    Source checkReduction(PragmaCustomConstruct construct, Source& commented_loop);
    Source get_Params(PragmaCustomConstruct construct,Statement statement,  int cod, int transfer, HLT::Outline outline);
    void get_Args(PragmaCustomConstruct construct,Statement statement, Source& param_list, int cod, int transfer);
    
    bool findName(Source Name);
    int get_real_line(AST_t asT, ScopeLink scopeL, AST_t actLineAST, int update, int searching_construct);
    //AST_t fill_smart_use_table(AST_t asT, ScopeLink scopeL, Scope sC, int outline_num_line, ObjectList<Symbol> prmters, int hmppOrig, int offset, HLT::Outline outline);
    AST_t fill_smart_use_table(AST_t asT, ScopeLink scopeL, Scope sC, int outline_num_line, ObjectList<Symbol> prmters , int hmppOrig, int offset, AST_t prevAST);
    void fill_where_put_aL(ObjectList<Symbol> prmters, HLT::Outline outline, int nup);
    void fill_where_put_dS(ObjectList<Symbol> prmters, HLT::Outline outline, int nup);
    int decimal(int *array, int size);
    int dec2dec(int number, int indx,int *array, int size);
    void binary(int number, int indx,int *array, int size);
    ObjectList<Source> splitMathExpression(Scope sC,std::string secondO);
    bool put_advanced_pragma();
    class TraverseASTFunctor4LocateOMP : public TraverseASTFunctor {
        private:
            ScopeLink _sl;
        public:

            TraverseASTFunctor4LocateOMP(ScopeLink sl) : _sl(sl) {};
            virtual ASTTraversalResult do_(const TL::AST_t &a) const
            {

                bool retBool = false;
//                std::cout<<"a6: "<<a.prettyprint()<<"\n";  
//                 std::cin.get();
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
//                                std::cout<<"a69: "<<a.prettyprint()<<"\n";  
//                                std::cin.get();
                                retBool = true;
                                return ast_traversal_result_helper(retBool,false);
                        } 
                    }
                }
                return ast_traversal_result_helper(false, true);
            };
    };
};


#endif // OUTLINE_PHASE
