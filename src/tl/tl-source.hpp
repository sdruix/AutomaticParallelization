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



#ifndef TL_SOURCE_T_HPP
#define TL_SOURCE_T_HPP

#include "tl-common.hpp"
#include <string>
#include "tl-object.hpp"
#include "tl-type.hpp"
#include "tl-ast.hpp"
#include "tl-scope.hpp"
#include "tl-scopelink.hpp"
#include "tl-refptr.hpp"
#include "cxx-lexer.h"
#include "cxx-driver.h"
#include "cxx-scope.h"
#include "cxx-buildscope.h"

namespace TL
{
    class Type;
    class Source;

    //! Auxiliar class used by Source
    class LIBTL_CLASS SourceChunk
    {
        private:
            int _refcount;
        public:
            virtual std::string get_source() const = 0;
            virtual ~SourceChunk() { } 
            virtual bool is_source_text() { return false; }
            virtual bool is_source_ref() { return false; }

            SourceChunk()
                : _refcount(1)
            {
            }

            void obj_reference()
            {
                this->_refcount++;
            }

            void obj_unreference()
            {
                this->_refcount--;

                if (this->_refcount == 0)
                {
                    delete this;
                }
            }
    };

    //! A chunk of literal text
    class LIBTL_CLASS SourceText : public SourceChunk
    {
        private:
            std::string _source;
        public:
            virtual std::string get_source() const
            {
                return _source;
            }

            SourceText(const std::string& str)
                : _source(str)
            {
            }

            virtual ~SourceText() { } 

            virtual bool is_source_text() { return true; }

            friend class Source;
    };

    //! A chunk that references another Source
    class LIBTL_CLASS SourceRef : public SourceChunk
    {
        private:
            RefPtr<Source> _src;
        public:
            SourceRef(RefPtr<Source> src)
                : _src(src)
            {
            }
            virtual std::string get_source() const;

            virtual ~SourceRef() { }

            virtual bool is_source_ref() { return true; }

            friend class Source;
    };

    typedef RefPtr<SourceChunk> SourceChunkRef;

    typedef RefPtr<ObjectList<SourceChunkRef> > chunk_list_ref_t;

    //! A class used to generate in, a convenient way, code in the compiler
    class LIBTL_CLASS Source : public Object
    {
        public:
            //! Flags that modify the behaviour of parsing
            enum ParseFlags
            {
                UNKNOWN = 0,
                DEFAULT = 1 << 0,
                //! Allows symbols be redefined, thus overwriting previous definitions
                ALLOW_REDECLARATION = 1 << 1,
                //! Does not check an expression
                DO_NOT_CHECK_EXPRESSION = 1 << 2,
            };
        private:
            chunk_list_ref_t _chunk_list;

            void append_text_chunk(const std::string& str);
            void append_source_ref(SourceChunkRef src);

            bool all_blanks() const;

            //! Parses a member declaration
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param class_type Class type where this member should belong to. Make sure this is a named type!
             */
            AST_t parse_member(AST_t ref_tree, TL::ScopeLink scope_link, Type class_type);

            typedef int (*prepare_lexer_fun_t)(const char*);
            typedef int (*parse_fun_t)(AST*);
            template <typename T>
            struct FinishParseFun
            { 
                typedef T (*Type)(ParseFlags, decl_context_t, scope_link_t*, AST);
            };

            template <typename T>
            T parse_generic(AST_t ref_tree, 
                    TL::ScopeLink scope_link, 
                    ParseFlags parse_flags,
                    const std::string& subparsing_prefix,
                    prepare_lexer_fun_t prepare_lexer,
                    parse_fun_t parse_function,
                    typename FinishParseFun<T>::Type finish_parse
                    );

            template <typename T>
            T parse_generic_lang(AST_t ref_tree, 
                    TL::ScopeLink scope_link, 
                    ParseFlags parse_flags,
                    const std::string& subparsing_prefix,
                    typename FinishParseFun<T>::Type finish_parse
                    );


            template <typename T>
                T parse_generic_lang_scope(
                        decl_context_t decl_context,
                        TL::ScopeLink sl,
                        ParseFlags parse_flags,
                        const std::string& subparsing_prefix,
                        typename FinishParseFun<T>::Type finish_parse
                        );

            template <typename T>
                T parse_generic_scope(
                        decl_context_t decl_context,
                        TL::ScopeLink scope_link, 
                        ParseFlags parse_flags,
                        const std::string& subparsing_prefix,
                        prepare_lexer_fun_t prepare_lexer,
                        parse_fun_t parse_function,
                        typename FinishParseFun<T>::Type finish_parse
                        );
        public:
            //! Constructor
            /*!
             * Creates an empty source
             */
            Source()
                : _chunk_list(0)
            {
                _chunk_list = chunk_list_ref_t(new ObjectList<SourceChunkRef>());
            }

            virtual ~Source()
            {
            }

            //! Constructor
            /*!
             * Creates a source after a string.
             */
            Source(const std::string& str)
                : _chunk_list(0)
            {
                _chunk_list = chunk_list_ref_t(new ObjectList<SourceChunkRef>());
                _chunk_list->push_back(SourceChunkRef(new SourceText(str)));
            }

            Source(RefPtr<Object> obj)
                : _chunk_list(0)
            {
                RefPtr<Source> cast = RefPtr<Source>::cast_dynamic(obj);

                if (cast.get_pointer() == NULL)
                {
                    if (typeid(*obj.get_pointer()) != typeid(Undefined))
                    {
                        std::cerr << "Bad initialization of Source" << std::endl;
                    }
                    else
                    {
                        _chunk_list = chunk_list_ref_t(new ObjectList<SourceChunkRef>());
                    }
                }
                else
                {
                    // Share the list
                    _chunk_list = cast->_chunk_list;
                }

                // ---
            }

            //! Copy-constructor
            Source(const Source& src)
                // This is fine, we want to share the same source list for both
                : Object(src), _chunk_list(src._chunk_list)
            {
            }

            //! States that this is a source
            virtual bool is_source() const
            {
                return true;
            }
            
            //! Returns the textual information held by this Source
            /*!
             * Referenced Source objects in this one are recursively called
             * their get_source to form the whole text.
             *
             * \a with_newlines Formats in a pretty way the source code so it can be more readable
             */
            std::string get_source(bool with_newlines = false) const;

            //! This is a convenience function that calls get_source
            operator std::string();
            
            //! Convenience function to build lists with separators
            /*!
             * If the original source is empty, no separator will be added.
             */
            Source& append_with_separator(const std::string& src, const std::string& separator);
            //! Convenience function to build lists with separators
            /*!
             * If the original source is empty, no separator will be added.
             */
            Source& append_with_separator(Source& src, const std::string& separator);

            //! Appends a reference to a Source in this object
            /*!
             * Do not create cyclic dependences of sources
             */
            Source& operator<<(Source& src);
            //! Appends a text chunk
            Source& operator<<(const std::string& str);
            //! Appends a text chunk after an integer
            /*!
             * \param n This integer is: converted into decimal base and appended as a string
             */
            Source& operator<<(int n);

            //! Appends a reference to Source
            Source& operator<<(RefPtr<Source>);

            // These should work correctly in C++ as they are able to get the exact
            // declaration context of the reference tree (ref_tree)
            //! Parses a top-level declaration in context of global scope
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             *
             * This function is only for C/C++
             */
            AST_t parse_global(AST_t ref_tree, TL::ScopeLink scope_link);
            //! Parses a statement
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             */
            AST_t parse_statement(Scope sc, TL::ScopeLink sl, ParseFlags parse_flags = DEFAULT);
            AST_t parse_statement(AST_t ref_tree, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);
            //! Parses an expression
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             *
             * This function can be used in C/C++ and Fortran
             */
            AST_t parse_expression(Scope sc, TL::ScopeLink sl, ParseFlags parse_flags = DEFAULT);
            AST_t parse_expression(AST_t ref_tree, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);
            //! Parses an expression list
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             *
             * This function can be used in C/C++ and Fortran
             */
            AST_t parse_expression_list(AST_t ref_tree, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);

            //! Parses an id-expression
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             *
             * This function is only for C/C++
             */
            AST_t parse_id_expression(AST_t ref_tree, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);

            //! Parses an id-expression
            /*
             * \param scope Scope used to parse this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             *
             * This function is only for C/C++
             */
            AST_t parse_id_expression(Scope scope, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);

            //! Parses an id-expression without checking the expression
            /*!
             * \param scope Scope used to parse this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             *
             * This function is only for C/C++
             */
            AST_t parse_id_expression_wo_check(Scope scope, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);

            //! Parses a declaration
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param parse_flags Parsing flags
             *
             * This function is only for C/C++
             */
            AST_t parse_declaration(AST_t ref_tree, TL::ScopeLink scope_link, ParseFlags parse_flags = DEFAULT);

            //! Parses a member declaration
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \param class_symbol Class symbol where this member should belong to
             *
             * This function is only for C/C++
             */
            AST_t parse_member(AST_t ref_tree, TL::ScopeLink scope_link, Symbol class_symbol);
            //! Convenience function to parse a type and synthesize it
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \return The synthesized type
             *
             * This function is only for C/C++
             */
            Type parse_type(AST_t ref_tree, TL::ScopeLink scope_link);
            //! Convenience function to parse a comma separated list of types and synthesize them
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             * \return The synthesized type
             *
             * This function is only for C/C++
             */
            ObjectList<Type> parse_type_list(AST_t ref_tree, TL::ScopeLink scope_link);

            //! Parses a Fortran program unit
            /*!
             * \param ref_tree Reference tree used when parsing this code
             * \param scope_link Scope link used to get the scope of \a ref_tree
             *
             * This function is only for Fortran
             *
             */
            AST_t parse_program_unit(AST_t ref_tree, ScopeLink scope_link);

            // Format string for debugging
            static std::string format_source(const std::string&);

            //! States whether this Source is empty
            bool empty() const;

            bool operator==(const Source& src) const;
            bool operator!=(const Source& src) const;
            bool operator<(const Source& src) const;
            Source& operator=(const Source& src);
    };

    //! Creates an inner comment in the code
    /*!
     * When these are prettyprinted onto the output file
     * they are converted into normal C or C++ comments
     */
    LIBTL_EXTERN std::string comment(const std::string& str);
    //! Creates an inner preprocessor line
    /*!
     * When these are prettyprinted onto the output file
     * they are converted into normal C or C++ preprocessor lines
     */
    LIBTL_EXTERN std::string preprocessor_line(const std::string& str);

    //! Creates a placeholder for the given AST_t
    /*!
     * This function creates a placeholder for statements. Once parsed, \a
     * placeholder can be used as a reference tree for further parsings and can
     * be replaced. If it is not replaced it will default to an empty
     * statement.
     */
    LIBTL_EXTERN std::string statement_placeholder(AST_t& placeholder);

    //! Creates a #line marker
    /*!
     * This function adds a line marker useable for cpp-style preprocessing. 
     * Use this to add more context to your trees, so warnings and messages
     * have better context
     * \a filename Can be an empty string
     * \a line Line
     */
    LIBTL_EXTERN std::string line_marker(const std::string& filename, int line);

    //! Convenience function to convert a list into a string
    /*!
     * \param t List of elements of type T
     * \param to_str Function that gives a std::string after an object of type T
     * \param separator Separator that will be used to separe the strings
     * \return A single string with the result of \a to_str applied to all elements of \a t separated with \a separator
     */
    template <class T>
    std::string to_string(const ObjectList<T>& t, Functor<std::string, T>& to_str, const std::string& separator = "")
    {
        std::string result;

        for (typename ObjectList<T>::const_iterator it = t.begin();
                it != t.end();
                it++)
        {
            if (it != t.begin())
            {
                result = result + separator;
            }

            result = result + to_str(*it);
        }

        return result;
    }

    LIBTL_EXTERN std::string to_string(const ObjectList<std::string>& t, const std::string& separator = "");
}

#endif // TL_SOURCE_T_HPP
