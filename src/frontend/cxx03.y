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

%{
/*
   Parser of ISO/IEC 14882:2003 - C++

   It parses a superset of the language.

   Must be compiled with rofi-bison-2.3
   Ask for it at <rferrer@ac.upc.edu>
 */

#include "cxx-ast.h"
#include "cxx-parser.h"
#include "cxx-lexer.h"
#include "cxx-utils.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
// Sometimes we need lots of memory
#define YYMAXDEPTH (10000000)

%}

%glr-parser

%union {
	token_atrib_t token_atrib;
	AST ast;
	AST ast2[2];
	AST ast3[3];
	AST ast4[4];
	node_t node_type;
    const char *text;
};


// This is a specific feature of rofi-bison 2.3
// %default-merge <ambiguityHandler>

%parse-param {AST* parsed_tree}

%{
extern int yylex(void);
static AST ambiguityHandler (YYSTYPE x0, YYSTYPE x1);
void yyerror(AST* parsed_tree UNUSED_PARAMETER, const char* c);
%}

// C++ tokens
%token<token_atrib> ADD_ASSIGN "+="
%token<token_atrib> ANDAND "&&"
%token<token_atrib> AND_ASSIGN "&="
%token<token_atrib> ASM "__asm__"
%token<token_atrib> AUTO "auto"
%token<token_atrib> TOKEN_BOOL "bool"
%token<token_atrib> BOOLEAN_LITERAL "boolean-literal"
%token<token_atrib> BREAK "break" 
%token<token_atrib> CASE "case"
%token<token_atrib> CATCH "catch"
%token<token_atrib> TOKEN_CHAR "char"
%token<token_atrib> CHARACTER_LITERAL "character-literal"
%token<token_atrib> CLASS "class"
%token<token_atrib> TOKEN_CONST "const"
%token<token_atrib> CONST_CAST "const_cast"
%token<token_atrib> CONTINUE "continue"
%token<token_atrib> DECIMAL_LITERAL "decimal-literal"
%token<token_atrib> DEFAULT "default"
%token<token_atrib> TOKEN_DELETE "delete"
%token<token_atrib> DIV_ASSIGN "/="
%token<token_atrib> DO "do"
%token<token_atrib> TWO_COLONS "::"
%token<token_atrib> TOKEN_DOUBLE "double"
%token<token_atrib> DYNAMIC_CAST "dynamic_cast"
%token<token_atrib> ELSE "else"
%token<token_atrib> ENUM "enum"
%token<token_atrib> EQUAL "=="
%token<token_atrib> DECLTYPE "decltype"
%token<token_atrib> EXPLICIT "explicit"
%token<token_atrib> EXPORT "export"
%token<token_atrib> EXTERN "extern"
%token<token_atrib> TOKEN_FLOAT "float"
%token<token_atrib> FLOATING_LITERAL "floating-literal"
%token<token_atrib> HEXADECIMAL_FLOAT "hexadecimal-floating-literal"
%token<token_atrib> FOR "for"
%token<token_atrib> FRIEND "friend"
%token<token_atrib> GOTO "goto"
%token<token_atrib> HEXADECIMAL_LITERAL "hexadecimal-integer-literal"
%token<token_atrib> IDENTIFIER "identifier"
%token<token_atrib> IF "if"
%token<token_atrib> INLINE "inline"
%token<token_atrib> TOKEN_INT "int"
%token<token_atrib> LEFT "<<"
%token<token_atrib> LEFT_ASSIGN "<<="
%token<token_atrib> LESS_OR_EQUAL "<="
%token<token_atrib> TOKEN_LONG "long"
%token<token_atrib> MINUSMINUS "--"
%token<token_atrib> MOD_ASSIGN "%="
%token<token_atrib> MUL_ASSIGN "*="
%token<token_atrib> MUTABLE "mutable"
%token<token_atrib> NAMESPACE "namespace"
%token<token_atrib> TOKEN_NEW "new"
%token<token_atrib> NOT_EQUAL "!="
%token<token_atrib> OCTAL_LITERAL "octal-literal"
%token<token_atrib> OPERATOR "operator"
%token<token_atrib> OR_ASSIGN "|="
%token<token_atrib> OROR "||"
%token<token_atrib> PLUSPLUS "++"
%token<token_atrib> PRIVATE "private"
%token<token_atrib> PROTECTED "protected"
%token<token_atrib> PTR_OP "->"
%token<token_atrib> PTR_OP_MUL "->*"
%token<token_atrib> PUBLIC "public"
%token<token_atrib> REGISTER "register"
%token<token_atrib> REINTERPRET_CAST "reinterpret_cast"
%token<token_atrib> RETURN "return"
%token<token_atrib> TOKEN_SHORT "short"
%token<token_atrib> TOKEN_SIGNED "signed"
%token<token_atrib> SIZEOF "sizeof"
%token<token_atrib> STATIC "static"
%token<token_atrib> STATIC_CAST "static_cast"
%token<token_atrib> STRING_LITERAL "string-literal"
%token<token_atrib> STRUCT "struct"
%token<token_atrib> SUB_ASSIGN "-="
%token<token_atrib> SWITCH "switch"
%token<token_atrib> TEMPLATE "template"
%token<token_atrib> TOKEN_THIS "this"
%token<token_atrib> THROW "throw"
%token<token_atrib> ELLIPSIS "..."
%token<token_atrib> TRY "try"
%token<token_atrib> TYPEDEF "typedef"
%token<token_atrib> TYPEID "typeid"
%token<token_atrib> TYPENAME "typename"
%token<token_atrib> UNION "union"
%token<token_atrib> TOKEN_UNSIGNED "unsigned"
%token<token_atrib> USING "using"
%token<token_atrib> VIRTUAL "virtual"
%token<token_atrib> TOKEN_VOID "void"
%token<token_atrib> TOKEN_VOLATILE "volatile"
%token<token_atrib> TOKEN_WCHAR_T "wchar_t"
%token<token_atrib> WHILE "while"
%token<token_atrib> XOR_ASSIGN "^="

%token<token_atrib> STATIC_ASSERT "static_assert"

%token<token_atrib> UNKNOWN_PRAGMA "<unknown-pragma>"

%token<token_atrib> PP_COMMENT "<preprocessor-comment>"
%token<token_atrib> PP_TOKEN "<preprocessor-token>"

// g++ type traits
%token<token_atrib> GXX_HAS_NOTHROW_ASSIGN "__has_nothrow_assign"
%token<token_atrib> GXX_HAS_NOTHROW_CONSTRUCTOR "__has_nothrow_constructor"
%token<token_atrib> GXX_HAS_NOTHROW_COPY "__has_nothrow_copy"
%token<token_atrib> GXX_HAS_TRIVIAL_ASSIGN "__has_trivial_assign"
%token<token_atrib> GXX_HAS_TRIVIAL_CONSTRUCTOR "__has_trivial_constructor"
%token<token_atrib> GXX_HAS_TRIVIAL_COPY "__has_trivial_copy"
%token<token_atrib> GXX_HAS_TRIVIAL_DESTRUCTOR "__has_trivial_destructor"
%token<token_atrib> GXX_HAS_VIRTUAL_DESTRUCTOR "__has_virtual_destructor"
%token<token_atrib> GXX_IS_ABSTRACT "__is_abstract"
%token<token_atrib> GXX_IS_BASE_OF "__is_base_of"
%token<token_atrib> GXX_IS_CLASS "__is_class"
%token<token_atrib> GXX_IS_CONVERTIBLE_TO "__is_convertible_to"
%token<token_atrib> GXX_IS_EMPTY "__is_empty"
%token<token_atrib> GXX_IS_ENUM "__is_enum"
%token<token_atrib> GXX_IS_LITERAL_TYPE "__is_literal_type"
%token<token_atrib> GXX_IS_POD "__is_pod"
%token<token_atrib> GXX_IS_POLYMORPHIC "__is_polymorphic"
%token<token_atrib> GXX_IS_STANDARD_LAYOUT "__is_standard_layout"
%token<token_atrib> GXX_IS_TRIVIAL "__is_trivial"
%token<token_atrib> GXX_IS_UNION "__is_union"

// Lexical symbols
%token<token_atrib> '!'
%token<token_atrib> '%'
%token<token_atrib> '&'
%token<token_atrib> '('
%token<token_atrib> ')'
%token<token_atrib> '*'
%token<token_atrib> '+'
%token<token_atrib> ','
%token<token_atrib> '-'
%token<token_atrib> '.'
%token<token_atrib> '/'
%token<token_atrib> ':'
%token<token_atrib> ';'
%token<token_atrib> '<'
%token<token_atrib> '='
// AB1 is '>' when it is just before another '>'
// KLUDGE: Note that since names can't be repeated we surround this one with spaces
// The error message may be a bit weird, as if it was bad formatted
%token<token_atrib> AB1 "'>>' "
// AB2 is '>' when it is just before '='
// KLUDGE: Note that since names can't be repeated we surround this one with one space before
// The error message may be a bit weird, as if it was bad formatted
%token<token_atrib> AB2 "'>=' "
%token<token_atrib> '>'
%token<token_atrib> '?'
%token<token_atrib> '['
%token<token_atrib> ']'
%token<token_atrib> '^'
%token<token_atrib> '{'
%token<token_atrib> '|'
%token<token_atrib> '}'
%token<token_atrib> '~'

// Tokens implemented with grammar
%type<token_atrib> right_token
%type<token_atrib> right_assign_token
%type<token_atrib> greater_equal_token
%type<token_atrib> right_bracket_token

// GNU Extensions
%token<token_atrib> BUILTIN_VA_ARG "__builtin_va_arg"
%token<token_atrib> BUILTIN_OFFSETOF "__builtin_offsetof"
%token<token_atrib> ALIGNOF "__alignof__"
%token<token_atrib> EXTENSION "__extension__"
%token<token_atrib> REAL "__real__"
%token<token_atrib> IMAG "__imag__"
%token<token_atrib> LABEL "__label__"
%token<token_atrib> COMPLEX "__complex__"
%token<token_atrib> TYPEOF "__typeof__"
%token<token_atrib> RESTRICT "__restrict__"
%token<token_atrib> ATTRIBUTE "__attribute__"
%token<token_atrib> THREAD "__thread__"


// Nonterminals
%type<ast> abstract_declarator
%type<ast> abstract_direct_declarator
%type<ast> access_specifier
%type<ast> additive_expression
%type<ast> and_expression
%type<ast> asm_definition
%type<ast> asm_operand
%type<ast> asm_operand_list
%type<ast> asm_operand_list_nonempty
%type<ast> asm_specification
%type<ast> assignment_expression
%type<ast> attribute
%type<ast> attribute_list
%type<ast> attributes
%type<ast> attributes_opt
%type<ast> attribute_value
%type<ast> base_clause
%type<ast> base_specifier
%type<ast> base_specifier_list
%type<ast> block_declaration
%type<ast> non_empty_block_declaration
%type<ast> common_block_declaration
%type<ast> builtin_types
%type<ast> cast_expression
%type<ast> class_head
%type<ast> class_key
%type<ast> class_or_namespace_name
%type<ast> class_specifier
%type<ast> compound_statement
%type<ast> condition
%type<ast> condition_opt
%type<ast> conditional_expression
%type<ast> constant_expression
%type<ast> conversion_declarator
%type<ast> conversion_function_id
%type<ast> conversion_type_id
%type<ast> ctor_initializer
%type<ast> ctor_initializer_opt
%type<ast> cv_qualifier
%type<ast> cv_qualifier_seq
%type<ast> declaration
%type<ast> declaration_sequence
%type<ast> declaration_statement
%type<ast> declarator
%type<ast> declarator_id
%type<ast> decl_specifier_alone_seq
%type<ast> decl_specifier_seq_0
%type<ast> decl_specifier_seq_0_may_end_with_attribute
%type<ast> decl_specifier_seq_ended_with_named_type_spec
%type<ast> delete_expression
%type<ast> designation
%type<ast> designator
%type<ast> designator_list
%type<ast> offsetof_member_designator
%type<ast> direct_declarator
%type<ast> direct_new_declarator
%type<ast> elaborated_type_specifier
%type<ast> enumeration_definition
%type<ast> enumeration_list
%type<ast> enumeration_list_proper
%type<ast> enum_specifier
%type<ast> equality_expression
%type<ast> exception_declaration
%type<ast> exception_specification
%type<ast> exclusive_or_expression
%type<ast> explicit_instantiation
%type<ast> explicit_specialization
%type<ast> expression
%type<ast> expression_opt
%type<ast> expression_list
%type<ast> expression_statement
%type<ast> for_init_statement
%type<ast> non_functional_declarator
%type<ast> non_functional_direct_declarator
%type<ast> nonglobal_non_functional_declarator
%type<ast> nonglobal_non_functional_direct_declarator
%type<ast> functional_declarator
%type<ast> functional_declarator_id
%type<ast> functional_final_declarator_id
%type<ast> functional_direct_declarator
%type<ast> function_body
%type<ast3> function_definition_header
%type<ast> function_definition
%type<ast> function_specifier
%type<ast> handler
%type<ast> handler_seq
%type<ast> id_expression
%type<ast> id_type_expr
%type<ast> if_else_eligible_statements
%type<ast> if_else_statement
%type<ast> if_statement
%type<ast> inclusive_or_expression
%type<ast> init_declarator
%type<ast> init_declarator_list
%type<ast> initializer
%type<ast> initializer_clause
%type<ast> initializer_list
%type<ast> equal_initializer
%type<ast> parent_initializer
%type<ast> equal_or_parent_initializer
%type<ast> iteration_statement
%type<ast> jump_statement
%type<ast> label_declaration
%type<ast> label_declarator_seq
%type<ast> labeled_statement
%type<ast> linkage_specification
%type<ast> literal
%type<ast> logical_and_expression
%type<ast> logical_or_expression
%type<ast> member_declaration
%type<ast> member_declarator
%type<ast> member_declarator_list
%type<ast> member_specification
%type<ast> member_specification_seq
%type<ast> mem_initializer
%type<ast> mem_initializer_id
%type<ast> mem_initializer_list
%type<ast> multiplicative_expression
%type<ast> named_namespace_definition
%type<ast> namespace_inline
%type<ast> namespace_alias_definition
%type<ast> namespace_definition
%type<ast> nested_name_specifier
%type<ast> nested_name_specifier_0
%type<ast> new_declarator
%type<ast> new_expression
%type<ast> new_initializer
%type<ast> new_placement
%type<ast> new_type_id
%type<ast> no_if_statement
%type<ast> nonabstract_declarator
%type<ast> nonabstract_direct_declarator
%type<ast> nontype_specifier
%type<ast> nontype_specifier_for_named
%type<ast> nontype_specifier_for_named_without_attribute
%type<ast> nontype_specifier_no_end_attrib_seq
%type<ast> nontype_specifier_no_end_attrib_seq_for_named
%type<ast> nontype_specifier_seq
%type<ast> nontype_specifier_seq_for_named
%type<ast> nontype_specifier_without_attribute
%type<ast> operator
%type<ast> operator_function_id
%type<ast> parameter_declaration
%type<ast> parameter_declaration_clause
%type<ast> parameter_declaration_clause_nonempty
%type<ast> parameter_declaration_list
%type<ast> pm_expression
%type<ast> postfix_expression
%type<ast> primary_expression
%type<ast> pseudo_destructor_name
%type<ast> ptr_operator
%type<ast> qualified_id
%type<ast> qualified_id_globals
%type<ast> qualified_id_globals_no_template
%type<ast> qualified_id_globals_operator
%type<ast> qualified_id_globals_template
%type<ast> qualified_id_no_template
%type<ast> qualified_id_template
%type<ast> qualified_id_type_name
%type<ast> qualified_id_type_expr
%type<ast> unqualified_id_funct
%type<ast> unqualified_id_type_name
%type<ast> relational_expression
%type<ast> selection_statement
%type<ast> shift_expression
%type<ast> simple_declaration
%type<ast> non_empty_simple_declaration
%type<ast> simple_type_specifier
%type<ast> statement
%type<ast> statement_seq
%type<ast> storage_class_specifier
%type<ast> string_literal
%type<ast> template_and_expression
%type<ast> template_argument
%type<ast> template_argument_list
%type<ast> template_assignment_expression
%type<ast> template_conditional_expression
%type<ast> templated_declaration
%type<ast> template_declaration
%type<ast> template_equality_expression
%type<ast> template_exclusive_or_expression
%type<ast> template_expression
%type<ast> template_id
%type<ast> destructor_id
%type<ast> destructor_template_id
%type<ast> template_inclusive_or_expression
%type<ast> template_logical_and_expression
%type<ast> template_logical_or_expression
%type<ast> template_parameter
%type<ast> template_parameter_list
%type<ast> template_relational_expression
%type<ast> template_shift_expression
%type<ast> throw_expression
%type<ast> translation_unit
%type<ast> try_block
%type<ast> type_id
%type<ast> type_id_list
%type<ast> type_parameter
%type<ast> named_type_specifier
%type<ast> no_named_type_specifier
%type<ast> no_named_simple_type_specifier
%type<ast> named_simple_type_specifier
%type<ast> type_specifier_alone
%type<ast> type_specifier_seq_0
%type<ast> type_specifier_seq_0_may_end_with_attribute
%type<ast> type_specifier_seq_ended_with_named_type_spec
%type<ast> unary_expression
%type<ast> unknown_pragma
%type<ast> unnamed_namespace_definition
%type<ast> unqualified_id
%type<ast> using_declaration
%type<ast> using_directive
%type<ast> volatile_optional
%type<ast> static_assert_declaration
%type<ast> gnu_type_traits
%type<ast> braced_init_list

// Nonglobal versions of some productions
// their FIRST set should never include '::' (TWO_COLONS)
%type<ast> nonglobal_abstract_declarator
%type<ast> nonglobal_conversion_declarator
%type<ast> nonglobal_declarator
%type<ast> nonglobal_declarator_id
%type<ast> nonglobal_direct_declarator
%type<ast> nonglobal_functional_declarator
%type<ast> nonglobal_functional_declarator_id
%type<ast> nonglobal_functional_direct_declarator
%type<ast> nonglobal_functional_final_declarator_id
%type<ast> nonglobal_id_expression
%type<ast> nonglobal_id_type_expr
%type<ast> nonglobal_init_declarator
%type<ast> nonglobal_init_declarator_list
%type<ast> nonglobal_member_declarator
%type<ast> nonglobal_member_declarator_list
%type<ast> nonglobal_new_declarator
%type<ast> nonglobal_nonabstract_declarator
%type<ast> nonglobal_ptr_operator


%type<node_type> unary_operator
%type<node_type> assignment_operator





%type<ast> subparse_type_list

// Subparsing
%token<token_atrib> SUBPARSE_EXPRESSION "<subparse-expression>"
%token<token_atrib> SUBPARSE_EXPRESSION_LIST "<subparse-expression-list>"
%token<token_atrib> SUBPARSE_STATEMENT "<subparse-statement>"
%token<token_atrib> SUBPARSE_DECLARATION "<subparse-declaration>"
%token<token_atrib> SUBPARSE_MEMBER "<subparse-member>"
%token<token_atrib> SUBPARSE_TYPE "<subparse-type>"
%token<token_atrib> SUBPARSE_TYPE_LIST "<subparse-type-list>"
%token<token_atrib> SUBPARSE_ID_EXPRESSION "<subparse-id-expression>"

























































































%type<ast> shape_seq
%type<ast> shape
%type<ast> noshape_cast_expression



















































%token<token_atrib> STATEMENT_PLACEHOLDER "<statement-placeholder>"

%{
    static AST* decode_placeholder(const char *);
%}



















// This is code





























%token<token_atrib> VERBATIM_PRAGMA "<verbatim pragma>"
%token<token_atrib> VERBATIM_CONSTRUCT "<verbatim construct>"
%token<token_atrib> VERBATIM_TYPE "<verbatim type clause>"
%token<token_atrib> VERBATIM_TEXT "<verbatim text>"

%type<ast> verbatim_construct


%token<token_atrib> PRAGMA_CUSTOM "<pragma-custom>"
%token<token_atrib> PRAGMA_CUSTOM_NEWLINE "<pragma-custom-newline>"
%token<token_atrib> PRAGMA_CUSTOM_DIRECTIVE "<pragma-custom-directive>"
%token<token_atrib> PRAGMA_CUSTOM_CONSTRUCT "<pragma-custom-construct>"
%token<token_atrib> PRAGMA_CUSTOM_CONSTRUCT_NOEND "<pragma-custom-construct-noend>"
%token<token_atrib> PRAGMA_CUSTOM_END_CONSTRUCT "<pragma-custom-end-construct>"
%token<token_atrib> PRAGMA_CUSTOM_CLAUSE "<pragma-custom-clause>"

%token<token_atrib> PRAGMA_CLAUSE_ARG_TEXT "<pragma-clause-argument-text>"

%type<ast> pragma_custom_directive
%type<ast> pragma_custom_line_directive
%type<ast> pragma_custom_line_construct
%type<ast> pragma_custom_construct_statement

%type<ast> pragma_custom_construct_declaration
%type<ast> pragma_custom_construct_member_declaration








%type<ast> pragma_custom_clause
%type<ast> pragma_custom_clause_seq
%type<ast> pragma_custom_clause_opt_seq

// %type<ast> pragma_expression_entity
// %type<ast> pragma_expression_entity_list

%type<ast> pragma_clause_arg_list

%type<text> pragma_clause_arg
%type<text> pragma_clause_arg_item 
%type<text> pragma_clause_arg_text


































































































































































































































































%type<ast> custom_construct_statement
%type<ast> custom_construct_header
%type<ast> custom_construct_parameters_seq
%type<ast> custom_construct_parameter
%token<token_atrib> CONSTRUCT "__construct__"


















































%token<token_atrib> SUBPARSE_OMP_UDR_DECLARE "<subparse-omp-udr-declare>"
%token<token_atrib> SUBPARSE_OMP_UDR_DECLARE_2 "<subparse-omp-udr-declare-2>"

%type<ast> omp_udr_operator_list
%type<ast> omp_udr_operator
%type<ast> omp_udr_operator_2

%type<ast> omp_udr_qualified_operator

%type<ast> omp_udr_unqualified_operator
%type<ast> omp_udr_builtin_op
%type<ast> omp_udr_type_specifier
%type<ast> omp_udr_type_specifier_2
%type<ast> omp_udr_declare_arg
%type<ast> omp_udr_declare_arg_2
%type<ast> omp_udr_expression

%token<token_atrib> SUBPARSE_OMP_UDR_IDENTITY "<subparse-omp-udr-identity>"
%token<token_atrib> OMP_UDR_CONSTRUCTOR "constructor"

%token<token_atrib> SUBPARSE_OMP_OPERATOR_NAME "<subparse_omp_operator_name>"

%type<ast> omp_udr_identity

%type<ast> omp_udr_constructor_arguments























































































































































































































































// Lexical Symbol for superscalar regions
%token<token_atrib> TWO_DOTS ".."

// Tokens for subparsing
%token<token_atrib> SUBPARSE_SUPERSCALAR_DECLARATOR "<subparse-superscalar-declarator>"
%token<token_atrib> SUBPARSE_SUPERSCALAR_DECLARATOR_LIST "<subparse-superscalar-declarator-list>"
%token<token_atrib> SUBPARSE_SUPERSCALAR_EXPRESSION "<subparse-superscalar-expression>"

// Tokens for rules
%type<ast> superscalar_declarator superscalar_declarator_list opt_superscalar_region_spec_list superscalar_region_spec_list superscalar_region_spec

















































































%token<token_atrib> CUDA_DEVICE "__device__" 
%token<token_atrib> CUDA_GLOBAL "__global__"
%token<token_atrib> CUDA_HOST "__host__"
%token<token_atrib> CUDA_CONSTANT "__constant__"
%token<token_atrib> CUDA_SHARED "__shared__"
%token<token_atrib> CUDA_KERNEL_LEFT "<<<"
%token<token_atrib> CUDA_KERNEL_RIGHT ">>>"

%type<ast> cuda_specifiers
%type<ast> cuda_kernel_call
%type<ast> cuda_kernel_arguments
%type<ast> cuda_kernel_config_list

%type<token_atrib> cuda_kernel_config_left
%type<token_atrib> cuda_kernel_config_right



























































































%token<token_atrib> XL_BUILTIN_SPEC "_Builtin"













%type<ast> subparsing

%start translation_unit

%%

// I don't know the exact reason behind this, but the first rule
// determines the result of the ambiguity handler, so define
// first translation_unit to ensure that the ambiguity handler
// returns 'ast' type.

// *********************************************************
// A.3 - Basic concepts
// *********************************************************

translation_unit : declaration_sequence
{
	*parsed_tree = $1;
}
| /* empty */
{
    *parsed_tree = NULL;
}
;

// *********************************************************
// A.6. - Declarations
// *********************************************************

declaration_sequence : declaration
{
	$$ = ASTListLeaf($1);
}
| declaration_sequence declaration
{
	$$ = ASTList($1, $2);
}
;

declaration : block_declaration 
{
	$$ = $1;
}
| function_definition 
{
	$$ = $1;
}
| template_declaration
{
	$$ = $1;
}
| explicit_instantiation
{
	$$ = $1;
}
| explicit_specialization
{
	$$ = $1;
}
| linkage_specification
{
	$$ = $1;
}
| namespace_definition
{
	$$ = $1;
}
;

linkage_specification : EXTERN string_literal '{' declaration_sequence '}'
{
	$$ = ASTMake2(AST_LINKAGE_SPEC, $2, $4, $1.token_file, $1.token_line, NULL);
}
| EXTERN string_literal '{' '}'
{
	$$ = ASTMake2(AST_LINKAGE_SPEC, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| EXTERN string_literal declaration
{
	$$ = ASTMake2(AST_LINKAGE_SPEC_DECL, $2, $3, $1.token_file, $1.token_line, NULL);
}
;

namespace_definition : named_namespace_definition
{
	$$ = $1;
}
| unnamed_namespace_definition
{
	$$ = $1;
}
;

namespace_inline : INLINE
{
    $$ = ASTLeaf(AST_INLINE_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

// extension_namespace_definition generates exactly the same
// so it is not repeated
named_namespace_definition : NAMESPACE IDENTIFIER '{' declaration_sequence '}'
{
	AST identif = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_NAMESPACE_DEFINITION, identif, $4, $1.token_file, $1.token_line, NULL);
}
| NAMESPACE IDENTIFIER '{' '}'
{
	AST identif = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_NAMESPACE_DEFINITION, identif, NULL, $1.token_file, $1.token_line, NULL);
}
// GNU extensions
| namespace_inline NAMESPACE IDENTIFIER attributes_opt '{' declaration_sequence '}'
{
	AST identif = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);

	$$ = ASTMake4(AST_GCC_NAMESPACE_DEFINITION, identif, $6, $4, $1, $2.token_file, $2.token_line, NULL);
}
| namespace_inline NAMESPACE IDENTIFIER attributes_opt '{' '}'
{
	AST identif = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);

	$$ = ASTMake4(AST_GCC_NAMESPACE_DEFINITION, identif, NULL, $4, $1, $2.token_file, $2.token_line, NULL);
}
| NAMESPACE IDENTIFIER attributes '{' declaration_sequence '}'
{
	AST identif = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake4(AST_GCC_NAMESPACE_DEFINITION, identif, $5, $3, NULL, $1.token_file, $1.token_line, NULL);
}
| NAMESPACE IDENTIFIER attributes '{' '}'
{
	AST identif = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake4(AST_GCC_NAMESPACE_DEFINITION, identif, NULL, $3, NULL, $1.token_file, $1.token_line, NULL);
}
;

unnamed_namespace_definition : NAMESPACE '{' declaration_sequence '}'
{
	$$ = ASTMake2(AST_NAMESPACE_DEFINITION, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| NAMESPACE '{' '}'
{
	$$ = ASTMake2(AST_NAMESPACE_DEFINITION, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
;

block_declaration : simple_declaration
{
	$$ = $1;
}
| common_block_declaration
{
    $$ = $1;
}
;

non_empty_block_declaration : non_empty_simple_declaration
{
    $$ = $1;
}
| common_block_declaration
{
    $$ = $1;
}
;

common_block_declaration : asm_definition
{
	$$ = $1;
}
| namespace_alias_definition
{
	$$ = $1;
}
| using_declaration
{
	$$ = $1;
}
| using_directive
{
	$$ = $1;
}
| label_declaration 
{
	$$ = $1;
}
| static_assert_declaration
{
    $$ = $1;
}
| EXTENSION block_declaration
{
	$$ = ASTMake1(AST_GCC_EXTENSION, $2, $1.token_file, $1.token_line, $1.token_text);
}
| unknown_pragma
{
	$$ = $1;
}
// Prettyprinted comments
| PP_COMMENT
{
	$$ = ASTLeaf(AST_PP_COMMENT, $1.token_file, $1.token_line, $1.token_text);
}
// Prettyprinted preprocessor elements
| PP_TOKEN
{
	$$ = ASTLeaf(AST_PP_TOKEN, $1.token_file, $1.token_line, $1.token_text);
}
;

/* GNU Extension */
label_declaration : LABEL label_declarator_seq ';'
{
	$$ = ASTMake1(AST_GCC_LABEL_DECL, $2, $1.token_file, $1.token_line, NULL);
}
;

label_declarator_seq : IDENTIFIER 
{
    AST symbol_holder = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
	$$ = ASTListLeaf(symbol_holder);
}
| label_declarator_seq ',' IDENTIFIER
{
	AST label = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);
	$$ = ASTList($1, label);
}
;
/* End of GNU extension */

/* GNU Extension */
attributes : attributes attribute
{
	$$ = ASTList($1, $2);
}
| attribute
{
	$$ = ASTListLeaf($1);
}
;

attributes_opt : attributes
{
    $$ = $1;
}
| 
{
    $$ = NULL;
}
;

attribute : ATTRIBUTE '(' '(' attribute_list ')' ')'
{
	$$ = ASTMake1(AST_GCC_ATTRIBUTE, $4, $1.token_file, $1.token_line, $1.token_text);
}
| ATTRIBUTE '(''(' ')'')'
{
	$$ = ASTMake1(AST_GCC_ATTRIBUTE, NULL, $1.token_file, $1.token_line, $1.token_text);
}
;

attribute_list : attribute_value
{
	$$ = ASTListLeaf($1);
}
| attribute_list ',' attribute_value
{
	$$ = ASTList($1, $3);
}
;

// Why on earth ASTSon1 is always null ?
attribute_value : IDENTIFIER
{
	AST identif = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake3(AST_GCC_ATTRIBUTE_EXPR, identif, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| TOKEN_CONST
{
	AST identif = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake3(AST_GCC_ATTRIBUTE_EXPR, identif, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| IDENTIFIER '(' expression_list ')'
{
	AST identif1 = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
	
	$$ = ASTMake3(AST_GCC_ATTRIBUTE_EXPR, identif1, NULL, $3, $1.token_file, $1.token_line, NULL);
}
;
/* End of GNU extension */

// Assembler definition
// 
// GNU Extensions.
// The first one includes the standard 'asm-definition' but also allows for a
// volatile optional that is exclusive from gcc. The important thing here is
// that AST_ASM_DEFINITION never have additional colons
asm_definition : ASM volatile_optional '(' string_literal ')' ';'
{
	$$ = ASTMake2(AST_ASM_DEFINITION, $4, $2, $1.token_file, $1.token_line, $1.token_text);
}
// From here, none of these asm-definitions are standard but gcc only
| ASM volatile_optional '(' string_literal ':' asm_operand_list ')' ';'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, $6, NULL, NULL, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
// ( string_literal : asm_operand_list : asm_operand_list )
// ( string_literal : asm_operand_list : )
// ( string_literal : : asm_operand_list )
// ( string_literal :: asm_operand_list ) [C++ only] [1]
// ( string_literal : : )
// ( string_literal :: ) [C++ only] [2]
| ASM volatile_optional '(' string_literal ':' asm_operand_list ':' asm_operand_list ')' ';'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, $6, $8, NULL, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
// [1] and [2]
| ASM volatile_optional '(' string_literal TWO_COLONS asm_operand_list ')'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, NULL, NULL, $6, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
// ( string_literal : asm_operand_list : asm_operand_list : asm_operand_list )
| ASM volatile_optional '(' string_literal ':' asm_operand_list ':' asm_operand_list ':' asm_operand_list ')' ';'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, $6, $8, $10, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
// ( string_literal :: asm_operand_list ) 
// ( string_literal :: ) 
| ASM volatile_optional '(' string_literal TWO_COLONS asm_operand_list ')' ';'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, NULL, $6, NULL, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
// ( string_literal :: asm_operand_list : asm_operand_list ) 
// ( string_literal :: : asm_operand_list )
// ( string_literal :: asm_operand_list : )
// ( string_literal :: : )
// ( string_literal ::: ) <-- Note that ":::" is lexed as ":: :"
| ASM volatile_optional '(' string_literal TWO_COLONS asm_operand_list ':' asm_operand_list ')' ';'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, NULL, $6, $8, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
// ( string_literal : asm_operand_list :: asm_operand_list ) 
// ( string_literal : :: asm_operand_list ) 
// ( string_literal : asm_operand_list :: ) 
// ( string_literal : :: )  <-- Note that this is ": ::" not ":::"
| ASM volatile_optional '(' string_literal ':' asm_operand_list TWO_COLONS asm_operand_list ')' ';'
{
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			$4, $6, NULL, $8, ASTFileName($4), ASTLine($4), NULL);
	$$ = ASTMake2(AST_GCC_ASM_DEFINITION, $2, asm_parms, $1.token_file, $1.token_line, $1.token_text);
}
;

volatile_optional : /* empty */
{
	$$ = NULL;
}
| TOKEN_VOLATILE
{
	$$ = ASTLeaf(AST_VOLATILE_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

asm_operand_list : asm_operand_list_nonempty
{
	$$ = $1;
}
| /* empty */
{
	$$ = NULL;
};


/* GNU Extensions */
asm_operand_list_nonempty : asm_operand
{
	$$ = ASTListLeaf($1);
}
| asm_operand_list_nonempty ',' asm_operand
{
	$$ = ASTList($1, $3);
}
;

asm_operand : string_literal '(' expression ')' 
{
	$$ = ASTMake3(AST_GCC_ASM_OPERAND, NULL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| '[' IDENTIFIER ']' string_literal '(' expression ')'
{
    AST symbol_tree = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake3(AST_GCC_ASM_OPERAND, symbol_tree, $4, $6, $1.token_file, $1.token_line, NULL);
}
| string_literal
{
	$$ = $1;
}
;
/* End of GNU extensions */

static_assert_declaration : STATIC_ASSERT '(' constant_expression ',' string_literal ')' ';'
{
    $$ = ASTMake2(AST_STATIC_ASSERT, $3, $5, $1.token_file, $1.token_line, NULL);
}
;

namespace_alias_definition : NAMESPACE IDENTIFIER '=' id_expression ';'
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_NAMESPACE_ALIAS, identifier, $4, $1.token_file, $1.token_line, NULL);
}
;

using_declaration : USING id_type_expr ';'
{
	$$ = ASTMake1(AST_USING_DECLARATION, $2, $1.token_file, $1.token_line, NULL);
}
| USING TYPENAME id_type_expr ';'
{
	$$ = ASTMake1(AST_USING_DECLARATION_TYPENAME, $3, $1.token_file, $1.token_line, NULL);
}
;

using_directive : USING NAMESPACE id_expression ';'
{
	$$ = ASTMake1(AST_USING_NAMESPACE_DIRECTIVE, $3, $1.token_file, $1.token_line, NULL);
}
// GNU extension
| USING NAMESPACE id_expression attributes ';'
{
	$$ = ASTMake2(AST_GCC_USING_NAMESPACE_DIRECTIVE, $3, $4, $1.token_file, $1.token_line, NULL);
}
;

simple_declaration : non_empty_simple_declaration 
{
    $$ = $1;
}
| ';'
{
    // This is an error but also a common extension
    $$ = ASTLeaf(AST_EMPTY_DECL, $1.token_file, $1.token_line, $1.token_text);
}
;

non_empty_simple_declaration : decl_specifier_seq_0 init_declarator_list ';'  %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_init_declarator_list ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| init_declarator_list ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_alone_seq ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

// Does not end with a named type specifier
decl_specifier_seq_0 : nontype_specifier_seq no_named_type_specifier nontype_specifier_no_end_attrib_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq_for_named named_type_specifier nontype_specifier_no_end_attrib_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier nontype_specifier_no_end_attrib_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| named_type_specifier nontype_specifier_no_end_attrib_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_no_end_attrib_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

decl_specifier_seq_0_may_end_with_attribute : nontype_specifier_seq no_named_type_specifier nontype_specifier_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq_for_named named_type_specifier nontype_specifier_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier nontype_specifier_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| named_type_specifier nontype_specifier_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

// This one ends with a named type specifier
decl_specifier_seq_ended_with_named_type_spec : nontype_specifier_seq_for_named named_type_specifier
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| named_type_specifier
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

// This does not declare an object, maybe just types, so restrict it a bit
// 
// Note that, in contrast to decl_specifier_seq, we allow here to end with an attribute
// ('nontype_specifier_seq' instead of 'nontype_specifier_no_end_attrib_seq')
// In these cases there is not any declarator, so a trailing __attribute__ would not be
// valid
decl_specifier_alone_seq : nontype_specifier_seq type_specifier_alone nontype_specifier_seq
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq type_specifier_alone
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_alone nontype_specifier_seq
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_alone
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

nontype_specifier_seq : nontype_specifier
{
	$$ = ASTListLeaf($1);
}
| nontype_specifier_seq nontype_specifier
{
	$$ = ASTList($1, $2);
}
;

nontype_specifier_seq_for_named : nontype_specifier_for_named
{
	$$ = ASTListLeaf($1);
}
| nontype_specifier_seq_for_named nontype_specifier_for_named
{
	$$ = ASTList($1, $2);
}
;

nontype_specifier_no_end_attrib_seq_for_named : nontype_specifier_for_named_without_attribute
{
	$$ = ASTListLeaf($1);
}
| nontype_specifier_seq_for_named nontype_specifier_for_named_without_attribute
{
	$$ = ASTList($1, $2);
}
;

nontype_specifier_no_end_attrib_seq : nontype_specifier_without_attribute
{
    $$ = ASTListLeaf($1);
}
| nontype_specifier_seq nontype_specifier_without_attribute
{
    $$ = ASTList($1, $2);
}
;


nontype_specifier : nontype_specifier_without_attribute
{
    $$ = $1;
}
// GNU extension
| attribute
{
	$$ = $1;
}
;

nontype_specifier_for_named_without_attribute : storage_class_specifier
{
	$$ = $1;
}
| function_specifier
{
	$$ = $1;
}
| FRIEND
{
	$$ = ASTLeaf(AST_FRIEND_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TYPEDEF
{
	$$ = ASTLeaf(AST_TYPEDEF_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
// To ease things
| cv_qualifier
{
	$$ = $1;
}
// GNU Extension
| COMPLEX
{
	$$ = ASTLeaf(AST_GCC_COMPLEX_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
;

nontype_specifier_for_named : nontype_specifier_for_named_without_attribute
{
    $$ = $1;
}
// GNU extension
| attribute
{
	$$ = $1;
}
;

nontype_specifier_without_attribute : storage_class_specifier
{
	$$ = $1;
}
| function_specifier
{
	$$ = $1;
}
| FRIEND
{
	$$ = ASTLeaf(AST_FRIEND_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TYPEDEF
{
	$$ = ASTLeaf(AST_TYPEDEF_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
// To ease things
| cv_qualifier
{
	$$ = $1;
}
// Repeat them
| TOKEN_SIGNED
{
	$$ = ASTLeaf(AST_SIGNED_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_UNSIGNED
{
	$$ = ASTLeaf(AST_UNSIGNED_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_LONG
{
	$$ = ASTLeaf(AST_LONG_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_SHORT
{
	$$ = ASTLeaf(AST_SHORT_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
// GNU Extension
| COMPLEX
{
	$$ = ASTLeaf(AST_GCC_COMPLEX_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
;

storage_class_specifier : AUTO 
{
	$$ = ASTLeaf(AST_AUTO_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| REGISTER
{
	$$ = ASTLeaf(AST_REGISTER_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| STATIC
{
	$$ = ASTLeaf(AST_STATIC_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| EXTERN
{
	$$ = ASTLeaf(AST_EXTERN_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| MUTABLE
{
	$$ = ASTLeaf(AST_MUTABLE_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
// GNU Extension
| THREAD
{
	$$ = ASTLeaf(AST_THREAD_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

function_specifier : INLINE
{
	$$ = ASTLeaf(AST_INLINE_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| VIRTUAL
{
	$$ = ASTLeaf(AST_VIRTUAL_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| EXPLICIT
{
	$$ = ASTLeaf(AST_EXPLICIT_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

no_named_type_specifier : type_specifier_alone
{
    $$ = $1;
}
| no_named_simple_type_specifier
{
    $$ = $1;
}
// GNU Extensions
| COMPLEX
{
	$$ = ASTLeaf(AST_GCC_COMPLEX_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
;

named_type_specifier : named_simple_type_specifier
{
    $$ = $1;
}
;

type_specifier_alone : class_specifier
{
	$$ = $1;
}
| enum_specifier
{
	$$ = $1;
}
| elaborated_type_specifier
{
	$$ = $1;
}
;

/*
type_specifier_seq has been rewritten in a similar fashion to "decl_specifier_seq"
*/

type_specifier_seq_0 : nontype_specifier_seq no_named_type_specifier nontype_specifier_no_end_attrib_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq_for_named named_type_specifier nontype_specifier_no_end_attrib_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier nontype_specifier_no_end_attrib_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| named_type_specifier nontype_specifier_no_end_attrib_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

type_specifier_seq_0_may_end_with_attribute : nontype_specifier_seq no_named_type_specifier nontype_specifier_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq_for_named named_type_specifier nontype_specifier_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nontype_specifier_seq no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier nontype_specifier_seq %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| named_type_specifier nontype_specifier_seq_for_named %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| no_named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

type_specifier_seq_ended_with_named_type_spec : nontype_specifier_seq_for_named named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| named_type_specifier %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

named_simple_type_specifier : id_type_expr
{
	$$ = ASTMake1(AST_SIMPLE_TYPE_SPEC, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

simple_type_specifier : named_simple_type_specifier
{
    $$ = $1;
}
|  no_named_simple_type_specifier 
{
    $$ = $1;
}
;

no_named_simple_type_specifier : builtin_types
{
	$$ = $1;
}
// c++0x
| DECLTYPE '(' expression ')'
{
    $$ = ASTMake1(AST_DECLTYPE, $3, $1.token_file, $1.token_line, $1.token_text);
}
// GNU Extension
| TYPEOF unary_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_GCC_TYPEOF_EXPR, $2, $1.token_file, $1.token_line, $1.token_text);
}
| TYPEOF '(' type_id ')' %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_GCC_TYPEOF, $3, $1.token_file, $1.token_line, $1.token_text);
}
;

builtin_types : TOKEN_CHAR
{
	$$ = ASTLeaf(AST_CHAR_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_WCHAR_T
{
	$$ = ASTLeaf(AST_WCHAR_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_BOOL
{
	$$ = ASTLeaf(AST_BOOL_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_SHORT
{
	$$ = ASTLeaf(AST_SHORT_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_INT
{
	$$ = ASTLeaf(AST_INT_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_LONG
{
	$$ = ASTLeaf(AST_LONG_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_SIGNED
{
	$$ = ASTLeaf(AST_SIGNED_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_UNSIGNED
{
	$$ = ASTLeaf(AST_UNSIGNED_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_FLOAT
{
	$$ = ASTLeaf(AST_FLOAT_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_DOUBLE
{
	$$ = ASTLeaf(AST_DOUBLE_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_VOID
{
	$$ = ASTLeaf(AST_VOID_TYPE, $1.token_file, $1.token_line, $1.token_text);
}
;

elaborated_type_specifier : class_key id_type_expr
{
	$$ = ASTMake2(AST_ELABORATED_TYPE_CLASS_SPEC, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| ENUM id_type_expr
{
	$$ = ASTMake1(AST_ELABORATED_TYPE_ENUM_SPEC, $2, $1.token_file, $1.token_line, NULL);
}
| TYPENAME qualified_id_type_expr
{
	$$ = ASTMake1(AST_ELABORATED_TYPENAME_SPEC, $2, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| class_key attributes id_type_expr
{
	$$ = ASTMake3(AST_GCC_ELABORATED_TYPE_CLASS_SPEC, $1, $3, $2, ASTFileName($1), ASTLine($1), NULL);
}
| ENUM attributes id_type_expr
{
	$$ = ASTMake2(AST_GCC_ELABORATED_TYPE_ENUM_SPEC, $3, $2, $1.token_file, $1.token_line, NULL);
}
;



// *********************************************************
// A.7 - Declarators
// *********************************************************
init_declarator_list : init_declarator
{
	$$ = ASTListLeaf($1);
}
| init_declarator_list ',' init_declarator
{
	$$ = ASTList($1, $3);
}
;

nonglobal_init_declarator_list : nonglobal_init_declarator
{
    $$ = ASTListLeaf($1);
}
| nonglobal_init_declarator ',' init_declarator_list
{
    // Prepend
    AST it = $3;
    while (ast_get_child(it, 0) != NULL)
        it = ast_get_child(it, 0);
    ast_set_child(it, 0, ASTListLeaf($1));

    $$ = $3;
}
;

init_declarator : declarator %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_INIT_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| declarator equal_or_parent_initializer %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_INIT_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| non_functional_declarator braced_init_list %merge<ambiguityHandler>
{
    $$ = ASTMake2(AST_INIT_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extensions
| declarator asm_specification %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, NULL, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| declarator attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, NULL, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| declarator asm_specification attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, NULL, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| declarator asm_specification initializer %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, $3, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| declarator attributes initializer %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, $3, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| declarator asm_specification attributes initializer %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, $4, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_init_declarator : nonglobal_declarator %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_INIT_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator equal_or_parent_initializer %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_INIT_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_non_functional_declarator braced_init_list %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_INIT_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extensions
| nonglobal_declarator asm_specification  %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, NULL, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, NULL, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator asm_specification attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, NULL, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator asm_specification initializer %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, $3, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator attributes initializer %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, $3, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator asm_specification attributes initializer %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_INIT_DECLARATOR, $1, $4, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

/* GNU Extension */
asm_specification : ASM '(' string_literal ')'
{
	$$ = ASTMake1(AST_GCC_ASM_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
/* End of GNU Extension */

nonglobal_declarator : nonglobal_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_ptr_operator declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
/* GNU Extension */
| attributes direct_declarator
{
    $$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator declarator
{
    $$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_non_functional_declarator : nonglobal_non_functional_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_ptr_operator non_functional_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
/* GNU Extension */
| attributes non_functional_direct_declarator
{
    $$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator non_functional_declarator
{
    $$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_non_functional_direct_declarator : nonglobal_declarator_id %dprec 2
{
	$$ = $1;
}
| nonglobal_non_functional_direct_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_non_functional_direct_declarator '[' ']' %dprec 1
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| '(' non_functional_declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

declarator : direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
/* GNU Extension */
| attributes direct_declarator
{
    $$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator declarator
{
    $$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_ptr_operator : '*'
{
	$$ = ASTMake2(AST_POINTER_SPEC, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| '*' cv_qualifier_seq
{
	$$ = ASTMake2(AST_POINTER_SPEC, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| nonglobal_id_type_expr TWO_COLONS '*'
{
	$$ = ASTMake2(AST_POINTER_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_id_type_expr TWO_COLONS '*' cv_qualifier_seq
{
	$$ = ASTMake2(AST_POINTER_SPEC, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
| '&'
{
	$$ = ASTLeaf(AST_REFERENCE_SPEC, $1.token_file, $1.token_line, NULL);
}
// C++0x
| ANDAND
{
    $$ = ASTLeaf(AST_RVALUE_REFERENCE_SPEC, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| '&' cv_qualifier_seq
{
	$$ = ASTMake1(AST_GCC_REFERENCE_SPEC, $2, $1.token_file, $1.token_line, NULL);
}
;

ptr_operator : '*'
{
	$$ = ASTMake2(AST_POINTER_SPEC, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| '*' cv_qualifier_seq
{
	$$ = ASTMake2(AST_POINTER_SPEC, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| id_type_expr TWO_COLONS '*'
{
	$$ = ASTMake2(AST_POINTER_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| id_type_expr TWO_COLONS '*' cv_qualifier_seq
{
	$$ = ASTMake2(AST_POINTER_SPEC, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
| '&'
{
	$$ = ASTLeaf(AST_REFERENCE_SPEC, $1.token_file, $1.token_line, NULL);
}
// C++0x
| ANDAND
{
    $$ = ASTLeaf(AST_RVALUE_REFERENCE_SPEC, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| '&' cv_qualifier_seq
{
	$$ = ASTMake1(AST_GCC_REFERENCE_SPEC, $2, $1.token_file, $1.token_line, NULL);
}
;

/* 
   A nonfunctional declarator will never generate a function declarator
 */

non_functional_declarator : non_functional_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator non_functional_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// GNU extension
| attributes non_functional_direct_declarator
{
	$$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator non_functional_declarator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

non_functional_direct_declarator : declarator_id %dprec 2
{
	$$ = $1;
}
| non_functional_direct_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| non_functional_direct_declarator '[' ']' %dprec 1
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| '(' non_functional_declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

/*
   A functional declarator is a syntactic enforced declarator that will have
   a functional nature
 */
functional_declarator : functional_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator functional_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// GNU extension
| attributes functional_direct_declarator
{
	$$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator functional_declarator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

functional_direct_declarator : functional_declarator_id %dprec 2
{
	$$ = $1;
}
| '(' functional_declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

functional_declarator_id : functional_final_declarator_id '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| functional_final_declarator_id '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| functional_final_declarator_id '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, $5, ASTFileName($1), ASTLine($1), NULL);
}
| functional_final_declarator_id '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
;

// This rule is needed because of redundant parentheses
functional_final_declarator_id : declarator_id
{
    $$ = $1;
}
| '(' functional_final_declarator_id ')'
{
    $$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

nonglobal_functional_declarator : nonglobal_functional_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator functional_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// GNU extension
| attributes functional_direct_declarator
{
	$$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator functional_declarator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_functional_direct_declarator : nonglobal_functional_declarator_id %dprec 2
{
	$$ = $1;
}
| '(' functional_declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

nonglobal_functional_declarator_id : nonglobal_functional_final_declarator_id '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_functional_final_declarator_id '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_functional_final_declarator_id '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, $5, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_functional_final_declarator_id '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
;

// This rule is needed because of redundant parentheses
nonglobal_functional_final_declarator_id : nonglobal_declarator_id
{
    $$ = $1;
}
| '(' functional_final_declarator_id ')'
{
    $$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

cv_qualifier_seq : cv_qualifier
{
	$$ = ASTListLeaf($1);
}
| cv_qualifier_seq cv_qualifier
{
	$$ = ASTList($1, $2);
}
;

cv_qualifier : TOKEN_CONST
{
	$$ = ASTLeaf(AST_CONST_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOKEN_VOLATILE
{
	$$ = ASTLeaf(AST_VOLATILE_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
// GNU Extension
| RESTRICT
{
	$$ = ASTLeaf(AST_GCC_RESTRICT_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

nonglobal_direct_declarator : nonglobal_declarator_id %dprec 2
{
	$$ = $1;
}
| nonglobal_direct_declarator '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_direct_declarator '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, $5, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_direct_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_direct_declarator '[' ']' %dprec 1
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| '(' declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

nonglobal_declarator_id : nonglobal_id_expression
{
	$$ = ASTMake1(AST_DECLARATOR_ID_EXPR, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

direct_declarator : declarator_id %dprec 2
{
	$$ = $1;
}
| direct_declarator '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| direct_declarator '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, $5, ASTFileName($1), ASTLine($1), NULL);
}
| direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
| direct_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| direct_declarator '[' ']' %dprec 1
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| '(' declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

declarator_id : id_expression
{
	$$ = ASTMake1(AST_DECLARATOR_ID_EXPR, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

enum_specifier : ENUM IDENTIFIER '{' enumeration_list '}'
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_ENUM_SPECIFIER, identifier, $4, $1.token_file, $1.token_line, NULL);
}
| ENUM '{' enumeration_list '}'
{
	$$ = ASTMake2(AST_ENUM_SPECIFIER, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| ENUM IDENTIFIER '{' '}'
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_ENUM_SPECIFIER, identifier, NULL, $1.token_file, $1.token_line, NULL);
}
| ENUM '{' '}'
{
	$$ = ASTMake2(AST_ENUM_SPECIFIER, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
// GCC extensions
| ENUM attributes IDENTIFIER '{' enumeration_list '}'
{
	AST identifier = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);

	$$ = ASTMake3(AST_GCC_ENUM_SPECIFIER, identifier, $5, $2, $1.token_file, $1.token_line, NULL);
}
| ENUM attributes '{' enumeration_list '}'
{
	$$ = ASTMake3(AST_GCC_ENUM_SPECIFIER, NULL, $4, $2, $1.token_file, $1.token_line, NULL);
}
| ENUM attributes IDENTIFIER '{' '}'
{
	AST identifier = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);

	$$ = ASTMake3(AST_GCC_ENUM_SPECIFIER, identifier, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| ENUM attributes '{' '}'
{
	$$ = ASTMake3(AST_GCC_ENUM_SPECIFIER, NULL, NULL, $2, $1.token_file, $1.token_line, NULL);
}
;

enumeration_list : enumeration_list_proper
{
	$$ = $1;
}
// This is a running comma that many people forgets here. It is of non
// standard nature
| enumeration_list_proper ','
{
	$$ = $1;
};

enumeration_list_proper : enumeration_list_proper ',' enumeration_definition
{
	$$ = ASTList($1, $3);
}
| enumeration_definition
{
	$$ = ASTListLeaf($1);
}
;

enumeration_definition : IDENTIFIER
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake2(AST_ENUMERATOR_DEF, identifier, NULL, $1.token_file, $1.token_line, NULL);
}
| IDENTIFIER '=' constant_expression
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake2(AST_ENUMERATOR_DEF, identifier, $3, $1.token_file, $1.token_line, NULL);
}
;

type_id : type_specifier_seq_0_may_end_with_attribute
{
	$$ = ASTMake2(AST_TYPE_ID, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec
{
	$$ = ASTMake2(AST_TYPE_ID, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 abstract_declarator
{
	$$ = ASTMake2(AST_TYPE_ID, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_abstract_declarator
{
	$$ = ASTMake2(AST_TYPE_ID, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_abstract_declarator : nonglobal_ptr_operator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_ptr_operator abstract_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| abstract_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
// GNU extension
| attributes ptr_operator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator abstract_declarator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| attributes abstract_direct_declarator
{
	$$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

abstract_declarator : ptr_operator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator abstract_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| abstract_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
// GNU extension
| attributes ptr_operator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator abstract_declarator
{
	$$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| attributes abstract_direct_declarator
{
	$$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

abstract_direct_declarator : '(' abstract_declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
| '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, NULL, $2, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, NULL, $2, $4, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, NULL, $2, NULL, $4, $1.token_file, $1.token_line, NULL);
}
| '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, NULL, $2, $4, $5, $1.token_file, $1.token_line, NULL);
}
| abstract_direct_declarator '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| abstract_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| abstract_direct_declarator '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, $5, ASTFileName($1), ASTLine($1), NULL);
}
| abstract_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
| '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| '[' ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| abstract_direct_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| abstract_direct_declarator '[' ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

parameter_declaration_clause : parameter_declaration_clause_nonempty
{
	$$ = $1;
}
| parameter_declaration_clause_nonempty ',' ELLIPSIS
{
    AST variadic_tree = ASTLeaf(AST_VARIADIC_ARG, $3.token_file, $3.token_line, $3.token_text);
	$$ = ASTList($1, variadic_tree);
} 
| parameter_declaration_clause_nonempty ELLIPSIS
{
    AST variadic_tree = ASTLeaf(AST_VARIADIC_ARG, $2.token_file, $2.token_line, $2.token_text);
	$$ = ASTList($1, variadic_tree);
} 
// C++ "T f(...)" is the same as C "T f()" since
// C++ "T f()" is the same as C "T f(void)"
| ELLIPSIS
{
    AST variadic_tree = ASTLeaf(AST_VARIADIC_ARG, $1.token_file, $1.token_line, $1.token_text);
	$$ = ASTListLeaf(variadic_tree);
}
// I don't like these kind of rules but we will make an exception here
| /* empty */
{
	$$ = ASTLeaf(AST_EMPTY_PARAMETER_DECLARATION_CLAUSE, NULL, 0, NULL);
}
;

parameter_declaration_clause_nonempty : parameter_declaration_list
{
	$$ = $1;
}
;

parameter_declaration_list : parameter_declaration
{
	$$ = ASTListLeaf($1);
}
| parameter_declaration_list ',' parameter_declaration
{
	$$ = ASTList($1, $3);
}
;

parameter_declaration : decl_specifier_seq_0 nonabstract_declarator %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_nonabstract_declarator %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0 nonabstract_declarator '=' assignment_expression  %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_nonabstract_declarator '=' assignment_expression  %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0_may_end_with_attribute %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0 abstract_declarator  %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_abstract_declarator %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0  '=' assignment_expression  %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0 abstract_declarator '=' assignment_expression  %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_abstract_declarator '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_PARAMETER_DECL, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
// GCC Extension
| decl_specifier_seq_0 nonabstract_declarator attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_nonabstract_declarator attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0 nonabstract_declarator attributes '=' assignment_expression  %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, $5, $3, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_nonabstract_declarator attributes '=' assignment_expression  %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, $5, $3, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0 abstract_declarator attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_abstract_declarator attributes %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
// --
| decl_specifier_seq_0 abstract_declarator attributes '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, $5, $3, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_abstract_declarator attributes '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake4(AST_GCC_PARAMETER_DECL, $1, $2, $5, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_nonabstract_declarator : nonabstract_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_ptr_operator nonabstract_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
/* GNU Extension */
| attributes nonabstract_direct_declarator
{
    $$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator nonabstract_declarator
{
    $$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonabstract_declarator : nonabstract_direct_declarator
{
	$$ = ASTMake1(AST_DECLARATOR, $1, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator nonabstract_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
/* GNU Extension */
| attributes nonabstract_direct_declarator
{
    $$ = ASTMake2(AST_GCC_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| attributes ptr_operator nonabstract_declarator
{
    $$ = ASTMake3(AST_GCC_POINTER_DECLARATOR, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nonabstract_direct_declarator : IDENTIFIER
{
	AST symbol = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
    $$ = ASTMake1(AST_DECLARATOR_ID_EXPR, symbol, ASTFileName(symbol), ASTLine(symbol), NULL);
}
| nonabstract_direct_declarator '(' parameter_declaration_clause ')'
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonabstract_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonabstract_direct_declarator '(' parameter_declaration_clause ')' exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, NULL, $5, ASTFileName($1), ASTLine($1), NULL);
}
| nonabstract_direct_declarator '(' parameter_declaration_clause ')' cv_qualifier_seq exception_specification
{
	$$ = ASTMake4(AST_DECLARATOR_FUNC, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
| nonabstract_direct_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| nonabstract_direct_declarator '[' ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| '(' nonabstract_declarator ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_DECLARATOR, $2, $1.token_file, $1.token_line, NULL);
}
;

equal_initializer : '=' initializer_clause
{
    $$ = ASTMake1(AST_EQUAL_INITIALIZER, $2, $1.token_file, $1.token_line, NULL);
}
;

equal_or_parent_initializer : equal_initializer
{
    $$ = $1;
}
| parent_initializer
{
    $$ = $1;
}
;

parent_initializer : '(' expression_list ')'
{
	$$ = ASTMake1(AST_PARENTHESIZED_INITIALIZER, $2, $1.token_file, $1.token_line, NULL);
}
;

initializer : equal_initializer
{
	$$ = $1;
}
| parent_initializer
{
    $$ = $1;
}
| braced_init_list
{
    $$ = $1;
}
;

initializer_clause : assignment_expression
{
	$$ = $1;
}
| braced_init_list
{
    $$ = $1;
}
;

braced_init_list : '{' initializer_list '}'
{
	$$ = ASTMake1(AST_INITIALIZER_BRACES, $2, $1.token_file, $1.token_line, NULL);
}
| '{' initializer_list ',' '}'
{
	$$ = ASTMake1(AST_INITIALIZER_BRACES, $2, $1.token_file, $1.token_line, NULL);
}
| '{' '}'
{
	$$ = ASTMake1(AST_INITIALIZER_BRACES, NULL, $1.token_file, $1.token_line, NULL);
}
;

initializer_list : initializer_clause %merge<ambiguityHandler>
{
	$$ = ASTListLeaf($1);
}
| initializer_list ',' initializer_clause %merge<ambiguityHandler>
{
	$$ = ASTList($1, $3);
}
// C++0x pack expansion
| initializer_clause ELLIPSIS
{
    AST pack_expansion = ASTMake1(AST_PACK_EXPANSION, $1, ASTFileName($1), ASTLine($1), NULL);
    $$ = ASTListLeaf(pack_expansion);
}
| initializer_list ',' initializer_clause ELLIPSIS
{
    AST pack_expansion = ASTMake1(AST_PACK_EXPANSION, $1, ASTFileName($1), ASTLine($1), NULL);
    $$ = ASTList($1, pack_expansion);
}
// C99 extensions
| designation initializer_clause
{
    AST designated_initializer = ASTMake2(AST_DESIGNATED_INITIALIZER, $1, $2, ASTFileName($1), ASTLine($1), NULL);

    $$ = ASTListLeaf(designated_initializer);
}
| initializer_list ',' designation initializer_clause
{
    AST designated_initializer = ASTMake2(AST_DESIGNATED_INITIALIZER, $3, $4, ASTFileName($3), ASTLine($3), NULL);

    $$ = ASTList($1, designated_initializer);
}
// GNU Extensions
| IDENTIFIER ':' initializer_clause
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	AST gcc_initializer_clause = ASTMake2(AST_GCC_INITIALIZER_CLAUSE, identifier, $3, $1.token_file, $1.token_line, NULL);

	$$ = ASTListLeaf(gcc_initializer_clause);
}
| initializer_list ',' IDENTIFIER ':' initializer_clause
{
	AST identifier = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);

	AST gcc_initializer_clause = ASTMake2(AST_GCC_INITIALIZER_CLAUSE, identifier, $5, ASTFileName($1), ASTLine($1), NULL);

	$$ = ASTList($1, gcc_initializer_clause);
}
;

designation : designator_list '='
{
    $$ = ASTMake1(AST_DESIGNATION, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

designator_list : designator
{
    $$ = ASTListLeaf($1);
}
| designator_list designator
{
    $$ = ASTList($1, $2);
}
;

designator : '[' constant_expression ']'
{
    $$ = ASTMake1(AST_INDEX_DESIGNATOR, $2, $1.token_file, $1.token_line, NULL);
}
| '.' IDENTIFIER
{
    AST symbol = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

    $$ = ASTMake1(AST_FIELD_DESIGNATOR, symbol, $1.token_file, $1.token_line, NULL);
}
;

function_definition_header : functional_declarator
{
    $$[0] = NULL;
    $$[1] = $1;
    $$[2] = NULL;
}
| decl_specifier_seq_0 functional_declarator
{
    $$[0] = $1;
    $$[1] = $2;
    $$[2] = NULL;
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_functional_declarator
{
    $$[0] = $1;
    $$[1] = $2;
    $$[2] = NULL;
}
/* GCC */
| functional_declarator attributes
{
    $$[0] = NULL;
    $$[1] = $1;
    $$[2] = $2;
}
| decl_specifier_seq_0 functional_declarator attributes
{
    $$[0] = $1;
    $$[1] = $2;
    $$[2] = $3;
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_functional_declarator attributes
{
    $$[0] = $1;
    $$[1] = $2;
    $$[2] = $3;
}
;

ctor_initializer_opt : /* empty */
{
    $$ = NULL;
}
| ctor_initializer
{
    $$ = $1;
};

function_definition : function_definition_header ctor_initializer_opt function_body 
{
    const char* filename = NULL;
    int line = 0;
    // This is a bit crude but effective
    AST trees[] = { $1[0], $1[1], $1[2], $2, $3 };
    int num_trees = sizeof(trees) / sizeof(trees[0]);
    int i;
    for (i = 0; i < num_trees; i++)
    {
        if (trees[i] != NULL)
        {
            filename = ASTFileName(trees[i]);
            line = ASTLine(trees[i]);
        }
    }

    if ($1[2] == NULL)
    {
        $$ = ASTMake4(AST_FUNCTION_DEFINITION, $1[0], $1[1], $2, $3, filename, line, NULL);
    }
    else
    {
        // GCC
        AST functional_decl = ASTMake2(AST_GCC_FUNCTIONAL_DECLARATOR, $1[1], $1[2], filename, line, NULL);
        $$ = ASTMake4(AST_FUNCTION_DEFINITION, $1[0], functional_decl, $2, $3, filename, line, NULL);
    }
}
| function_definition_header '=' TOKEN_DELETE ';'
{
    const char* filename = NULL;
    int line = 0;
    // This is a bit crude but effective
    AST trees[] = { $1[0], $1[1], $1[2] };
    int num_trees = sizeof(trees) / sizeof(trees[0]);
    int i;
    for (i = 0; i < num_trees; i++)
    {
        if (trees[i] != NULL)
        {
            filename = ASTFileName(trees[i]);
            line = ASTLine(trees[i]);
        }
    }
    $$ = ASTMake3(AST_DELETED_FUNCTION_DEFINITION, $1[0], $1[1], $1[2], filename, line, $3.token_text);
}
| function_definition_header '=' DEFAULT ';'
{
    const char* filename = NULL;
    int line = 0;
    // This is a bit crude but effective
    AST trees[] = { $1[0], $1[1], $1[2] };
    int num_trees = sizeof(trees) / sizeof(trees[0]);
    int i;
    for (i = 0; i < num_trees; i++)
    {
        if (trees[i] != NULL)
        {
            filename = ASTFileName(trees[i]);
            line = ASTLine(trees[i]);
        }
    }
    $$ = ASTMake3(AST_DEFAULTED_FUNCTION_DEFINITION, $1[0], $1[1], $1[2], filename, line, $3.token_text);
}
| EXTENSION function_definition
{
	$$ = ASTMake1(AST_GCC_EXTENSION, $2, $1.token_file, $1.token_line, $1.token_text);
}
;

function_body : compound_statement
{
	$$ = ASTMake1(AST_FUNCTION_BODY, $1, ASTFileName($1), ASTLine($1), NULL);
}
| try_block
{
    $$ = ASTMake1(AST_FUNCTION_BODY, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

// *********************************************************
// A.8 - Classes
// *********************************************************

class_specifier : class_head '{' member_specification_seq '}'
{
	$$ = ASTMake2(AST_CLASS_SPECIFIER, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| class_head '{' '}'
{
	// AST member_declaration = ASTLeaf(AST_EMPTY_DECL, $2.token_file, $2.token_line, NULL);
	// AST member_specification = 
	// 	ASTMake3(AST_MEMBER_SPEC, NULL, member_declaration, 
	// 			NULL, ASTFileName(member_declaration), ASTLine(member_declaration), NULL);

	$$ = ASTMake2(AST_CLASS_SPECIFIER, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

class_head : class_key 
{
	$$ = ASTMake3(AST_CLASS_HEAD_SPEC, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| class_key id_type_expr
{
	$$ = ASTMake3(AST_CLASS_HEAD_SPEC, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| class_key base_clause
{
	$$ = ASTMake3(AST_CLASS_HEAD_SPEC, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| class_key id_type_expr base_clause
{
	$$ = ASTMake3(AST_CLASS_HEAD_SPEC, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extensions
| class_key attributes
{
	$$ = ASTMake4(AST_GCC_CLASS_HEAD_SPEC, $1, NULL, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| class_key attributes id_type_expr
{
	$$ = ASTMake4(AST_GCC_CLASS_HEAD_SPEC, $1, $3, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| class_key attributes base_clause
{
	$$ = ASTMake4(AST_GCC_CLASS_HEAD_SPEC, $1, NULL, $3, $2, ASTFileName($1), ASTLine($1), NULL);
}
| class_key attributes id_type_expr base_clause
{
	$$ = ASTMake4(AST_GCC_CLASS_HEAD_SPEC, $1, $3, $4, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

class_key : CLASS
{
	$$ = ASTLeaf(AST_CLASS_KEY_CLASS, $1.token_file, $1.token_line, $1.token_text);
}
| STRUCT
{
	$$ = ASTLeaf(AST_CLASS_KEY_STRUCT, $1.token_file, $1.token_line, $1.token_text);
}
| UNION
{
	$$ = ASTLeaf(AST_CLASS_KEY_UNION, $1.token_file, $1.token_line, $1.token_text);
}
;

member_specification_seq : member_specification
{
	$$ = ASTListLeaf($1);
}
| member_specification_seq member_specification
{
	$$ = ASTList($1, $2);
}
;

member_specification : member_declaration
{
	$$ = $1;
}
| access_specifier ':'
{
	$$ = ASTMake1(AST_MEMBER_ACCESS_SPEC, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

member_declaration : decl_specifier_seq_0 member_declarator_list ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_MEMBER_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_member_declarator_list ';' %merge<ambiguityHandler> 
{
	$$ = ASTMake2(AST_MEMBER_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}

| decl_specifier_alone_seq ';' %merge<ambiguityHandler>  
{
	$$ = ASTMake2(AST_MEMBER_DECLARATION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| member_declarator_list ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_MEMBER_DECLARATION, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
| function_definition 
{
	$$ = $1;
}
| id_expression ';' %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_MEMBER_DECLARATION_QUALIF, $1, ASTFileName($1), ASTLine($1), NULL);
}
| using_declaration
{
	$$ = $1;
}
| template_declaration %merge<ambiguityHandler>
{
	$$ = $1;
}
| unknown_pragma
{
	$$ = $1;
}
| verbatim_construct
{
    $$ = $1;
}
| static_assert_declaration 
{
    $$ = $1;
}
// This is a common tolerated error
| ';' 
{
	$$ = ASTLeaf(AST_EMPTY_DECL, $1.token_file, $1.token_line, NULL);
}
// GNU Extension
| EXTENSION member_declaration
{
	$$ = ASTMake1(AST_GCC_EXTENSION, $2, $1.token_file, $1.token_line, $1.token_text);
}
;

nonglobal_member_declarator_list : nonglobal_member_declarator
{
    $$ = ASTListLeaf($1);
}
| nonglobal_member_declarator ',' member_declarator_list
{
    // Prepend
    AST it = $3;
    while (ast_get_child(it, 0) != NULL)
        it = ast_get_child(it, 0);
    ast_set_child(it, 0, ASTListLeaf($1));

    $$ = $3;
}
;

member_declarator_list : member_declarator
{
	$$ = ASTListLeaf($1);
}
| member_declarator_list ',' member_declarator
{
	$$ = ASTList($1, $3);
}
;

member_declarator : declarator 
{
	$$ = ASTMake2(AST_MEMBER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| declarator equal_initializer
{
	$$ = ASTMake2(AST_MEMBER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| non_functional_declarator braced_init_list
{
	$$ = ASTMake2(AST_MEMBER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| ':' constant_expression
{
	$$ = ASTMake2(AST_BITFIELD_DECLARATOR, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| IDENTIFIER ':' constant_expression
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
	AST declarator_id_expr = ASTMake1(AST_DECLARATOR_ID_EXPR, identifier, ASTFileName(identifier), ASTLine(identifier), NULL);

	$$ = ASTMake2(AST_BITFIELD_DECLARATOR, declarator_id_expr, $3, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| declarator attributes 
{
	$$ = ASTMake3(AST_GCC_MEMBER_DECLARATOR, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| declarator attributes equal_initializer
{
	$$ = ASTMake3(AST_GCC_MEMBER_DECLARATOR, $1, $3, $2, ASTFileName($1), ASTLine($1), NULL);
}
| non_functional_declarator attributes braced_init_list
{
	$$ = ASTMake3(AST_GCC_MEMBER_DECLARATOR, $1, $3, $2, ASTFileName($1), ASTLine($1), NULL);
}
| IDENTIFIER attributes ':' constant_expression
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake3(AST_GCC_BITFIELD_DECLARATOR, identifier, $4, $2, $1.token_file, $1.token_line, NULL);
}
| attributes ':' constant_expression
{
	$$ = ASTMake3(AST_GCC_BITFIELD_DECLARATOR, NULL, $3, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_member_declarator : nonglobal_declarator 
{
	$$ = ASTMake2(AST_MEMBER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator equal_initializer
{
	$$ = ASTMake2(AST_MEMBER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_non_functional_declarator braced_init_list
{
	$$ = ASTMake2(AST_MEMBER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| ':' constant_expression
{
	$$ = ASTMake2(AST_BITFIELD_DECLARATOR, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| IDENTIFIER ':' constant_expression
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
	AST declarator_id_expr = ASTMake1(AST_DECLARATOR_ID_EXPR, identifier, ASTFileName(identifier), ASTLine(identifier), NULL);

	$$ = ASTMake2(AST_BITFIELD_DECLARATOR, declarator_id_expr, $3, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| nonglobal_declarator attributes 
{
	$$ = ASTMake3(AST_GCC_MEMBER_DECLARATOR, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_declarator attributes equal_initializer
{
	$$ = ASTMake3(AST_GCC_MEMBER_DECLARATOR, $1, $3, $2, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_non_functional_declarator attributes braced_init_list
{
	$$ = ASTMake3(AST_GCC_MEMBER_DECLARATOR, $1, $3, $2, ASTFileName($1), ASTLine($1), NULL);
}
| IDENTIFIER attributes ':' constant_expression
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake3(AST_GCC_BITFIELD_DECLARATOR, identifier, $4, $2, $1.token_file, $1.token_line, NULL);
}
| attributes ':' constant_expression
{
	$$ = ASTMake3(AST_GCC_BITFIELD_DECLARATOR, NULL, $3, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

// *********************************************************
// A.9 - Derived classes
// *********************************************************

base_clause : ':' base_specifier_list
{
	$$ = ASTMake1(AST_BASE_CLAUSE, $2, $1.token_file, $1.token_line, NULL);
}
;

base_specifier_list : base_specifier
{
	$$ = ASTListLeaf($1);
}
| base_specifier_list ',' base_specifier
{
	$$ = ASTList($1, $3);
}
;

base_specifier : id_type_expr
// without access_specifier
{
	$$ = ASTMake3(AST_BASE_SPEC, NULL, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
// without virtual but with access_specifier
| access_specifier id_type_expr
{
	$$ = ASTMake3(AST_BASE_SPEC, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// with virtual and optionally access_specifier
| VIRTUAL id_type_expr
{
    AST virtual_spec = ASTLeaf(AST_VIRTUAL_SPEC, $1.token_file, $1.token_line, $1.token_text);
	$$ = ASTMake3(AST_BASE_SPEC, virtual_spec, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| VIRTUAL access_specifier id_type_expr
{
    AST virtual_spec = ASTLeaf(AST_VIRTUAL_SPEC, $1.token_file, $1.token_line, $1.token_text);
	$$ = ASTMake3(AST_BASE_SPEC, virtual_spec, $2, $3, $1.token_file, $1.token_line, NULL);
}
// with access_specifier and then virtual
| access_specifier VIRTUAL id_type_expr
{
    AST virtual_spec = ASTLeaf(AST_VIRTUAL_SPEC, $2.token_file, $2.token_line, $2.token_text);
	$$ = ASTMake3(AST_BASE_SPEC, virtual_spec, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

access_specifier : PRIVATE
{
	$$ = ASTLeaf(AST_PRIVATE_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| PROTECTED
{
	$$ = ASTLeaf(AST_PROTECTED_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| PUBLIC
{
	$$ = ASTLeaf(AST_PUBLIC_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

// *********************************************************
// A.5. - Statements
// *********************************************************


statement : no_if_statement
{
	$$ = $1;
}
| if_statement %dprec 2
{
	$$ = $1;
}
| if_else_statement %dprec 1
{
	$$ = $1;
}
;

no_if_statement : labeled_statement
{
	$$ = $1;
}
| expression_statement %merge<ambiguityHandler>
{
	$$ = $1;
}
| compound_statement
{
	$$ = $1;
}
| selection_statement
{
	$$ = $1;
}
| iteration_statement
{
	$$ = $1;
}
| jump_statement
{
	$$ = $1;
}
| declaration_statement %merge<ambiguityHandler>
{
	$$ = $1;
}
| try_block
{
	$$ = $1;
}
;

labeled_statement : IDENTIFIER ':' statement
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
	
	$$ = ASTMake2(AST_LABELED_STATEMENT, identifier, $3, $1.token_file, $1.token_line, NULL);
}
| CASE constant_expression ':' statement
{
	$$ = ASTMake2(AST_CASE_STATEMENT, $2, $4, $1.token_file, $1.token_line, NULL);
}
| DEFAULT ':' statement
{
	$$ = ASTMake1(AST_DEFAULT_STATEMENT, $3, $1.token_file, $1.token_line, NULL);
}
// GNU Extension
| CASE constant_expression ELLIPSIS constant_expression ':' statement
{
	$$ = ASTMake3(AST_GCC_CASE_STATEMENT, $2, $4, $6, $1.token_file, $1.token_line, NULL);
}
;

expression_statement : expression ';'
{
	$$ = ASTMake1(AST_EXPRESSION_STATEMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
| ';'
{
	// Empty statement ...
	$$ = ASTLeaf(AST_EMPTY_STATEMENT, $1.token_file, $1.token_line, NULL);
}
;

declaration_statement : non_empty_block_declaration
{
	$$ = ASTMake1(AST_DECLARATION_STATEMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

compound_statement : '{' statement_seq '}'
{
	$$ = ASTMake1(AST_COMPOUND_STATEMENT, $2, $1.token_file, $1.token_line, NULL);
}
| '{' '}'
{
	$$ = ASTMake1(AST_COMPOUND_STATEMENT, NULL, $1.token_file, $1.token_line, NULL);
}
;

statement_seq : statement
{
	$$ = ASTListLeaf($1);
}
| statement_seq statement
{
	$$ = ASTList($1, $2);
}
;

// If ambiguity
if_statement : IF '(' condition ')' statement
{
	$$ = ASTMake4(AST_IF_ELSE_STATEMENT, $3, $5, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
;

// Only if's with else within them
if_else_statement : IF '(' condition ')' if_else_eligible_statements ELSE statement
{
	$$ = ASTMake4(AST_IF_ELSE_STATEMENT, $3, $5, $7, NULL, $1.token_file, $1.token_line, NULL);
}
;

// Here we will generate if's that do not have an else inside
if_else_eligible_statements : no_if_statement
{
	$$ = $1;
}
| if_else_statement
{
	$$ = $1;
}
;

selection_statement : SWITCH '(' condition ')' statement
{
	$$ = ASTMake3(AST_SWITCH_STATEMENT, $3, $5, NULL, $1.token_file, $1.token_line, NULL);
}
;

condition : expression %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITION, NULL, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 declarator '=' initializer_clause %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITION, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_declarator '=' initializer_clause %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITION, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 declarator braced_init_list %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITION, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_declarator braced_init_list %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITION, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extension
| type_specifier_seq_0 declarator asm_specification attributes '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITION, $4,
			ASTMake4(AST_GCC_CONDITION_DECL, $1, $2, $3, $6, ASTFileName($1), ASTLine($1), NULL),
 ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_declarator asm_specification attributes '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITION, $4,
			ASTMake4(AST_GCC_CONDITION_DECL, $1, $2, $3, $6, ASTFileName($1), ASTLine($1), NULL),
 ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 declarator attributes '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITION, $3,
			ASTMake4(AST_GCC_CONDITION_DECL, $1, $2, NULL, $5, ASTFileName($1), ASTLine($1), NULL),
 ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_declarator attributes '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITION, $3,
			ASTMake4(AST_GCC_CONDITION_DECL, $1, $2, NULL, $5, ASTFileName($1), ASTLine($1), NULL),
 ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 declarator asm_specification '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITION, NULL,
			ASTMake4(AST_GCC_CONDITION_DECL, $1, $2, $3, $5, ASTFileName($1), ASTLine($1), NULL),
 ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_declarator asm_specification '=' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITION, NULL,
			ASTMake4(AST_GCC_CONDITION_DECL, $1, $2, $3, $5, ASTFileName($1), ASTLine($1), NULL),
 ASTFileName($1), ASTLine($1), NULL);
}
;

iteration_statement : WHILE '(' condition ')' statement
{
	$$ = ASTMake2(AST_WHILE_STATEMENT, $3, $5, $1.token_file, $1.token_line, NULL);
}
| DO statement WHILE '(' expression ')' ';'
{
	$$ = ASTMake2(AST_DO_STATEMENT, $2, $5, $1.token_file, $1.token_line, NULL);
}
| FOR '(' for_init_statement condition_opt ';' expression_opt ')' statement
{
    AST loop_control = ASTMake3(AST_LOOP_CONTROL, $3, $4, $6, $1.token_file, $1.token_line, NULL);
	$$ = ASTMake3(AST_FOR_STATEMENT, loop_control, $8, NULL, $1.token_file, $1.token_line, NULL);
}
;
expression_opt : expression
{
    $$ = $1;
}
| /* empty */
{
    $$ = NULL;
}
;

condition_opt : condition
{
    $$ = $1;
}
| /* empty */
{
    $$ = NULL;
}
;


for_init_statement : expression_statement %merge<ambiguityHandler>
{
	$$ = $1;
}
| non_empty_simple_declaration %merge<ambiguityHandler>
{
	$$ = $1;
}
;

jump_statement : BREAK ';'
{
	$$ = ASTLeaf(AST_BREAK_STATEMENT, $1.token_file, $1.token_line, NULL);
}
| CONTINUE ';'
{
	$$ = ASTLeaf(AST_CONTINUE_STATEMENT, $1.token_file, $1.token_line, NULL);
}
| RETURN ';'
{
	$$ = ASTMake1(AST_RETURN_STATEMENT, NULL, $1.token_file, $1.token_line, NULL);
}
| RETURN expression ';'
{
	$$ = ASTMake1(AST_RETURN_STATEMENT, $2, $1.token_file, $1.token_line, NULL);
}
| RETURN braced_init_list ';'
{
	$$ = ASTMake1(AST_RETURN_STATEMENT, $2, $1.token_file, $1.token_line, NULL);
}
| GOTO IDENTIFIER ';'
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);
	
	$$ = ASTMake1(AST_GOTO_STATEMENT, identifier, $1.token_file, $1.token_line, NULL);
}
// GNU Extension
| GOTO '*' expression ';'
{
	$$ = ASTMake1(AST_GCC_GOTO_STATEMENT, $3, $1.token_file, $1.token_line, NULL);
}
;

// *********************************************************
// A.10 - Special member functions
// *********************************************************

conversion_function_id : OPERATOR conversion_type_id
{
	$$ = ASTMake1(AST_CONVERSION_FUNCTION_ID, $2, $1.token_file, $1.token_line, NULL);
}
;

conversion_type_id : type_specifier_seq_0_may_end_with_attribute
{
	$$ = ASTMake2(AST_CONVERSION_TYPE_ID, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec
{
	$$ = ASTMake2(AST_CONVERSION_TYPE_ID, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 conversion_declarator
{
	$$ = ASTMake2(AST_CONVERSION_TYPE_ID, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_conversion_declarator
{
	$$ = ASTMake2(AST_CONVERSION_TYPE_ID, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

conversion_declarator : ptr_operator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator conversion_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

nonglobal_conversion_declarator : nonglobal_ptr_operator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_ptr_operator conversion_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

ctor_initializer : ':' mem_initializer_list
{
	$$ = ASTMake1(AST_CTOR_INITIALIZER, $2, $1.token_file, $1.token_line, NULL);
}
;

mem_initializer_list : mem_initializer
{
	$$ = ASTListLeaf($1);
}
| mem_initializer_list ',' mem_initializer
{
	$$ = ASTList($1, $3);
}
;

mem_initializer : mem_initializer_id '(' ')'
{
	$$ = ASTMake2(AST_MEM_INITIALIZER, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| mem_initializer_id '(' expression_list ')'
{
	$$ = ASTMake2(AST_MEM_INITIALIZER, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| mem_initializer_id braced_init_list
{
	$$ = ASTMake2(AST_MEM_INITIALIZER, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extensions
| '(' expression_list ')'
{
	$$ = ASTMake1(AST_GCC_MEM_INITIALIZER, $2, $1.token_file, $1.token_line, NULL);
}
| '(' ')'
{
	$$ = ASTMake1(AST_GCC_MEM_INITIALIZER, NULL, $1.token_file, $1.token_line, NULL);
}
;

mem_initializer_id : id_expression
{
	$$ = ASTMake1(AST_MEM_INITIALIZER_ID, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

// *********************************************************
// A.4 - Expressions
// *********************************************************

primary_expression : literal
{
	$$ = $1;
}
| TOKEN_THIS
{
	$$ = ASTLeaf(AST_THIS_VARIABLE, $1.token_file, $1.token_line, NULL);
}
| '(' expression ')' 
{
	$$ = ASTMake1(AST_PARENTHESIZED_EXPRESSION, $2, $1.token_file, $1.token_line, NULL);
}
| id_expression
{
	$$ = $1;
}
// GNU Extensions
/*
     ( compound-statement )
     __builtin_va_arg ( assignment-expression , type-name )
     __builtin_offsetof ( type-name , offsetof-member-designator )
*/
| '(' compound_statement ')'
{
	$$ = ASTMake1(AST_GCC_PARENTHESIZED_EXPRESSION, $2, $1.token_file, $1.token_line, NULL);
}
| BUILTIN_VA_ARG '(' assignment_expression ',' type_id ')'
{
	$$ = ASTMake2(AST_GCC_BUILTIN_VA_ARG, $3, $5, $1.token_file, $1.token_line, NULL);
}
| BUILTIN_OFFSETOF '(' type_id ',' offsetof_member_designator ')'
{
    $$ = ASTMake2(AST_GCC_BUILTIN_OFFSETOF, $3, $5, $1.token_file, $1.token_line, NULL);
}
| gnu_type_traits
{
    $$ = $1;
}
;

/* GNU extension */
/*
     __has_nothrow_assign ( type-id )   
     __has_nothrow_constructor ( type-id )
     __has_nothrow_copy ( type-id )
     __has_trivial_assign ( type-id )   
     __has_trivial_constructor ( type-id )
     __has_trivial_copy ( type-id )
     __has_trivial_destructor ( type-id )
     __has_virtual_destructor ( type-id )     
     __is_abstract ( type-id )
     __is_base_of ( type-id , type-id )
     __is_class ( type-id )
     __is_convertible_to ( type-id , type-id )     
     __is_empty ( type-id )
     __is_enum ( type-id )
     __is_literal_type ( type-id )
     __is_pod ( type-id )
     __is_polymorphic ( type-id )
     __is_standard_layout ( type-id )
     __is_trivial ( type-id )
     __is_union ( type-id )
*/
gnu_type_traits : GXX_HAS_NOTHROW_ASSIGN '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_NOTHROW_CONSTRUCTOR '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_NOTHROW_COPY '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_TRIVIAL_ASSIGN '(' type_id ')'   
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_TRIVIAL_CONSTRUCTOR '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_TRIVIAL_COPY '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_TRIVIAL_DESTRUCTOR '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_HAS_VIRTUAL_DESTRUCTOR '(' type_id ')'     
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_ABSTRACT '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_BASE_OF '(' type_id ',' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, $5, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_CLASS '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_CONVERTIBLE_TO '(' type_id ',' type_id ')'     
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, $5, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_EMPTY '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_ENUM '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_LITERAL_TYPE '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_POD '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_POLYMORPHIC '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_STANDARD_LAYOUT '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_TRIVIAL '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| GXX_IS_UNION '(' type_id ')'
{
    $$ = ASTMake2(AST_GXX_TYPE_TRAITS, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
;


/* GNU extension */
/*
   offsetof-member-designator:
     identifier
     offsetof-member-designator . identifier
     offsetof-member-designator [ expression ]
*/
offsetof_member_designator :  IDENTIFIER designator_list
{
    $$ = ASTMake2(AST_GCC_OFFSETOF_MEMBER_DESIGNATOR,
            ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text),
            $2, $1.token_file, $1.token_line, NULL);
}
| IDENTIFIER
{
    $$ = ASTMake2(AST_GCC_OFFSETOF_MEMBER_DESIGNATOR,
            ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text),
            NULL, $1.token_file, $1.token_line, NULL);
}
;

id_expression : qualified_id
{
	$$ = $1;
}
| unqualified_id
{
	$$ = $1;
}
;

nonglobal_id_expression : unqualified_id
{
    $$ = $1;
}
| qualified_id_no_template
{
    $$ = $1;
}
| qualified_id_template
{
    $$ = $1;
}
;

id_type_expr : qualified_id_type_name
{
    $$ = $1;
}
| unqualified_id_type_name
{
    $$ = $1;
}
| qualified_id_template
{
    $$ = $1;
}
;

nonglobal_id_type_expr: qualified_id_no_template
{
    $$ = $1;
}
| qualified_id_template
{
    $$ = $1;
}
| unqualified_id_type_name
{
    $$ = $1;
}
;

qualified_id_type_expr : qualified_id_type_name
{
    $$ = $1;
}
| qualified_id_template
{
    $$ = $1;
}
| qualified_id_globals_template
{
    $$ = $1;
}
;

qualified_id : qualified_id_no_template
{
    $$ = $1;
}
| qualified_id_globals
{
    $$ = $1;
}
| qualified_id_template
{
    $$ = $1;
}
;

qualified_id_globals : qualified_id_globals_no_template
{
    $$ = $1;
}
| qualified_id_globals_template
{
    $$ = $1;
}
| qualified_id_globals_operator
{
    $$ = $1;
}
;

qualified_id_type_name : qualified_id_globals_no_template
{
    $$ = $1;
}
| qualified_id_no_template
{
    $$ = $1;
}
;

qualified_id_globals_no_template : TWO_COLONS nested_name_specifier unqualified_id
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake3(AST_QUALIFIED_ID, global_op, $2, $3, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS IDENTIFIER
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake3(AST_QUALIFIED_ID, global_op, NULL, identifier, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS template_id
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake3(AST_QUALIFIED_ID, global_op, NULL, $2, $1.token_file, $1.token_line, NULL);
}
;

qualified_id_globals_operator : TWO_COLONS operator_function_id 
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);
	
	$$ = ASTMake3(AST_QUALIFIED_ID, global_op, NULL, $2, $1.token_file, $1.token_line, NULL);
}
;

qualified_id_globals_template : TWO_COLONS nested_name_specifier TEMPLATE template_id
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake3(AST_QUALIFIED_TEMPLATE, global_op, $2, $4, $1.token_file, $1.token_line, NULL);
}
;

qualified_id_no_template : nested_name_specifier unqualified_id
{
	$$ = ASTMake3(AST_QUALIFIED_ID, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

qualified_id_template : nested_name_specifier TEMPLATE template_id
{
	$$ = ASTMake3(AST_QUALIFIED_TEMPLATE, NULL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nested_name_specifier : class_or_namespace_name TWO_COLONS %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_NESTED_NAME_SPECIFIER, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| class_or_namespace_name TWO_COLONS nested_name_specifier_0 %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_NESTED_NAME_SPECIFIER, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

nested_name_specifier_0 : class_or_namespace_name TWO_COLONS %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_NESTED_NAME_SPECIFIER, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| TEMPLATE template_id TWO_COLONS %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_NESTED_NAME_SPECIFIER_TEMPLATE, $2, NULL, ASTFileName($2), ASTLine($2), NULL);
}
| class_or_namespace_name TWO_COLONS nested_name_specifier_0 %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_NESTED_NAME_SPECIFIER, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| TEMPLATE template_id TWO_COLONS nested_name_specifier_0 %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_NESTED_NAME_SPECIFIER_TEMPLATE, $2, $4, ASTFileName($2), ASTLine($2), NULL);
}
;

class_or_namespace_name : template_id
{
	$$ = $1;
}
| IDENTIFIER
{
	$$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;

unqualified_id : unqualified_id_type_name
{
    $$ = $1;
}
| unqualified_id_funct
{
    $$ = $1;
}
;

unqualified_id_type_name : IDENTIFIER
{
	$$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
| template_id
{
	$$ = $1;
}
;

unqualified_id_funct : operator_function_id
{
	$$ = $1;
}
| conversion_function_id
{
	$$ = $1;
}
| destructor_id
{
    $$ = $1;
}
;

destructor_id : '~' IDENTIFIER
{
	// Construct an artificial name for it
    char c[256];
    snprintf(c, 255, "~%s", $2.token_text);

	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, uniquestr(c));

	$$ = ASTMake1(AST_DESTRUCTOR_ID, identifier, $1.token_file, $1.token_line, NULL);
}
| destructor_template_id
{
    $$ = $1;
}
;


destructor_template_id : '~' template_id
{
	AST symbol = ASTSon0($2);

	// Construct an artificial name for it
    char c[256];
    snprintf(c, 255, "~%s", ASTText(symbol));

	$$ = ASTMake1(AST_DESTRUCTOR_TEMPLATE_ID, $2, $1.token_file, $1.token_line, uniquestr(c));
}
;

postfix_expression : primary_expression
{
	$$ = $1;
}
| postfix_expression '[' expression ']'
{
	$$ = ASTMake2(AST_ARRAY_SUBSCRIPT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression '[' braced_init_list ']'
{
	$$ = ASTMake2(AST_ARRAY_SUBSCRIPT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression '(' ')' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_FUNCTION_CALL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression '(' expression_list ')' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_FUNCTION_CALL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| simple_type_specifier '(' ')' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_EXPLICIT_TYPE_CONVERSION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| simple_type_specifier '(' expression_list ')' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_EXPLICIT_TYPE_CONVERSION, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| simple_type_specifier braced_init_list
{
	$$ = ASTMake2(AST_EXPLICIT_TYPE_CONVERSION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| TYPENAME qualified_id_type_expr '(' ')'
{
	$$ = ASTMake2(AST_TYPENAME_EXPLICIT_TYPE_CONV, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| TYPENAME qualified_id_type_expr '(' expression_list ')'
{
	$$ = ASTMake2(AST_TYPENAME_EXPLICIT_TYPE_CONV, $2, $4, $1.token_file, $1.token_line, NULL);
}
| TYPENAME qualified_id_type_expr braced_init_list
{
	$$ = ASTMake2(AST_TYPENAME_EXPLICIT_TYPE_CONV, $2, $3, $1.token_file, $1.token_line, NULL);
}
| postfix_expression '.' id_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_CLASS_MEMBER_ACCESS, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression '.' TEMPLATE id_expression
{
	$$ = ASTMake2(AST_CLASS_TEMPLATE_MEMBER_ACCESS, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression PTR_OP id_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_POINTER_CLASS_MEMBER_ACCESS, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression PTR_OP TEMPLATE id_expression 
{
	$$ = ASTMake2(AST_POINTER_CLASS_TEMPLATE_MEMBER_ACCESS, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression '.' pseudo_destructor_name %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_PSEUDO_DESTRUCTOR_CALL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression PTR_OP pseudo_destructor_name %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_POINTER_PSEUDO_DESTRUCTOR_CALL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression PLUSPLUS
{
	$$ = ASTMake1(AST_POSTINCREMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression MINUSMINUS
{
	$$ = ASTMake1(AST_POSTDECREMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
| DYNAMIC_CAST '<' type_id '>' '(' expression ')'
{
	$$ = ASTMake2(AST_DYNAMIC_CAST, $3, $6, $1.token_file, $1.token_line, NULL);
}
| STATIC_CAST '<' type_id '>' '(' expression ')' 
{
	$$ = ASTMake2(AST_STATIC_CAST, $3, $6, $1.token_file, $1.token_line, NULL);
}
| REINTERPRET_CAST '<' type_id '>' '(' expression ')'
{
	$$ = ASTMake2(AST_REINTERPRET_CAST, $3, $6, $1.token_file, $1.token_line, NULL);
}
| CONST_CAST '<' type_id '>' '(' expression ')'
{
	$$ = ASTMake2(AST_CONST_CAST, $3, $6, $1.token_file, $1.token_line, NULL);
}
| TYPEID '(' expression ')' %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_TYPEID_EXPR, $3, $1.token_file, $1.token_line, NULL);
}
| TYPEID '(' type_id ')'  %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_TYPEID_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| '(' type_id ')' '{' initializer_list '}'
{
	$$ = ASTMake2(AST_GCC_POSTFIX_EXPRESSION, $2, $5, $1.token_file, $1.token_line, NULL);
}
| '(' type_id ')' '{' initializer_list ',' '}'
{
	$$ = ASTMake2(AST_GCC_POSTFIX_EXPRESSION, $2, $5, $1.token_file, $1.token_line, NULL);
}
;

expression_list : initializer_list
{
    $$ = $1;
}
;

pseudo_destructor_name : id_expression TWO_COLONS destructor_id
{
	$$ = ASTMake2(AST_PSEUDO_DESTRUCTOR_NAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| id_expression TWO_COLONS TEMPLATE destructor_template_id
{
	$$ = ASTMake2(AST_PSEUDO_DESTRUCTOR_NAME_TEMPLATE, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
;

unary_expression : postfix_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| PLUSPLUS cast_expression
{
	$$ = ASTMake1(AST_PREINCREMENT, $2, $1.token_file, $1.token_line, NULL);
}
| MINUSMINUS cast_expression
{
	$$ = ASTMake1(AST_PREDECREMENT, $2, $1.token_file, $1.token_line, NULL);
}
| unary_operator cast_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1($1, $2, ASTFileName($2), ASTLine($2), NULL);
}
| SIZEOF unary_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_SIZEOF, $2, $1.token_file, $1.token_line, NULL);
}
| SIZEOF '(' type_id ')' %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_SIZEOF_TYPEID, $3, $1.token_file, $1.token_line, NULL);
}
| new_expression
{
	$$ = $1;
}
| delete_expression
{
	$$ = $1;
}
// GNU Extensions
| EXTENSION cast_expression
{
	$$ = ASTMake1(AST_GCC_EXTENSION_EXPR, $2, $1.token_file, $1.token_line, $1.token_text);
}
| ALIGNOF unary_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_GCC_ALIGNOF, $2, $1.token_file, $1.token_line, $1.token_text);
}
| ALIGNOF '(' type_id ')' %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_GCC_ALIGNOF_TYPE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| REAL cast_expression
{
	$$ = ASTMake1(AST_GCC_REAL_PART, $2, $1.token_file, $1.token_line, NULL);
}
| IMAG cast_expression
{
	$$ = ASTMake1(AST_GCC_IMAG_PART, $2, $1.token_file, $1.token_line, NULL);
}
| ANDAND IDENTIFIER
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake1(AST_GCC_LABEL_ADDR, identifier, $1.token_file, $1.token_line, NULL);
}
;

unary_operator : '*'
{
	$$ = AST_DERREFERENCE;
}
| '&' 
{
	$$ = AST_REFERENCE;
}
| '+'
{
	$$ = AST_PLUS;
}
| '-'
{
	$$ = AST_NEG;
}
| '!'
{
	$$ = AST_NOT;
}
| '~'
{
	$$ = AST_COMPLEMENT;
}
;

new_expression : TOKEN_NEW new_type_id 
{
	$$ = ASTMake4(AST_NEW_EXPRESSION, NULL, NULL, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW new_type_id new_initializer
{
	$$ = ASTMake4(AST_NEW_EXPRESSION, NULL, NULL, $2, $3, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW new_placement new_type_id 
{
	$$ = ASTMake4(AST_NEW_EXPRESSION, NULL, $2, $3, NULL, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW new_placement new_type_id new_initializer
{
	$$ = ASTMake4(AST_NEW_EXPRESSION, NULL, $2, $3, $4, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW new_type_id 
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_EXPRESSION, global_op, NULL, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW new_type_id new_initializer
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_EXPRESSION, global_op, NULL, $3, $4, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW new_placement new_type_id 
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_EXPRESSION, global_op, $3, $4, NULL, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW new_placement new_type_id new_initializer
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_EXPRESSION, global_op, $3, $4, $5, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW '(' type_id ')' 
{
	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, NULL, NULL, $3, NULL, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW '(' type_id ')' new_initializer
{
	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, NULL, NULL, $3, $5, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW new_placement '(' type_id ')' 
{
	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, NULL, $2, $4, NULL, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW new_placement '(' type_id ')' new_initializer
{
	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, NULL, $2, $4, $6, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW '(' type_id ')' 
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, global_op, NULL, $4, NULL, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW '(' type_id ')' new_initializer
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, global_op, NULL, $4, $6, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW new_placement '(' type_id ')' 
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, global_op, $3, $5, NULL, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_NEW new_placement '(' type_id ')' new_initializer
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake4(AST_NEW_TYPE_ID_EXPR, global_op, $3, $5, $7, $1.token_file, $1.token_line, NULL);
}
;

new_placement : '(' expression_list ')'
{
	$$ = ASTMake1(AST_NEW_PLACEMENT, $2, $1.token_file, $1.token_line, NULL);
}
;

new_type_id : type_specifier_seq_0_may_end_with_attribute
{
	$$ = ASTMake2(AST_NEW_TYPE_ID, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec
{
	$$ = ASTMake2(AST_NEW_TYPE_ID, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 new_declarator
{
	$$ = ASTMake2(AST_NEW_TYPE_ID, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_new_declarator
{
	$$ = ASTMake2(AST_NEW_TYPE_ID, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

new_declarator : ptr_operator 
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| ptr_operator new_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| direct_new_declarator
{
	$$ = $1;
}
;

nonglobal_new_declarator : nonglobal_ptr_operator 
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| nonglobal_ptr_operator new_declarator
{
	$$ = ASTMake2(AST_POINTER_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| direct_new_declarator
{
	$$ = $1;
}
;

direct_new_declarator : '[' expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| direct_new_declarator '[' constant_expression ']'
{
	$$ = ASTMake2(AST_DECLARATOR_ARRAY, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

new_initializer : '(' ')'
{
	$$ = ASTMake1(AST_NEW_INITIALIZER, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' expression_list ')'
{
	$$ = ASTMake1(AST_NEW_INITIALIZER, $2, $1.token_file, $1.token_line, NULL);
}
| braced_init_list
{
	$$ = ASTMake1(AST_NEW_INITIALIZER, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

delete_expression : TOKEN_DELETE cast_expression 
{
	$$ = ASTMake2(AST_DELETE_EXPR, NULL, $2, $1.token_file, $1.token_line, NULL);
}
| TOKEN_DELETE '[' ']' cast_expression
{
	$$ = ASTMake2(AST_DELETE_ARRAY_EXPR, NULL, $4, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_DELETE cast_expression 
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake2(AST_DELETE_EXPR, global_op, $3, $1.token_file, $1.token_line, NULL);
}
| TWO_COLONS TOKEN_DELETE '[' ']' cast_expression
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake2(AST_DELETE_ARRAY_EXPR, global_op, $5, $1.token_file, $1.token_line, NULL);
}
;

cast_expression : unary_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| '(' type_id ')' cast_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_CAST_EXPRESSION, $2, $4, $1.token_file, $1.token_line, NULL);
}
;

// pm stands for "pointer to member"
pm_expression : cast_expression
{
	$$ = $1;
}
| pm_expression PTR_OP_MUL cast_expression
{
	$$ = ASTMake2(AST_POINTER_TO_POINTER_MEMBER, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| pm_expression '.' '*' cast_expression
{
	$$ = ASTMake2(AST_POINTER_TO_MEMBER, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
;

multiplicative_expression : pm_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| multiplicative_expression '*' pm_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_MULT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| multiplicative_expression '/' pm_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_DIV, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| multiplicative_expression '%' pm_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_MOD, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

additive_expression : multiplicative_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| additive_expression '+' multiplicative_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_ADD, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| additive_expression '-' multiplicative_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_MINUS, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

shift_expression : additive_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| shift_expression LEFT additive_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SHL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| shift_expression right_token additive_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SHR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

relational_expression : shift_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| relational_expression '<' shift_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOWER_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| relational_expression '>' shift_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GREATER_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| relational_expression greater_equal_token shift_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GREATER_OR_EQUAL_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| relational_expression LESS_OR_EQUAL shift_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOWER_OR_EQUAL_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

equality_expression : relational_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| equality_expression EQUAL relational_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_EQUAL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| equality_expression NOT_EQUAL relational_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_DIFFERENT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

and_expression : equality_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| and_expression '&' equality_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_BITWISE_AND, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

exclusive_or_expression : and_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| exclusive_or_expression '^' and_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_BITWISE_XOR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

inclusive_or_expression : exclusive_or_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| inclusive_or_expression '|' exclusive_or_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_BITWISE_OR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

logical_and_expression : inclusive_or_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| logical_and_expression ANDAND inclusive_or_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOGICAL_AND, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

logical_or_expression : logical_and_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| logical_or_expression OROR logical_and_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOGICAL_OR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

conditional_expression : logical_or_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| logical_or_expression '?' expression ':' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITIONAL_EXPRESSION, $1, $3, $5, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extension
| logical_or_expression '?' ':' assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITIONAL_EXPRESSION, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
;

assignment_expression : conditional_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| logical_or_expression assignment_operator initializer_clause %merge<ambiguityHandler>
{
	$$ = ASTMake2($2, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| throw_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
;

expression : assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_EXPRESSION, $1, ASTFileName($1), ASTLine($1), NULL);
}
| expression ',' assignment_expression %merge<ambiguityHandler>
{
	AST comma_expression = ASTMake2(AST_COMMA, $1, $3, ASTFileName($1), ASTLine($1), NULL);

	$$ = ASTMake1(AST_EXPRESSION, comma_expression, ASTFileName(comma_expression), ASTLine(comma_expression), NULL);
}
;

assignment_operator : '='
{
	$$ = AST_ASSIGNMENT;
}
| MUL_ASSIGN
{
	$$ = AST_MUL_ASSIGNMENT;
}
| DIV_ASSIGN
{
	$$ = AST_DIV_ASSIGNMENT;
}
| ADD_ASSIGN
{
	$$ = AST_ADD_ASSIGNMENT;
}
| SUB_ASSIGN
{
	$$ = AST_SUB_ASSIGNMENT;
}
| LEFT_ASSIGN
{
	$$ = AST_SHL_ASSIGNMENT;
}
| right_assign_token
{
	$$ = AST_SHR_ASSIGNMENT;
}
| AND_ASSIGN
{
	$$ = AST_AND_ASSIGNMENT;
}
| OR_ASSIGN
{
	$$ = AST_OR_ASSIGNMENT;
}
| XOR_ASSIGN
{
	$$ = AST_XOR_ASSIGNMENT;
}
| MOD_ASSIGN
{
	$$ = AST_MOD_ASSIGNMENT;
}
;

constant_expression : conditional_expression
{
	$$ = ASTMake1(AST_CONSTANT_EXPRESSION, $1, ASTFileName($1), ASTLine($1), NULL);
}
;

// *********************************************************
// A.2 - Lexical conventions
// *********************************************************

literal : DECIMAL_LITERAL
{
	$$ = ASTLeaf(AST_DECIMAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| OCTAL_LITERAL
{
	$$ = ASTLeaf(AST_OCTAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| HEXADECIMAL_LITERAL
{
	$$ = ASTLeaf(AST_HEXADECIMAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| HEXADECIMAL_FLOAT
{
    $$ = ASTLeaf(AST_HEXADECIMAL_FLOAT, $1.token_file, $1.token_line, $1.token_text);
}
| FLOATING_LITERAL
{
	$$ = ASTLeaf(AST_FLOATING_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| BOOLEAN_LITERAL
{
	$$ = ASTLeaf(AST_BOOLEAN_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| CHARACTER_LITERAL
{
	$$ = ASTLeaf(AST_CHARACTER_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| string_literal
{
	$$ = $1;
}
;

// *********************************************************
// A.11 - Overloading
// *********************************************************

operator_function_id : OPERATOR operator
{
	$$ = ASTMake1(AST_OPERATOR_FUNCTION_ID, $2, $1.token_file, $1.token_line, NULL);
}
| OPERATOR operator '<' template_argument_list '>'
{
	$$ = ASTMake2(AST_OPERATOR_FUNCTION_ID_TEMPLATE, $2, $4, $1.token_file, $1.token_line, NULL);
}
| OPERATOR operator '<' '>'
{
	$$ = ASTMake2(AST_OPERATOR_FUNCTION_ID_TEMPLATE, $2, NULL, $1.token_file, $1.token_line, NULL);
}
;

operator : TOKEN_NEW
{
	$$ = ASTLeaf(AST_NEW_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| TOKEN_DELETE
{
	$$ = ASTLeaf(AST_DELETE_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| TOKEN_NEW '[' ']'
{
	$$ = ASTLeaf(AST_NEW_ARRAY_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| TOKEN_DELETE '[' ']'
{
	$$ = ASTLeaf(AST_DELETE_ARRAY_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '+'
{
	$$ = ASTLeaf(AST_ADDERATOR, $1.token_file, $1.token_line, NULL);
}
| '-'
{
	$$ = ASTLeaf(AST_MINUSERATOR, $1.token_file, $1.token_line, NULL);
}
| '*'
{
	$$ = ASTLeaf(AST_MULTERATOR, $1.token_file, $1.token_line, NULL);
}
| '/'
{
	$$ = ASTLeaf(AST_DIVERATOR, $1.token_file, $1.token_line, NULL);
}
| '%' 
{
	$$ = ASTLeaf(AST_MODERATOR, $1.token_file, $1.token_line, NULL);
}
| '^'
{
	$$ = ASTLeaf(AST_BITWISE_XOR_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '&'
{
	$$ = ASTLeaf(AST_BITWISE_AND_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '|'
{
	$$ = ASTLeaf(AST_BITWISE_OR_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '~'
{
	$$ = ASTLeaf(AST_BITWISE_NEG_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '!'
{
	$$ = ASTLeaf(AST_LOGICAL_NOT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '='
{
	$$ = ASTLeaf(AST_ASSIGNMENT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '<'
{
	$$ = ASTLeaf(AST_LOWER_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '>'
{
	$$ = ASTLeaf(AST_GREATER_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| ADD_ASSIGN
{
	$$ = ASTLeaf(AST_ADD_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| SUB_ASSIGN
{
	$$ = ASTLeaf(AST_SUB_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| MUL_ASSIGN
{
	$$ = ASTLeaf(AST_MUL_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| DIV_ASSIGN
{
	$$ = ASTLeaf(AST_DIV_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| MOD_ASSIGN
{
	$$ = ASTLeaf(AST_MOD_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| XOR_ASSIGN
{
	$$ = ASTLeaf(AST_XOR_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| AND_ASSIGN
{
	$$ = ASTLeaf(AST_AND_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| OR_ASSIGN
{
	$$ = ASTLeaf(AST_OR_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| LEFT
{
	$$ = ASTLeaf(AST_LEFT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| right_token
{
	$$ = ASTLeaf(AST_RIGHT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| LEFT_ASSIGN
{
	$$ = ASTLeaf(AST_LEFT_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| right_assign_token
{
	$$ = ASTLeaf(AST_RIGHT_ASSIGN_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| EQUAL
{
	$$ = ASTLeaf(AST_EQUALERATOR, $1.token_file, $1.token_line, NULL);
}
| NOT_EQUAL
{
	$$ = ASTLeaf(AST_DIFFERENTERATOR, $1.token_file, $1.token_line, NULL);
}
| LESS_OR_EQUAL
{
	$$ = ASTLeaf(AST_LESS_OR_EQUAL_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| greater_equal_token
{
	$$ = ASTLeaf(AST_GREATER_OR_EQUAL_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| ANDAND
{
	$$ = ASTLeaf(AST_LOGICAL_AND_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| OROR
{
	$$ = ASTLeaf(AST_LOGICAL_OR_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| PLUSPLUS
{
	$$ = ASTLeaf(AST_INCREMENT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| MINUSMINUS
{
	$$ = ASTLeaf(AST_DECREMENT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| ','
{
	$$ = ASTLeaf(AST_COMMAERATOR, $1.token_file, $1.token_line, NULL);
}
| PTR_OP
{
	$$ = ASTLeaf(AST_POINTER_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| PTR_OP_MUL
{
	$$ = ASTLeaf(AST_POINTER_DERREF_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '(' ')'
{
	$$ = ASTLeaf(AST_FUNCTION_CALL_OPERATOR, $1.token_file, $1.token_line, NULL);
}
| '[' ']'
{
	$$ = ASTLeaf(AST_SUBSCRIPT_OPERATOR, $1.token_file, $1.token_line, NULL);
}
;

// *********************************************************
// A.12 - Templates
// *********************************************************

template_id : IDENTIFIER '<' template_argument_list right_bracket_token
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake2(AST_TEMPLATE_ID, identifier, $3, $1.token_file, $1.token_line, NULL);
}
| IDENTIFIER '<' right_bracket_token
{
	AST identifier = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);

	$$ = ASTMake2(AST_TEMPLATE_ID, identifier, NULL, $1.token_file, $1.token_line, NULL);
}
;

template_argument_list : template_argument %merge<ambiguityHandler>
{
	$$ = ASTListLeaf($1);
}
| template_argument_list ',' template_argument %merge<ambiguityHandler>
{
	$$ = ASTList($1, $3);
}
;

template_argument : template_assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_TEMPLATE_EXPRESSION_ARGUMENT, 
			ASTMake1(AST_EXPRESSION, $1, ASTFileName($1), ASTLine($1), NULL), 
 ASTFileName($1), ASTLine($1), NULL);
}
| type_id %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_TEMPLATE_TYPE_ARGUMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
// A template_assignment_expression can generate one of these
// | id_expression 
// {
// 	$$ = $1;
// }
;

template_declaration : TEMPLATE '<' template_parameter_list '>' templated_declaration
{
	$$ = ASTMake2(AST_TEMPLATE_DECLARATION, $3, $5, $1.token_file, $1.token_line, NULL);
}
| EXPORT TEMPLATE '<' template_parameter_list '>' templated_declaration
{
	$$ = ASTMake2(AST_EXPORT_TEMPLATE_DECLARATION, $4, $6, $1.token_file, $1.token_line, NULL);
}
;

template_parameter_list : template_parameter
{
	$$ = ASTListLeaf($1);
}
| template_parameter_list ',' template_parameter
{
	$$ = ASTList($1, $3);
}
;

template_parameter : type_parameter %merge<ambiguityHandler>
{
	$$ = $1;
}
| parameter_declaration %merge<ambiguityHandler>
{
	$$ = $1;
}
;

type_parameter : CLASS
{
	$$ = ASTMake2(AST_TYPE_PARAMETER_CLASS, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| CLASS IDENTIFIER
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);
	
	$$ = ASTMake2(AST_TYPE_PARAMETER_CLASS, identifier, NULL, $1.token_file, $1.token_line, NULL);
}
| CLASS '=' type_id
{
	$$ = ASTMake2(AST_TYPE_PARAMETER_CLASS, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| CLASS IDENTIFIER '=' type_id
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_TYPE_PARAMETER_CLASS, identifier, $4, $1.token_file, $1.token_line, NULL);
}
| TYPENAME 
{
	$$ = ASTMake2(AST_TYPE_PARAMETER_TYPENAME, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| TYPENAME IDENTIFIER
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_TYPE_PARAMETER_TYPENAME, identifier, NULL, $1.token_file, $1.token_line, NULL);
}
| TYPENAME '=' type_id
{
	$$ = ASTMake2(AST_TYPE_PARAMETER_TYPENAME, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| TYPENAME IDENTIFIER '=' type_id
{
	AST identifier = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

	$$ = ASTMake2(AST_TYPE_PARAMETER_TYPENAME, identifier, $4, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE '<' template_parameter_list '>' CLASS
{
	$$ = ASTMake3(AST_TYPE_PARAMETER_TEMPLATE, $3, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE '<' template_parameter_list '>' CLASS IDENTIFIER
{
	AST identifier = ASTLeaf(AST_SYMBOL, $6.token_file, $6.token_line, $6.token_text);

	$$ = ASTMake3(AST_TYPE_PARAMETER_TEMPLATE, $3, identifier, NULL, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE '<' template_parameter_list '>' CLASS '=' id_expression
{
	$$ = ASTMake3(AST_TYPE_PARAMETER_TEMPLATE, $3, NULL, $7, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE '<' template_parameter_list '>' CLASS IDENTIFIER '=' id_expression
{
	AST identifier = ASTLeaf(AST_SYMBOL, $6.token_file, $6.token_line, $6.token_text);

	$$ = ASTMake3(AST_TYPE_PARAMETER_TEMPLATE, $3, identifier, $8, $1.token_file, $1.token_line, NULL);
}
;

explicit_instantiation : TEMPLATE decl_specifier_seq_0 declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, NULL, $2, $3, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE decl_specifier_seq_ended_with_named_type_spec nonglobal_declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, NULL, $2, $3, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE decl_specifier_seq_0 ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, NULL, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE decl_specifier_seq_ended_with_named_type_spec ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, NULL, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, NULL, NULL, $2, $1.token_file, $1.token_line, NULL);
}
// GNU Extensions
| storage_class_specifier TEMPLATE decl_specifier_seq_0 declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, $4, ASTFileName($1), ASTLine($1), NULL);
}
| storage_class_specifier TEMPLATE decl_specifier_seq_ended_with_named_type_spec nonglobal_declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, $4, ASTFileName($1), ASTLine($1), NULL);
}
| storage_class_specifier TEMPLATE decl_specifier_seq_0 ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| storage_class_specifier TEMPLATE decl_specifier_seq_ended_with_named_type_spec ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| storage_class_specifier TEMPLATE declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| function_specifier TEMPLATE decl_specifier_seq_0 declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, $4, ASTFileName($1), ASTLine($1), NULL);
}
| function_specifier TEMPLATE decl_specifier_seq_ended_with_named_type_spec nonglobal_declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, $4, ASTFileName($1), ASTLine($1), NULL);
}
| function_specifier TEMPLATE decl_specifier_seq_0 ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| function_specifier TEMPLATE decl_specifier_seq_ended_with_named_type_spec ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| function_specifier TEMPLATE declarator ';' %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_EXPLICIT_INSTANTIATION, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

explicit_specialization : TEMPLATE '<' '>' templated_declaration
{
	$$ = ASTMake1(AST_EXPLICIT_SPECIALIZATION, $4, $1.token_file, $1.token_line, NULL);
}
| TEMPLATE '<' '>' explicit_specialization
{
	$$ = ASTMake1(AST_EXPLICIT_SPECIALIZATION, $4, $1.token_file, $1.token_line, NULL);
}
// This is invalid, all enclosed things must be explicitly specialized
// | TEMPLATE '<' '>' template_declaration
// {
// 	$$ = ASTMake1(AST_EXPLICIT_SPECIALIZATION, $4, $1.token_file, $1.token_line, NULL);
// }
;


// These are the declarations that can follow a template preffix
// We give them known forms to ease semantic analysis
templated_declaration : decl_specifier_seq_0 init_declarator ';' %merge<ambiguityHandler>
{
	// Crafted form of simple declaration
    AST simple_decl_holder = ASTListLeaf($2);
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, simple_decl_holder, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec nonglobal_init_declarator ';' %merge<ambiguityHandler>
{
	// Crafted form of simple declaration
    AST simple_decl_holder = ASTListLeaf($2);
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, simple_decl_holder, ASTFileName($1), ASTLine($1), NULL);
}
| init_declarator ';' %merge<ambiguityHandler>
{
    AST init_decl_holder = ASTListLeaf($1);
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, NULL, init_decl_holder, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_0 ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| decl_specifier_seq_ended_with_named_type_spec ';' %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SIMPLE_DECLARATION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| function_definition %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_declaration %merge<ambiguityHandler>
{
	$$ = $1;
}
;

// *********************************************************
// A.12.1 - Template Expressions
// *********************************************************
// Template expressions have restrictions with > token at the outermost level

// Get back to the normal expressions
template_shift_expression : additive_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_shift_expression LEFT additive_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_SHL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
// Not here
// | template_shift_expression right_token additive_expression
// {
// 	$$ = ASTMake2(AST_SHR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
// }
;

template_relational_expression : template_shift_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_relational_expression '<' template_shift_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOWER_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
// Not here
// | template_relational_expression '>' shift_expression
// {
// }
// Not here
// | template_relational_expression greater_equal_token shift_expression
// {
// }
| template_relational_expression LESS_OR_EQUAL template_shift_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOWER_OR_EQUAL_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_equality_expression : template_relational_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_equality_expression EQUAL template_relational_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_EQUAL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| template_equality_expression NOT_EQUAL template_relational_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_DIFFERENT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_and_expression : template_equality_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_and_expression '&' template_equality_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_BITWISE_AND, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_exclusive_or_expression : template_and_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_exclusive_or_expression '^' template_and_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_BITWISE_XOR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_inclusive_or_expression : template_exclusive_or_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_inclusive_or_expression '|' template_exclusive_or_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_BITWISE_OR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_logical_and_expression : template_inclusive_or_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_logical_and_expression ANDAND template_inclusive_or_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOGICAL_AND, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_logical_or_expression : template_logical_and_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_logical_or_expression OROR template_logical_and_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_LOGICAL_OR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

template_conditional_expression : template_logical_or_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_logical_or_expression '?' template_expression ':' template_assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake3(AST_CONDITIONAL_EXPRESSION, $1, $3, $5, ASTFileName($1), ASTLine($1), NULL);
}
// GNU Extension
| template_logical_or_expression '?' ':' template_assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_GCC_CONDITIONAL_EXPRESSION, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
;

template_assignment_expression : template_conditional_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| template_logical_or_expression assignment_operator template_assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2($2, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
// Extremely unlikely
// | template_throw_expression
// {
// }
;

template_expression : template_assignment_expression %merge<ambiguityHandler>
{
	$$ = ASTMake1(AST_EXPRESSION, $1, ASTFileName($1), ASTLine($1), NULL);
}
| template_expression ',' template_assignment_expression %merge<ambiguityHandler>
{
	AST comma_expression = ASTMake2(AST_COMMA, $1, $3, ASTFileName($1), ASTLine($1), NULL);

	$$ = ASTMake1(AST_EXPRESSION, comma_expression, ASTFileName(comma_expression), ASTLine(comma_expression), NULL);
}
;


// *********************************************************
// A.13 - Exception handling
// *********************************************************

try_block : TRY compound_statement handler_seq
{
	$$ = ASTMake2(AST_TRY_BLOCK, $2, $3, $1.token_file, $1.token_line, NULL);
}
;

handler_seq : handler
{
	$$ = ASTListLeaf($1);
}
| handler_seq handler
{
	$$ = ASTList($1, $2);
}
;

handler : CATCH '(' exception_declaration ')' compound_statement
{
	$$ = ASTMake2(AST_CATCH_HANDLER, $3, $5, $1.token_file, $1.token_line, NULL);
}
;

exception_declaration : type_specifier_seq_0 nonabstract_declarator  
{
	$$ = ASTMake2(AST_EXCEPTION_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0 abstract_declarator
{
	$$ = ASTMake2(AST_EXCEPTION_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_0_may_end_with_attribute
{
	$$ = ASTMake2(AST_EXCEPTION_DECLARATION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
|  type_specifier_seq_ended_with_named_type_spec nonglobal_nonabstract_declarator  
{
	$$ = ASTMake2(AST_EXCEPTION_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec nonglobal_abstract_declarator
{
	$$ = ASTMake2(AST_EXCEPTION_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_specifier_seq_ended_with_named_type_spec
{
	$$ = ASTMake2(AST_EXCEPTION_DECLARATION, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| ELLIPSIS
{
	$$ = ASTLeaf(AST_ANY_EXCEPTION, $1.token_file, $1.token_line, NULL);
}
;

exception_specification : THROW '(' ')' 
{
	$$ = ASTMake1(AST_EXCEPTION_SPECIFICATION, NULL, $1.token_file, $1.token_line, NULL);
}
| THROW '(' type_id_list ')'
{
	$$ = ASTMake1(AST_EXCEPTION_SPECIFICATION, $3, $1.token_file, $1.token_line, NULL);
}
;

type_id_list : type_id 
{
	$$ = ASTListLeaf($1);
}
| type_id_list ',' type_id
{
	$$ = ASTList($1, $3);
}
;

throw_expression : THROW
{
	$$ = ASTMake1(AST_THROW_EXPRESSION, NULL, $1.token_file, $1.token_line, NULL);
}
| THROW assignment_expression
{
	$$ = ASTMake1(AST_THROW_EXPRESSION, $2, $1.token_file, $1.token_line, NULL);
}
;

unknown_pragma : UNKNOWN_PRAGMA
{
	$$ = ASTLeaf(AST_UNKNOWN_PRAGMA, $1.token_file, $1.token_line, $1.token_text);
}

// This eases parsing, though it should be viewed as a lexical issue
string_literal : STRING_LITERAL
{
	$$ = ASTLeaf(AST_STRING_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| string_literal STRING_LITERAL
{
	const char* str1 = ASTText($1);
	const char* str2 = $2.token_text;
	char* text = calloc(strlen(str1) + strlen(str2) + 1, sizeof(*text));

	strcat(text, str1);
	strcat(text, str2);

	$$ = ASTLeaf(AST_STRING_LITERAL, ASTFileName($1), ASTLine($1), text);
}
;

// *******************************************************
// * Crazy tokens implemented in grammar
// * We synthesize some fake tokens here
// *******************************************************

right_token : AB1 '>'
{
    $$.token_line = $1.token_line;
    $$.token_text = uniquestr(">>");
}
;

right_assign_token : AB1 AB2 '='
{
    $$.token_line = $1.token_line;
    $$.token_text = uniquestr(">>=");
}
;

greater_equal_token : AB2 '='
{
    $$.token_line = $1.token_line;
    $$.token_text = uniquestr(">=");
}
;

right_bracket_token : '>'
{
    $$.token_line = $1.token_line;
    $$.token_text = $1.token_text;
}
| AB1
{
    $$.token_line = $1.token_line;
    $$.token_text = $1.token_text;
}
| AB2
{
    $$.token_line = $1.token_line;
    $$.token_text = $1.token_text;
}
;





















translation_unit : subparsing
{
	*parsed_tree = $1;
}
;

subparsing : SUBPARSE_EXPRESSION expression
{
	$$ = $2;
}
| SUBPARSE_STATEMENT statement_seq
{
	$$ = $2;
}
| SUBPARSE_STATEMENT
{
	$$ = NULL;
}
| SUBPARSE_MEMBER member_specification_seq
{
	$$ = $2;
}
| SUBPARSE_DECLARATION declaration_sequence
{
	$$ = $2;
}
| SUBPARSE_DECLARATION
{
    $$ = NULL;
}
| SUBPARSE_TYPE type_id
{
    $$ = $2;
}
| SUBPARSE_TYPE_LIST subparse_type_list
{
    $$ = $2;
}
| SUBPARSE_EXPRESSION_LIST expression_list
{
    $$ = $2;
}
| SUBPARSE_ID_EXPRESSION id_expression
{
    $$ = $2;
}
;


subparse_type_list : type_specifier_seq_0
{
    $$ = ASTListLeaf($1);
}
| type_specifier_seq_ended_with_named_type_spec
{
    $$ = ASTListLeaf($1);
}
| subparse_type_list ',' type_specifier_seq_ended_with_named_type_spec
{
    $$ = ASTList($1, $3);
}
| subparse_type_list ',' type_specifier_seq_0
{
    $$ = ASTList($1, $3);
}
;

























postfix_expression : postfix_expression '[' expression_opt ':' expression_opt ']'
{
    $$ = ASTMake3(AST_ARRAY_SECTION, $1, $3, $5, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression '[' expression ';' expression ']'
{
    $$ = ASTMake3(AST_ARRAY_SECTION_SIZE, $1, $3, $5, ASTFileName($1), ASTLine($1), NULL);
}

;

noshape_cast_expression : unary_expression %merge<ambiguityHandler>
{
	$$ = $1;
}
| '(' type_id ')' cast_expression %merge<ambiguityHandler>
{
	$$ = ASTMake2(AST_CAST_EXPRESSION, $2, $4, $1.token_file, $1.token_line, NULL);
}
;

cast_expression : shape_seq noshape_cast_expression %merge<ambiguityHandler>
{
    $$ = ASTMake2(AST_SHAPING_EXPRESSION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;

shape_seq : shape_seq shape %dprec 2
{
    $$ = ASTList($1, $2);
}
| shape %dprec 1
{
    $$ = ASTListLeaf($1);
}
;

shape: '[' expression ']'
{
    $$ = $2;
}
;














statement : STATEMENT_PLACEHOLDER
{
    // The lexer ensures this has the following form
    // @STATEMENT-PH::0x1234abcd@, where the pointer coded
    // is an 'AST*'
    AST *tree = decode_placeholder($1.token_text);

    // This is an empty statement
    $$ = *tree = ASTMake1(AST_DECLARATION_STATEMENT,
            ASTLeaf(AST_EMPTY_DECL, $1.token_file, $1.token_line, $1.token_text), 
            $1.token_file, $1.token_line, NULL);
};



// This is code














































































// Grammar entry point

no_if_statement : pragma_custom_construct_statement
{
    $$ = $1;
}
| pragma_custom_directive
{
    $$ = $1;
}
;

declaration : pragma_custom_construct_declaration
{
    $$ = $1;
}
| pragma_custom_directive
{
	$$ = $1;
}
;

member_declaration : pragma_custom_construct_member_declaration
{
    $$ = $1;
}
| pragma_custom_directive
{
    $$ = $1;
}
;


















// Pragma custom

pragma_custom_directive : PRAGMA_CUSTOM pragma_custom_line_directive
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_DIRECTIVE, $2, NULL, $1.token_file, $1.token_line, $1.token_text);
}
;


pragma_custom_construct_declaration : PRAGMA_CUSTOM pragma_custom_line_construct declaration
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_CONSTRUCT, $2, $3, $1.token_file, $1.token_line, $1.token_text);
}
;

pragma_custom_construct_member_declaration : PRAGMA_CUSTOM pragma_custom_line_construct member_declaration
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_CONSTRUCT, $2, $3, $1.token_file, $1.token_line, $1.token_text);
}
;

pragma_custom_construct_statement : PRAGMA_CUSTOM pragma_custom_line_construct statement
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_CONSTRUCT, $2, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
























































pragma_custom_line_directive : PRAGMA_CUSTOM_DIRECTIVE pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $2, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM_DIRECTIVE '(' pragma_clause_arg_list ')' pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $5, $3, $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM_NEWLINE
{
    // This is a degenerated case caused by wrong designed pragmas
    $$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, NULL, NULL, NULL, 0, NULL);
}
;

pragma_custom_line_construct : PRAGMA_CUSTOM_CONSTRUCT pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $2, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM_CONSTRUCT '(' pragma_clause_arg_list ')' pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $5, $3, $1.token_file, $1.token_line, $1.token_text);
}
;

pragma_custom_clause_opt_seq : /* empty */
{
	$$ = NULL;
}
| pragma_custom_clause_seq
{
	$$ = $1;
}
;

pragma_custom_clause_seq : pragma_custom_clause
{
	$$ = ASTListLeaf($1);
}
| pragma_custom_clause_seq ',' pragma_custom_clause
{
	$$ = ASTList($1, $3);
}
| pragma_custom_clause_seq pragma_custom_clause
{
	$$ = ASTList($1, $2);
}
;

pragma_custom_clause : PRAGMA_CUSTOM_CLAUSE '(' pragma_clause_arg_list ')'
{
	$$ = ASTMake1(AST_PRAGMA_CUSTOM_CLAUSE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM_CLAUSE '(' ')'
{
	$$ = ASTMake1(AST_PRAGMA_CUSTOM_CLAUSE, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM_CLAUSE 
{
	$$ = ASTMake1(AST_PRAGMA_CUSTOM_CLAUSE, NULL, $1.token_file, $1.token_line, $1.token_text);
}
;

pragma_clause_arg_list : pragma_clause_arg
{
    AST node = ASTLeaf(AST_PRAGMA_CLAUSE_ARG, NULL, 0, $1);

    $$ = ASTListLeaf(node);
}
;

pragma_clause_arg : pragma_clause_arg_item
{
    $$ = $1;
}
| pragma_clause_arg pragma_clause_arg_item
{
    $$ = strappend($1, $2);
}
;

pragma_clause_arg_item : pragma_clause_arg_text
{
    $$ = $1;
}
;

pragma_clause_arg_text : PRAGMA_CLAUSE_ARG_TEXT
{
    $$ = $1.token_text;
}
;


// Verbatim construct
verbatim_construct : VERBATIM_PRAGMA VERBATIM_TYPE '(' IDENTIFIER ')' VERBATIM_TEXT
{
    AST ident = ASTLeaf(AST_SYMBOL, $4.token_file, $4.token_line, $4.token_text);

    $$ = ASTMake1(AST_VERBATIM, ident, $1.token_file, $1.token_line, $6.token_text);
}
| VERBATIM_PRAGMA VERBATIM_TEXT
{
    $$ = ASTMake1(AST_VERBATIM, NULL, $1.token_file, $1.token_line, $2.token_text);
}
;

common_block_declaration : verbatim_construct
{
    $$ = $1;
}
;

member_declaration : verbatim_construct
{
    $$ = $1;
}
;













// Grammar entry point
statement : custom_construct_statement
{
    $$ = $1;
}
;

// Custom code construct

custom_construct_statement : custom_construct_header statement
{
    $$ = ASTMake2(AST_CUSTOM_CONSTRUCT_STATEMENT, $1, $2, ASTFileName($1), ASTLine($1), NULL);
};

custom_construct_header : CONSTRUCT IDENTIFIER custom_construct_parameters_seq
{
    $$ = ASTMake1(AST_CUSTOM_CONSTRUCT_HEADER, $3, $1.token_file, $1.token_line, $2.token_text);
}
| CONSTRUCT IDENTIFIER 
{
    $$ = ASTMake1(AST_CUSTOM_CONSTRUCT_HEADER, NULL, $1.token_file, $1.token_line, $2.token_text);
}
;

custom_construct_parameters_seq : custom_construct_parameter
{
    $$ = ASTListLeaf($1);
}
| custom_construct_parameters_seq ',' custom_construct_parameter
{
    $$ = ASTList($1, $3);
}
;

custom_construct_parameter : IDENTIFIER ':' expression
{
    $$ = ASTMake2(AST_CUSTOM_CONSTRUCT_PARAMETER,
            ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text), 
            $3, 
            $1.token_file, $1.token_line, NULL);
}
;




































omp_udr_declare_arg : omp_udr_operator_list ':' omp_udr_type_specifier
{
    $$ = ASTMake3(AST_OMP_UDR_DECLARE_ARG, NULL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}

| TEMPLATE '<' template_parameter_list '>' omp_udr_operator_list ':' omp_udr_type_specifier
{
    $$ = ASTMake3(AST_OMP_UDR_DECLARE_ARG, $3, $5, $7, $1.token_file, $1.token_line, NULL);
}

;


omp_udr_declare_arg_2 : omp_udr_unqualified_operator ':' omp_udr_type_specifier_2 ':' omp_udr_expression
{
    $$ = ASTMake3(AST_OMP_UDR_DECLARE_ARG_2, $1, $3, $5, ASTFileName($1), ASTLine($1), NULL);
}
;









omp_udr_type_specifier : type_id
{
    $$ = ASTListLeaf($1);
}
| omp_udr_type_specifier ',' type_id
{
    $$ = ASTList($1, $3);
}
;


omp_udr_type_specifier_2 : type_id
{
    $$ = ASTListLeaf($1);
}
| omp_udr_type_specifier_2 ',' type_id
{
    $$ = ASTList($1, $3);
}


omp_udr_unqualified_operator :  IDENTIFIER
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
| omp_udr_builtin_op
{
	$$ = $1;
	struct { const char *op; const char *name; } map[] =
    { 
        { "+", "_plus_"},
        { "-", "_minus_"},
        { "*", "_mult_"},
        { "/", "_div_"},
        { "&", "_and_"},
        { "|", "_or_"},
        { "^", "_exp_"},
        { "&&", "_andand_"},
        { "||", "_oror_"},
        { NULL, NULL }
    };

	int i; 
	char found = 0;
	for (i = 0; map[i].op != NULL && !found; i++)
	{
		if ((found = (strcmp(ast_get_text($$), map[i].op) == 0)))
        {
            ast_set_type($$, AST_SYMBOL);
            ast_set_text($$, map[i].name);
		    break;
        }
	}
	if (!found)
    {
		internal_error("Unhandled operator '%s'", ast_get_text($$));
    }
}
;

omp_udr_expression : expression
{
    $$ = $1;
}
;

omp_udr_operator_2 : omp_udr_unqualified_operator
{
    $$ = $1;
}

| omp_udr_qualified_operator
{
    $$ = $1;
}

;


omp_udr_qualified_operator : TWO_COLONS nested_name_specifier omp_udr_unqualified_operator
{
	AST global_op = ASTLeaf(AST_GLOBAL_SCOPE, $1.token_file, $1.token_line, NULL);

	$$ = ASTMake3(AST_QUALIFIED_ID, global_op, $2, $3, $1.token_file, $1.token_line, NULL);
}
| nested_name_specifier omp_udr_unqualified_operator
{
	$$ = ASTMake3(AST_QUALIFIED_ID, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;


omp_udr_operator_list : omp_udr_operator
{
    $$ = ASTListLeaf($1);
}
| omp_udr_operator_list ',' omp_udr_operator
{
    $$ = ASTList($1, $3);
}
;

omp_udr_operator : id_expression
{
    $$ = $1;
}

| omp_udr_builtin_op
{
    $$ = $1;
}
| '.' unqualified_id
{
    $$ = ASTMake1(AST_OMP_UDR_MEMBER_OP, $2, $1.token_file, $1.token_line, $1.token_text);
}

;

omp_udr_builtin_op : '+'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| '-'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| '*'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| '/'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| '&'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| '|'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| '^'
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| ANDAND
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
| OROR
{
    $$ = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, $1.token_file, $1.token_line, $1.token_text);
}
;

subparsing : SUBPARSE_OMP_UDR_DECLARE omp_udr_declare_arg
{
    $$ = $2;
}
;

subparsing : SUBPARSE_OMP_UDR_DECLARE_2 omp_udr_declare_arg_2
{
    $$ = $2;
}
;

subparsing : SUBPARSE_OMP_UDR_IDENTITY omp_udr_identity
{
    $$ = $2;
}
;

subparsing : SUBPARSE_OMP_OPERATOR_NAME omp_udr_operator_2
{
    $$ = $2;
}
;

omp_udr_identity : initializer_clause
{
    $$ = $1;
}

| OMP_UDR_CONSTRUCTOR omp_udr_constructor_arguments
{
    $$ = ASTMake1(AST_OMP_UDR_CONSTRUCTOR, $2, $1.token_file, $1.token_line, $1.token_text);
}
| OMP_UDR_CONSTRUCTOR 
{
    $$ = ASTMake1(AST_OMP_UDR_CONSTRUCTOR,
            ASTMake1(AST_OMP_UDR_CONSTRUCTOR_ARGUMENTS, NULL, $1.token_file, $1.token_line, NULL),
            $1.token_file, $1.token_line, $1.token_text);
}

;


omp_udr_constructor_arguments : '(' ')'
{
    $$ = ASTMake1(AST_OMP_UDR_CONSTRUCTOR_ARGUMENTS, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' expression_list ')'
{
    $$ = ASTMake1(AST_OMP_UDR_CONSTRUCTOR_ARGUMENTS, $2, $1.token_file, $1.token_line, NULL);
}
;




















// Grammar entry point
subparsing : SUBPARSE_SUPERSCALAR_DECLARATOR superscalar_declarator opt_superscalar_region_spec_list
{
	$$ = ASTMake2(AST_SUPERSCALAR_DECLARATOR, $2, $3, ASTFileName($2), ASTLine($2), NULL);
}
| SUBPARSE_SUPERSCALAR_DECLARATOR_LIST superscalar_declarator_list
{
    $$ = $2;
}
| SUBPARSE_SUPERSCALAR_EXPRESSION expression opt_superscalar_region_spec_list
{
	$$ = ASTMake2(AST_SUPERSCALAR_EXPRESSION, $2, $3, ASTFileName($2), ASTLine($2), NULL);
}
;

superscalar_declarator_list : superscalar_declarator opt_superscalar_region_spec_list
{
	AST ss_decl = ASTMake2(AST_SUPERSCALAR_DECLARATOR, $1, $2, ASTFileName($1), ASTLine($1), NULL);
    $$ = ASTListLeaf(ss_decl);
}
| superscalar_declarator_list ',' superscalar_declarator opt_superscalar_region_spec_list
{
	AST ss_decl = ASTMake2(AST_SUPERSCALAR_DECLARATOR, $3, $4, ASTFileName($3), ASTLine($3), NULL);
    $$ = ASTList($1, ss_decl);
}
;

superscalar_declarator : declarator_id
{
	$$ = $1;
}
| superscalar_declarator '[' assignment_expression ']'
{
	$$ = ASTMake4(AST_DECLARATOR_ARRAY, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

opt_superscalar_region_spec_list :
/* NULL */
{
	$$ = NULL;
}
| superscalar_region_spec_list
;

superscalar_region_spec_list : superscalar_region_spec
{
	$$ = ASTListLeaf($1);
}
| superscalar_region_spec_list superscalar_region_spec
{
	$$ = ASTList($1, $2);
}
;

superscalar_region_spec : '{' '}'
{
	$$ = ASTLeaf(AST_SUPERSCALAR_REGION_SPEC_FULL, $1.token_file, $1.token_line, NULL);
}
| '{' expression '}'
{
	$$ = ASTMake1(AST_SUPERSCALAR_REGION_SPEC_SINGLE, $2, $1.token_file, $1.token_line, NULL);
}
| '{' expression TWO_DOTS expression '}'
{
	$$ = ASTMake2(AST_SUPERSCALAR_REGION_SPEC_RANGE, $2, $4, $1.token_file, $1.token_line, NULL);
}
| '{' expression ':' expression '}'
{
	$$ = ASTMake2(AST_SUPERSCALAR_REGION_SPEC_LENGTH, $2, $4, $1.token_file, $1.token_line, NULL);
}
;























nontype_specifier_without_attribute : cuda_specifiers
{
    $$ = $1;
}
;

postfix_expression : cuda_kernel_call
{
    $$ = $1;
}
;

cuda_specifiers : CUDA_DEVICE
{
    $$ = ASTLeaf(AST_CUDA_DEVICE, $1.token_file, $1.token_line, $1.token_text);
}
| CUDA_GLOBAL
{
    $$ = ASTLeaf(AST_CUDA_GLOBAL, $1.token_file, $1.token_line, $1.token_text);
}
| CUDA_HOST
{
    $$ = ASTLeaf(AST_CUDA_HOST, $1.token_file, $1.token_line, $1.token_text);
}
| CUDA_CONSTANT
{
    $$ = ASTLeaf(AST_CUDA_CONSTANT, $1.token_file, $1.token_line, $1.token_text);
}
| CUDA_SHARED
{
    $$ = ASTLeaf(AST_CUDA_SHARED, $1.token_file, $1.token_line, $1.token_text);
}
;

cuda_kernel_call : postfix_expression cuda_kernel_arguments '(' ')'
{
    $$ = ASTMake3(AST_CUDA_KERNEL_CALL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| postfix_expression cuda_kernel_arguments '(' expression_list ')'
{
    $$ = ASTMake3(AST_CUDA_KERNEL_CALL, $1, $2, $4, ASTFileName($1), ASTLine($1), NULL);
}
;

cuda_kernel_arguments : cuda_kernel_config_left cuda_kernel_config_list cuda_kernel_config_right
{
    $$ = $2;
}
;

cuda_kernel_config_list : assignment_expression ',' assignment_expression ',' assignment_expression ',' assignment_expression
{
    $$ = ASTMake4(AST_CUDA_KERNEL_ARGUMENTS, $1, $3, $5, $7, ASTFileName($1), ASTLine($1), NULL);
}
| assignment_expression ',' assignment_expression ',' assignment_expression
{
    $$ = ASTMake4(AST_CUDA_KERNEL_ARGUMENTS, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| assignment_expression ',' assignment_expression
{
    $$ = ASTMake4(AST_CUDA_KERNEL_ARGUMENTS, $1, $3, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

cuda_kernel_config_left : CUDA_KERNEL_LEFT
{
    $$ = $1;
}
;









cuda_kernel_config_right : AB1 AB1 '>'
{
    $$ = $1;
}
;










nontype_specifier_without_attribute : XL_BUILTIN_SPEC
{
    $$ = ASTLeaf(AST_XL_BUILTIN_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;




%%





























// This is code


#define TOK_SEPARATOR "::"
static AST* decode_placeholder(const char *c)
{
    const char * colons = strstr(c, TOK_SEPARATOR);

    if (colons == NULL)
    {
        internal_error("Invalid placeholder token", 0);
    }

    colons += strlen(TOK_SEPARATOR);

    AST *tree = NULL;
    sscanf(colons, "%p", &tree);

    if (tree == NULL)
    {
        internal_error("Invalid AST* reference", 0);
    }

    return tree;
}



#include "cxx-utils.h"

static AST ambiguityHandler (YYSTYPE x0, YYSTYPE x1)
{
	AST son0 = x0.ast;
	AST son1 = x1.ast;

	if (son0 == son1) 
	{
		internal_error("Ambiguity function received two trees that are the same!\n", 0);
	}

    return ast_make_ambiguous(son0, son1);
}



void yyerror(AST* parsed_tree UNUSED_PARAMETER, const char* c)
{
	fprintf(stderr, "%s:%d: error: %s\n", scanning_now.current_filename, scanning_now.line_number, c);
}
