/*--------------------------------------------------------------------
 (C) Copyright 2006-2011 Barcelona Supercomputing Center
 Centro Nacional de Supercomputacion
 
 This file is part of Mercurium C/C++ source-to-source compiler.
 
 See AUTHORS file in the top level directory for information
 regarding developers and contributors.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.
 
 Mercurium C/C++ source-to-source compiler is distributed in the hope
 that it will be useful, but WITHOUT ANY WARRANTY; without even the
 implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the GNU Lesser General Public License for more
 details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with Mercurium C/C++ source-to-source compiler; if
 not, write to the Free Software Foundation, Inc., 675 Mass Ave,
 Cambridge, MA 02139, USA.
 --------------------------------------------------------------------*/



#include "hlt-outline.hpp"
#include "hlt-exception.hpp"
#include "cxx-utils.h"
#include "tl-traverse.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <fstream>


using namespace TL::HLT;

int Outline::_num_outlines = 0;

Outline::Outline(ScopeLink sl, Statement stmt)
: _sl(sl),
        _function_def(NULL),
        _packed_arguments(false),
        _do_not_embed(false),
        _use_nonlocal_scope(false),
        _outline_performed(false),
        _overriden_outline_name(false),
        _default_parameter_passing(POINTER) {
    _outline_statements.append(stmt);
    
    set_cod_trans(0, 0);
    _exec=0;
}
Outline::Outline(ScopeLink sl, Statement stmt, ObjectList <std::string> unchanged, int out_num)
: _sl(sl),
        _function_def(NULL),
        _packed_arguments(false),
        _do_not_embed(false),
        _use_nonlocal_scope(false),
        _outline_performed(false),
        _overriden_outline_name(false),
        _default_parameter_passing(POINTER) {
    _outline_statements.append(stmt);
    set_cod_trans(0, 0);
    _exec=0;
    _unchanged_vars = unchanged;
    _real_outline = 1;
    _outline_num=out_num;
    
}
Outline::Outline(ScopeLink sl, Statement stmt, int out_num)
: _sl(sl),
        _function_def(NULL),
        _packed_arguments(false),
        _do_not_embed(false),
        _use_nonlocal_scope(false),
        _outline_performed(false),
        _overriden_outline_name(false),
        _default_parameter_passing(POINTER) {
    _outline_statements.append(stmt);
    set_cod_trans(0, 0);
    _exec=0;
    _outline_num=out_num;
    
}
Outline::Outline(ScopeLink sl, ObjectList<Statement> stmt_list, int out_num)
: _sl(sl),
        _function_def(NULL),
        _packed_arguments(false),
        _do_not_embed(false),
        _use_nonlocal_scope(false),
        _outline_statements(stmt_list),
        _outline_performed(false),
        _overriden_outline_name(false),
        _default_parameter_passing(POINTER) {
    set_cod_trans(0, 0);
    _exec=0;
    _real_outline = 0;
    _outline_num = out_num;
    
    
}
void Outline::set_cod_trans(int cod, int trans) {
    _cod = cod;
    _trans = trans;
}

void Outline::set_allocate(AST_t allocateAst, ScopeLink allocateScopeLink) {
    _allocateAst = allocateAst;
    _allocateScopeLink = allocateScopeLink;
}
TL::Source Outline::get_source() {
    do_outline();
    
    if (!_do_not_embed) {
        // Now embed the outline
        embed_outline();
    }
    
    return _outlined_source;
}

Outline& Outline::use_packed_arguments() {
    _packed_arguments = true;
    return *this;
}

Outline& Outline::do_not_embed() {
    _do_not_embed = true;
    return *this;
}
void Outline::set_unchanged_vars(ObjectList<std::string> unchanged){
    _unchanged_vars = unchanged;
}
TL::ObjectList<TL::Symbol> Outline::recomputeParameters(){
    compute_referenced_entities();
    //    std::cout<<"*****OS"<<_outline_statements[0].prettyprint()<<std::endl;
    //    std::cout<<"Parameters: "<<_parameter_passed_symbols.size()<<std::endl;
    //    for(int i=0;i<_parameter_passed_symbols.size();++i){
    //        std::cout<<i<<": "<<_parameter_passed_symbols[i].get_name()<<std::endl;
    //    }
    //    
    //    std::cin.get();
    return _parameter_passed_symbols;
}
void Outline::do_outline() {
    if (_outline_performed)
        return;
    //    _outline_num=_outline_statements[0].get_ast().get_line(); 
    //    std::cout<<_outline_num<<std::endl;
    //    std::cin.get();
    _outline_performed = true;
    //std::cout<<"+sddasdRO: "<<_real_outline<<std::endl;
    if(_exec==0 && _real_outline){
        // We can start building the outline code
        Source template_headers,
                template_headers_fwd,
                required_qualification,
                outline_parameters,
                outline_body,
                static_qualifier,
                forward_declarations;
        Source startIN, separationIN, finalIN; 
        Source startOUT, separationOUT, finalOUT;
        Source startOUT2, separationOUT2, finalOUT2;
        Source pragma_instruction,pragma_instrucion_addition, outv, intv, outv2, intv2, gridify_text, reduced_vars_redeclaration, reduced_vars_recover;
        
        _exec=1;
        _outlined_source
                << forward_declarations
                << template_headers
                << static_qualifier
                << pragma_instruction << pragma_instrucion_addition <<"\n"
                << "void " << required_qualification << _outline_name
                << "(" << outline_parameters << ")"
                << "{" 
                << reduced_vars_redeclaration
                << gridify_text
                << outline_body 
                << reduced_vars_recover   
                << "}"
                ;
        if(!red_string.empty()){
            reduced_vars_redeclaration = get_reduced_vars_redeclaration();
            reduced_vars_recover = get_reduced_vars_recover(); 
            gridify_text = find_grid(_sl.get_scope(_outline_statements[0].get_ast()));
        }
       
        
        //   std::cout<<"Number of UnChangedVars : "<<_unchanged_vars.size();
        //        for(int a=0;a<_unchanged_vars.size();++a){
        //            if(a==0)
        //                std::cout<<"->(";
        //            else if(_unchanged_vars.size()>1)
        //                std::cout<<", ";
        //            std::cout<<_unchanged_vars[a];     
        //        }
        Source groupName;
        std::ifstream groupFileR("inGroup.data");
        std::string lineF;
        getline(groupFileR, lineF);
        int inG = atoi(lineF.c_str());
        if(inG){
            std::ifstream outFun("numTransform.data");
            std::string num;
            getline(outFun, num);
            int numTransform = atoi(num.c_str());
            outFun.close();
            std::ifstream groupFileR("numGroup.data");
            std::string line;
            getline(groupFileR, line);
            int numG = atoi(line.c_str());
            groupFileR.close();
            groupName << "<group"<<numG<<"_"<<numTransform<<"> ";
        }
        //        //#pragma hmpp codeletname codelet, target = CUDA, args[array].io=inout, args[array].size={row * col}
        Source sizeS, target;
        if(!inG)
            target << ", target = CUDA:OPENCL";
        pragma_instruction << "#pragma hmpp " <<groupName<< _outline_name <<" codelet"
                << target
                << outv
                << sizeS
                << intv;
        startIN << "args[";
        separationIN << ",";
        finalIN << "].io=in";
//         std::cout<<"HAHA"<<std::endl;
//        std::cin.get();
        intv = get_parameter_in(_sl.get_scope(_outline_statements[0].get_ast()), startIN, separationIN, finalIN);
        startOUT << "args[";
        separationOUT << ",";
        finalOUT << "].io=inout";
        outv = get_parameter_io(_sl.get_scope(_outline_statements[0].get_ast()), startOUT, separationOUT, finalOUT);

        sizeS = get_parameter_sizes(_sl.get_scope(_outline_statements[0].get_ast()));

        
        if (!red_string.empty()) {
            Source reducedVarsSize;
            
            reducedVarsSize = get_reduced_vars_sizes();
            pragma_instruction << reducedVarsSize;
            
        }
        
        std::cout<<"Trans: "<<_trans<<" Cod: "<<_cod<<std::endl;
        //        std::cin.get();
        if (_trans == 1 && (_cod==0 || _cod==1)) {
            //        #pragma codelet, &
            //        #pragma hmpp & args[*].transfer=auto
            if(red_string.empty())
                pragma_instruction << ", & \n #pragma hmpp & args[*].transfer=auto";
            else {
                Source i,o,emptyS;
                i<<"";
                o<<"";
                separationOUT << ",";
                i = get_parameter_in(_sl.get_scope(_outline_statements[0].get_ast()), emptyS, separationOUT, emptyS);
                o = get_parameter_io(_sl.get_scope(_outline_statements[0].get_ast()), emptyS, separationOUT, emptyS);
                
                
                int started =0;
                if(!o.empty()) {
                    std::string realO;
                    realO= std::string(o).substr(std::string(o).find_first_of(", ")+2,std::string(o).length());
                    //                std::cout<<"o: "<<std::string(realO)<<std::endl;
                    pragma_instruction << ", & \n #pragma hmpp & args["<<realO;
                    started=1;
                }
                if(!i.empty()) {
                    std::string realI;
                    realI= std::string(i).substr(std::string(i).find_first_of(", ")+2,std::string(i).length());
                    //                std::cout<<"i: "<<std::string(realI)<<std::endl;
                    if(started)
                        pragma_instruction<<", "<<realI;
                    else
                        pragma_instruction << ", & \n #pragma hmpp & args["<<realI;
                    started=1;
                }
                
                if(started)
                    pragma_instruction<<"].transfer=auto";
            }
        }
        
        Source transStart, transSep, transFin;
        
        if (_trans == 2 && _cod==0) {
            //        <<args[invar].transfer=atcall
            pragma_instrucion_addition
                    << intv2;
            transStart << "args[";
            transSep << ",";
            transFin << "].transfer=atcall";
            intv2 = get_parameter_in(_sl.get_scope(_outline_statements[0].get_ast()), transStart, transSep, transFin);
        } 
        
        if (_trans == 3 && _cod==0) {
            //<<args[outvar].transfer=atcall
            pragma_instrucion_addition
                    << outv2;
            startOUT2 << "args[";
            separationOUT2 << ",";
            finalOUT2 << "].transfer=atcall";
            outv2 = get_parameter_io(_sl.get_scope(_outline_statements[0].get_ast()), startOUT2, separationOUT2, finalOUT2);
        }
        if (_trans == 4 && _cod==0) {
            //args[outvar].transfer=atfirstcall, args[invar].transfer=atcall
            pragma_instrucion_addition
                    << outv2
                    << intv2;
            transStart << "args[";
            transSep << ",";
            transFin << "].transfer=atcall";
            intv2 = get_parameter_in(_sl.get_scope(_outline_statements[0].get_ast()), transStart, transSep, transFin);
            startOUT2 << "args[";
            separationOUT2 << ",";
            finalOUT2 << "].transfer=atfirstcall";
            outv2 = get_parameter_io(_sl.get_scope(_outline_statements[0].get_ast()), startOUT2, separationOUT2, finalOUT2);
        }
        if (_trans == 5 && _cod==0) {
            //args[invar].transfer=atfirstcall, args[outvar].transfer=atcall
            
            pragma_instrucion_addition
                    << intv2
                    << outv2;
            transStart << "args[";
            transSep << ",";
            transFin << "].transfer=atfirstcall";
            intv2 = get_parameter_in(_sl.get_scope(_outline_statements[0].get_ast()), transStart, transSep, transFin);
            //std::cout<<std::string(intv)<<std::endl;
            startOUT2 << "args[";
            separationOUT2 << ",";
            finalOUT2 << "].transfer=atcall";
            outv2 = get_parameter_io(_sl.get_scope(_outline_statements[0].get_ast()), startOUT2, separationOUT2, finalOUT2);
            
        }
        // This gets some information about the enclosing function
        compute_outline_name(template_headers_fwd, template_headers,
                required_qualification, static_qualifier);
        
        // Now find out all the required symbols
        compute_referenced_entities();
        
        outline_parameters = get_parameter_declarations(_sl.get_scope(_outline_statements[0].get_ast()));
        
        
        
        if (!_enclosing_function.is_member()) {
            compute_additional_declarations(template_headers_fwd, _sl.get_scope(_outline_statements[0].get_ast()));
        } else {
            // Additional declarations will go inside the class
            compute_additional_declarations(template_headers_fwd, _enclosing_function.get_class_type().get_symbol().get_scope());
        }
        
        compute_outlined_body(outline_body);
        int j=0;
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Symbol paramSymbol = _sl.get_scope(_outline_statements[0].get_ast()).get_symbol_from_name(_parameter_passed_symbols[j].get_name());
            if(!is_reduced(paramSymbol.get_name())) {
                _correspondence_table[_parameter_passed_symbols[j].get_name()]=paramSymbol;
                std::string actN = _parameter_passed_symbols[j].get_name();
                //                    std::cout<<"_correspondence_table["<<actN<<"] ->"<<_correspondence_table[actN].get_name()<<std::endl;
            }
        }
        if (!red_string.empty()) {
            std::string act,workingString;
            workingString=red_string;
            while(workingString.find_first_of(":")>=0 && workingString.find_first_of(":")<workingString.length()) {
                //std::cout <<"n: "<<num<<std::endl;
                if(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
                    act = workingString.substr(workingString.find_first_of(":")+1,workingString.find_first_of(",")-1);
                    workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
                } else {
                    act = workingString.substr(workingString.find_first_of(":")+1,workingString.length());
                    workingString = "";
                }
                std::stringstream actSS;
                actSS << act << "_reduced";
                //            std::cout<<act<<" is reduced<<std::endl;
                //            std::cin.get();
                _correspondence_table[actSS.str()]=_sl.get_scope(_outline_statements[0].get_ast()).get_symbol_from_name(act);;
                //      std::cout<<"_correspondence_table["<<actSS.str()<<"] ->"<<_correspondence_table[actSS.str()].get_name()<<std::endl;
            }
        }
        //    std::cin.get();
        if (_is_member) {
            if (!_is_inlined_member) {
                // For non inlined member functions we need some more things
                declare_members(template_headers_fwd);
            } else {
                fill_member_forward_declarations(template_headers_fwd, forward_declarations);
            }
        } else if (!_is_member) {
            fill_nonmember_forward_declarations(template_headers_fwd, forward_declarations);
        }
    }
    //_unchanged_vars.clear();
}

static std::string template_header_regeneration(TL::TemplateHeader template_header) {
    using namespace TL;
    ObjectList<std::string> template_parameters
            = template_header.get_parameters().map(
            functor<std::string, TemplateParameterConstruct > (&LangConstruct::prettyprint)
            );
    
    return "template <" + concat_strings(template_parameters, ",") + " >";
}

void Outline::compute_outline_name(Source &template_headers_fwd,
        Source &template_headers,
        Source &required_qualification,
        Source &static_qualifier) {
    // Note: We are assuming all statements come from the same function
    // definition
    // This disqualifies empty lists of statements
    _function_def = new FunctionDefinition(_outline_statements[0].get_enclosing_function());
    _enclosing_function = _function_def->get_function_symbol();
    
    _is_member = _enclosing_function.is_member();
    
    IdExpression id_expr = _function_def->get_function_name();
    
    // FIXME - This is a bit lame
    _is_inlined_member = (!id_expr.is_qualified() && _is_member);
    
    if (id_expr.is_qualified()) {
        required_qualification
                << id_expr.get_qualified_part()
                ;
    }
    
    _is_templated = _function_def->is_templated();
    _has_linkage_specifier = _function_def->has_linkage_specifier();
    if (_is_templated) {
        _template_header = _function_def->get_template_header();
        
        template_headers <<
                concat_strings(_template_header.map(functor(template_header_regeneration)))
                ;
        
        if (!_is_member) {
            template_headers_fwd << template_headers;
        } else {
            if (_enclosing_function.get_class_type()
                    .get_symbol().get_type().is_template_specialized_type()) {
                
                ObjectList<TemplateHeader> one_less_template_header(_template_header.begin() + 1, _template_header.end());
                template_headers_fwd <<
                        concat_strings(one_less_template_header.map(functor(template_header_regeneration)))
                        ;
            } else {
                template_headers_fwd << template_headers;
            }
        }
    } else if (_has_linkage_specifier) {
        ObjectList<LinkageSpecifier> linkage_specifiers = _function_def->get_linkage_specifier();
        template_headers_fwd << concat_strings(linkage_specifiers, " ");
    }
    
    if (!_overriden_outline_name) {
        _outline_name
                << "_ol_" << _outline_num << "_" << _enclosing_function.get_name()
                ;
    }
    
    if (_is_member && _is_inlined_member) {
        static_qualifier = Source("static ");
    }
}

static void get_referenced_entities(TL::Statement stmt, TL::ObjectList<TL::Symbol>* entities) {
    TL::ObjectList<TL::IdExpression> local_list = stmt.non_local_symbol_occurrences(TL::Statement::ONLY_VARIABLES);
    entities->insert(local_list.map(functor(&TL::IdExpression::get_symbol)));
}




struct GetDeclarationInScope {
private:
    Outline& _outline;
    TL::Scope _sc;
public:
    
    GetDeclarationInScope(Outline& outline, TL::Scope sc)
    : _outline(outline), _sc(sc) {
    }
    
    std::string operator()(TL::Symbol sym) {
        Outline::ParameterPassing passing = _outline.get_parameter_passing(sym);
        
        TL::Type type = sym.get_type();
        TL::Type aux_type = sym.get_type();
        int red=0;
        int notlocal=0;
        red = _outline.is_reduced(sym.get_name());
        //std::cout<<"Name: "<<sym.get_name()<<std::endl;
        if (passing == Outline::POINTER) {
            // std::cout<<"p1: "<<sym.get_name()<<std::endl;
            if (type.is_array()) {
                //       std::cout<<"p2: "<<sym.get_name()<<std::endl;
                aux_type = type.array_element();
                
                //If matrix
                if (aux_type.is_array() ) {
                    //        std::cout<<"p3: "<<sym.get_name()<<std::endl;
                    //   std::cout<<"m: "<<sym.get_name()<<std::endl;
                    aux_type = type;
                } else {
                    //      std::cout<<"p4: "<<sym.get_name()<<std::endl;
                    //If array
                    //  std::cout<<"a: "<<sym.get_name()<<std::endl;
                    aux_type = type.array_element();
                    aux_type = aux_type.get_pointer_to();
                    
                    // array[size]
                    //aux_type = type;
                }
                
                
                
            } else if(red){
                //                std::cout<<sym.get_name()<<" is reduced"<<std::endl;
                aux_type =  aux_type.get_pointer_to();
            } else if(sym.get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && sym.get_point_of_declaration().prettyprint(true).find_first_of("[")<sym.get_point_of_declaration().prettyprint(true).length()) {
                notlocal=1;
                // std::cout<<"p4: "<<sym.get_name()<<std::endl;
                
                //aux_type =  _sc.get_symbol_from_name(sym.get_name()).get_type();
            }
            
        } 
        
        
        
        TL::Source returnSource;
        if (notlocal)
            returnSource<<sym.get_point_of_declaration().prettyprint(true);
        else
            returnSource <<aux_type.get_declaration(_sc, sym.get_name());
        if(red){
            returnSource<<"_reduced";
        }
        //std::cout<<std::string(returnSource)<<std::endl;
        //std::cin.get(); //pausa
        return std::string(returnSource);
    }
};


struct GetFieldDeclarations : public GetDeclarationInScope {
private:
    TL::Source _src;
public:
    
    GetFieldDeclarations(Outline& outline, TL::Scope sc, TL::Source & src)
    : GetDeclarationInScope(outline, sc),
            _src(src) {
    }
    
    void operator()(TL::Symbol sym) {
        _src << GetDeclarationInScope::operator()(sym) << ";";
    }
};

static bool is_local_or_nonstatic_member(const TL::Symbol& sym) {
    return sym.has_local_scope()
            || (sym.is_member() && !sym.is_static());
}


void Outline::compute_additional_declarations(Source template_headers,
        Scope scope_of_decls) {
    if (_packed_arguments) {
        Source arg_typename;
        
        CXX_LANGUAGE() {
            if (_enclosing_function.get_type().is_template_specialized_type()) {
                _additional_decls_source
                        << template_headers
                        ;
            }
        }
        
        arg_typename
        << "struct _arg_pack_" << _outline_num << "_t"
                ;
        
        C_LANGUAGE() {
            _packed_argument_typename << arg_typename;
        }
        
        CXX_LANGUAGE() {
            _packed_argument_typename << "_arg_pack_" << _outline_num << "_t";
            
            if (_enclosing_function.get_type().is_template_specialized_type()) {
                TemplateHeader& last_template_header = *(_template_header.rbegin());
                
                _packed_argument_typename
                        << "<"
                        << concat_strings(last_template_header.get_parameters().map(functor(&TemplateParameterConstruct::get_name)), ",")
                        << ">"
                        ;
            }
        }
        
        Source fields;
        _additional_decls_source
                << arg_typename
                << "{"
                << fields
                << "};"
                ;
        
        if (_enclosing_function.is_member()
                && !_enclosing_function.is_static()) {
            Type ptr_class_type = _enclosing_function.get_class_type();
            
            Type enclosing_function_type = _enclosing_function.get_type();
            
            if (enclosing_function_type.is_const()) {
                ptr_class_type = ptr_class_type.get_const_type();
            }
            
            //if(!ptr_class_type.is_array())
            ptr_class_type = ptr_class_type.get_pointer_to();
            
            fields
                    << ptr_class_type.get_declaration(scope_of_decls, "_this") << ";"
                    ;
        }
        
        std::for_each(_parameter_passed_symbols.begin(), _parameter_passed_symbols.end(),
                GetFieldDeclarations(*this, scope_of_decls, fields));
        
    }
}

int Outline::get_outline_num(){
    return _outline_num;
}
int Outline::is_reduced(std::string name){
    std::string act, workingString;
    if(std::string(red_string).find(":")>=0 && std::string(red_string).find(":")<std::string(red_string).length()){
        //        std::cin.get();
        workingString = std::string(red_string).substr(std::string(red_string).find_first_of(":")+1,std::string(red_string).length());
        while(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
            act = workingString.substr(0,workingString.find_first_of(",")-1);
            //            std::cout<<"c: -"<<name<<"- -"<<act<<"-"<<std::endl;
            workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
            if(act.compare(name)==0) {
                //                std::cout<<"OK"<<std::endl;
                return 1;
            }
        }
        if(!workingString.empty()) { 
            act = workingString;
            //            std::cout<<"c: -"<<name<<"- -"<<act<<"-"<<std::endl;
            if(act.compare(name)==0) {
                //                std::cout<<"OK"<<std::endl;
                return 1;
            } 
        }
        //        std::cout<<"FALSE"<<std::endl;
        //        std::cin.get();
        return 0;
    }
    //    std::cout<<"Not reduced variables to compare\n";
    return 0;
}
TL::Source Outline::get_reduced_vars_redeclaration(){
    Source text;
    Scope funct_scope = _outline_statements[0].get_scope();
    std::string act, realDeclaration, workingString;
    workingString = std::string(red_string).substr(std::string(red_string).find_first_of(":")+1,std::string(red_string).length());
    //std::cout<<"****************____¿****************"<<std::endl;
    while(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
        act = workingString.substr(0,workingString.find_first_of(",")-1);
        workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
        realDeclaration =std::string(funct_scope.get_symbol_from_name(act).get_type().get_declaration(funct_scope,
                act));
        text << realDeclaration <<" = *"<<act<<"_reduced;\n";
    }
    if(!workingString.empty()) {
        act = workingString;
        realDeclaration =std::string(funct_scope.get_symbol_from_name(act).get_type().get_declaration(funct_scope,
                act));
        text << realDeclaration <<" = *"<<act<<"_reduced;\n";
    }
    //std::cout<<std::string(text)<<std::endl;
    //std::cin.get(); //pausa
    return text;
}
TL::Source Outline::get_reduced_vars_recover(){
    Source text;
    std::string act, workingString;
    workingString = std::string(red_string).substr(std::string(red_string).find_first_of(":")+1,std::string(red_string).length());
    while(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
        act = workingString.substr(0,workingString.find_first_of(",")-1);
        workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
        text << "*" << act <<"_reduced = "<<act<<";\n";
    }
    if(!workingString.empty()) {
        act = workingString;
        text << "*" << act <<"_reduced = "<<act<<";\n";
        //std::cout<<std::string(text)<<std::endl;
        // std::cin.get(); //pausa
    }
    return text;
}
TL::Source Outline::get_reduced_vars_sizes(){
    Source reduced_vars;
    reduced_vars <<", args[";
    std::string workingString=std::string(red_string);
    int num=0;
    std::string act;
    while(workingString.find_first_of(":")>=0 && workingString.find_first_of(":")<workingString.length()) {
        //std::cout <<"n: "<<num<<std::endl;
        if(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.find_first_of(",")-1);
            workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
        } else {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.length());
            workingString = "";
        }
        //  std::cout << act <<std::endl;
        if(num==0)
            reduced_vars<< act<<"_reduced";
        else
            reduced_vars<<", "<<act <<"_reduced";
        num++;
    }
    
    reduced_vars <<"].io=inout, args[";
    workingString=std::string(red_string);
    num=0;
    while(workingString.find_first_of(":")>=0 && workingString.find_first_of(":")<workingString.length()) {
        //std::cout <<"n: "<<num<<std::endl;
        if(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.find_first_of(",")-1);
            workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
        } else {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.length());
            workingString = "";
        }
        //  std::cout << act <<std::endl;
        if(num==0)
            reduced_vars<< act<<"_reduced";
        else
            reduced_vars<<", "<<act<<"_reduced";
        num++;
    }
    reduced_vars <<"].size={1}";
    //std::cout<<std::string(reduced_vars)<<std::endl;
    return reduced_vars;
}

TL::Source Outline::get_reduced_vars_sizes_specific(std::vector<std::string> red_s){
    Source reduced_vars;
    reduced_vars <<", args[";
    std::string workingString=std::string(red_string);
    int num=0;
    std::string act;
    while(workingString.find_first_of(":")>=0 && workingString.find_first_of(":")<workingString.length()) {
        //std::cout <<"n: "<<num<<std::endl;
        if(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.find_first_of(",")-1);
            workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
        } else {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.length());
            workingString = "";
        }
        //  std::cout << act <<std::endl;
        for(int x=0;x<red_s.size();++x){
            if(act.compare(red_s[x])==0){
                if(num==0)
                    reduced_vars<< act<<"_reduced";
                else
                    reduced_vars<<", "<<act <<"_reduced";
                num++;
            }
        }
    }
    
    
    workingString=std::string(red_string);
    num=0;
    while(workingString.find_first_of(":")>=0 && workingString.find_first_of(":")<workingString.length()) {
        //std::cout <<"n: "<<num<<std::endl;
        if(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.find_first_of(",")-1);
            workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
        } else {
            act = workingString.substr(workingString.find_first_of(":")+1,workingString.length());
            workingString = "";
        }
        //  std::cout << act <<std::endl;
        for(int x=0;x<red_s.size();++x){
            if(act.compare(red_s[x])==0){
                reduced_vars <<", args["<< act<<"_reduced].addr="<<"\""<<_correspondence_table[act].get_name()<<"\"";
                num++;
            }
        }
    }
    
    if(num>0) {
        //        std::cout<<"RV: "<<std::string(reduced_vars)<<std::endl;
        //        std::cin.get();
        return reduced_vars;
    } else {
        Source empty;
        empty<<"";
        return empty;
    }
}
TL::Source Outline::get_parameter_declarations(Scope scope_of_decls) {
    Source parameters;
    
    if (_parameter_passed_symbols.empty()) {
        
        C_LANGUAGE() {
            parameters << "void";
        }
    } else {
        if (_packed_arguments) {
            Source packed_argument_typename;
            packed_argument_typename
                    << _packed_argument_typename
                    ;
            parameters
                    << packed_argument_typename << " *_args"
                    ;
        } else {
            //Enclosing function->Dins de quina funcio es troba el block a fer outlineing
            if (_enclosing_function.is_member() && !_enclosing_function.is_static()) {
                Type ptr_class_type = _enclosing_function.get_class_type();
                
                Type enclosing_function_type = _enclosing_function.get_type();
                
                if (enclosing_function_type.is_const()) {
                    ptr_class_type = ptr_class_type.get_const_type();
                }
                // if(!ptr_class_type.is_array())
                ptr_class_type = ptr_class_type.get_pointer_to();
                
                parameters
                        << ptr_class_type.get_declaration(scope_of_decls, "_this")
                        ;
            }
            
            
            GetDeclarationInScope get_declarations(*this, scope_of_decls);
            ObjectList<std::string> declarations =
                    _parameter_passed_symbols.map(functor(&GetDeclarationInScope::operator(), get_declarations));
            
            //            std::cout<<"*************+++++++++++++++++++++++++++++++++++++++++*****************"<<std::endl;
            //            for(int l=0;l<declarations.size();++l)
            //                std::cout<<std::string(declarations[l])<<std::endl;
            //            std::cin.get();
            
            
            //            for(int l=0;l<scope_of_decls.get_all_symbols(false).size();++l)
            //                std::cout<<scope_of_decls.get_all_symbols(false)[l].get_name()<<std::endl;
            //            std::cin.get();
            parameters.append_with_separator(
            concat_strings(declarations, ","),
                    ",");
            
        }
    }
    
    
    //    if(!red_string.empty()){
    //        std::string workingString=std::string(red_string);
    //        std::string act;
    //        Scope funct_scope = _outline_statements[0].get_scope();
    //        while(workingString.find_first_of(":")>=0 && workingString.find_first_of(":")<workingString.length()) {
    //            
    //            if(workingString.find_first_of(",")>=0 && workingString.find_first_of(",")<workingString.length()) {
    //                act = workingString.substr(workingString.find_first_of(":")+1,workingString.find_first_of(",")-1);
    //                workingString = workingString.substr(workingString.find_first_of(",")+1,workingString.length());
    //            } else {
    //                act = workingString.substr(workingString.find_first_of(":")+1,workingString.length());
    //                workingString = "";
    //            }
    //            std::cout <<act<<std::endl;
    //
    //            Source realDeclaration =std::string(funct_scope.get_symbol_from_name(act).get_type().get_declaration(funct_scope,
    //                    act));
    //            Source text;
    //            std::string type;
    //            type = std::string(realDeclaration).substr(0,std::string(realDeclaration).find(act));
    //            text << type <<"*"<<act<<"_reduced";
    //            std::cout<<std::string(text)<<std::endl;
    //            if(std::string(parameters).find(std::string(text))<0 ||std::string(parameters).find(std::string(text))>std::string(parameters).length()) {
    //                std::cout<<"Falta: "<<std::string(text)<<std::endl;
    //                parameters << ", "<<text;
    //            }
    //            
    //        }
    //        std::cout<<"Parameters: "<<std::string(parameters)<<std::endl;
    //        std::cin.get();
    //    }
    return parameters;
}
//Argumemnts for args[*].inout

TL::Source Outline::get_parameter_io(Scope scope_of_decls, Source start, Source separation, Source final) {
    Source parameters;
    AST_t ast = _outline_statements[0].get_ast();
    
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    int l = 0;
    int num = 0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
        if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){

            Expression expr(expr_list[l], _sl);
            
            
            int r = 0;
            Expression firstOperand = expr.get_first_operand();
            
            
            size_t EndPart1 = std::string(firstOperand.prettyprint()).find_first_of("[");
            Source cutParam;
            cutParam << std::string(std::string(firstOperand.prettyprint()).substr(0, EndPart1));
            cutParam = cleanWhiteSpaces(std::string(cutParam));
            Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
            
            
            if (paramSym.get_type().is_array() || paramSym.get_type().is_pointer() || (paramSym.get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && paramSym.get_point_of_declaration().prettyprint(true).find_first_of("[")<paramSym.get_point_of_declaration().prettyprint(true).length())){// || paramSym.get_type().is_pointer()) {// && std::string(parameters).find(std::string(cutParam)) > 0) {
                
                Source caseFirst;
                Source caseOthers;
                caseFirst << ", " << start << std::string(cutParam);
                caseOthers << separation << " " << std::string(cutParam);
                
                size_t caseFind1 = std::string(parameters).find(std::string(caseFirst));
                size_t caseFind2 = std::string(parameters).find(std::string(caseOthers));
                bool constrain1= (caseFind1 >= 0 && caseFind1 < std::string(parameters).length());
                bool constrain2= (caseFind2 >= 0 && caseFind2 < std::string(parameters).length());
                bool fconstrain = (!constrain1 && !constrain2);
                // std::cout<<"Array in:"<<std::string(cutParam)<<std::endl;
                //            std::cout<<"Finding( \""<<std::string(caseFirst) <<"\",\""<<std::string(caseOthers)<<"\") in(\""<<std::string(parameters)<<"\")"<<std::endl;
                //            std::cout<<"Resulting:("<<caseFind1<<","<< caseFind2 <<")"<<std::endl;
                //        std::cout<<"Cosntrains:("<<constrain1<<","<< constrain2 <<")"<<std::endl;      
                //        std::cout<<"Fosntrain:("<<fconstrain <<")"<<std::endl;
                int finded=0;
                if(fconstrain){
                    for(int w=0;w<_unchanged_vars.size();++w){
                        //   std::cout<<"-"<<_unchanged_vars[w]<<"- vs1 -"<<std::string(cutParam)<<"-"<<std::endl;
                        if(_unchanged_vars[w].compare(std::string(cutParam))==0){
                            finded =1;
                            //                        std::cout<<"-"<<std::string(cutParam)<<"-"<<std::endl;
                            int find_unch=0;
                            for(int y=0;y<_unchanged_to_in.size();++y){
                                if(std::string(_unchanged_to_in[y]).compare(std::string(cutParam))==0)
                                    find_unch=1;
                            }
                            if(!find_unch)
                                _unchanged_to_in.push_back(cutParam);
                        }
                    }
                    if (num ==0 && !finded) {
                        parameters << ", " << start;
                        parameters << std::string(cutParam);
                        num++;
                    } else if(fconstrain && !finded){
                        parameters << separation << " ";
                        parameters << std::string(cutParam);
                        num++;
                    }
                }
            }
        }
    }
    if (num > 0) {
        parameters << std::string(final);
    }
    return parameters;
}
std::unordered_map<std::string,TL::ObjectList<TL::AST_t>> Outline::get_parameter_io(Scope scope_of_decls) {
    
    std::unordered_map<std::string,TL::ObjectList<TL::AST_t>> parameters;
    AST_t ast = _outline_statements[0].get_ast();
    
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    int l = 0;
    int num = 0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
        int isArray = 0;
        Expression expr(expr_list[l], _sl);
       
        
        Source cutParam;
         if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
//            std::cout<<"1: "<<expr_list[l].prettyprint()<<std::endl;
//            std::cin.get();
            int r = 0;
            Expression firstOperand = expr.get_first_operand();
            
            
            size_t EndPart1 = std::string(firstOperand.prettyprint()).find_first_of("[");
            cutParam = firstOperand.prettyprint();
            if(EndPart1>0 && EndPart1<std::string(firstOperand.prettyprint()).length()) {
               cutParam = std::string(std::string(firstOperand.prettyprint()).substr(0, EndPart1));
               isArray=1;
            }
            //std::cout<<"P: "<<std::string(cutParam)<<std::endl;
            cutParam = cleanWhiteSpaces(std::string(cutParam));
            //std::cout<<"E: "<<std::string(cutParam)<<std::endl;
            
            
         
            
        } else {
//             std::cout<<"2: "<<expr_list[l].prettyprint()<<std::endl;
            std::string ppExpr=expr_list[l].prettyprint();
             
            if(ppExpr.find("++")==0) {
                cutParam = ppExpr.substr(ppExpr.find("++")+2,ppExpr.length());
            } else if(ppExpr.find("--")==0) {
                cutParam = ppExpr.substr(ppExpr.find("--")+2,ppExpr.length());
            }else if(ppExpr.find("++")==ppExpr.length()-3) {
                cutParam = ppExpr.substr(0,ppExpr.find("++"));
            }else if(ppExpr.find("--")==ppExpr.length()-3) {
                cutParam = ppExpr.substr(0,ppExpr.find("--"));
            }
//            std::cout<<std::string(cutParam)<<std::endl;
            size_t EndPart1 = std::string(cutParam).find_first_of("[");
            if(EndPart1>0 && EndPart1<std::string(cutParam).length()){
                cutParam = std::string(std::string(cutParam).substr(0, EndPart1));
                isArray=1;
            }
            cutParam = cleanWhiteSpaces(std::string(cutParam));
            
           
        }
        if(isArray)
            parameters[std::string(cutParam)].push_back(expr_list[l]);

    }
    return parameters;
}
int Outline::get_parameter_ioSpecificIsIteratorDependent(Scope scope_of_decls, std::string name, std::string iterVar) {
    AST_t ast = _outline_statements[0].get_ast();
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    int l = 0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
        Source cutParam;
         if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
            Expression expr(expr_list[l], _sl);
            Expression firstOperand = expr.get_first_operand();
            size_t EndPart1 = std::string(firstOperand.prettyprint()).find_first_of("[");
            
            cutParam << std::string(std::string(firstOperand.prettyprint()).substr(0, EndPart1));
            cutParam = cleanWhiteSpaces(std::string(cutParam));

            Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
            if(paramSym.get_name().compare(name)==0){
                if (paramSym.get_type().is_array() || paramSym.get_type().is_pointer() || (paramSym.get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && paramSym.get_point_of_declaration().prettyprint(true).find_first_of("[")<paramSym.get_point_of_declaration().prettyprint(true).length())){// || paramSym.get_type().is_pointer()) {// && std::string(parameters).find(std::string(cutParam)) > 0) {
                    Expression secondOperand = expr.get_second_operand();
                    std::string secondO = secondOperand.prettyprint();
                    while(secondO.find_first_of("[")>=0 && secondO.find_first_of("[")<secondO.length()) {
                        std::string actIterator = secondO.substr(secondO.find_first_of("[")+1,secondO.length());
                        actIterator = actIterator.substr(0,actIterator.find_first_of("]"));
                        actIterator = cleanWhiteSpaces(actIterator);
                        // std::cout<< name << "-> "<<actIterator <<" =? " <<iterVar <<" on ("<<secondO<<")"<<std::endl;
                        // std::cin.get();
                        if(actIterator.compare(iterVar)==0)
                            return 1;
                        secondO = secondO.substr(secondO.find_first_of("]")+1, secondO.length());
                    }
                }
            }
        } else {
            return 0;
        }
    }
    return 0;
}

std::string Outline::cleanWhiteSpaces(std::string toClean) {
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

void Outline::set_reduction(TL::Source red_str){
    
    red_string = red_str;
}
void Outline::clear_reduction() {
    Source emptyStr;
    emptyStr <<"";
    red_string = emptyStr;
}
TL::Source Outline::find_grid(TL::Scope scope_of_decls){
    Source gridify_text;
    gridify_text << "\n#pragma hmppcg gridify(";
    AST_t ast = _outline_statements[0].get_ast();
    std::string astText= ast.prettyprint(true);
    //std::cout<<"a: "<<astText<<std::endl;
    int num = 0;
    size_t forIndx;
    
    while(astText.find_first_of(" for")>=0 && astText.find_first_of(" for")<astText.length() && num<2){
        forIndx = astText.find_first_of(" for");
        //std::cout<<"aC: "<<astText<<std::endl;
        //std::cout <<astText.substr(astText.find_first_of(" for"),astText.find_first_of(" for")+4)<<std::endl;
        astText = astText.substr(astText.find_first_of(" for")+4,astText.length());
        size_t spaces;
        Source stringSpaces;
        spaces = astText.substr(0,astText.find_first_of("(")).length();
        for(int s=0;s<spaces;s++){
            stringSpaces <<" ";
        }
        if(astText.substr(0,astText.find_first_of("(")).compare(std::string(stringSpaces))==0){
            astText = astText.substr(astText.find_first_of("(")+1,astText.length());
            
            std::string express;
            express = astText.substr(0,astText.find_first_of("="));
            // std::cout<<"0: "<<express<<std::endl;
            while(express.find_first_of(" ")==0) {
                express = express.substr(express.find_first_of(" ")+1,express.length());
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
                gridify_text << express;
            else
                gridify_text <<", "<<express;
            num++;
        }
    }
    
    
    
    gridify_text<<")";
    //std::cout<<"s: "<<std::string(red_string)<<std::endl;
    if(!std::string(red_string).empty()){
        gridify_text<<", reduce("<<std::string(red_string)<<")";
    }
    gridify_text<<"\n";
    Source test;
    test << std::string(gridify_text);
    return test;
}
TL::Source Outline::get_parameter_in(Scope scope_of_decls, Source start, Source separation, Source final) {
    Source parameters;
    AST_t ast = _outline_statements[0].get_ast();
    compute_referenced_entities();
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    ObjectList<Source> in_params; 
    Source outv;
    Source nulls;
    nulls<<"";
    _unchanged_to_in.clear();
    outv = get_parameter_io(scope_of_decls, start, separation, separation);
    int l = 0;
    int num = 0, j=0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();it != expr_list.end(); it++, l++) {
        
        Symbol paramSym;
        Source cutParam;
         if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
//            std::cout<<"1"<<expr_list[l].prettyprint()<<std::endl;
//            std::cin.get();
            Expression expr(expr_list[l], _sl);
            int r = 0;
            Expression secondOperand = expr.get_second_operand();
            ObjectList<Source> operands;
            operands = splitMathExpression(scope_of_decls, secondOperand.prettyprint());
            for (int e=0;e<operands.size();e++){
                //            std::cout<<std::string(operands[e])<<std::endl;
                size_t EndPart1 = std::string(operands[e]).find_first_of("[");
                if(EndPart1>0 && EndPart1<std::string(operands[e]).length()) {
                    
                    cutParam << std::string(std::string(operands[e]).substr(0, EndPart1));
                    //                std::cout<<"-"<<std::string(cutParam)<<"-"<<std::endl;
                    cutParam = cleanWhiteSpaces(std::string(cutParam));
                    //Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                    paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                }
            }
        } else {
//            std::cout<<"2"<<expr_list[l].prettyprint()<<std::endl;
//            std::cin.get();
            std::string ppExpr=expr_list[l].prettyprint();
            Source cutParam;
            if(ppExpr.find("++")==0) {
                cutParam = ppExpr.substr(ppExpr.find("++")+2,ppExpr.length());
            } else if(ppExpr.find("--")==0) {
                cutParam = ppExpr.substr(ppExpr.find("--")+2,ppExpr.length());
            }else if(ppExpr.find("++")==ppExpr.length()-3) {
                cutParam = ppExpr.substr(0,ppExpr.find("++"));
            }else if(ppExpr.find("--")==ppExpr.length()-3) {
                cutParam = ppExpr.substr(0,ppExpr.find("--"));
            }
            size_t EndPart1 = std::string(cutParam).find_first_of("[");
            if(EndPart1>0 && EndPart1<std::string(cutParam).length()) 
                cutParam = std::string(std::string(cutParam).substr(0, EndPart1));
            while(std::string(cutParam).find_first_of(" ")==0)
                std::string(cutParam) = std::string(cutParam).substr(1,std::string(cutParam).length());
            while(std::string(cutParam).find_first_of(" ")<std::string(cutParam).length())
                std::string(cutParam) = std::string(cutParam).substr(0,std::string(cutParam).length()-1);
            paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
        }
        j=0;
        if(!paramSym.is_invalid()) {
            for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                    itu != _parameter_passed_symbols.end();
                    itu++, j++) {
                if(!_parameter_passed_symbols[j].is_invalid()){
                    //                            std::cout<<"-"<<_parameter_passed_symbols[j].get_name()<<"- vs -"<<std::string(cutParam)<<std::endl;
                    if(_parameter_passed_symbols[j].get_name().compare(std::string(cutParam))==0){
                        Source varName;
                        varName << _parameter_passed_symbols[j].get_name();
                        if (_parameter_passed_symbols[j].get_type().is_array() || _parameter_passed_symbols[j].get_type().is_pointer() || _parameter_passed_symbols[j].get_type().is_pointer() || (_parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && _parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).find_first_of("[")<_parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).length())) {
                            //                                    std::cout<<"In parameter: "<<std::string(varName)<<std::endl;
                            Source caseFirst;
                            Source caseOthers;
                            caseFirst << ", " << start << std::string(cutParam);
                            caseOthers << separation << " " << std::string(cutParam);
                            
                            size_t caseFind1 = std::string(parameters).find(std::string(caseFirst));
                            size_t caseFind2 = std::string(parameters).find(std::string(caseOthers));
                            bool constrain1= (caseFind1 >= 0 && caseFind1 < std::string(parameters).length());
                            bool constrain2= (caseFind2 >= 0 && caseFind2 < std::string(parameters).length());
                            bool fconstrain = (!constrain1 && !constrain2);
                            if(fconstrain){
                                Source caseFirst1;
                                Source caseOthers1;
                                caseFirst1 << ", " << start << std::string(cutParam);
                                caseOthers1 << separation << " " << std::string(cutParam);
                                
                                size_t caseFind11 = std::string(outv).find(std::string(caseFirst1));
                                size_t caseFind21 = std::string(outv).find(std::string(caseOthers1));
                                bool constrain11= (caseFind11 >= 0 && caseFind11 < std::string(outv).length());
                                bool constrain21= (caseFind21 >= 0 && caseFind21 < std::string(outv).length());
                                bool fconstrain1 = (!constrain11 && !constrain21);
                                
                                if(fconstrain1) {
                                    if (num ==0) {
                                        parameters << ", " << start;
                                        parameters << std::string(cutParam);
                                        num++;
                                        in_params.push_back(cutParam);
                                    } else if(fconstrain){
                                        parameters << separation << " ";
                                        parameters << std::string(cutParam);
                                        in_params.push_back(cutParam);
                                        num++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    
    for(int y=0;y<_unchanged_to_in.size();++y){
        int finded=0;
        for(int x=0;x<in_params.size();++x){
            if(std::string(_unchanged_to_in[y]).compare(std::string(in_params[x]))==0){
                finded=1;
            }
        }
        if (num ==0 && !finded) {
            parameters << ", " << start;
            parameters << std::string(_unchanged_to_in[y]);
            num++;
        } else if(!finded){
            parameters << separation << " ";
            parameters << std::string(_unchanged_to_in[y]);
            num++;
        }
        //         std::cout<<std::string(parameters)<<std::endl;
    }
    
    //std::cout<<std::string(parameters)<<std::endl;
    //std::cin.get();
    if (num > 0) {
        parameters << std::string(final);
        //        std::cout<<std::string(parameters)<<std::endl;
    }
    
    return parameters;
    
}

std::unordered_map<std::string,TL::ObjectList<TL::AST_t>>  Outline::get_parameter_in(Scope scope_of_decls) {
    std::unordered_map<std::string,TL::ObjectList<TL::AST_t>> parameters;
    AST_t ast = _outline_statements[0].get_ast();
    compute_referenced_entities();
    TraverseASTFunctor4All expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    ObjectList<Source> in_params; 
    Source nulls;
    nulls<<"";
    _unchanged_to_in.clear();
    int l = 0;
    int num = 0, j=0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
        Symbol paramSym;
        Source cutParam;
        if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
            Expression expr(expr_list[l], _sl);
            int r = 0;
            //std::cout<<"E:"<<expr.prettyprint()<<std::endl;
            
            std::string secondOperandString = expr.prettyprint().substr(expr.prettyprint().find("=")+1, expr.prettyprint().length());
            //Expression secondOperand = expr.get_second_operand();
            ObjectList<Source> operands;
            operands = splitMathExpression(scope_of_decls, secondOperandString);
            switch(expr.prettyprint()[expr.prettyprint().find_first_of("=")-1]) {
                case '+':
                case '-':
                case '/':
                case '*':
                    Source firstO;
                    firstO = expr.prettyprint().substr(0,expr.prettyprint().find_first_of("=")-1); 
                    operands.push_back(firstO);
                    break;
            }
            for (int e=0;e<operands.size();e++){
                size_t EndPart1 = std::string(operands[e]).find_first_of("[");
                if(EndPart1>0 && EndPart1<std::string(operands[e]).length()) {
                    cutParam = std::string(std::string(operands[e]).substr(0, EndPart1));
                } else {
                    cutParam = operands[e];
                }
                cutParam = cleanWhiteSpaces(std::string(cutParam));

//                std::cout<<std::string(cutParam)<<std::endl;
                //Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                j=0;
                if(!paramSym.is_invalid()) {
                    for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                            itu != _parameter_passed_symbols.end();
                            itu++, j++) {
                        if(!_parameter_passed_symbols[j].is_invalid()){
//                                                        std::cout<<"-"<<_parameter_passed_symbols[j].get_name()<<"- vs -"<<std::string(cutParam)<<std::endl;
                            if(_parameter_passed_symbols[j].get_name().compare(std::string(cutParam))==0){
                                Source varName;
                                varName << _parameter_passed_symbols[j].get_name();
                                parameters[std::string(varName)].push_back(expr_list[l]);
                            }
                        }
                    }
                }
//                std::cin.get();
            }
                    
        } else {
            
            std::string ppExpr=expr_list[l].prettyprint();
//            std::cout<<ppExpr<<std::endl;
//            std::cin.get();
            if(ppExpr.find("++")==0) {
                cutParam = ppExpr.substr(ppExpr.find("++")+2,ppExpr.length());
            } else if(ppExpr.find("--")==0) {
                cutParam = ppExpr.substr(ppExpr.find("--")+2,ppExpr.length());
            }else if(ppExpr.find("++")==ppExpr.length()-3) {
                cutParam = ppExpr.substr(0,ppExpr.find("++"));
            }else if(ppExpr.find("--")==ppExpr.length()-3) {
                cutParam = ppExpr.substr(0,ppExpr.find("--"));
            }
                cutParam = ppExpr.substr(0,ppExpr.find("--"));
            size_t EndPart1 = std::string(cutParam).find_first_of("[");
            if(EndPart1>0 && EndPart1<std::string(cutParam).length()) 
                cutParam = std::string(std::string(cutParam).substr(0, EndPart1));
            while(std::string(cutParam).find_first_of(" ")==0)
                std::string(cutParam) = std::string(cutParam).substr(1,std::string(cutParam).length());
            while(std::string(cutParam).find_first_of(" ")<std::string(cutParam).length())
                std::string(cutParam) = std::string(cutParam).substr(0,std::string(cutParam).length()-1);
            paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
            j=0;
                if(!paramSym.is_invalid()) {
                    for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                            itu != _parameter_passed_symbols.end();
                            itu++, j++) {
                        if(!_parameter_passed_symbols[j].is_invalid()){
                            //                            std::cout<<"-"<<_parameter_passed_symbols[j].get_name()<<"- vs -"<<std::string(cutParam)<<std::endl;
                            if(_parameter_passed_symbols[j].get_name().compare(std::string(cutParam))==0){
                                Source varName;
                                varName << _parameter_passed_symbols[j].get_name();
                                parameters[std::string(varName)].push_back(expr_list[l]);
                            }
                        }
                    }
                }
        }
        
        
    }
    
    
    return parameters;
    
}

TL::Source Outline::get_parameter_in_noch(Scope scope_of_decls, Source start, Source separation, Source final) {
    Source parameters;
    AST_t ast = _outline_statements[0].get_ast();
    compute_referenced_entities();
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    ObjectList<Source> in_params; 
    int l = 0;
    int num = 0, j=0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
         if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
            Expression expr(expr_list[l], _sl);
            int r = 0;
            Expression secondOperand = expr.get_second_operand();
            ObjectList<Source> operands;
            operands = splitMathExpression(scope_of_decls, secondOperand.prettyprint());
            for (int e=0;e<operands.size();e++){
                //            std::cout<<std::string(operands[e])<<std::endl;
                size_t EndPart1 = std::string(operands[e]).find_first_of("[");
                if(EndPart1>0 && EndPart1<std::string(operands[e]).length()) {
                    Source cutParam;
                    cutParam << std::string(std::string(operands[e]).substr(0, EndPart1));
                    //                std::cout<<"-"<<std::string(cutParam)<<"-"<<std::endl;
                    cutParam = cleanWhiteSpaces(std::string(cutParam));
                    //Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                    Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                    j=0;
                    if(!paramSym.is_invalid()) {
                        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                                itu != _parameter_passed_symbols.end();
                                itu++, j++) {
                            if(!_parameter_passed_symbols[j].is_invalid()){
                                //                            std::cout<<"-"<<_parameter_passed_symbols[j].get_name()<<"- vs -"<<std::string(cutParam)<<std::endl;
                                if(_parameter_passed_symbols[j].get_name().compare(std::string(cutParam))==0){
                                    Source varName;
                                    varName << _parameter_passed_symbols[j].get_name();
                                    if (_parameter_passed_symbols[j].get_type().is_array() || _parameter_passed_symbols[j].get_type().is_pointer() || _parameter_passed_symbols[j].get_type().is_pointer() || (_parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && _parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).find_first_of("[")<_parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).length())) {
                                        //                                    std::cout<<"In parameter: "<<std::string(varName)<<std::endl;
                                        Source caseFirst;
                                        Source caseOthers;
                                        caseFirst << ", " << start << std::string(cutParam);
                                        caseOthers << separation << " " << std::string(cutParam);
                                        
                                        size_t caseFind1 = std::string(parameters).find(std::string(caseFirst));
                                        size_t caseFind2 = std::string(parameters).find(std::string(caseOthers));
                                        bool constrain1= (caseFind1 >= 0 && caseFind1 < std::string(parameters).length());
                                        bool constrain2= (caseFind2 >= 0 && caseFind2 < std::string(parameters).length());
                                        bool fconstrain = (!constrain1 && !constrain2);
                                        
                                        if (num ==0) {
                                            parameters << ", " << start;
                                            parameters << std::string(cutParam);
                                            num++;
                                            in_params.push_back(cutParam);
                                        } else if(fconstrain){
                                            parameters << separation << " ";
                                            parameters << std::string(cutParam);
                                            in_params.push_back(cutParam);
                                            num++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    if (num > 0) {
        parameters << std::string(final);
    }
    return parameters;
    
}

TL::Source Outline::get_parameter_sizes(Scope scope_of_decls) {
    int num = 0;
    int j = 0;
    compute_referenced_entities();
    //    std::cout << "Param Elements: " << _parameter_passed_symbols.size() <<std::endl;
    Source parameters;
    parameters<<"";
    if (_parameter_passed_symbols.size() > 0) {
        
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Source varName;
            varName << _parameter_passed_symbols[j].get_name();
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
            Type paramType = paramSymbol.get_type();
            if (_parameter_passed_symbols[j].get_type().is_array()) {
                Source cutIni,cutIniFin, paramIni;
                paramIni << paramType.get_declaration(_parameter_passed_symbols[j].get_scope(), std::string(varName));
                //std::cout<<"De: "<<_parameter_passed_symbols<<std::endl;
                
                
                cutIniFin << std::string(std::string(paramIni).substr(0, std::string(paramIni).length()-1));
                size_t firstClau = std::string(cutIniFin).find_first_of("[");
                cutIni << std::string(std::string(cutIniFin).substr(firstClau+1, std::string(cutIniFin).length()));
                //std::cout<<std::string(varName)<<" size: "<<std::string(cutIni)<<std::endl;
                //                    std::cout<<"*******************Houston we have a problem****************"<<std::endl;
                TL::Type type = scope_of_decls.get_symbol_from_name(std::string(varName)).get_type();
                TL::Type aux_type = scope_of_decls.get_symbol_from_name(std::string(varName)).get_type();
                if (type.is_array()) {
                    
                    aux_type = type.array_element();
                    //If Array
                    if (!aux_type.is_array()) {
                        num++;
                        if (num > 0)
                            parameters << ", ";
                        parameters << "args[" << std::string(varName) << "].size={" << std::string(cutIni) << "}";
                        
                    }
                }
            }
            
            
        }
    }
    int numDynamicVars= get_num_dynamic_var(scope_of_decls);
    if(numDynamicVars>0) {
        //  std::cout<<"Dynamic Vars: "<<numDynamicVars<<std::endl;
        AST_t ast = _outline_statements[0].get_ast();
        
        //std::cout<<"Pre: "<<std::string(parameters)<<std::endl;
        Source dynamicSizes;
        dynamicSizes = get_dynamic_parameter_sizes(scope_of_decls, ast, _sl);
        parameters << dynamicSizes;
        // std::cout<<"Post: "<<std::string(parameters)<<std::endl;
    }
    return parameters;
}


TL::Source Outline::get_parameter_addr(Scope scope_of_decls) {
    int num = 0;
    int j = 0;
    compute_referenced_entities();
    //    std::cout << "Param Elements: " << _parameter_passed_symbols.size() <<std::endl;
    Source parameters;
    parameters<<"";
    if (_parameter_passed_symbols.size() > 0) {
        
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Source varName;
            varName << _parameter_passed_symbols[j].get_name();
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
            if(_parameter_passed_symbols[j].get_type().is_pointer()) {
                parameters << ", ";
                parameters << "args[" << std::string(varName) << "].addr=\"" << std::string(varName) << "\"";
            }
            
        }
        
        
    }
    
    return parameters;
}

TL::Source Outline::get_parameter_Haddr(Scope scope_of_decls) {
    int num = 0;
    int j = 0;
    compute_referenced_entities();
    //    std::cout << "Param Elements: " << _parameter_passed_symbols.size() <<std::endl;
    Source parameters;
    parameters<<"";
    if (_parameter_passed_symbols.size() > 0) {
        
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Source varName;
            varName << _parameter_passed_symbols[j].get_name();
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
            if(_parameter_passed_symbols[j].get_type().is_pointer()) {
                parameters << ", ";
                parameters << "args[" << std::string(varName) << "].hostdata=\"" << std::string(varName) << "\"";
            }
            
        }
        
        
    }
    
    return parameters;
}
//Size of dynamic Vars
TL::Source Outline::get_dynamic_parameter_sizes(Scope scope_of_decls, AST_t blockAst, ScopeLink allocateScopeLink) {
    
    int j = 0;
    compute_referenced_entities();
    Source parameters;
    parameters<<"";
    AST_t allocateAst = blockAst.get_enclosing_function_definition_declaration();
    for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
            itu != _parameter_passed_symbols.end();
            itu++, j++) {
        Source varName,declaration;
        varName << _parameter_passed_symbols[j].get_name();
        if(_parameter_passed_symbols[j].get_type().is_pointer()) {
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
            TraverseASTFunctor4Malloc expr_traverse(allocateScopeLink);
            ObjectList<AST_t> asts = allocateAst.depth_subtrees(expr_traverse);
            int l=0;
            for (ObjectList<AST_t>::iterator it = asts.begin();
                    it != asts.end();
                    it++,l++) {
                Expression expr(asts[l], allocateScopeLink);
                std::string firstOperand;
                firstOperand = expr.get_first_operand().prettyprint();
                size_t arrayAcces;
                arrayAcces = firstOperand.find("[");
                if(arrayAcces < 0 || arrayAcces>firstOperand.length()) {
                    Symbol sym = expr.get_first_operand().get_symbol();
                    if(sym.get_type().is_pointer()) {
                        std::string mallocExpr, mallocString;
                        mallocExpr = expr.prettyprint();
                        size_t findMalloc;
                        findMalloc = mallocExpr.find("malloc");
                        if(findMalloc > 0 && findMalloc<mallocExpr.length()) {
                            mallocString = mallocExpr.substr(findMalloc+6,mallocExpr.length());
                            parameters << ", args["<< std::string(varName) << "].size={" << std::string(mallocString) << "/"<<paramSymbol.get_type().points_to().get_size()<<"}";
                        }
                    }
                }
            }
        }
    }
    return parameters;
}

///#pragma numfunc allocate, data["u"], data["x"].size={m*n}, data["x"].elementsize="sizeof(double)"
TL::Source Outline::get_dynamic_var(Scope scope_of_decls) {
    int num = 0;
    int j = 0;
    compute_referenced_entities();
    Source parameters;
    parameters<<"";
    if (_parameter_passed_symbols.size() > 0) {
        //Data["u"] 
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Source varName;
            varName << _parameter_passed_symbols[j].get_name();
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
            if(_parameter_passed_symbols[j].get_type().is_pointer()) {
                if (num==0) {
                    parameters << ", data[\""<< std::string(varName)<<"\"";
                } else{
                    parameters << ", \""<< std::string(varName) << "\"";
                }
                num++;
            }
        }    
        if(num>0)
            parameters<<"]";     
        //Data.size={m*n}
        j=0;
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Source varName,declaration;
            varName << _parameter_passed_symbols[j].get_name();
            if(_parameter_passed_symbols[j].get_type().is_pointer()) {
                Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
                TraverseASTFunctor4Malloc expr_traverse(_allocateScopeLink);
                ObjectList<AST_t> asts = _allocateAst.depth_subtrees(expr_traverse);
                //std::cout << "------------"<<std::endl;
                int l=0;
                for (ObjectList<AST_t>::iterator it = asts.begin();
                        it != asts.end();
                        it++,l++) {
                    Expression expr(asts[l], _allocateScopeLink);
                    std::string firstOperand;
                    firstOperand = expr.get_first_operand().prettyprint();
                    size_t arrayAcces;
                    arrayAcces = firstOperand.find("[");
                    if(arrayAcces < 0 || arrayAcces>firstOperand.length()) {
                        Symbol sym = expr.get_first_operand().get_symbol();
                        if(sym.get_type().is_pointer()) {
                            std::string mallocExpr, mallocString;
                            mallocExpr = expr.prettyprint();
                            size_t findMalloc;
                            findMalloc = mallocExpr.find("malloc");
                            if(findMalloc > 0 && findMalloc<mallocExpr.length()) {
                                mallocString = mallocExpr.substr(findMalloc+6,mallocExpr.length());
                                parameters << ", data[\"" << std::string(varName) << "\"].size={" << std::string(mallocString) << "/"<<paramSymbol.get_type().points_to().get_size()<<"}";
                            }
                        }
                    }
                }
            }
        }
        
        j=0;
        //Data.elementsize="sizeof(double)"
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            Source varName;
            varName << _parameter_passed_symbols[j].get_name();
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(std::string(varName));
            if(_parameter_passed_symbols[j].get_type().is_pointer()) {
                Source declaration;
                parameters << ", data[\"" << std::string(varName) << "\"].elementsize=\"" << paramSymbol.get_type().points_to().get_size() << "\"";
            }
        } 
        
    }
    return parameters;
}
int Outline::get_num_dynamic_var(Scope scope_of_decls) {
    int num = 0;
    int j = 0;
    compute_referenced_entities();
    if (_parameter_passed_symbols.size() > 0) {
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            if(_parameter_passed_symbols[j].get_type().is_pointer()) {
                num++;
            }
            
        }
    }
    
    return num;
}

struct DoNotPass : public TL::Predicate<TL::Symbol> {
private:
    Outline& _outline;
public:
    
    DoNotPass(Outline & outline)
    : _outline(outline) {
    }
    
    virtual bool do_(DoNotPass::ArgType sym) const {
        return (_outline.get_parameter_passing(sym) != Outline::DO_NOT_PASS);
    }
};

void Outline::compute_referenced_entities() {
    ObjectList<Symbol> all_referenced_symbols;
    
    std::for_each(_outline_statements.begin(), _outline_statements.end(),std::bind2nd(std::ptr_fun(get_referenced_entities), &all_referenced_symbols));
    
    if (_use_nonlocal_scope) {
        // Remove those that can use the "file" scope
        _replaced_symbols = all_referenced_symbols.filter(predicate(is_local_or_nonstatic_member));
        _parameter_passed_symbols = all_referenced_symbols.filter(predicate(&Symbol::has_local_scope));
    } else {
        _replaced_symbols = all_referenced_symbols;
        _parameter_passed_symbols = all_referenced_symbols;
    }
    //    std::cout<<"\n**********************************************"<<endl;
    
    
    // Remove those that we've been told they should not be passed
    _parameter_passed_symbols = _parameter_passed_symbols.filter(DoNotPass(*this));
    
}

struct AuxiliarOutlineReplace {
private:
    Outline &_outline;
    TL::ReplaceSrcIdExpression *_replacements;
    TL::Symbol _enclosing_function;
    bool _packed_args;
    
public:
    
    AuxiliarOutlineReplace(
    Outline &outline,
            TL::ReplaceSrcIdExpression& replacements,
            TL::Symbol enclosing_function,
            bool packed_args)
    : _outline(outline),
            _replacements(&replacements),
            _enclosing_function(enclosing_function),
            _packed_args(packed_args) {
    }
    
    void operator()(TL::Symbol sym) {
        Outline::ParameterPassing passing = _outline.get_parameter_passing(sym);
        if (!IS_CXX_LANGUAGE
                || !sym.is_member()
                || !(_enclosing_function.is_member() && !_enclosing_function.is_static())
                || !sym.get_class_type().is_same_type(_enclosing_function.get_class_type())) {
            if (_packed_args) {
                if (passing == Outline::POINTER) {
                    _replacements->add_replacement(sym, "(*_args->" + sym.get_name() + ")");
                    
                } else if (passing == Outline::VALUE) {
                    _replacements->add_replacement(sym, "(_args->" + sym.get_name() + ")");
                } else {
                    throw HLTException("invalid passing mode");
                }
            } else {
                if (passing == Outline::POINTER) {
                    //Comentat elimina punters dins de la funció(no com a parametres)
                    //_replacements->add_replacement(sym, "(*" + sym.get_name() + ")");
                    
                    
                } else if (passing == Outline::VALUE) {
                    // Do nothing, actually
                    // _replacements->add_replacement(sym, "(" + sym.get_name() + ")");
                } else {
                    throw HLTException("invalid passing mode");
                }
            }
        } else {
            if (_packed_args) {
                _replacements->add_replacement(sym, "(_args->_this->" + sym.get_name() + ")");
            } else {
                _replacements->add_replacement(sym, "(_this->" + sym.get_name() + ")");
            }
        }
    }
};

struct auxiliar_replace_t {
    TL::Source *src;
    TL::ReplaceSrcIdExpression *repls;
};

static void print_replaced_stmts(TL::Statement stmt, auxiliar_replace_t aux) {
    (*aux.src) << aux.repls->replace(stmt);
}

void Outline::compute_outlined_body(Source &outlined_body) {
    ReplaceSrcIdExpression replacements(_sl);
    
    std::for_each(_replaced_symbols.begin(),
    _replaced_symbols.end(),
    AuxiliarOutlineReplace(*this, replacements, _enclosing_function, _packed_arguments));
    
    auxiliar_replace_t aux = {&outlined_body, &replacements};
    
    std::for_each(_outline_statements.begin(),
    _outline_statements.end(),
    std::bind2nd(std::ptr_fun(print_replaced_stmts), aux));
}

void Outline::declare_members(Source template_headers) {
    Source member_decl;
    
    member_decl
            << _additional_decls_source
            ;
    
    if (_enclosing_function.get_type().is_template_specialized_type()) {
        member_decl
                << template_headers
                ;
    }
    
    Source parameters;
    member_decl
            << "static void " << _outline_name << "(" << parameters << ");"
            ;
    
    AST_t point_of_decl = _enclosing_function.get_point_of_declaration();
    Type class_type = _enclosing_function.get_class_type();
    
    parameters = get_parameter_declarations(class_type.get_symbol().get_scope());
    
    AST_t member_tree = member_decl.parse_member(
            point_of_decl, _sl,
            // class_type is a named type, get the type of its symbol
            class_type.get_symbol());
    
    point_of_decl.append(member_tree);
}
void Outline::set_outline_num_line(int line){
    _num_line=line;
}
int Outline::get_outline_num_line(){
    return _num_line;
}
void Outline::fill_nonmember_forward_declarations(Source template_headers, Source &forward_declarations) {
    forward_declarations
            // FIXME
            << _additional_decls_source
            << template_headers
            << _enclosing_function.get_type().get_declaration(_enclosing_function.get_scope(), _enclosing_function.get_name()) << ";";
}

void Outline::fill_member_forward_declarations(Source /*template_headers*/, Source &forward_declarations) {
    forward_declarations
            << _additional_decls_source
            ;
}

void Outline::embed_outline() {
    AST_t outline_tree;
    //    std::cout<<"1"<<std::endl;
    //    std::cout<<_outlined_source.get_source()<<std::endl;
    //    std::cin.get();
    if (!_is_member || !_is_inlined_member) {
        outline_tree = _outlined_source.parse_declaration(_function_def->get_point_of_declaration(),
                _sl);
        
    } else {
        // This requires a different function
        outline_tree = _outlined_source.parse_member(_function_def->get_point_of_declaration(),
                _sl, _enclosing_function.get_class_type().get_symbol());
        
    }
    //    std::cout<<"2"<<std::endl;
    
    _function_def->get_ast().prepend_sibling_function(outline_tree);
}

Outline& Outline::set_outline_name(const std::string& str) {
    _outline_name = str;
}

std::string Outline::get_outline_name() {
    do_outline();
    return _outline_name;
}

Outline::~Outline() {
    //  _correspondence_table.clear();
    //  delete _function_def;
}

void Outline::set_default_parameter_passing(ParameterPassing passing) {
    _default_parameter_passing = passing;
}

void Outline::set_parameter_passing(Symbol sym, ParameterPassing passing) {
    if (!_parameter_info.contains(functor(&ParameterInfo::related_symbol), sym)) {
        ParameterInfo param_info;
        
        param_info.related_symbol = sym;
        param_info.passing = passing;
        param_info.outline_ref = sym.get_name();
        
        _parameter_info.append(param_info);
    } else {
        ParameterInfo &param_info = *(_parameter_info
                .find(functor(&ParameterInfo::related_symbol), sym).begin());
        
        param_info.passing = passing;
    }
}

Outline::ParameterPassing Outline::get_parameter_passing(Symbol sym) {
    set_parameter_passing_if_not_set(sym);
    
    ParameterInfo &param_info = *(_parameter_info
            .find(functor(&ParameterInfo::related_symbol), sym).begin());
    
    return param_info.passing;
}

void Outline::set_parameter_passing_if_not_set(Symbol sym) {
    if (!_parameter_info.contains(functor(&ParameterInfo::related_symbol), sym)) {
        ParameterInfo param_info;
        
        param_info.related_symbol = sym;
        param_info.passing = _default_parameter_passing;
        param_info.outline_ref = sym.get_name();
        
        _parameter_info.append(param_info);
    }
}

TL::ObjectList<TL::Symbol> Outline::get_parameter_list() {
    do_outline();
    return _parameter_passed_symbols;
}

std::string Outline::get_packing_struct_typename() {
    do_outline();
    return _packed_argument_typename;
}

TL::Source Outline::get_parameter_io_specific(Scope scope_of_decls, Source start, Source separation, Source final,std::vector<std::string> specific_names, int nup){
    Source parameters;
    AST_t ast = _outline_statements[0].get_ast();
    
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    int l = 0;
    int num = 0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
         if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
            Expression expr(expr_list[l], _sl);
            
            
            int r = 0;
            Expression firstOperand = expr.get_first_operand();
            
            
            size_t EndPart1 = std::string(firstOperand.prettyprint()).find_first_of("[");
            Source cutParam;
            cutParam << std::string(std::string(firstOperand.prettyprint()).substr(0, EndPart1));
            cutParam = cleanWhiteSpaces(std::string(cutParam));
            Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
            
            
            if (paramSym.get_type().is_array() || paramSym.get_type().is_pointer() || (paramSym.get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && paramSym.get_point_of_declaration().prettyprint(true).find_first_of("[")<paramSym.get_point_of_declaration().prettyprint(true).length())){// || paramSym.get_type().is_pointer()) {// && std::string(parameters).find(std::string(cutParam)) > 0) {
                
                Source caseFirst;
                Source caseOthers;
                caseFirst << ", " << start << std::string(cutParam);
                caseOthers << separation << " " << std::string(cutParam);
                
                size_t caseFind1 = std::string(parameters).find(std::string(caseFirst));
                size_t caseFind2 = std::string(parameters).find(std::string(caseOthers));
                bool constrain1= (caseFind1 >= 0 && caseFind1 < std::string(parameters).length());
                bool constrain2= (caseFind2 >= 0 && caseFind2 < std::string(parameters).length());
                bool fconstrain = (!constrain1 && !constrain2);
                // std::cout<<"Array in:"<<std::string(cutParam)<<std::endl;
                //            std::cout<<"Finding( \""<<std::string(caseFirst) <<"\",\""<<std::string(caseOthers)<<"\") in(\""<<std::string(parameters)<<"\")"<<std::endl;
                //            std::cout<<"Resulting:("<<caseFind1<<","<< caseFind2 <<")"<<std::endl;
                //        std::cout<<"Cosntrains:("<<constrain1<<","<< constrain2 <<")"<<std::endl;      
                //        std::cout<<"Fosntrain:("<<fconstrain <<")"<<std::endl;
                int finded=0;
                int specified=0;
                if(nup){
                    for(int w=0;w<_unchanged_vars.size();++w){
                        //std::cout<<"-"<<_unchanged_vars[w]<<"- vs1 -"<<std::string(cutParam)<<"-"<<std::endl;
                        if(_unchanged_vars[w].compare(std::string(cutParam))==0){
                            finded =1;
                            break;
                        }
                    }
                }
                for(int e=0;e<specific_names.size();++e){
                    //                std::cout<<"Compare(IO-spec) : -"<<specific_names[e]<<"- vs -"<<std::string(cutParam)<<"-"<<std::endl;
                    if(specific_names[e].compare(std::string(cutParam))==0) {
                        //                    std::cout<<"Equals\n";
                        specified=1;
                    }
                }
                if (fconstrain && num ==0 && !finded && specified) {
                    parameters << ", " << start << std::string(cutParam);
                    //                std::cout<<std::string(parameters)<<std::endl;
                    num++;
                } else if(fconstrain && !finded && specified){
                    parameters << separation << " " << std::string(cutParam);
                    //                std::cout<<std::string(parameters)<<std::endl;
                    num++;
                }
                //            std::cin.get();
            }
        }
    }
    if (num > 0) {
        parameters << std::string(final);
    }
    return parameters;
    
}
TL::Source Outline::get_parameter_in_specific(Scope scope_of_decls, Source start, Source separation, Source final,std::vector<std::string> specific_names, int nup){
    
    Source parameters;
    AST_t ast = _outline_statements[0].get_ast();
    compute_referenced_entities();
    TraverseASTFunctor4AssigmentLine expr_traverse(_sl);
    ObjectList<AST_t> expr_list = ast.depth_subtrees(expr_traverse);
    ObjectList<Source> in_params; 
    int l = 0;
    int num = 0, j=0;
    for (ObjectList<AST_t>::iterator it = expr_list.begin();
            it != expr_list.end(); it++, l++) {
        if((expr_list[l].prettyprint().find("++")<0 || expr_list[l].prettyprint().find("++")>expr_list[l].prettyprint().length())
                && (expr_list[l].prettyprint().find("--")<0 || expr_list[l].prettyprint().find("--")>expr_list[l].prettyprint().length())){
            Expression expr(expr_list[l], _sl);
            int r = 0;
            Expression secondOperand = expr.get_second_operand();
            ObjectList<Source> operands;
            operands = splitMathExpression(scope_of_decls, secondOperand.prettyprint());
            for (int e=0;e<operands.size();e++){
                //            std::cout<<std::string(operands[e])<<std::endl;
                size_t EndPart1 = std::string(operands[e]).find_first_of("[");
                if(EndPart1>0 && EndPart1<std::string(operands[e]).length()) {
                    Source cutParam;
                    cutParam << std::string(std::string(operands[e]).substr(0, EndPart1));
                    //                std::cout<<"-"<<std::string(cutParam)<<"-"<<std::endl;
                    cutParam = cleanWhiteSpaces(std::string(cutParam));
                    //Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                    Symbol paramSym = scope_of_decls.get_symbol_from_name(std::string(cutParam));
                    j=0;
                    if(!paramSym.is_invalid()) {
                        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                                itu != _parameter_passed_symbols.end();
                                itu++, j++) {
                            if(!_parameter_passed_symbols[j].is_invalid()){
                                //                            std::cout<<"-"<<_parameter_passed_symbols[j].get_name()<<"- vs -"<<std::string(cutParam)<<std::endl;
                                if(_parameter_passed_symbols[j].get_name().compare(std::string(cutParam))==0){
                                    Source varName;
                                    varName << _parameter_passed_symbols[j].get_name();
                                    if (_parameter_passed_symbols[j].get_type().is_array() || _parameter_passed_symbols[j].get_type().is_pointer() || _parameter_passed_symbols[j].get_type().is_pointer() || (_parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).find_first_of("[")>=0 && _parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).find_first_of("[")<_parameter_passed_symbols[j].get_point_of_declaration().prettyprint(true).length())) {
                                        //                                    std::cout<<"In parameter: "<<std::string(varName)<<std::endl;
                                        Source caseFirst;
                                        Source caseOthers;
                                        caseFirst << ", " << start << std::string(cutParam);
                                        caseOthers << separation << " " << std::string(cutParam);
                                        //std::cout<< "-"<<std::string(caseFirst) << "- in. -"<<std::string(parameters)<<"-"<<std::endl;
                                        //std::cout<< "-"<<std::string(caseOthers) << "- in. -"<<std::string(parameters)<<"-"<<std::endl;
                                        //std::cin.get();
                                        size_t caseFind1 = std::string(parameters).find(std::string(caseFirst));
                                        size_t caseFind2 = std::string(parameters).find(std::string(caseOthers));
                                        bool constrain1= (caseFind1 >= 0 && caseFind1 < std::string(parameters).length());
                                        bool constrain2= (caseFind2 >= 0 && caseFind2 < std::string(parameters).length());
                                        bool fconstrain = (!constrain1 && !constrain2);
                                        if(fconstrain) {
                                            int finded=0;
                                            for(int i=0;i<specific_names.size();++i){
                                                if(std::string(varName).compare(specific_names[i])==0){
                                                    finded=1;
                                                }
                                            }
                                            if(finded){
                                                if (num > 0) {
                                                    parameters << std::string(separation) << " ";
                                                } else {
                                                    parameters << ", " << std::string(start);
                                                }
                                                
                                                num++;
                                                
                                                parameters << std::string(varName);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    
    if (num > 0) {
        parameters << std::string(final);
        //        std::cout<<std::string(parameters)<<std::endl;
    }
    return parameters;
    
    
}
TL::Source Outline::get_parameter_addr_specific(Scope scope_of_decls,std::vector<std::string> specific_names){
    int num = 0;
    int j = 0;
    compute_referenced_entities();
    //    std::cout << "Param Elements: " << _parameter_passed_symbols.size() <<std::endl;
    Source parameters;
    if (_parameter_passed_symbols.size() > 0) {
        for (ObjectList<Symbol>::iterator itu = _parameter_passed_symbols.begin();
                itu != _parameter_passed_symbols.end();
                itu++, j++) {
            
            Symbol paramSymbol = scope_of_decls.get_symbol_from_name(_parameter_passed_symbols[j].get_name());
            for(int k=0;k<specific_names.size();++k){
                //                    std::cout<<"Compare(addr-spec) -"<<_parameter_passed_symbols[j].get_name()<<"- vs -"<<specific_names[k]<<"-"<<std::endl;
                if(_parameter_passed_symbols[j].get_name().compare(specific_names[k])==0){
                    parameters << ", ";
                    parameters << "args[" << _parameter_passed_symbols[j].get_name() << "].addr=\"" << paramSymbol.get_name() << "\"";
                }
            }
            
            
        }
        
        
    }
    //std::cin.get();
    
    return parameters;
}

TL::ObjectList<TL::Source> Outline::splitMathExpression(Scope sC,std::string secondO)
{
    //    std::cout<<"Second Operator: "<<secondO<<endl;
    ObjectList<Source> operators;
    int numElem=0;
    Source empty;
    std::string math[11] = {"+","*","/","-","<",">","=","?",":","&","|"};
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
//                        std::cout<<"HI"<<std::endl;
                        i++;
                    }
                    
                }
                if(math[x].compare("-")==0) {
                    if(nextChar.compare(">")==0) {
//                        std::cout<<"HI"<<std::endl;
                        i++;
                        find = 0;
                    }
                    
                }
                
            }
            if(!find){
                Source actElem;
                actElem = operators[numElem];
                actElem<<actChar;
                //         std::cout<<"Act elem:" <<std::string(actElem)<<endl;
                operators.pop_back();
                operators.push_back(actElem);
                //        std::cout<<"Act elem(op):" <<std::string(operators[numElem])<<endl;
                // perators[numElem].actChar;   
                Symbol findedS = sC.get_symbol_from_name(std::string(operators[numElem]));
                
                if(!findedS.is_invalid()) {
                    if(findedS.is_function()) {
                        if(nextChar.compare("(")==0) {
                            //                                std::cout<<std::string(operators[numElem])<<" discarted is function!!"<<endl;
                            operators[numElem]=empty;
                        }
                    }
                }
                
                
                //  std::cout<<"Working with("<<numElem<<"): "<<std::string(operators[numElem])<<endl;
            }else if(std::string(operators[numElem]).compare(std::string(empty))!=0){
                //for (int u=0; u<operators.size()-1;++u)
                //   std::cout<<u<<"(prev): "<<std::string(operators[u])<<endl;
                //   std::cout<<numElem<<"(last): "<<std::string(operators[numElem])<<endl;
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
        //        std::cout<<"operators empty"<<endl;
    }
    //    for (int u=0; u<operators.size();++u)
    //               std::cout<<u<<"(checked): -"<<std::string(operators[u])<<"-"<<endl;  
    return operators;
}

