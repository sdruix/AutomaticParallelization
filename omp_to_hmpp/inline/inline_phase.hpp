#ifndef INLINE_PHASE_HPP
#define INLINE_PHASE_HPP

#include <tl-compilerphase.hpp>
#include <hlt/hlt-inline.hpp>
#include <hlt/hlt-common.hpp>
#include <tl-ast.hpp>
#include <tl-scopelink.hpp>
#include <tl-langconstruct.hpp>
#include <tl-symbol.hpp>
#include <cxx-utils.h>
#include <uniquestr.h>
#include <tl-source.hpp>
#include <tl-datareference.hpp>
#include <tr1/regex>
#include "FunctionDefinitionPred.hpp"

using namespace TL;
using namespace TL::HLT;
using namespace std;

class InlinePhase : public CompilerPhase {
public:
    InlinePhase();
    //    ~InlinePhase();
    virtual void run(
            DTO &dto);
    void set_FCall(
            Expression* _function_call2add);
    void set_FSym(
            Symbol* _function_symbol2add);
    void set_PSym(
            ObjectList< Symbol>* param_symbols2add);
    void inlineFunction(
            Symbol &called_sym,
            Expression &expr);
private:
    inline bool exists(const std::string& name);
    Source _nameReturn;
    ObjectList<string> _deletedFuncs;
    ObjectList<Source> _referenceVars;
    ObjectList<Symbol> _inlinedFunctions;
    FunctionDefinitionPred _function_def_pred;
    int _retid;
    int _forced;
    AST_t _translation_unit;
    int _varid;
    Source _functionName;
    int _callNum;
    int _rowOfCall;
    Expression *_function_call;
    Symbol *_function_symbol;
    ObjectList<Symbol> *param_symbols;
    bool is_reference(Source name);
    // Auxiliar function where we will find function calls
    void find_functions(
            FunctionDefinition function_def,
            ScopeLink scope_link);
    
    void getParamSymbols(
            ObjectList< Symbol> &param_symbols,
            Scope &funct_scopeB);
    void getParamDeclaration(
            Source &parameter_declarations,
            Type function_type,
            Scope &funct_scope,
            Expression &expr,
            ObjectList< Symbol> &param_symbols,
            Statement funct_body);
    void solve_return(
            Type function_type,
            Source &parameter_declarations,
            Source &return_code,
            Scope &funct_scope);
    void replace_call(
            FunctionDefinition funct_def,
            Expression &expr,
            Source &result);
   

    Expression* get_FCall();

    Symbol* get_FSym();

    ObjectList< Symbol>* get_PSym();

    static const char* inline_prettyprint_callback(
            AST _a,
            void* data);

    static const char* solve_predicate(
            AST_t a,
            Expression function_call,
            Symbol function_symbol,
            void* data);
   
    static const char* solve_result_predicate(
            AST_t a,
            Expression* function_call,
            Symbol* function_symbol,
            void* data);


    void phase_cleanup(
            DTO& data_flow);

};

#endif // OMP_TO_HMPP_PHASE

