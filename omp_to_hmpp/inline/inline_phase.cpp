#include "inline_phase.hpp"

#include "FunctionCallsPred.hpp"
#include <stdlib.h>
#include "hlt/hlt-common.hpp"
#include "tl-omp.hpp"
#include <iostream>
#include <fstream>


#include <bits/basic_string.h>

using namespace TL;
using namespace TL::HLT;
using namespace std;

InlinePhase::InlinePhase() {

    OpenMP::OpenMPPhase ompP;
    ompP.register_directive("parallel");
    ompP.register_directive("for");
    ompP.register_directive("hmpp");
    ompP.register_directive("fixed");
   ompP.register_directive("check");
   ompP.register_directive("for check");
    ompP.register_directive("for fixed");
    ompP.register_directive("critical");

    ompP.register_directive("threadprivate");
    ompP.register_directive("atomic");
    ompP.register_directive("master");

    _callNum=0;
    _retid = 0;
    _varid = 0;
}
inline bool InlinePhase::exists(const std::string& name) {
    return ( access(name.c_str(), F_OK) != -1);
}
void InlinePhase::run(DTO& dto) {

    ofstream params;
   
    string line;
    _translation_unit = dto["translation_unit"];
    ScopeLink scope_link = dto["scope_link"];

    ObjectList<AST_t> list_of_fun_defs = _translation_unit.depth_subtrees(_function_def_pred);
    std::stringstream name;
    name << "../outline/fun2Outline.data";
    _forced = 0;
    if (!exists(name.str().c_str())) {
        ofstream outFile;
        outFile.open("fun2Outline.data", ios::trunc);
        outFile << "main";
        outFile.close();
        name.str("fun2Outline.data");
        _forced = 1;
    }
    for (ObjectList<AST_t>::iterator it = list_of_fun_defs.begin(); it != list_of_fun_defs.end(); it++) {
        FunctionDefinition function_def(*it, scope_link);
        TL::Symbol function_sym = function_def.get_function_symbol();
        TL::Statement function_body = function_def.get_function_body();
        std::cout<<"Chech if is oulined: "<<function_def.get_function_name()<<"\n";
        ifstream inFile(name.str().c_str());
        while(getline(inFile, line)) {
           if(std::string(function_def.get_function_name()).compare(line)==0){
                std::cout<<"Starting inlines in function body named: "<< function_def.get_function_name() <<"\n {\n";
               
                find_functions(function_def, scope_link);
                cout<<"Continue"<<endl;
                inFile.seekg (0, ios::end);
            }
        }
       
        inFile.close();
//        if(_forced) {
////            cout<<"forced"<<endl;
//            for(int fN=0; fN<_inlinedFunctions.size();++fN){
////                cout<<function_def.get_function_name() << " vs. "<<_inlinedFunctions[fN].get_name()<<endl;
//                if(std::string(function_def.get_function_name()).compare(_inlinedFunctions[fN].get_name())==0){
//                    std::cout<<"Starting inlines in inlined function body named by force: "<< function_def.get_function_name() <<"\n";
//                    cin.get();
//                    find_functions(function_def, scope_link);
//                }
//            }
//        }

    }
    string temp = name.str().c_str();
    name.str("");
    name << "rm "<<temp;
    system(name.str().c_str());
    int j=0;
   
    for (ObjectList<Symbol>::iterator it = _inlinedFunctions.begin(); it != _inlinedFunctions.end(); it++, j++) {
        std::cout<<"Inlined Functions: "<<it->get_name()<<"\n";
        Symbol _function_symbol = _inlinedFunctions[j];

        AST_t definition_tree = _function_symbol.get_definition_tree();
        Expression expr(definition_tree, scope_link);
        FunctionDefinition funct_def(definition_tree, expr.get_scope_link());
        AST_t defAst = funct_def.get_ast();
        Source emptySource,emptySourceVar;
        emptySourceVar <<"deletedFunctionBodyNamed_"<<it->get_name();
       
        int finded=0;
        int aux = 0;
        for (ObjectList<string>::iterator it1 = _deletedFuncs.begin(); it1 != _deletedFuncs.end(); it1++, aux++) {
           if(std::string(it->get_name()).compare(_deletedFuncs[aux])==0)
               finded=1;
        }
       if(!finded) {
            emptySource<<"int "<<emptySourceVar<<" = 1;";
            AST_t emptyAst = emptySource.parse_statement(defAst, expr.get_scope_link());
            defAst.replace_with(emptyAst);
             _deletedFuncs.push_back(it->get_name());
        }
   
    }
   
}

/**
 *
 * @param function_def  function that contains function calls that will be inlined.
 *                      This means that this function will is actually the callsite
 *                      of the called functions, and that this is the place were
 *                      the code (from the inlined functions) will be written to
 * @param scope_link
 */
void InlinePhase::find_functions(FunctionDefinition function_def, ScopeLink scope_link) {
    FunctionCallsPred function_calls_pred(scope_link);
    Statement function_body = function_def.get_function_body();

    ObjectList<AST_t> list_of_calls = function_body.get_ast().depth_subtrees(function_calls_pred);

    for (ObjectList<AST_t>::iterator it = list_of_calls.begin(); it != list_of_calls.end(); it++, _callNum++) {
//        cout<<_callNum<<endl;
        AST_t element = *it;


        Expression expr(element, scope_link);
        
        // We already know it is a function call, no need to check again
        Expression _function_call = expr.get_called_expression();
        Expression last_function_call = _function_call;
        set_FCall(&_function_call);
        
//        cin.get();
        if (_function_call.is_id_expression()) {

            IdExpression id_expr = _function_call.get_id_expression();
            Symbol called_sym = id_expr.get_symbol();
            Symbol last_called_sym =  called_sym;
            set_FSym(&called_sym);
//            cout<<called_sym.is_valid()<<endl;
//            cout<<called_sym.is_function()<<endl;
//            cout<<called_sym.is_defined()<<endl;
           cout<<"HI"<<endl;
            if (called_sym.is_valid() && called_sym.is_function() && called_sym.is_defined()) {
                cout << "\nFinding if necessary forward inline for function '" << id_expr << "' in " << element.get_locus() << "\n";
                _functionName = called_sym.get_name();
                _rowOfCall = element.get_line();
                int fnd = 0;
                for(int fN = 0; fN<_inlinedFunctions.size();++fN){
                    if(_inlinedFunctions[fN].get_name().compare(std::string(_functionName))==0){
                     fnd = 1;
                     break;
                    }
                }
               
                if(!fnd) {
                     _inlinedFunctions.push_back(called_sym);
                    cout << "\nForward inline of "<<called_sym.get_name()<<" called on: "<<function_def.get_function_name().get_symbol().get_name()<<" \n";
                    ObjectList<AST_t> list_of_fun_defs = _translation_unit.depth_subtrees(_function_def_pred);
                    for (ObjectList<AST_t>::iterator it = list_of_fun_defs.begin(); it != list_of_fun_defs.end(); it++) {
                        FunctionDefinition function_defNF(*it, scope_link);
                        TL::Symbol function_sym = function_defNF.get_function_symbol();
                        if(function_sym.get_name().compare(called_sym.get_name())==0) {
                            find_functions(function_defNF,scope_link);
                            set_FCall(&last_function_call);
                            set_FSym(&last_called_sym);
//                            cout<<"HI2s"<<endl;
                        }
                    }
                }
                cout << "\nApplying inlining for function" << called_sym.get_name() << "\n {";
                inlineFunction(called_sym, expr);
                cout<<"} \n";
            } else if(called_sym.is_defined()){
                cerr << "************************************"<<
                        "\n You can not use "<<called_sym.get_name()<<"inside HMPP codelet.\n"
                     << "************************************";
                exit(-1);
            }
        }
    }
    if(list_of_calls.size()==0) {
        cout<<"} \n No function calls in : "<<function_def.get_function_name().get_symbol().get_name()<<endl;
    } else {
        cout<<"} \n"<<function_def.get_function_name().get_symbol().get_name()<< " finished -------------"<<endl;
    }
}

/**
 *
 * @param called_sym    symbol of the called function that will be inlined
 * @param expr          expression that we build with the function invocation
 *                      substituted by function body
 */
void InlinePhase::inlineFunction(Symbol& called_sym, Expression& expr) {


    //////////////////////////////////////////7

    Symbol _function_symbol = called_sym;
   
    AST_t definition_tree = _function_symbol.get_definition_tree();
    FunctionDefinition funct_def(definition_tree, expr.get_scope_link());
    Statement funct_body = funct_def.get_function_body();
    Scope funct_scope = funct_def.get_scope();
    Scope funct_scopeB = funct_body.get_scope();
     
    Source result;
    Source parameter_declarations,
            inlined_function_body,
            return_code;

    ////////////////////////////Parameter Declaration
    Type function_type = _function_symbol.get_type();

    bool has_ellipsis = false;
    ObjectList<Type> parameters = function_type.parameters(has_ellipsis);

    ObjectList<Symbol> param_symbols;
    getParamSymbols(param_symbols, funct_scopeB);
    set_PSym(&param_symbols);
   
    getParamDeclaration(parameter_declarations, function_type, funct_scope, expr, param_symbols, funct_body);

   
    ////////////////////////////Solve Return Type
    solve_return(function_type, parameter_declarations, return_code, funct_scope);

    ////////////////////////////Arbre d'execucio
//    cout<<funct_body.get_ast().prettyprint()<<endl;
    const char *c = prettyprint_in_buffer_callback(funct_body.get_ast().get_internal_ast(),
            &InlinePhase::inline_prettyprint_callback, (void*) this);
//    cout<<"HI2"<<endl;
    if (c != NULL) {
        inlined_function_body << std::string(c);
    }
   
    Source resultR;
    resultR
            << parameter_declarations << "\n"
            << inlined_function_body << "\n"
            << return_code << "\n";

   
    /////////////////////////Replace Call
    replace_call(funct_def, expr, resultR);

    set_FCall(NULL);
    set_FSym(NULL);
    set_PSym(NULL);
    _referenceVars.clear();

}

/**
 *
 * @param param_symbols List of symbols inside the body
 * @param funct_scopeB  Body Scope
 */
void InlinePhase::getParamSymbols(ObjectList<Symbol> &param_symbols, Scope& funct_scopeB) {
    ObjectList<Symbol> possible_params = funct_scopeB.get_all_symbols(0);
    int j = 0;
    for (ObjectList<Symbol>::iterator itu = possible_params.begin();
            itu != possible_params.end();
            itu++, j++) {
        if (itu->is_parameter() == 1) {
            param_symbols.append(possible_params[j]);
        }
    }

}

/**
 *
 * @param parameter_declarations
 * @param function_type
 * @param funct_scope Ambit
 * @param expr Valors de crida
 * @param param_symbols Simbols
 * @param funct_body
 */
void InlinePhase::getParamDeclaration(Source& parameter_declarations,
        Type function_type,
        Scope& funct_scope,
        Expression& expr,
        ObjectList<Symbol>& param_symbols,
        Statement funct_body) {
   
    ObjectList<Expression> arguments = expr.get_argument_list();
    int i = 0;
    bool has_ellipsis = false;
    ObjectList<Type> parameters = function_type.parameters(has_ellipsis);
    for (ObjectList<Type>::iterator it = parameters.begin();
            it != parameters.end();
            it++, i++) {
        Source param_name;
        Source init;
        Source declaration;
        string realDeclaration;
        _varid++;
        param_name
                << "_p_" << i << "_" << _functionName << "_" << _callNum;
        realDeclaration =std::string(it->get_declaration(funct_scope,
                param_name));
        size_t andpersand = std::string(realDeclaration).find("&");
       
        if(andpersand>0 && andpersand < realDeclaration.length()) {
            realDeclaration.replace(realDeclaration.find("&"), 1, "*");
            init << "= &" << arguments[i];
           
            _referenceVars.insert(param_name);
        } else {
           
            init << "=" << arguments[i];
        }
       declaration << realDeclaration;
       
       
        parameter_declarations
                <<declaration
                << init
                << ";"
                ;

    }
     
}

/**
 *
 * @param function_type Type of return
 * @param parameter_declarations New parameter declarations including agrument inlineing
 * @param return_code Function return code crated
 * @param funct_scope Ambit
 */
void InlinePhase::solve_return(Type function_type,
        Source& parameter_declarations,
        Source& return_code,
        Scope& funct_scope) {
    Type return_type = function_type.returns();
    Source nameRet;
    if (return_type.is_valid()
            && !return_type.is_void()) {
    _retid++;
   
    nameRet<<"_return_" << _callNum;
   
   
        // This is only valid in C, in C++ we will use an aligned char and a
        // new with placement
        parameter_declarations
                << return_type.get_declaration(funct_scope,
                nameRet) << ";";

    } else {
         nameRet<<"";
    }
    _nameReturn = nameRet;
   
}

/**
 *
 * @param inline_source_tree
 * @param funct_def
 * @param expr
 * @param result
 */
void InlinePhase::replace_call(FunctionDefinition funct_def,
        Expression &expr,
        Source &result) {

    TL::AST_t inline_source_tree;
    ScopeLink sl = expr.get_scope_link();
    AST_t fAst = expr.get_ast();
    std::cout<<std::string(_nameReturn)<<"\n";
    if(std::string(_nameReturn).compare("")!=0){
        inline_source_tree = _nameReturn.parse_expression(fAst, sl);
        expr.get_ast().replace(inline_source_tree);
        inline_source_tree = result.parse_statement(fAst, sl);
        expr.get_ast().prepend(inline_source_tree);
    } else {
        inline_source_tree = result.parse_statement(fAst, sl);
        expr.get_ast().replace(inline_source_tree);
       
    }
}

void InlinePhase::set_FCall(Expression* _function_call2add) {
    _function_call = _function_call2add;
}

void InlinePhase::set_FSym(Symbol* _function_symbol2add) {
    _function_symbol = _function_symbol2add;
}

void InlinePhase::set_PSym(ObjectList< Symbol>* param_symbols2add) {
    param_symbols = param_symbols2add;
}

void InlinePhase::phase_cleanup(DTO& data_flow) {

}

Expression* InlinePhase::get_FCall() {
    return _function_call;
}

Symbol* InlinePhase::get_FSym() {

    return _function_symbol;
}

ObjectList< Symbol>* InlinePhase::get_PSym() {

    return param_symbols;
}

const char* InlinePhase::inline_prettyprint_callback(AST _a, void* data) {
    AST_t a(_a);
    
    InlinePhase* _this = reinterpret_cast<InlinePhase*> (data);
    Expression function_call = *_this->get_FCall();
    Symbol function_symbol = *_this->get_FSym();
    if (ReturnStatement::predicate(a)) {
        std::cout<<a.prettyprint(false)<<"\n";
        return solve_result_predicate(a, &function_call, &function_symbol, data);
    } else if (IdExpression::predicate(a)) {
        std::cout<<a.prettyprint(false)<<"\n";
        return solve_predicate(a, function_call, function_symbol, data);
    } else
        return NULL;
}

const char* InlinePhase::solve_predicate(AST_t a, Expression function_call, Symbol function_symbol, void* data) {
    InlinePhase* _this = reinterpret_cast<InlinePhase*> (data);
    IdExpression id_expr(a, (function_call).get_scope_link());

    Symbol sym = id_expr.get_symbol();
   
    if (sym.is_parameter()) {
        Source src,paramName;
        paramName << "_p_" << sym.get_parameter_position() << "_" << _this->_functionName << "_" << _this->_callNum;
        //TODO, if is in reference variables array, put * before

        bool ref = _this->is_reference(paramName);
        if(ref) {
                src << "*";
        }
        src << paramName;
        return uniquestr(src.get_source().c_str());
    } else if ((function_symbol).is_member()
            && id_expr.is_unqualified()
            && sym.is_member()
            && sym.get_class_type().is_same_type((function_symbol).get_class_type())) {
        Source src;
        src << "_this." << id_expr;

        return uniquestr(src.get_source().c_str());
    } else
        return NULL;
}

const char* InlinePhase::solve_result_predicate(AST_t a, Expression* function_call, Symbol* function_symbol, void* data) {
    Type function_type = (*function_symbol).get_type();
    Type return_type = function_type.returns();
    Source src;
    if (return_type.is_valid() && !return_type.is_void()) {
       
        ReturnStatement ret_stmt(a, (*function_call).get_scope_link());

        Expression expr = ret_stmt.get_return_expression();
        Source exprSrc, nameRet;


        InlinePhase* _this = reinterpret_cast<InlinePhase*> (data);

            nameRet<<"ret_"<<(*function_call).prettyprint()<<_this->_callNum;

            exprSrc << ""
                    << return_type.get_declaration((*function_call).get_scope(),
                    std::string(nameRet))  <<";";


            exprSrc << std::string(nameRet)<<" = "<< expr.prettyprint() << ";\n";

        AST_t retAst = exprSrc.parse_statement(expr.get_ast(), (*function_call).get_scope_link());

        const char *c = prettyprint_in_buffer_callback(retAst.get_internal_ast(),
                &InlinePhase::inline_prettyprint_callback, data);

        src
        << std::string(c)
        <<_this->_nameReturn <<" = "<< std::string(nameRet) <<";"
        ;


    }
    return uniquestr(src.get_source().c_str());

}


bool InlinePhase::is_reference(Source name) {
   
    for (unsigned int i=0;i<_referenceVars.size();i++) {
        if(std::string(_referenceVars[i]).compare(std::string(name))==0)
            return true;
    }
    return false;
}


EXPORT_PHASE(InlinePhase);

