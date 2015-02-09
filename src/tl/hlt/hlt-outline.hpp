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



#ifndef HLT_OUTLINE_HPP
#define HLT_OUTLINE_HPP

#include "hlt-transform.hpp"

#include "tl-objectlist.hpp"
#include "tl-symbol.hpp"
#include "tl-langconstruct.hpp"
#include "hlt-unroll.hpp"
#include <tl-pragmasupport.hpp>
#include <unordered_map>


namespace TL {
    namespace HLT {
        //! \addtogroup HLT High Level Transformations
        //! @{

        //! This class implements 'outlining' of parts of code

        /*!
          Outlining means creating a function off a part of code (this is like
          the opposite of inlining). This class works on a given statement, or
          set of statements in the very same scope, and creates a function with
          that statement in it. It takes care of creating the required
          parameters and returns information about the newly created function.
         */
        struct LIBHLT_CLASS Outline : public BaseTransform {
        public:
            //! Kind of parameter pass

            enum ParameterPassing {
                INVALID = 0,
                //! This symbol must not be passed at all to the outlined function
                DO_NOT_PASS,
                //! This symbol must be passed by pointer
                POINTER,
                //! This symbol must be passed by value
                VALUE,
                // Not implemented
                /* REFERENCE */
            };
            ScopeLink _sl;
            ObjectList<Statement> _outline_statements;
            std::unordered_map<std::string,Symbol> _correspondence_table;
            Source red_string;


        private:

            struct ParameterInfo {
                Symbol related_symbol;
                ParameterPassing passing;
                std::string outline_ref;
            };
            int _real_outline;
            int _cod;
            int _trans;
            FunctionDefinition* _function_def;
            bool _packed_arguments;
            bool _do_not_embed;
            bool _use_nonlocal_scope;
            int _outline_num;
            bool _outline_performed;
            bool _overriden_outline_name;
            
            ParameterPassing _default_parameter_passing;
            ObjectList<ParameterInfo> _parameter_info;
            AST_t _allocateAst;
            ScopeLink _allocateScopeLink;
            
            



            Source _outline_name;
            Source _outlined_source;
            Source _additional_decls_source;
            
            Symbol _enclosing_function;

            Source _packed_argument_typename;
            int _num_line;
            

            bool _is_member;
            bool _is_inlined_member;
            bool _is_templated;
            bool _has_linkage_specifier;
            
            int  _exec;
            ObjectList<TemplateHeader> _template_header;
            
            ObjectList<Symbol> _replaced_symbols;
            ObjectList<Symbol> _parameter_passed_symbols;
            ObjectList<Symbol> _pass_param;


            void do_outline();
            void compute_outline_name(
                    Source &template_headers_fwd,
                    Source &template_headers,
                    Source &required_qualification,
                    Source & static_qualifier);
            void compute_referenced_entities();
            void compute_outlined_body(Source & outlined_body);

            void declare_members(Source template_headers);
            void fill_nonmember_forward_declarations(Source template_headers, Source & forward_declarations);
            void fill_member_forward_declarations(Source template_headers, Source & forward_declarations);


            void compute_additional_declarations(Source template_headers, Scope scope_of_decls);

            void set_parameter_passing_if_not_set(Symbol sym);

            void embed_outline();
            
            static int _num_outlines;

            

        protected:
            virtual Source get_source();
        public:
            ObjectList<std::string> _unchanged_vars;
            ObjectList<Source> _unchanged_to_in;
            void clear_reduction(); 
            void set_unchanged_vars(ObjectList <std::string> unchanged);
            int get_outline_num();
            void set_reduction(Source red_str);
            void set_allocate(AST_t allocateAst, ScopeLink allocateScopeLink);
            void set_cod_trans(int cod, int trans);
            int is_reduced(std::string);
            void set_outline_num_line(int line);
            int get_outline_num_line();
            Source get_reduced_vars_sizes();
            Source get_reduced_vars_redeclaration();
            Source get_reduced_vars_recover();
            Source get_parameter_declarations(Scope scope_of_decls);
            Source get_parameter_io(Scope scope_of_decls, Source start, Source separation, Source final);
            Source get_parameter_io_specific(Scope scope_of_decls, Source start, Source separation, Source final,std::vector<std::string> specific_names, int nup);
            Source get_parameter_in(Scope scope_of_decls, Source start, Source separation, Source final);
            Source get_parameter_in_specific(Scope scope_of_decls, Source start, Source separation, Source final,std::vector<std::string> specific_names, int nup);
            Source get_parameter_in_noch(Scope scope_of_decls, Source start, Source separation, Source final);
            Source get_parameter_sizes(Scope scope_of_decls);
            Source get_parameter_allocate(Scope scope_of_decls);
            Source get_parameter_addr(Scope scope_of_decls);
            Source get_parameter_addr_specific(Scope scope_of_decls,std::vector<std::string> specific_names);
            Source get_parameter_Haddr(Scope scope_of_decls);
            Source get_dynamic_var(Scope scope_of_decls);
            Source get_dynamic_parameter_sizes(Scope scope_of_decls, AST_t allocateAst, ScopeLink allocateScopeLink);
            Source find_grid(Scope scope_of_decls);
            int get_num_dynamic_var(Scope scope_of_decls);
            ObjectList<Source> splitMathExpression(Scope sC,std::string secondO);
            class TraverseASTFunctor4AssigmentLine : public TraverseASTFunctor {
            private:
                ScopeLink _slAL;
            public:

                TraverseASTFunctor4AssigmentLine(ScopeLink sl) : _slAL(sl) {};
                virtual ASTTraversalResult do_(const TL::AST_t &a) const
                {
                   
                    if (Expression::predicate(a)) {
                        Expression expr(a, _slAL);
                       // std::cout<<"e: "<<expr.prettyprint()<<endl;
                        bool retBool = false;
                        bool is_assigment = expr.is_assignment();
                        bool is_op_assigment = expr.is_operation_assignment();
                        if(is_assigment || is_op_assigment)
                            retBool = true;
                        return ast_traversal_result_helper(retBool,false);
                    }
                    return ast_traversal_result_helper(false, true);
                };
            };
            
            
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
            
            class TraverseASTFunctor4LocateUse : public TraverseASTFunctor {
            private:
                ScopeLink _slLU;
            public:

                TraverseASTFunctor4LocateUse(ScopeLink sl) : _slLU(sl) {};
                virtual ASTTraversalResult do_(const TL::AST_t &a) const
                {
                   
                    bool retBool = false;
//                   std::cout<<a.prettyprint()<<std::endl;
//                    if(ForStatement::predicate(a)) {
//                        Statement s(a,_slLU);
//                        ForStatement fS(s);
//                        std::cout<<fS.get_loop_body().get_ast().get_enclosing_statement().prettyprint()<<std::endl;
//                        TraverseASTFunctor4LocateUse forFor(s.get_scope_link());
//                        ObjectList<AST_t> expr_list = fS.get_loop_body().get_ast().depth_subtrees(forFor);
//                        for(int i=0;i<expr_list.size();++i){
//                            if(Expression::predicate(expr_list[i]))
//                            std::cout<<i<<": "<<expr_list[i].prettyprint()<<std::endl;
//                        }
//                        std::cin.get();
//                    }
                    if (Expression::predicate(a)) {
//                         std::cout<<"p: "<<a.prettyprint(true)<<std::endl;
                        Expression expr(a, _slLU);
                        if(expr.is_assignment()){
//                            std::cout<<"a2: "<<expr.prettyprint()<<std::endl;    
//                            std::cin.get();
                            retBool = true;
                        }
                        if(expr.is_function_call()){
//                            std::cout<<"a3: "<<expr.prettyprint()<<std::endl;    
//                            std::cin.get();
                            retBool = true;
                        }

                        if(expr.is_operation_assignment()){
//                            std::cout<<"a5: "<<expr.prettyprint()<<std::endl;    
//                            std::cin.get();
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
//                            std::cout<<"a61: "<<a.prettyprint()<<std::endl;  
//                            if(a.prettyprint().find(";")>0 && a.prettyprint().find(";")<a.prettyprint().length()) {
//                                Source aS;
//                                aS <<a.prettyprint().substr(0,a.prettyprint().find(";"));
//                                AST_t aAST = aS.parse_(a,_sl);
//                                if(Expression::predicate(aAST))
//                                    std::cout<<aAST.prettyprint()<<std::endl;
//                            }
                            retBool = true;
                            return ast_traversal_result_helper(retBool,false);
                        } else {
                            PragmaCustomConstruct test(a,_slLU);
                            if(test.is_construct()){
//                                 std::cout<<"a69: "<<a.prettyprint()<<"\n";  
                                 retBool = true;
                                 return ast_traversal_result_helper(retBool,false);
                            } 
                        }
                    }
                    return ast_traversal_result_helper(false, true);
                };
            };
            
            class TraverseASTFunctor4LocateFor : public TraverseASTFunctor {
                private:
                    ScopeLink _slLF;
                public:

                    TraverseASTFunctor4LocateFor(ScopeLink sl) : _slLF(sl) {};
                    virtual ASTTraversalResult do_(const TL::AST_t &a) const
                    {
                        bool retBool = false;
                        std::cout<<a.prettyprint()<<std::endl;
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
                        return ast_traversal_result_helper(false, true);
                    };
            };
            
            typedef std::unordered_map <std::string,AST_t> iter4io; 
            std::unordered_map<std::string,AST_t> get_parameter_io(Scope scope_of_decls);
            int get_parameter_ioSpecificIsIteratorDependent(Scope scope_of_decls, std::string name, std::string iterVar);
            ObjectList<Symbol> get_parameter_list();
            std::string cleanWhiteSpaces(std::string toClean);

            //! Creates an Outline object given a single statement
            Source get_reduced_vars_sizes_specific(std::vector<std::string> red_s);
            Outline(ScopeLink sl, Statement stmt);
            Outline(ScopeLink sl, Statement stmt, int out_num);
            Outline(ScopeLink sl, Statement stmt, ObjectList <std::string> unchanged, int out_num);
            //! Creates an Outline object given a set of statements
            /*!
              \param sl ScopeLink
              \param stmt_list This is a list of statements that should share the very same scope
             */
            Outline(ScopeLink sl, ObjectList<Statement> stmt_list, int out_num);

            //! Enables packed arguments
            /*!
              Packed arguments will pack all the arguments into a single
              structure and pass the structure by pointer
             */
            Outline & use_packed_arguments();

            //! Sets the outline function name
            /*!
              %Outline function will have a computed name unless it is set using this function
             */
            Outline & set_outline_name(const std::string & str);

            //! Returns the outline function name
            /*!
              If set_outline_name was called, the name set on the call will be returned here, otherwise
              this will be the computed name of the outline function
             */
            std::string get_outline_name();

            //! Disables embedding newly created outline
            /*!
              This disables automatic embedding of the outline. This is discouraged since
              sometimes it is not obvious where the outline must be placed.
             */
            Outline & do_not_embed();

            //! Sets a default parameter pass mode
            /*!
              For all symbols without an explicit pass mode, this will be the pass mode used.
              If no default pass mode is defined, it will be POINTER
              \sa ParameterPassing
             */
            void set_default_parameter_passing(ParameterPassing passing);
            //! Sets a parameter pass mode for a given Symbol
            /*!
              \param symbol The symbol whose pass mode is being set
              \param passing Passing mode
              \sa ParameterPassing
             */
            void set_parameter_passing(Symbol symbol, ParameterPassing passing);

            //! Returns the pass mode for a given symbol
            /*!
              If the symbol had not a pass mode set beforehand, the default
              passing mode will be returned.
             */
            ParameterPassing get_parameter_passing(Symbol);

            //! Returns the typename of the packing struct
            /*!
              If packed arguments are used, this is the name of the packed type
              as it should be used when filling it in point where the outline
              should be called.
             */
            std::string get_packing_struct_typename();

            //! Returns the parameters expected by the outline function
            /*!
              If packed arguments are used, this list contain the fields, in
              declaration order, of the struct.
             */


            ~Outline();
        };
        //! @}
    }
}

#endif // HLT_OUTLINE_HPP
