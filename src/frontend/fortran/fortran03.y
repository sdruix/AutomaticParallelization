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
/**
   Bison grammar for mf03
*/
#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
	
#ifdef HAVE_STDINT_H
  #include <stdint.h>
#else
  // This is a common workaround
  #define SIZE_MAX ((size_t)-1)
#endif

#include "cxx-ast.h"
#include "cxx-utils.h"

#include "cxx-driver.h"

#include "fortran03-lexer.h"
// Enable debugging support

#define YYDEBUG 1
#define YYERROR_VERBOSE 1

// Parser memory
#define YYMAXDEPTH (INT_MAX)

// This is mandatory for GNU Bison
void yyerror(AST* parsed_tree, const char* c);

#define yylex mf03lex
#define yytext mf03text
extern int yylex(void);

%}

// Enable debug
%debug 

// We want a GLR parser
%glr-parser

// This is a parameter for yyparse
// where AST will be stored
%parse-param {AST* parsed_tree}


%union {
	token_atrib_t token_atrib;
	AST ast;
	AST ast2[2];
	AST ast3[3];
	AST ast4[4];
	node_t node_type;
    const char *text;
};

%{

static AST ast_make_node_label(node_t node_type, 
        AST label,
        AST ast1,
        AST ast2,
        AST ast3,
        AST ast4,
        const char* filename, 
        int line, 
        const char* token)
{
    AST stmt = ASTMake4(node_type, ast1, ast2, ast3, ast4, filename, line, token);
    if (label != NULL)
    {
        stmt = ASTMake2(AST_LABELED_STATEMENT, label, stmt, filename, line, token);
    }

    return stmt;
}

#define ASTMake1Label(n, lbl, f, l, t) ast_make_node_label((n), (lbl), NULL, NULL, NULL, NULL, (f), (l), (t))
#define ASTMake2Label(n, lbl, a1, f, l, t) ast_make_node_label((n), (lbl), (a1), NULL, NULL, NULL, (f), (l), (t))
#define ASTMake3Label(n, lbl, a1, a2, f, l, t) ast_make_node_label((n), (lbl), (a1), (a2), NULL, NULL, (f), (l), (t))
#define ASTMake4Label(n, lbl, a1, a2, a3, f, l, t) ast_make_node_label((n), (lbl), (a1), (a2), (a3), NULL, (f), (l), (t))
#define ASTMake5Label(n, lbl, a1, a2, a3, a4, f, l, t) ast_make_node_label((n), (lbl), (a1), (a2), (a3), (a4), (f), (l), (t))

static AST ambig_fun_array_ctor(YYSTYPE x0, YYSTYPE x1)
{
    AST result = ast_make_ambiguous(x0.ast, x1.ast);
    ast_set_text(result, "ARRAY_CTOR");

    return result;
}

static AST ambig_assignment_statement_function(YYSTYPE x0, YYSTYPE x1)
{
    AST result = ast_make_ambiguous(x0.ast, x1.ast);
    ast_set_text(result, "ASSIGNMENT");

    return result;
}

static AST ambig_io_control_spec(YYSTYPE x0, YYSTYPE x1)
{
   AST result = ast_make_ambiguous(x0.ast, x1.ast);
   ast_set_text(result, uniquestr("ambiguous_io_spec"));

   return result;
}

static void append_statement_to_block(AST block, AST stmt)
{
    if (ASTType(block) == AST_EMPTY_STATEMENT)
    {
        ast_set_type(block, AST_COMPOUND_STATEMENT);
        ast_set_child(block, 0, ASTListLeaf(stmt));
    }
    else if (ASTType(block) == AST_COMPOUND_STATEMENT)
    {
        ast_set_child(block, 0, ast_list_concat(ASTSon0(block), ASTListLeaf(stmt)));
    }
    else
    {
        internal_error("Invalid tree %s\n", ast_print_node_type(ASTType(block)));
    }
}

%}

// Rules
%type<ast> data_stmt_set
%type<ast> common_stmt
%type<ast> constant_expr
%type<ast> prefix
%type<ast> function_stmt
%type<ast> function_prototype
%type<ast> allocate_object
%type<ast> critical_construct
%type<ast> open_stmt
%type<ast> program
%type<ast> data_i_do_object
%type<ast> dealloc_opt
%type<ast> flush_spec
%type<ast> equivalence_stmt
%type<ast> endfile_stmt
%type<ast> type_bound_procedure_part
%type<ast> end_if_stmt
%type<ast> inquire_spec
%type<ast> default_char_constant_expr
%type<ast> level_2_expr
%type<ast> procedure_designator
%type<ast> case_value_range
%type<ast> use_stmt
%type<ast> logical_literal_constant
%type<ast> function_subprogram
%type<ast> complex_part
%type<ast> private_or_sequence
%type<ast> case_stmt
%type<ast> optional_stmt
%type<ast> prefix_spec
%type<ast> io_implied_do
%type<ast> component_attr_spec
%type<ast> wait_stmt
%type<ast> contains_stmt
%type<ast> import_stmt
%type<ast> io_unit
%type<ast> allstop_stmt
%type<ast> where_stmt
%type<ast> procedure_declaration_stmt
%type<ast> array_name_dim_spec
%type<ast> real_literal_constant
%type<ast> forall_construct_stmt
%type<ast> ac_spec
%type<ast> pointer_stmt
%type<ast> enumerator_def_stmt
%type<ast> data_component_def_stmt
%type<ast> component_decl
%type<ast> main_program
%type<ast> top_level_program_unit_stmts_seq
%type<ast> non_top_level_program_unit_stmts_seq
%type<ast> top_level_program_unit_stmts
%type<ast> non_top_level_program_unit_stmts
%type<ast> program_body
%type<ast> interface_program_body
%type<ast> subscript_triplet
%type<ast> forall_assignment_stmts
%type<ast> end_enum_stmt
%type<ast> if_construct
%type<ast> elseif_seq
%type<ast> type_bound_proc_binding
%type<ast> interface_block
%type<ast> print_stmt
%type<ast> case_part
%type<ast> internal_subprogram
%type<ast> proc_language_binding_spec
%type<ast> do_variable
%type<ast> namelist_stmt
%type<ast> sync_images_stmt
%type<ast> nonlabel_do_stmt
%type<ast> actual_arg
%type<ast> id_variable
%type<ast> end_where_stmt
%type<ast> elsewhere_stmt
%type<ast> array_spec
%type<ast> array_spec_list
%type<ast> array_spec_item
%type<ast> array_constructor
%type<ast> add_operand
%type<ast> proc_component_attr_spec
%type<ast> derived_type_def
%type<ast> derived_type_body
%type<ast> equiv_operand
%type<ast> level_4_expr
%type<ast> forall_stmt
%type<ast> forall_limit
%type<ast> end_block_data_stmt
%type<ast> data_stmt
%type<ast> attr_spec
%type<ast> end_critical_stmt
%type<ast> data_i_do_variable
%type<ast> ac_implied_do
%type<ast> sync_stat
%type<ast> interface_stmt
%type<ast> proc_pointer_init
%type<ast> end_associate_stmt
%type<ast> actual_arg_spec
%type<ast> codimension_decl
%type<ast> alloc_opt
%type<ast> lock_stmt
%type<ast> stop_stmt
%type<ast> pause_stmt
%type<ast> final_procedure_stmt
%type<ast> kind_selector
%type<ast> protected_stmt
%type<ast> private_stmt
%type<ast> sequence_stmt
%type<ast> end_do_stmt
%type<ast> access_spec
%type<ast> association
%type<ast> defined_io_generic_spec
%type<ast> defined_io_generic_spec_fmt
%type<ast> type_param_value
%type<ast> name
%type<ast> name_opt
%type<ast> name_colon_opt
%type<ast> name_not_keyword
%type<ast> defined_operator_name 
%type<ast> intrinsic_operator_name
%type<ast> user_defined_operator_name
%type<ast> generic_spec
%type<ast> file_name_expr
%type<ast> binary_constant
%type<ast> default_char_expr
%type<ast> volatile_stmt
%type<ast> submodule_stmt
%type<ast> saved_entity
%type<ast> block_stmt
%type<ast> subroutine_subprogram
%type<ast> function_reference
%type<ast> where_assignment_stmt
%type<ast> component_spec
%type<ast> cosubscript
%type<ast> proc_decl
%type<ast> data_stmt_value
%type<ast> interface_specification
%type<ast> upper_bound
%type<ast> interface_body
%type<ast> structure_constructor
%type<ast> stride
%type<ast> namelist_item
%type<ast> forall_header
%type<ast> suffix
%type<ast> logical_variable
%type<ast> primary
%type<ast> allocate_coarray_spec
%type<ast> dimension_stmt
%type<ast> logical_expr
%type<ast> letter_spec
%type<ast> named_constant
%type<ast> end_type_stmt
%type<ast> module_nature
%type<ast> common_block_object
%type<ast> write_stmt
%type<ast> parameter_stmt
%type<ast> type_param_def_stmt
%type<ast> selector
%type<ast> module
%type<ast> type_guard_stmt
%type<ast> select_type_stmt
%type<ast> image_set
%type<ast> expr
%type<ast> data_ref
%type<ast> data_ref_no_array
%type<ast> lock_variable
%type<ast> case_expr
%type<ast> mult_operand
%type<ast> loop_control
%type<ast> while_loop_control
%type<ast> concurrent_loop_control
%type<ast> data_implied_do
%type<ast> char_literal_constant
%type<ast> associate_construct
%type<ast> arithmetic_if_stmt
%type<ast> section_subscript
%type<ast> derived_type_stmt
%type<ast> octal_constant
%type<ast> type_guard_part
%type<ast> component_def_stmts
%type<ast> subroutine_stmt
%type<ast> allocatable_decl
%type<ast> access_id
%type<ast> entity_decl
%type<ast> entity_decl_specs
%type<ast> block_data
%type<ast> io_implied_do_object
%type<ast> level_5_expr
%type<ast> declaration_type_spec
%type<ast> vectorial_type
%type<ast> type_bound_generic_stmt
%type<ast> image_selector
%type<ast> io_implied_do_control
%type<ast> char_length
%type<ast> unsigned_arithmetic_literal_constant
%type<ast> int_literal_constant
%type<ast> char_selector
%type<ast> external_stmt
%type<ast> forall_triplet_spec
%type<ast> only
%type<ast> assignment_stmt
%type<ast> connect_spec
%type<ast> masked_elsewhere_stmt
%type<ast> rewind_stmt
%type<ast> action_stmts
%type<ast> end_program_stmt
%type<ast> lower_bound
%type<ast> associate_stmt
%type<ast> proc_target
%type<ast> external_subprogram
%type<ast> sync_all_stmt
%type<ast> pointer_assignment_stmt
%type<ast> access_stmt
%type<ast> value_stmt
%type<ast> mask_expr
%type<ast> source_expr
%type<ast> close_spec
%type<ast> select_type_construct
%type<ast> case_selector
%type<ast> label
%type<ast> end_select_stmt
%type<ast> pointer_object
%type<ast> subscript
%type<ast> specification_expr
%type<ast> block_data_stmt
%type<ast> continue_stmt
%type<ast> format
%type<ast> end_module_stmt
%type<ast> return_stmt
%type<ast> level_3_expr
%type<ast> lock_stat
%type<ast> bind_entity
%type<ast> common_name
%type<ast> case_construct
%type<ast> dummy_arg
%type<ast> default_char_variable
%type<ast> implicit_stmt
%type<ast> or_operand
%type<ast> type_spec
%type<ast> boz_literal_constant
%type<ast> do_construct
%type<ast> nonblock_do_construct
%type<ast> action_term_do_construct
%type<ast> outer_shared_do_construct
%type<ast> outer_shared_do_construct_2
%type<ast> inner_shared_do_construct
%type<ast> shared_term_do_construct
%type<ast> do_term_action_stmt
%type<ast> call_stmt
%type<ast> label_do_stmt
%type<ast> label_do_shared_stmt
%type<ast> do_shared_label
%type<ast> backspace_stmt
%type<ast> allocate_stmt
%type<ast> where_construct
%type<ast> end_subroutine_stmt
%type<ast> type_param_attr_spec
%type<ast> module_subprogram
%type<ast> save_stmt
%type<ast> ac_value
%type<ast> stop_code
%type<ast> allocatable_stmt
%type<ast> iomsg_variable
%type<ast> goto_stmt
%type<ast> end_interface_stmt
%type<ast> rename
%type<ast> common_block_item
%type<ast> asynchronous_stmt
%type<ast> type_bound_proc_decl
%type<ast> io_control_spec
%type<ast> proc_interface
%type<ast> flush_stmt
%type<ast> length_selector
%type<ast> exit_stmt
%type<ast> initialization
%type<ast> deallocate_stmt
%type<ast> allocation
%type<ast> ac_do_variable
%type<ast> coarray_spec
%type<ast> level_0_expr
%type<ast> level_1_expr
%type<ast> derived_type_spec
%type<ast> cycle_stmt
%type<ast> select_case_stmt
%type<ast> component_part
%type<ast> pointer_decl
%type<ast> type_attr_spec
%type<ast> namelist_group_object
%type<ast> target_stmt
%type<ast> end_select_type_stmt
%type<ast> submodule
%type<ast> intrinsic_stmt
%type<ast> forall_construct
%type<ast> enumerator
%type<ast> module_subprogram_part
%type<ast> complex_literal_constant
%type<ast> type_param_spec
%type<ast> where_construct_stmt
%type<ast> where_construct_body
%type<ast> program_stmt
%type<ast> if_stmt
%type<ast> critical_stmt
%type<ast> inquire_stmt
%type<ast> component_data_source
%type<ast> label_assign_stmt
%type<ast> computed_goto_stmt
%type<ast> assigned_goto_stmt
%type<ast> target_decl
%type<ast> unlock_stmt
%type<ast> read_stmt
%type<ast> nullify_stmt
%type<ast> language_binding_spec
%type<ast> named_constant_def
%type<ast> sync_memory_stmt
%type<ast> mask_elsewhere_part
%type<ast> int_expr
%type<ast> comma_int_expr_opt
%type<ast> binding_attr
%type<ast> proc_component_def_stmt
%type<ast> forall_body_construct
%type<ast> close_stmt
%type<ast> end_mp_subprogram_stmt
%type<ast> wait_spec
%type<ast> entry_stmt
%type<ast> internal_subprogram_part
%type<ast> parent_identifier
%type<ast> separate_module_subprogram
%type<ast> hex_constant
%type<ast> end_function_stmt
%type<ast> enum_def
%type<ast> block
%type<ast> top_level_block
%type<ast> opt_statement_seq
%type<ast> intent_stmt
%type<ast> case_value
%type<ast> and_operand
%type<ast> where_body_construct
%type<ast> int_variable
%type<ast> data_stmt_object
%type<ast> enum_def_stmt
%type<ast> input_output_item
%type<ast> type_declaration_stmt
%type<ast> stat_variable
%type<ast> type_param_decl
%type<ast> codimension_stmt
%type<ast> int_constant_expr
%type<ast> equivalence_set
%type<ast> end_block_stmt
%type<ast> alt_return_spec
%type<ast> equivalence_object
%type<ast> mp_subprogram_stmt
%type<ast> block_construct
%type<ast> intent_spec
%type<ast> position_spec
%type<ast> module_stmt
%type<ast> proc_attr_spec
%type<ast> implicit_spec
%type<ast> numeric_expr
%type<ast> end_forall_stmt
%type<ast> stmt_function_stmt
%type<ast> proc_pointer_object
%type<ast> file_unit_number
%type<ast> intrinsic_type_spec
%type<ast> end_submodule_stmt
%type<ast> program_unit
%type<ast> variable
%type<ast> bind_stmt
%type<ast> ac_implied_do_control
%type<ast> type_bound_procedure_stmt
%type<ast> errmsg_variable
%type<ast> forall_step
%type<ast> format_stmt
%type<ast> procedure_stmt
%type<ast> where_body_construct_seq
%type<ast> mask_elsewhere_part_seq
%type<ast> private_or_sequence_seq
%type<ast> prefix_spec_seq
%type<ast> case_part_seq
%type<ast> forall_body_construct_seq
%type<ast> type_bound_proc_binding_seq
%type<ast> type_param_def_stmt_seq
%type<ast> program_unit_seq
%type<ast> type_guard_part_seq
%type<ast> component_def_stmts_seq
%type<ast> module_subprogram_seq
%type<ast> interface_specification_seq
%type<ast> internal_subprogram_seq
%type<ast> enumerator_def_stmt_seq
%type<ast> data_stmt_set_list
%type<ast> position_spec_list
%type<ast> type_param_name_list
%type<ast> external_name_list
%type<ast> equivalence_set_list
%type<ast> entity_name_list
%type<ast> binding_name_list
%type<ast> lock_stat_list
%type<ast> close_spec_list
%type<ast> type_attr_spec_list
%type<ast> io_implied_do_object_list
%type<ast> case_value_range_list
%type<ast> namelist_group_object_list
%type<ast> sync_stat_list
%type<ast> implicit_spec_list
%type<ast> letter_spec_list
%type<ast> data_stmt_object_list
%type<ast> component_decl_list
%type<ast> label_list
%type<ast> named_constant_def_list
%type<ast> bind_entity_list
%type<ast> flush_spec_list
%type<ast> io_control_spec_list
%type<ast> proc_component_attr_spec_list
%type<ast> saved_entity_list
%type<ast> input_output_item_list
%type<ast> common_block_object_list
%type<ast> codimension_decl_list
%type<ast> component_spec_list
%type<ast> only_list
%type<ast> binding_attr_list
%type<ast> forall_triplet_spec_list
%type<ast> object_name_list
%type<ast> alloc_opt_list
%type<ast> pointer_object_list
%type<ast> type_param_decl_list
%type<ast> connect_spec_list
%type<ast> section_subscript_list
%type<ast> pointer_decl_list
%type<ast> component_attr_spec_list
%type<ast> final_subroutine_name_list
%type<ast> procedure_name_list
%type<ast> enumerator_list
%type<ast> data_i_do_object_list
%type<ast> type_bound_proc_decl_list
%type<ast> wait_spec_list
%type<ast> cosubscript_list
%type<ast> intrinsic_procedure_name_list
%type<ast> type_param_spec_list
%type<ast> allocation_list
%type<ast> allocate_object_list
%type<ast> dummy_arg_name_list
%type<ast> dummy_arg_name_list_proto
%type<ast> proc_attr_spec_list
%type<ast> proc_decl_list
%type<ast> data_stmt_value_list
%type<ast> ac_value_list
%type<ast> association_list
%type<ast> dummy_arg_list
%type<ast> equivalence_object_list
%type<ast> allocatable_decl_list
%type<ast> import_name_list
%type<ast> inquire_spec_list
%type<ast> common_block_item_list
%type<ast> dealloc_opt_list
%type<ast> actual_arg_spec_list
%type<ast> rename_list
%type<ast> attr_spec_list
%type<ast> target_decl_list
%type<ast> access_id_list
%type<ast> array_name_dim_spec_list
%type<ast> entity_decl_list
%type<ast> namelist_item_list
%type<ast> a_list_of_names
%type<ast> decimal_literal 
%type<ast> labeldef
%type<ast> unknown_pragma
// Node types
%type<node_type> sign
// Token rules
%type<token_atrib> keyword
%type<token_atrib> eos
%type<token_atrib> intrinsic_operator
%type<token_atrib> extended_intrinsic_op
%type<token_atrib> user_defined_op
%type<token_atrib> local_defined_operator
%type<token_atrib> power_op
%type<token_atrib> mult_op
%type<token_atrib> add_op
%type<token_atrib> concat_op
%type<token_atrib> rel_op
%type<token_atrib> not_op
%type<token_atrib> and_op
%type<token_atrib> or_op
%type<token_atrib> equiv_op
%type<token_atrib> end_block_data_toks
%type<token_atrib> goto_toks
%type<token_atrib> elseif_toks
%type<token_atrib> elsewhere_toks
%type<token_atrib> selectcase_toks
// Tokens
%token<token_atrib> TOK_FORMAT "FORMAT"
%token<token_atrib> TOK_GENERIC "GENERIC"
%token<token_atrib> TOK_VOLATILE "VOLATILE"
%token<token_atrib> TOK_EQUIVALENCE "EQUIVALENCE"
%token<token_atrib> TOK_EOR "EOR"
%token<token_atrib> TOK_PROTECTED "PROTECTED"
%token<token_atrib> TOK_PAD "PAD"
%token<token_atrib> TOK_FILE "FILE"
%token<token_atrib> TOK_UNFORMATTED "UNFORMATTED"
%token<token_atrib> TOK_NAMED "NAMED"
%token<token_atrib> TOK_SUBROUTINE "SUBROUTINE"
%token<token_atrib> TOK_OPENED "OPENED"
%token<token_atrib> TOK_DELIM "DELIM"
%token<token_atrib> TOK_SOURCE "SOURCE"
%token<token_atrib> TOK_CRITICAL "CRITICAL"
%token<token_atrib> TOK_ACTION "ACTION"
%token<token_atrib> TOK_IMPORT "IMPORT"
%token<token_atrib> TOK_BLOCK "BLOCK"
%token<token_atrib> TOK_ENUM "ENUM"
%token<token_atrib> TOK_OVERRIDABLE "OVERRIDABLE"
%token<token_atrib> TOK_MODULE "MODULE"
%token<token_atrib> TOK_SIGN "SIGN"
%token<token_atrib> TOK_EXTENDS "EXTENDS"
%token<token_atrib> TOK_PASS "PASS"
%token<token_atrib> TOK_GO "GO"
%token<token_atrib> TOK_ENTRY "ENTRY"
%token<token_atrib> TOK_WHERE "WHERE"
%token<token_atrib> TOK_PROCEDURE "PROCEDURE"
%token<token_atrib> TOK_NAME "NAME"
%token<token_atrib> TOK_DOUBLE "DOUBLE"
%token<token_atrib> TOK_CONTAINS "CONTAINS"
%token<token_atrib> TOK_LOGICAL "LOGICAL"
%token<token_atrib> TOK_NEWUNIT "NEWUNIT"
%token<token_atrib> TOK_NULLIFY "NULLIFY"
%token<token_atrib> TOK_DEFERRED "DEFERRED"
%token<token_atrib> TOK_ONLY "ONLY"
%token<token_atrib> TOK_EXIST "EXIST"
%token<token_atrib> TOK_INTERFACE "INTERFACE"
%token<token_atrib> TOK_SAVE "SAVE"
%token<token_atrib> TOK_ADVANCE "ADVANCE"
%token<token_atrib> TOK_STAT "STAT"
%token<token_atrib> TOK_RETURN "RETURN"
%token<token_atrib> TOK_READWRITE "READWRITE"
%token<token_atrib> TOK_ASSIGNMENT "ASSIGNMENT"
%token<token_atrib> TOK_ASSIGN "ASSIGN"
%token<token_atrib> TOK_PRINT "PRINT"
%token<token_atrib> TOK_IOSTAT "IOSTAT"
%token<token_atrib> TOK_SYNC "SYNC"
%token<token_atrib> TOK_COMPLEX "COMPLEX"
%token<token_atrib> TOK_ASYNCHRONOUS "ASYNCHRONOUS"
%token<token_atrib> TOK_IMAGES "IMAGES"
%token<token_atrib> TOK_END "END"
%token<token_atrib> TOK_FINAL "FINAL"
%token<token_atrib> TOK_INOUT "INOUT"
%token<token_atrib> TOK_NEXTREC "NEXTREC"
%token<token_atrib> TOK_KIND "KIND"
%token<token_atrib> TOK_COMMON "COMMON"
%token<token_atrib> TOK_BLANK "BLANK"
%token<token_atrib> TOK_IOLENGTH "IOLENGTH"
%token<token_atrib> TOK_INTEGER "INTEGER"
%token<token_atrib> TOK_DEALLOCATE "DEALLOCATE"
%token<token_atrib> TOK_FUNCTION "FUNCTION"
%token<token_atrib> TOK_C "C"
%token<token_atrib> TOK_ENUMERATOR "ENUMERATOR"
%token<token_atrib> TOK_RECURSIVE "RECURSIVE"
%token<token_atrib> TOK_SEQUENCE "SEQUENCE"
%token<token_atrib> TOK_INQUIRE "INQUIRE"
%token<token_atrib> TOK_FLUSH "FLUSH"
%token<token_atrib> TOK_ELSE "ELSE"
%token<token_atrib> TOK_INTENT "INTENT"
%token<token_atrib> TOK_EXTERNAL "EXTERNAL"
%token<token_atrib> TOK_OPERATOR "OPERATOR"
%token<token_atrib> TOK_OPTIONAL "OPTIONAL"
%token<token_atrib> TOK_UNIT "UNIT"
%token<token_atrib> TOK_SIZE "SIZE"
%token<token_atrib> TOK_NOPASS "NOPASS"
%token<token_atrib> TOK_TYPE "TYPE"
%token<token_atrib> TOK_MOLD "MOLD"
%token<token_atrib> TOK_PRECISION "PRECISION"
%token<token_atrib> TOK_PENDING "PENDING"
%token<token_atrib> TOK_CONTINUE "CONTINUE"
%token<token_atrib> TOK_RESULT "RESULT"
%token<token_atrib> TOK_REAL "REAL"
%token<token_atrib> TOK_THEN "THEN"
%token<token_atrib> TOK_STREAM "STREAM"
%token<token_atrib> TOK_DO "DO"
%token<token_atrib> TOK_DEFAULT "DEFAULT"
%token<token_atrib> TOK_CONTIGUOUS "CONTIGUOUS"
%token<token_atrib> TOK_STOP "STOP"
%token<token_atrib> TOK_PAUSE "PAUSE"
%token<token_atrib> TOK_WHILE "WHILE"
%token<token_atrib> TOK_PROGRAM "PROGRAM"
%token<token_atrib> TOK_REC "REC"
%token<token_atrib> TOK_OPEN "OPEN"
%token<token_atrib> TOK_CASE "CASE"
%token<token_atrib> TOK_RECL "RECL"
%token<token_atrib> TOK_DIMENSION "DIMENSION"
%token<token_atrib> TOK_ELEMENTAL "ELEMENTAL"
%token<token_atrib> TOK_FORALL "FORALL"
%token<token_atrib> TOK_POSITION "POSITION"
%token<token_atrib> TOK_FMT "FMT"
%token<token_atrib> TOK_READ "READ"
%token<token_atrib> TOK_OUT "OUT"
%token<token_atrib> TOK_LOCK "LOCK"
%token<token_atrib> TOK_DECIMAL "DECIMAL"
%token<token_atrib> TOK_SELECT "SELECT"
%token<token_atrib> TOK_SELECTCASE "SELECTCASE"
%token<token_atrib> TOK_DIRECT "DIRECT"
%token<token_atrib> TOK_WRITE "WRITE"
%token<token_atrib> TOK_CODIMENSION "CODIMENSION"
%token<token_atrib> TOK_CLOSE "CLOSE"
%token<token_atrib> TOK_ID "ID"
%token<token_atrib> TOK_WAIT "WAIT"
%token<token_atrib> TOK_ALL "ALL"
%token<token_atrib> TOK_ELSEWHERE "ELSEWHERE"
%token<token_atrib> TOK_LEN "LEN"
%token<token_atrib> TOK_IMPURE "IMPURE"
%token<token_atrib> TOK_EXIT "EXIT"
%token<token_atrib> TOK_REWIND "REWIND"
%token<token_atrib> TOK_BACKSPACE "BACKSPACE"
%token<token_atrib> TOK_NML "NML"
%token<token_atrib> TOK_INTRINSIC "INTRINSIC"
%token<token_atrib> TOK_PUBLIC "PUBLIC"
%token<token_atrib> TOK_ERRMSG "ERRMSG"
%token<token_atrib> TOK_NAMELIST "NAMELIST"
%token<token_atrib> TOK_USE "USE"
%token<token_atrib> TOK_SUBMODULE "SUBMODULE"
%token<token_atrib> TOK_ERR "ERR"
%token<token_atrib> TOK_ENCODING "ENCODING"
%token<token_atrib> TOK_ACQUIRED "ACQUIRED"
%token<token_atrib> TOK_ABSTRACT "ABSTRACT"
%token<token_atrib> TOK_CHARACTER "CHARACTER"
%token<token_atrib> TOK_NUMBER "NUMBER"
%token<token_atrib> TOK_CONCURRENT "CONCURRENT"
%token<token_atrib> TOK_ENDFILE "ENDFILE"
%token<token_atrib> TOK_PARAMETER "PARAMETER"
%token<token_atrib> TOK_DATA "DATA"
%token<token_atrib> TOK_POS "POS"
%token<token_atrib> TOK_PRIVATE "PRIVATE"
%token<token_atrib> TOK_ROUND "ROUND"
%token<token_atrib> TOK_TO "TO"
%token<token_atrib> TOK_SEQUENTIAL "SEQUENTIAL"
%token<token_atrib> TOK_ALLOCATE "ALLOCATE"
%token<token_atrib> TOK_TARGET "TARGET"
%token<token_atrib> TOK_CLASS "CLASS"
%token<token_atrib> TOK_CYCLE "CYCLE"
%token<token_atrib> TOK_STATUS "STATUS"
%token<token_atrib> TOK_IOMSG "IOMSG"
%token<token_atrib> TOK_FORM "FORM"
%token<token_atrib> TOK_IS "IS"
%token<token_atrib> TOK_NONE "NONE"
%token<token_atrib> TOK_VALUE "VALUE"
%token<token_atrib> TOK_UNLOCK "UNLOCK"
%token<token_atrib> TOK_FORMATTED "FORMATTED"
%token<token_atrib> TOK_IN "IN"
%token<token_atrib> TOK_IMPLICIT "IMPLICIT"
%token<token_atrib> TOK_IF "IF"
%token<token_atrib> TOK_ASSOCIATE "ASSOCIATE"
%token<token_atrib> TOK_BIND "BIND"
%token<token_atrib> TOK_ALLOCATABLE "ALLOCATABLE"
%token<token_atrib> TOK_ACCESS "ACCESS"
%token<token_atrib> TOK_CALL "CALL"
%token<token_atrib> TOK_PURE "PURE"
%token<token_atrib> TOK_MEMORY "MEMORY"
%token<token_atrib> TOK_POINTER "POINTER"
%token<token_atrib> TOK_VECTOR "VECTOR"
%token<token_atrib> TOK_PIXEL "PIXEL"
%token<token_atrib> TOK_NON_OVERRIDABLE "NON_OVERRIDABLE"
%token<token_atrib> TOK_NON_INTRINSIC "NON_INTRINSIC"
// Combined keywords
%token<token_atrib> TOK_ALLSTOP "ALLSTOP"
%token<token_atrib> TOK_ENDDO "ENDDO"
%token<token_atrib> TOK_ENDIF "ENDIF"
%token<token_atrib> TOK_ENDFUNCTION "ENDFUNCTION"
%token<token_atrib> TOK_BLOCKDATA "BLOCKDATA" 
%token<token_atrib> TOK_ENDMODULE "ENDMODULE"
%token<token_atrib> TOK_DOUBLEPRECISION "DOUBLEPRECISION" 
%token<token_atrib> TOK_ENDINTERFACE "ENDINTERFACE"
%token<token_atrib> TOK_ELSEIF "ELSEIF" 
%token<token_atrib> TOK_ENDPROCEDURE "ENDPROCEDURE"
%token<token_atrib> TOK_ENDPROGRAM "ENDPROGRAM"
%token<token_atrib> TOK_ENDASSOCIATE "ENDASSOCIATE"
%token<token_atrib> TOK_ENDSELECT "ENDSELECT"
%token<token_atrib> TOK_ENDBLOCK "ENDBLOCK"
%token<token_atrib> TOK_ENDSUBMODULE "ENDSUBMODULE"
%token<token_atrib> TOK_ENDBLOCKDATA "ENDBLOCKDATA"
%token<token_atrib> TOK_ENDSUBROUTINE "ENDSUBROUTINE"
%token<token_atrib> TOK_ENDCRITICAL "ENDCRITICAL"
%token<token_atrib> TOK_ENDTYPE "ENDTYPE"
%token<token_atrib> TOK_DOUBLECOMPLEX "DOUBLECOMPLEX"
%token<token_atrib> TOK_GOTO "GOTO"
%token<token_atrib> '-'
%token<token_atrib> TOK_LOGICAL_NOT_EQUIVALENT ".NEQV."
%token<token_atrib> '%'
%token<token_atrib> '['
%token<token_atrib> ']'
%token<token_atrib> TOK_POINTER_ACCESS "=>"
%token<token_atrib> TOK_GREATER_THAN ">"
%token<token_atrib> ','
%token<token_atrib> TOK_EQUAL "=="
%token<token_atrib> '('
%token<token_atrib> '*'
%token<token_atrib> '='
%token<token_atrib> TOK_LOGICAL_AND ".AND."
%token<token_atrib> TOK_LOWER_THAN "<"
%token<token_atrib> TOK_LOGICAL_NOT ".NOT."
%token<token_atrib> ':'
%token<token_atrib> TOK_LOGICAL_EQUIVALENT ".EQV."
%token<token_atrib> TOK_GREATER_OR_EQUAL_THAN ">="
%token<token_atrib> TOK_LOGICAL_OR ".OR".
%token<token_atrib> TOK_LOWER_OR_EQUAL_THAN "<="
%token<token_atrib> TOK_NOT_EQUAL "/="
%token<token_atrib> ')'
%token<token_atrib> TOK_RAISE "**"
%token<token_atrib> '/'
%token<token_atrib> TOK_DOUBLE_SLASH "//"
%token<token_atrib> '+'
%token<token_atrib> TOK_TRUE ".TRUE."
%token<token_atrib> TOK_FALSE ".FALSE."
%token<token_atrib> DECIMAL_LITERAL "decimal literal"
%token<token_atrib> FORMAT_SPEC "format-specifier"
%token<token_atrib> IDENTIFIER "identifier"
%token<token_atrib> EOS "end of statement"
%token<token_atrib> BINARY_LITERAL "binary literal"
%token<token_atrib> OCTAL_LITERAL "octal literal"
%token<token_atrib> REAL_LITERAL "real literal"
%token<token_atrib> CHAR_LITERAL "character literal"
%token<token_atrib> HEX_LITERAL "hexadecimal literal"
%token<token_atrib> USER_DEFINED_OPERATOR "user-defined operator"
%token<token_atrib> TOK_END_NONBLOCK_DO "end-of-nonblock-do"
%token<token_atrib> TOK_SHARED_LABEL "shared-do-label"





%type<ast> subparsing

%token<token_atrib> SUBPARSE_PROGRAM_UNIT "<subparse-program-unit>"
%token<token_atrib> SUBPARSE_EXPRESSION "<subparse-expression>"
%token<token_atrib> SUBPARSE_STATEMENT "<subparse-statement>"





































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





%type<ast2> pragma_custom_construct_range
%type<ast2> pragma_custom_noend_construct_range
%type<ast> pragma_custom_noend_line_construct
%type<ast> pragma_custom_end_construct
%type<ast> pragma_custom_construct_program_unit

%type<ast> pragma_custom_clause
%type<ast> pragma_custom_clause_seq
%type<ast> pragma_custom_clause_opt_seq

// %type<ast> pragma_expression_entity
// %type<ast> pragma_expression_entity_list

%type<ast> pragma_clause_arg_list

%type<text> pragma_clause_arg
%type<text> pragma_clause_arg_item 
%type<text> pragma_clause_arg_text


































































































































































































































































%token<token_atrib> UNKNOWN_PRAGMA

%start program

%%

program : program_unit_seq
{
    *parsed_tree = $1;
}
;
program_unit : main_program
| external_subprogram
| module
| submodule
| block_data
;
external_subprogram : function_subprogram
| subroutine_subprogram
;
internal_subprogram_part : contains_stmt internal_subprogram_seq
{
    $$ = $2;
}
| contains_stmt
{
    $$ = NULL;
}
;
internal_subprogram : function_subprogram
| subroutine_subprogram
;
name : IDENTIFIER
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
| keyword
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
name_not_keyword : IDENTIFIER
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;

unsigned_arithmetic_literal_constant : int_literal_constant
| real_literal_constant
| complex_literal_constant
;
named_constant : name
;
intrinsic_operator : power_op
| mult_op
| add_op
| concat_op
| rel_op
| not_op
| and_op
| or_op
| equiv_op
;
extended_intrinsic_op : intrinsic_operator
;
label : DECIMAL_LITERAL
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
type_param_value : int_expr
| '*'
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
| ':'
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
type_spec : intrinsic_type_spec
| derived_type_spec
;
declaration_type_spec : intrinsic_type_spec
| TOK_TYPE '(' derived_type_spec ')'
{
    $$ = ASTMake1(AST_TYPE_NAME, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_CLASS '(' derived_type_spec ')'
{
    $$ = ASTMake1(AST_CLASS_NAME, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_CLASS '(' '*' ')'
{
    $$ = ASTMake1(AST_CLASS_NAME, 
            ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text), 
            $1.token_file, $1.token_line, NULL);
}
;
intrinsic_type_spec : TOK_INTEGER kind_selector
{
    $$ = ASTMake1(AST_INT_TYPE, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_INTEGER
{
    $$ = ASTMake1(AST_INT_TYPE, NULL, $1.token_file, $1.token_line, NULL);
}
| TOK_REAL kind_selector
{
    $$ = ASTMake1(AST_FLOAT_TYPE, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_REAL
{
    $$ = ASTMake1(AST_FLOAT_TYPE, NULL, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLE TOK_PRECISION
{
    $$ = ASTLeaf(AST_DOUBLE_TYPE, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLEPRECISION
{
    $$ = ASTLeaf(AST_DOUBLE_TYPE, $1.token_file, $1.token_line, NULL);
}
| TOK_COMPLEX kind_selector
{
    AST element_type = ASTMake1(AST_FLOAT_TYPE, $2, $1.token_file, $1.token_line, NULL);
    $$ = ASTMake1(AST_COMPLEX_TYPE, element_type, $1.token_file, $1.token_line, NULL);
}
| TOK_COMPLEX
{
    AST element_type = ASTMake1(AST_FLOAT_TYPE, NULL, $1.token_file, $1.token_line, NULL);
    $$ = ASTMake1(AST_COMPLEX_TYPE, element_type, $1.token_file, $1.token_line, NULL);
}
| TOK_CHARACTER char_selector
{
    $$ = ASTMake1(AST_CHARACTER_TYPE, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_CHARACTER
{
    $$ = ASTMake1(AST_CHARACTER_TYPE, NULL, $1.token_file, $1.token_line, NULL);
}
| TOK_LOGICAL kind_selector
{
    $$ = ASTMake1(AST_BOOL_TYPE, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_LOGICAL
{
    $$ = ASTMake1(AST_BOOL_TYPE, NULL, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLECOMPLEX
{
    AST element_type = ASTLeaf(AST_DOUBLE_TYPE, $1.token_file, $1.token_line, NULL);
    $$ = ASTMake1(AST_COMPLEX_TYPE, element_type, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLE TOK_COMPLEX
{
    AST element_type = ASTLeaf(AST_DOUBLE_TYPE, $1.token_file, $1.token_line, NULL);
    $$ = ASTMake1(AST_COMPLEX_TYPE, element_type, $1.token_file, $1.token_line, NULL);
}
| TOK_INTEGER '*' decimal_literal
{
    $$ = ASTMake1(AST_INT_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_REAL '*' decimal_literal
{
    $$ = ASTMake1(AST_FLOAT_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_COMPLEX '*' decimal_literal
{
    // A COMPLEX * N is equivalent to COMPLEX(KIND=N/2)
    const char* text = ASTText($3);
    int k = atoi(text);
    k /= 2;

    char c[16] = { 0 };
    snprintf(c, 15, "%d", k);
    c[15] = '\0';

    ast_set_text($3, c);

    $$ = ASTMake1(AST_COMPLEX_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLEPRECISION '*' decimal_literal
{
    $$ = ASTMake1(AST_FLOAT_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLE TOK_PRECISION '*' decimal_literal
{
    $$ = ASTMake1(AST_INT_TYPE, $4, $1.token_file, $1.token_line, NULL);
}
| TOK_LOGICAL '*' decimal_literal
{
    $$ = ASTMake1(AST_INT_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_VECTOR '(' vectorial_type ')'
{
    $$ = ASTMake1(AST_VECTOR_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
;
vectorial_type : TOK_PIXEL 
{
    $$ = ASTLeaf(AST_PIXEL_TYPE, $1.token_file, $1.token_line, NULL);
}
| TOK_INTEGER kind_selector
{
    $$ = ASTMake1(AST_INT_TYPE, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_REAL kind_selector
{
    $$ = ASTMake1(AST_FLOAT_TYPE, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_INTEGER '*' decimal_literal
{
    $$ = ASTMake1(AST_INT_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_REAL '*' decimal_literal
{
    $$ = ASTMake1(AST_FLOAT_TYPE, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_INTEGER
{
    $$ = ASTMake1(AST_INT_TYPE, NULL, $1.token_file, $1.token_line, NULL);
}
| TOK_REAL
{
    $$ = ASTMake1(AST_FLOAT_TYPE, NULL, $1.token_file, $1.token_line, NULL);
}
;
kind_selector : '(' TOK_KIND '=' int_constant_expr ')'
{
    $$ = $4;
}
| '(' int_constant_expr ')'
{
    $$ = $2;
}
;
int_literal_constant : boz_literal_constant
| DECIMAL_LITERAL
{
    $$ = ASTLeaf(AST_DECIMAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
decimal_literal : DECIMAL_LITERAL
{
    $$ = ASTLeaf(AST_DECIMAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
real_literal_constant : REAL_LITERAL
{
    $$ = ASTLeaf(AST_FLOATING_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
complex_literal_constant : '(' complex_part ',' complex_part ')'
{
    $$ = ASTMake2(AST_COMPLEX_LITERAL, $2, $4, $1.token_file, $1.token_line, NULL);
}
;
sign : '+'
{
    $$ = AST_PLUS;
}
| '-'
{
    $$ = AST_NEG;
}
;
complex_part : int_literal_constant
| real_literal_constant
| sign int_literal_constant
{
    $$ = ASTMake1($1, $2, ASTFileName($2), ASTLine($2), NULL);
}
| sign real_literal_constant
{
    $$ = ASTMake1($1, $2, ASTFileName($2), ASTLine($2), NULL);
}
| named_constant
;
char_selector : length_selector
| '(' TOK_LEN '=' type_param_value ',' TOK_KIND '=' int_constant_expr ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $4, $8, $1.token_file, $1.token_line, NULL);
}
| '(' type_param_value ',' TOK_KIND '=' int_constant_expr ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $2, $6, $1.token_file, $1.token_line, NULL);
}
| '(' type_param_value ',' int_constant_expr ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $2, $4, $1.token_file, $1.token_line, NULL);
}
| '(' TOK_KIND '=' int_constant_expr ',' TOK_LEN '=' type_param_value ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $8, $4, $1.token_file, $1.token_line, NULL);
}
| '(' TOK_KIND '=' int_constant_expr ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, NULL, $4, $1.token_file, $1.token_line, NULL);
}
;
length_selector : '(' TOK_LEN '=' type_param_value ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $4, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' type_param_value ')'
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| '*' char_length ','
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| '*' char_length
{
    $$ = ASTMake2(AST_CHAR_SELECTOR, $2, NULL, $1.token_file, $1.token_line, NULL);
}
;
char_length : '(' type_param_value ')'
{
    $$ = $2;
}
| int_literal_constant
;
char_literal_constant : CHAR_LITERAL
{
    $$ = ASTLeaf(AST_STRING_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
logical_literal_constant : TOK_TRUE
{
    $$ = ASTLeaf(AST_BOOLEAN_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_FALSE
{
    $$ = ASTLeaf(AST_BOOLEAN_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;

derived_type_def : derived_type_stmt derived_type_body end_type_stmt
{
    $$ = ASTMake3(AST_DERIVED_TYPE_DEF, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

derived_type_body : type_param_def_stmt_seq private_or_sequence_seq component_part type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, $2, $3, $4, ASTFileName($1), ASTLine($1), NULL);
}
| private_or_sequence_seq component_part type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq component_part type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, NULL, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq private_or_sequence_seq type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, $2, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq private_or_sequence_seq component_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, $2, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq private_or_sequence_seq 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, $2, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, NULL, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq component_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, NULL, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_def_stmt_seq 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, $1, NULL, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| component_part type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| private_or_sequence_seq type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
| private_or_sequence_seq component_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| private_or_sequence_seq 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_bound_procedure_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, NULL, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
| component_part 
{
    $$ = ASTMake4(AST_DERIVED_TYPE_DEF_BODY, NULL, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| /* empty */
{
    $$ = NULL;
}
;

derived_type_stmt : labeldef TOK_TYPE ',' type_attr_spec_list ':' ':' name '(' type_param_name_list ')' eos
{
    $$ = ASTMake4Label(AST_DERIVED_TYPE_STATEMENT, $1, $4, $7, $9, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_TYPE name '(' type_param_name_list ')' eos
{
    $$ = ASTMake4Label(AST_DERIVED_TYPE_STATEMENT, $1, NULL, $3, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_TYPE ':' ':' name '(' type_param_name_list ')' eos
{
    $$ = ASTMake4Label(AST_DERIVED_TYPE_STATEMENT, $1, NULL, $5, $7, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_TYPE ',' type_attr_spec_list ':' ':' name eos
{
    $$ = ASTMake4Label(AST_DERIVED_TYPE_STATEMENT, $1, $4, $7, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_TYPE ':' ':' name eos
{
    $$ = ASTMake4Label(AST_DERIVED_TYPE_STATEMENT, $1, NULL, $5, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_TYPE name eos
{
    $$ = ASTMake4Label(AST_DERIVED_TYPE_STATEMENT, $1, NULL, $3, NULL, $2.token_file, $2.token_line, NULL);
}
;
type_attr_spec : TOK_ABSTRACT
{
    $$ = ASTLeaf(AST_ABSTRACT, $1.token_file, $1.token_line, $1.token_text);
}
| access_spec
| language_binding_spec
| TOK_EXTENDS '(' name ')'
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $2.token_text);
}
;
private_or_sequence : private_stmt
| sequence_stmt
;
end_type_stmt : labeldef TOK_END TOK_TYPE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_TYPE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDTYPE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDTYPE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
sequence_stmt : labeldef TOK_SEQUENCE eos
{
    $$ = ASTMake1Label(AST_SEQUENCE_STATEMENT, $1, $2.token_file, $2.token_line, NULL);
}
;
type_param_def_stmt : labeldef TOK_INTEGER kind_selector ',' type_param_attr_spec ':' ':' type_param_decl_list eos
{
    $$ = ASTMake4Label(AST_TYPE_PARAMETER_DEF_STATEMENT, $1, $3, $5, $8, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_INTEGER ',' type_param_attr_spec ':' ':' type_param_decl_list eos
{
    $$ = ASTMake4Label(AST_TYPE_PARAMETER_DEF_STATEMENT, $1, NULL, $4, $7, $2.token_file, $2.token_line, NULL);
}
;
type_param_decl : name '=' int_constant_expr
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
type_param_attr_spec : TOK_KIND
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, strtoupper($1.token_text));
}
| TOK_LEN
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, strtoupper($1.token_text));
}
;
component_part : component_def_stmts_seq
;
component_def_stmts : data_component_def_stmt
| proc_component_def_stmt
;
data_component_def_stmt : labeldef declaration_type_spec ',' component_attr_spec_list ':' ':' component_decl_list eos
{
    $$ = ASTMake4Label(AST_DATA_COMPONENT_DEF_STATEMENT, $1, $2, $4, $7, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef declaration_type_spec component_decl_list eos
{
    $$ = ASTMake4Label(AST_DATA_COMPONENT_DEF_STATEMENT, $1, $2, NULL, $3, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef declaration_type_spec ':' ':' component_decl_list eos
{
    $$ = ASTMake4Label(AST_DATA_COMPONENT_DEF_STATEMENT, $1, $2, NULL, $5, ASTFileName($2), ASTLine($2), NULL);
}
;
component_attr_spec : access_spec
| TOK_ALLOCATABLE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_CODIMENSION '[' coarray_spec ']'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_CONTIGUOUS
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DIMENSION '(' array_spec ')'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POINTER
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;

component_decl : entity_decl
;

proc_component_def_stmt : labeldef TOK_PROCEDURE '(' proc_interface ')' ',' proc_component_attr_spec_list ':' ':' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROC_COMPONENT_DEF_STATEMENT, $1, $4, $7, $10, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_PROCEDURE '(' ')' ',' proc_component_attr_spec_list ':' ':' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROC_COMPONENT_DEF_STATEMENT, $1, NULL, $6, $9, $2.token_file, $2.token_line, NULL);
}
;
proc_component_attr_spec : TOK_POINTER
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, NULL);
}
| TOK_PASS '(' name ')'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_PASS
{
    $$ = ASTMake1(AST_ATTR_SPEC, NULL, $1.token_file, $1.token_line, NULL);
}
| TOK_NOPASS
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, NULL);
}
| access_spec
;
type_bound_procedure_part : contains_stmt private_stmt type_bound_proc_binding_seq
{
    $$ = ASTMake2(AST_TYPE_BOUND_PROCEDURE_PART, $2, $3, ASTFileName($2), ASTLine($2), NULL);
}
| contains_stmt type_bound_proc_binding_seq
{
    $$ = ASTMake2(AST_TYPE_BOUND_PROCEDURE_PART, NULL, $2, ASTFileName($2), ASTLine($2), NULL);
}
| contains_stmt private_stmt
{
    $$ = ASTMake2(AST_TYPE_BOUND_PROCEDURE_PART, NULL, $2, ASTFileName($2), ASTLine($2), NULL);
}
| contains_stmt
{
    // FIXME
    $$ = ASTMake2(AST_TYPE_BOUND_PROCEDURE_PART, NULL, NULL, NULL, 0, NULL);
}
;
private_stmt : labeldef TOK_PRIVATE eos
{
    AST priv_spec = ASTLeaf(AST_ATTR_SPEC, $2.token_file, $2.token_line, $2.token_text);
    $$ = ASTMake3Label(AST_ACCESS_STATEMENT, $1, priv_spec, NULL, ASTFileName(priv_spec), ASTLine(priv_spec), NULL);
}
;
type_bound_proc_binding : type_bound_procedure_stmt
| type_bound_generic_stmt
| final_procedure_stmt
;
type_bound_procedure_stmt : labeldef TOK_PROCEDURE ',' binding_attr_list ':' ':' type_bound_proc_decl_list eos
{
    $$ = ASTMake4Label(AST_TYPE_BOUND_PROCEDURE_STATEMENT, $1, NULL, $4, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE type_bound_proc_decl_list eos
{
    $$ = ASTMake4Label(AST_TYPE_BOUND_PROCEDURE_STATEMENT, $1, NULL, NULL, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE ':' ':' type_bound_proc_decl_list eos
{
    $$ = ASTMake4Label(AST_TYPE_BOUND_PROCEDURE_STATEMENT, $1, NULL, NULL, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE '(' name ')' ',' binding_attr_list ':' ':' binding_name_list eos
{
    $$ = ASTMake4Label(AST_TYPE_BOUND_PROCEDURE_STATEMENT, $1, $4, $7, $10, $2.token_file, $2.token_line, $2.token_text);
}
;
type_bound_proc_decl : name TOK_POINTER_ACCESS name
{
    $$ = ASTMake2(AST_RENAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
type_bound_generic_stmt : labeldef TOK_GENERIC ',' access_spec ':' ':' generic_spec TOK_POINTER_ACCESS binding_name_list eos
{
    $$ = ASTMake4Label(AST_TYPE_BOUND_GENERIC_PROCEDURE, $1, $4, $7, $9, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_GENERIC ':' ':' generic_spec TOK_POINTER_ACCESS binding_name_list eos
{
    $$ = ASTMake4Label(AST_TYPE_BOUND_GENERIC_PROCEDURE, $1, NULL, $5, $7, $2.token_file, $2.token_line, $2.token_text);
}
;
binding_attr : TOK_PASS '(' name ')'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PASS
{
    $$ = ASTMake1(AST_ATTR_SPEC, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NOPASS
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NON_OVERRIDABLE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DEFERRED
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| access_spec
;
final_procedure_stmt : labeldef TOK_FINAL ':' ':' final_subroutine_name_list eos
{
    $$ = ASTMake2Label(AST_FINAL_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_FINAL final_subroutine_name_list eos
{
    $$ = ASTMake2Label(AST_FINAL_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
derived_type_spec : name_not_keyword '(' type_param_spec_list ')'
{
    $$ = ASTMake2(AST_DERIVED_TYPE_NAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name_not_keyword
{
    $$ = ASTMake2(AST_DERIVED_TYPE_NAME, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
type_param_spec : name '=' type_param_value
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| type_param_value
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
;
structure_constructor : derived_type_spec '(' component_spec_list ')'
{
    $$ = ASTMake2(AST_DERIVED_TYPE_CONSTRUCTOR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| derived_type_spec '(' ')'
{
    $$ = ASTMake2(AST_DERIVED_TYPE_CONSTRUCTOR, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
component_spec : name '=' component_data_source
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| component_data_source
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
;
component_data_source : expr
;
enum_def : enum_def_stmt enumerator_def_stmt_seq end_enum_stmt
{
    $$ = ASTMake3(AST_ENUM_DEF, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
enum_def_stmt : labeldef TOK_ENUM ',' TOK_BIND '(' TOK_C ')' eos
{
    // Keep the original case
    char c[100];
    snprintf(c, 99, "%s, %s(%s)", $2.token_text, $4.token_text, $6.token_text);
    c[99] = '\0';

    $$ = ASTMake1Label(AST_ENUM_DEF_STATEMENT, $1, $2.token_file, $2.token_line, c);
}
;
enumerator_def_stmt : labeldef TOK_ENUMERATOR ':' ':' enumerator_list eos
{
    $$ = ASTMake2Label(AST_ENUMERATOR_DEF, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENUMERATOR enumerator_list eos
{
    $$ = ASTMake2Label(AST_ENUMERATOR_DEF, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
enumerator : named_constant '=' int_constant_expr
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| named_constant
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
end_enum_stmt : labeldef TOK_END TOK_ENUM eos
{
    $$ = ASTMake1Label(AST_END_STATEMENT, $1, $2.token_file, $2.token_line, $3.token_text);
}
;
boz_literal_constant : binary_constant
| octal_constant
| hex_constant
;
binary_constant : BINARY_LITERAL
{
    $$ = ASTLeaf(AST_BINARY_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
octal_constant : OCTAL_LITERAL
{
    $$ = ASTLeaf(AST_OCTAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
hex_constant : HEX_LITERAL
{
    $$ = ASTLeaf(AST_HEXADECIMAL_LITERAL, $1.token_file, $1.token_line, $1.token_text);
}
;
array_constructor : '(' '/' ac_spec '/' ')'
{
    $$ = ASTMake1(AST_ARRAY_CONSTRUCTOR, $3, $1.token_file, $1.token_line, $1.token_text);
}
| '[' ac_spec ']'
{
    $$ = ASTMake1(AST_ARRAY_CONSTRUCTOR, $2, $1.token_file, $1.token_line, $1.token_text);
}
;
ac_spec : type_spec ':' ':'
{
    $$ = ASTMake2(AST_ARRAY_CONSTRUCTOR_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| type_spec ':' ':' ac_value_list
{
    $$ = ASTMake2(AST_ARRAY_CONSTRUCTOR_SPEC, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
| ac_value_list
{
    $$ = ASTMake2(AST_ARRAY_CONSTRUCTOR_SPEC, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
;
ac_value : expr
| ac_implied_do
;
ac_implied_do : '(' ac_value_list ',' ac_implied_do_control ')'
{
    $$ = ASTMake2(AST_IMPLIED_DO, $2, $4, $1.token_file, $1.token_line, NULL);
}
;
ac_implied_do_control : ac_do_variable '=' int_expr ',' int_expr comma_int_expr_opt
{
    $$ = ASTMake4(AST_IMPLIED_DO_CONTROL, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
;
ac_do_variable : do_variable
;
type_declaration_stmt : labeldef declaration_type_spec ',' attr_spec_list ':' ':' entity_decl_list eos
{
    $$ = ASTMake4Label(AST_DECLARATION_STATEMENT, $1, $2, $4, $7, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef declaration_type_spec entity_decl_list eos
{
    $$ = ASTMake4Label(AST_DECLARATION_STATEMENT, $1, $2, NULL, $3, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef declaration_type_spec ':' ':' entity_decl_list eos
{
    $$ = ASTMake4Label(AST_DECLARATION_STATEMENT, $1, $2, NULL, $5, ASTFileName($2), ASTLine($2), NULL);
}
;
attr_spec : access_spec
| TOK_ALLOCATABLE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ASYNCHRONOUS
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_CODIMENSION '[' coarray_spec ']'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_CONTIGUOUS
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DIMENSION '(' array_spec ')'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_EXTERNAL
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_INTENT '(' intent_spec ')'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_INTRINSIC
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| language_binding_spec
| TOK_OPTIONAL
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PARAMETER
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POINTER
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PROTECTED
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SAVE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_TARGET
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_VALUE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_VOLATILE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;
entity_decl : name entity_decl_specs
{
    $$ = ASTMake2(AST_DECLARATION, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
entity_decl_specs : '(' array_spec ')' '[' coarray_spec ']' '*' char_length initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, $5, $8, $9, $1.token_file, $1.token_line, NULL);
}
| '[' coarray_spec ']' '*' char_length initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, $2, $5, $6, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')' '*' char_length initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, NULL, $5, $6, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')' '[' coarray_spec ']' initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, $5, NULL, $7, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')' '[' coarray_spec ']' '*' char_length
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, $5, $8, NULL, $1.token_file, $1.token_line, NULL);
}
| '*' char_length
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, NULL, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')' '[' coarray_spec ']'
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, $5, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')' initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, NULL, NULL, $4, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')' '*' char_length
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, NULL, $5, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' array_spec ')'
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, $2, NULL, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| '*' char_length initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, NULL, $2, $3, $1.token_file, $1.token_line, NULL);
}
| '[' coarray_spec ']' initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, $2, NULL, $4, $1.token_file, $1.token_line, NULL);
}
| '[' coarray_spec ']' '*' char_length
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, $2, $5, NULL, $1.token_file, $1.token_line, NULL);
}
| '[' coarray_spec ']'
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, $2, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
| initialization
{
    $$ = ASTMake4(AST_DECLARATION_SPECS, NULL, NULL, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
| /* empty */
{
    $$ = NULL;
}
;
initialization : '=' constant_expr
{
    $$ = $2;
}
| TOK_POINTER_ACCESS constant_expr
{
    $$ = ASTMake1(AST_POINTER_INITIALIZATION, $2, $1.token_file, $1.token_line, NULL);
}
;
access_spec : TOK_PUBLIC
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PRIVATE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;
proc_language_binding_spec : language_binding_spec
;
language_binding_spec : TOK_BIND '(' TOK_C ',' TOK_NAME '=' default_char_constant_expr ')'
{
    $$ = ASTMake1(AST_BIND_C_SPEC, $7, $1.token_file, $1.token_line, "bind");
}
| TOK_BIND '(' TOK_C ')'
{
    $$ = ASTMake1(AST_BIND_C_SPEC, NULL, $1.token_file, $1.token_line, "bind");
}
;
coarray_spec : array_spec
;
array_spec : array_spec_list
;
array_spec_list : array_spec_list ',' array_spec_item
{
    $$ = ast_list($1, $3);
}
| array_spec_item
{
    $$ = ast_list_leaf($1);
}
array_spec_item : lower_bound ':' upper_bound
{
    $$ = ASTMake2(AST_ARRAY_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| upper_bound
{
    $$ = ASTMake2(AST_ARRAY_SPEC, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
| lower_bound ':'
{
    $$ = ASTMake2(AST_ARRAY_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| lower_bound ':' '*'
{
    AST symbol = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);
    $$ = ASTMake2(AST_ARRAY_SPEC, $1, symbol, ASTFileName($1), ASTLine($1), NULL);
}
| ':'
{
    $$ = ASTMake2(AST_ARRAY_SPEC, NULL, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| '*'
{
    AST symbol = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
    $$ = ASTMake2(AST_ARRAY_SPEC, NULL, symbol, $1.token_file, $1.token_line, $1.token_text);
}
;
lower_bound : specification_expr
;
upper_bound : specification_expr
;
intent_spec : TOK_IN
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_OUT
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_INOUT
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;
access_stmt : labeldef access_spec ':' ':' access_id_list eos
{
    $$ = ASTMake3Label(AST_ACCESS_STATEMENT, $1, $2, $5, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef access_spec access_id_list eos
{
    $$ = ASTMake3Label(AST_ACCESS_STATEMENT, $1, $2, $3, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef access_spec eos
{
    $$ = ASTMake3Label(AST_ACCESS_STATEMENT, $1, $2, NULL, ASTFileName($2), ASTLine($2), NULL);
}
;
access_id : generic_spec
;
allocatable_stmt : labeldef TOK_ALLOCATABLE ':' ':' allocatable_decl_list eos
{
    $$ = ASTMake2Label(AST_ALLOCATABLE_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_ALLOCATABLE allocatable_decl_list eos
{
    $$ = ASTMake2Label(AST_ALLOCATABLE_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
allocatable_decl : name '(' array_spec ')' '[' coarray_spec ']'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, $6, ASTFileName($1), ASTLine($1), NULL);
}
| name '[' coarray_spec ']'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name '(' array_spec ')'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
asynchronous_stmt : labeldef TOK_ASYNCHRONOUS ':' ':' object_name_list eos
{
    $$ = ASTMake2Label(AST_ASYNCHRONOUS_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_ASYNCHRONOUS object_name_list eos
{
    $$ = ASTMake2Label(AST_ASYNCHRONOUS_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
bind_stmt : labeldef language_binding_spec ':' ':' bind_entity_list eos
{
    $$ = ASTMake3Label(AST_BIND_STATEMENT, $1, $2, $5, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef language_binding_spec bind_entity_list eos
{
    $$ = ASTMake3Label(AST_BIND_STATEMENT, $1, $2, $3, ASTFileName($2), ASTLine($2), NULL);
}
;
bind_entity : name
| common_name
;
common_name : '/' name '/'
{
    $$ = ASTMake1(AST_COMMON_NAME, $2, $1.token_file, $1.token_line, NULL);
}
;
codimension_stmt : labeldef TOK_CODIMENSION ':' ':' codimension_decl_list eos
{
    $$ = ASTMake2Label(AST_CODIMENSION_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_CODIMENSION codimension_decl_list eos
{
    $$ = ASTMake2Label(AST_CODIMENSION_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
codimension_decl : name '[' coarray_spec ']'
{
    $$ = ASTMake2(AST_CODIMENSION_DECL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
data_stmt : labeldef TOK_DATA data_stmt_set_list eos
{
    $$ = ASTMake2Label(AST_DATA_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
data_stmt_set : data_stmt_object_list '/' data_stmt_value_list '/'
{
    $$ = ASTMake2(AST_DATA_STATEMENT_SET, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
data_stmt_object : variable
| data_implied_do
;
data_implied_do : '(' data_i_do_object_list ',' data_i_do_variable '=' int_constant_expr ',' int_constant_expr comma_int_expr_opt ')'
{
    AST control = ASTMake4(AST_IMPLIED_DO_CONTROL, $4, $6, $8, $9, ASTFileName($4), ASTLine($4), NULL);

    $$ = ASTMake2(AST_IMPLIED_DO, $2, control, $1.token_file, $1.token_line, NULL);
}
;
data_i_do_object : data_ref
| data_implied_do
;
data_i_do_variable : do_variable
;
data_stmt_value : mult_operand
| add_operand '*' mult_operand 
{
    $$ = ASTMake2(AST_MULT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
dimension_stmt : labeldef TOK_DIMENSION ':' ':' array_name_dim_spec_list eos
{
    $$ = ASTMake2Label(AST_DIMENSION_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_DIMENSION array_name_dim_spec_list eos
{
    $$ = ASTMake2Label(AST_DIMENSION_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
array_name_dim_spec : name '(' array_spec ')'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
intent_stmt : labeldef TOK_INTENT '(' intent_spec ')' ':' ':' dummy_arg_name_list eos
{
    AST attr_spec = ASTMake1(AST_ATTR_SPEC, $4, $2.token_file, $2.token_line, $2.token_text);
    $$ = ASTMake3Label(AST_INTENT_STATEMENT, $1, attr_spec, $8, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_INTENT '(' intent_spec ')' dummy_arg_name_list eos
{
    AST attr_spec = ASTMake1(AST_ATTR_SPEC, $4, $2.token_file, $2.token_line, $2.token_text);
    $$ = ASTMake3Label(AST_INTENT_STATEMENT, $1, attr_spec, $6, $2.token_file, $2.token_line, $2.token_text);
}
;
optional_stmt : labeldef TOK_OPTIONAL ':' ':' dummy_arg_name_list eos
{
    $$ = ASTMake2Label(AST_OPTIONAL_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_OPTIONAL dummy_arg_name_list eos
{
    $$ = ASTMake2Label(AST_OPTIONAL_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
parameter_stmt : labeldef TOK_PARAMETER '(' named_constant_def_list ')' eos
{
    $$ = ASTMake2Label(AST_PARAMETER_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
named_constant_def : named_constant '=' constant_expr
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
pointer_stmt : labeldef TOK_POINTER ':' ':' pointer_decl_list eos
{
    $$ = ASTMake2Label(AST_POINTER_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_POINTER pointer_decl_list eos
{
    $$ = ASTMake2Label(AST_POINTER_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
pointer_decl : name '(' array_spec ')'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
protected_stmt : labeldef TOK_PROTECTED ':' ':' entity_name_list eos
{
    $$ = ASTMake2Label(AST_PROTECTED_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_PROTECTED entity_name_list eos
{
    $$ = ASTMake2Label(AST_PROTECTED_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
save_stmt : labeldef TOK_SAVE ':' ':' saved_entity_list eos
{
    $$ = ASTMake2Label(AST_SAVE_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_SAVE eos
{
    $$ = ASTMake2Label(AST_SAVE_STATEMENT, $1, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_SAVE saved_entity_list eos
{
    $$ = ASTMake2Label(AST_SAVE_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
saved_entity : name
| common_name
;
target_stmt : labeldef TOK_TARGET ':' ':' target_decl_list eos
{
    $$ = ASTMake2Label(AST_TARGET_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_TARGET target_decl_list eos
{
    $$ = ASTMake2Label(AST_TARGET_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
target_decl : name '(' array_spec ')' '[' coarray_spec ']'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, $6, ASTFileName($1), ASTLine($1), NULL);
}
| name '[' coarray_spec ']'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name '(' array_spec ')'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
value_stmt : labeldef TOK_VALUE ':' ':' dummy_arg_name_list eos
{
    $$ = ASTMake2Label(AST_VALUE_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_VALUE dummy_arg_name_list eos
{
    $$ = ASTMake2Label(AST_VALUE_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
volatile_stmt : labeldef TOK_VOLATILE ':' ':' object_name_list eos
{
    $$ = ASTMake2Label(AST_VOLATILE_STATEMENT, $1, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_VOLATILE object_name_list eos
{
    $$ = ASTMake2Label(AST_VOLATILE_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
implicit_stmt : labeldef TOK_IMPLICIT implicit_spec_list eos
{
    $$ = ASTMake2Label(AST_IMPLICIT_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_IMPLICIT TOK_NONE eos
{
    $$ = ASTMake2Label(AST_IMPLICIT_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
implicit_spec : declaration_type_spec '(' letter_spec_list ')'
{
    $$ = ASTMake2(AST_IMPLICIT_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
letter_spec : name '-' name
{
    $$ = ASTMake2(AST_LETTER_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name
{
    $$ = ASTMake2(AST_LETTER_SPEC, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
namelist_stmt : labeldef TOK_NAMELIST namelist_item_list eos
{
    $$ = ASTMake2Label(AST_NAMELIST_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
namelist_item : common_name namelist_group_object_list
{
    $$ = ASTMake2(AST_NAMELIST_ITEM, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
namelist_group_object : name
;
equivalence_stmt : labeldef TOK_EQUIVALENCE equivalence_set_list eos
{
    $$ = ASTMake2Label(AST_EQUIVALENCE_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
equivalence_set : '(' equivalence_object ',' equivalence_object_list ')'
{
    $$ = ASTMake2(AST_EQUIVALENCE_SET, $2, $4, $1.token_file, $1.token_line, NULL);
}
;
equivalence_object : data_ref
;
common_stmt : labeldef TOK_COMMON common_block_item_list eos
{
    $$ = ASTMake2Label(AST_COMMON_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
common_block_item_list : common_block_item
{
  $$ = ASTListLeaf($1);
}
| common_block_object_list
{
  AST common_block = ASTMake2(AST_COMMON_BLOCK_ITEM, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
  $$ = ASTListLeaf(common_block);
}
| common_block_item_list ',' common_block_item
{
  $$ = ASTList($1, $3);
}
;
common_block_item : '/' name '/' common_block_object_list
{
    $$ = ASTMake2(AST_COMMON_BLOCK_ITEM, $2, $4, $1.token_file, $1.token_line, NULL);
}
| '/' '/' common_block_object_list
{
    $$ = ASTMake2(AST_COMMON_BLOCK_ITEM, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_DOUBLE_SLASH common_block_object_list
{
    $$ = ASTMake2(AST_COMMON_BLOCK_ITEM, NULL, $2, $1.token_file, $1.token_line, NULL);
}
;
common_block_object : name '(' array_spec ')'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
variable : data_ref
;
logical_variable : variable
;
default_char_variable : variable
;
int_variable : variable
;
data_ref : data_ref_no_array
| data_ref '(' section_subscript_list ')'
{
    $$ = ASTMake2(AST_ARRAY_SUBSCRIPT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| data_ref '(' section_subscript_list ')' image_selector
{
    AST array_ref = ASTMake2(AST_ARRAY_SUBSCRIPT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
    $$ = ASTMake2(AST_IMAGE_REF, array_ref, $5, ASTFileName($1), ASTLine($1), NULL);
}
;
data_ref_no_array : name
| name image_selector
{
    $$ = ASTMake2(AST_IMAGE_REF, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| data_ref '%' name
{
    $$ = ASTMake2(AST_CLASS_MEMBER_ACCESS, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
subscript : int_expr
;
section_subscript : subscript
| subscript_triplet
;
subscript_triplet : subscript ':' subscript ':' stride
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, $1, $3, $5, ASTFileName($1), ASTLine($1), NULL);
}
| ':' subscript ':' stride
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, NULL, $2, $4, $1.token_file, $1.token_line, NULL);
}
| subscript ':' ':' stride
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, $1, NULL, $4, ASTFileName($1), ASTLine($1), NULL);
}
| subscript ':' subscript
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, $1, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| subscript ':'
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| ':' ':' stride
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, NULL, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| ':' subscript
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, NULL, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| ':'
{
    $$ = ASTMake3(AST_SUBSCRIPT_TRIPLET, NULL, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
;
stride : int_expr
;
image_selector : '[' cosubscript_list ']'
{
    $$ = $2;
}
;
cosubscript : int_expr
;
allocate_stmt : labeldef TOK_ALLOCATE '(' type_spec ':' ':' allocation_list ',' alloc_opt_list ')' eos
{
    $$ = ASTMake4Label(AST_ALLOCATE_STATEMENT, $1, $4, $7, $9, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_ALLOCATE '(' allocation_list ',' alloc_opt_list ')' eos
{
    $$ = ASTMake4Label(AST_ALLOCATE_STATEMENT, $1, NULL, $4, $6, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_ALLOCATE '(' type_spec ':' ':' allocation_list ')' eos
{
    $$ = ASTMake4Label(AST_ALLOCATE_STATEMENT, $1, $4, $7, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_ALLOCATE '(' allocation_list ')' eos
{
    $$ = ASTMake4Label(AST_ALLOCATE_STATEMENT, $1, NULL, $4, NULL, $2.token_file, $2.token_line, NULL);
}
;
alloc_opt : TOK_ERRMSG '=' errmsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_MOLD '=' source_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SOURCE '=' source_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_STAT '=' stat_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
stat_variable : int_variable
;
errmsg_variable : default_char_variable
;
source_expr : expr
;
allocation : allocate_object
;
allocate_object : allocate_object '[' allocate_coarray_spec ']'
{
    $$ = ASTMake3(AST_DIMENSION_DECL, $1, NULL, $3, ASTFileName($1), ASTLine($1), NULL);
}
| data_ref
;
allocate_coarray_spec : array_spec
;
nullify_stmt : labeldef TOK_NULLIFY '(' pointer_object_list ')' eos
{
    $$ = ASTMake2Label(AST_NULLIFY_STATEMENT, $1, $4, $2.token_file, $2.token_line, NULL);
}
;
pointer_object : data_ref
;
deallocate_stmt : labeldef TOK_DEALLOCATE '(' allocate_object_list ',' dealloc_opt_list ')' eos
{
    $$ = ASTMake3Label(AST_DEALLOCATE_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_DEALLOCATE '(' allocate_object_list ')' eos
{
    $$ = ASTMake3Label(AST_DEALLOCATE_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, NULL);
}
;
dealloc_opt : TOK_STAT '=' stat_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERRMSG '=' errmsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
primary : unsigned_arithmetic_literal_constant
| logical_literal_constant
| char_literal_constant
| array_constructor 
| structure_constructor %merge<ambig_fun_array_ctor>
| function_reference %merge<ambig_fun_array_ctor>
| data_ref %merge<ambig_fun_array_ctor>
| '(' expr ')'
{
    $$ = ASTMake1(AST_PARENTHESIZED_EXPRESSION, $2, $1.token_file, $1.token_line, NULL);
}
;
level_0_expr : '+' primary
{
    $$ = ASTMake1(AST_PLUS, $2, $1.token_file, $1.token_line, NULL);
}
| '-' primary
{
    $$ = ASTMake1(AST_NEG, $2, $1.token_file, $1.token_line, NULL);
}
| primary
;
level_1_expr : user_defined_op level_0_expr
{
    $$ = ASTMake2(AST_USER_DEFINED_UNARY_OP, 
            ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text),
            ASTMake2(AST_NAMED_PAIR_SPEC, NULL, $2, ASTFileName($2), ASTLine($2), NULL),
            $1.token_file, $1.token_line, NULL);
}
| level_0_expr
;
user_defined_op : USER_DEFINED_OPERATOR
;
mult_operand : level_1_expr power_op mult_operand
{
    $$ = ASTMake2(AST_POWER, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_1_expr
;
add_operand : add_operand '*' mult_operand 
{
    $$ = ASTMake2(AST_MULT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| add_operand '/' mult_operand 
{
    $$ = ASTMake2(AST_DIV, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| mult_operand 
;
level_2_expr : level_2_expr '+' add_operand
{
    $$ = ASTMake2(AST_ADD, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_2_expr '-' add_operand
{
    $$ = ASTMake2(AST_MINUS, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| add_operand
;
power_op : TOK_RAISE
;
mult_op : '*'
| '/'
;
add_op : '+'
| '-'
;
level_3_expr : level_3_expr concat_op level_2_expr
{
    $$ = ASTMake2(AST_CONCAT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_2_expr
;
concat_op : TOK_DOUBLE_SLASH
;
level_4_expr : level_3_expr TOK_EQUAL level_3_expr
{
    $$ = ASTMake2(AST_EQUAL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_3_expr TOK_NOT_EQUAL level_3_expr
{
    $$ = ASTMake2(AST_DIFFERENT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_3_expr TOK_LOWER_THAN level_3_expr
{
    $$ = ASTMake2(AST_LOWER_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_3_expr TOK_LOWER_OR_EQUAL_THAN level_3_expr
{
    $$ = ASTMake2(AST_LOWER_OR_EQUAL_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_3_expr TOK_GREATER_THAN level_3_expr
{
    $$ = ASTMake2(AST_GREATER_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_3_expr TOK_GREATER_OR_EQUAL_THAN level_3_expr
{
    $$ = ASTMake2(AST_GREATER_OR_EQUAL_THAN, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_3_expr
;
rel_op : TOK_EQUAL
| TOK_NOT_EQUAL
| TOK_LOWER_THAN
| TOK_LOWER_OR_EQUAL_THAN
| TOK_GREATER_THAN
| TOK_GREATER_OR_EQUAL_THAN
;
and_operand : not_op level_4_expr
{
    $$ = ASTMake1(AST_NOT, $2, $1.token_file, $1.token_line, NULL);
}
| level_4_expr
;
or_operand : or_operand and_op and_operand
{
    $$ = ASTMake2(AST_LOGICAL_AND, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| and_operand
;
equiv_operand : equiv_operand or_op or_operand
{
    $$ = ASTMake2(AST_LOGICAL_OR, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| or_operand
;
level_5_expr : level_5_expr TOK_LOGICAL_EQUIVALENT equiv_operand
{
    $$ = ASTMake2(AST_LOGICAL_EQUAL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| level_5_expr TOK_LOGICAL_NOT_EQUIVALENT equiv_operand
{
    $$ = ASTMake2(AST_LOGICAL_DIFFERENT, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| equiv_operand
;
not_op : TOK_LOGICAL_NOT
;
and_op : TOK_LOGICAL_AND
;
or_op : TOK_LOGICAL_OR
;
equiv_op : TOK_LOGICAL_EQUIVALENT
| TOK_LOGICAL_NOT_EQUIVALENT
;
expr : expr user_defined_op level_5_expr
{
    $$ = ASTMake3(AST_USER_DEFINED_BINARY_OP, 
            ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text),
            ASTMake2(AST_NAMED_PAIR_SPEC, NULL, $1, ASTFileName($1), ASTLine($1), NULL),
            ASTMake2(AST_NAMED_PAIR_SPEC, NULL, $3, ASTFileName($3), ASTLine($3), NULL),
            ASTFileName($1), ASTLine($1), NULL);
}
| level_5_expr
;
logical_expr : expr
;
default_char_expr : expr
;
int_expr : expr
;
numeric_expr : expr
;
specification_expr : int_expr
;
constant_expr : expr
;
default_char_constant_expr : default_char_expr
;
int_constant_expr : int_expr
;
assignment_stmt : labeldef data_ref '=' expr eos
{
    AST assig = ASTMake2(AST_ASSIGNMENT, $2, $4, ASTFileName($2), ASTLine($2), NULL);
    $$ = ASTMake2Label(AST_EXPRESSION_STATEMENT, $1, assig, ASTFileName(assig), ASTLine(assig), NULL);
}
;
pointer_assignment_stmt : labeldef proc_pointer_object TOK_POINTER_ACCESS proc_target eos
{
    AST assig = ASTMake2(AST_PTR_ASSIGNMENT, $2, $4, ASTFileName($2), ASTLine($2), NULL);
    $$ = ASTMake2Label(AST_EXPRESSION_STATEMENT, $1, assig, ASTFileName(assig), ASTLine(assig), NULL);
}
;
proc_pointer_object : data_ref
;
proc_target : expr
;
where_stmt : labeldef TOK_WHERE '(' mask_expr ')' where_assignment_stmt
{
    $$ = ASTMake3Label(AST_WHERE_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, NULL);
}
;
where_construct : where_construct_stmt where_construct_body end_where_stmt
{
    $$ = ASTMake3(AST_WHERE_CONSTRUCT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
where_construct_body : where_body_construct_seq mask_elsewhere_part_seq elsewhere_stmt where_body_construct_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, $1, $2, $3, $4, ASTFileName($1), ASTLine($1), NULL);
}
| mask_elsewhere_part_seq elsewhere_stmt where_body_construct_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, NULL, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| where_body_construct_seq elsewhere_stmt where_body_construct_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, $1, NULL, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| where_body_construct_seq mask_elsewhere_part_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, $1, $2, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| where_body_construct_seq mask_elsewhere_part_seq elsewhere_stmt 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, $1, $2, $3, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| where_body_construct_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, $1, NULL, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| where_body_construct_seq elsewhere_stmt 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, $1, $2, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| elsewhere_stmt where_body_construct_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, NULL, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| mask_elsewhere_part_seq 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, NULL, $1, NULL, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| mask_elsewhere_part_seq elsewhere_stmt 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, NULL, $1, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| elsewhere_stmt 
{
    $$ = ASTMake4(AST_WHERE_CONSTRUCT_BODY, NULL, NULL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| /* empty */
{
    $$ = NULL;
}
;
mask_elsewhere_part : masked_elsewhere_stmt where_body_construct_seq
{
    $$ = ASTMake2(AST_MASK_ELSEWHERE_PART, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| masked_elsewhere_stmt
{
    $$ = ASTMake2(AST_MASK_ELSEWHERE_PART, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
where_construct_stmt : labeldef name ':' TOK_WHERE '(' mask_expr ')' eos
{
    $$ = ASTMake3Label(AST_WHERE_CONSTRUCT_STATEMENT, $1, $2, $6, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef TOK_WHERE '(' mask_expr ')' eos
{
    $$ = ASTMake3Label(AST_WHERE_CONSTRUCT_STATEMENT, $1, NULL, $4, $2.token_file, $2.token_line, NULL);
}
;
where_body_construct : where_assignment_stmt
| where_stmt
| where_construct
;
where_assignment_stmt : assignment_stmt
;
mask_expr : logical_expr
;
masked_elsewhere_stmt : labeldef elsewhere_toks '(' mask_expr ')' name eos
{
    $$ = ASTMake3Label(AST_ELSEWHERE_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef elsewhere_toks '(' mask_expr ')' eos
{
    $$ = ASTMake3Label(AST_ELSEWHERE_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
elsewhere_stmt : labeldef elsewhere_toks name eos
{
    $$ = ASTMake3Label(AST_ELSEWHERE_STATEMENT, NULL, NULL, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef elsewhere_toks eos
{
    $$ = ASTMake3Label(AST_ELSEWHERE_STATEMENT, NULL, NULL, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
elsewhere_toks : TOK_ELSE TOK_WHERE
{
    $$ = $1;
}
| TOK_ELSEWHERE
{
    $$ = $1;
}
;
end_where_stmt : labeldef TOK_END TOK_WHERE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_WHERE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
;
forall_construct : forall_construct_stmt forall_body_construct_seq end_forall_stmt
{
    $$ = ASTMake3(AST_FORALL_CONSTRUCT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| forall_construct_stmt end_forall_stmt
{
    $$ = ASTMake3(AST_FORALL_CONSTRUCT, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
forall_construct_stmt : labeldef name ':' TOK_FORALL forall_header eos
{
    $$ = ASTMake3Label(AST_FORALL_CONSTRUCT_STATEMENT, $1, $2, $5, $3.token_file, $3.token_line, $4.token_text);
}
| labeldef TOK_FORALL forall_header eos
{
    $$ = ASTMake3Label(AST_FORALL_CONSTRUCT_STATEMENT, $1, NULL, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
forall_header : '(' type_spec ':' ':' forall_triplet_spec_list ',' mask_expr ')'
{
    $$ = ASTMake3(AST_FORALL_HEADER, $2, $5, $7, $1.token_file, $1.token_line, NULL);
}
| '(' forall_triplet_spec_list ',' mask_expr ')'
{
    $$ = ASTMake3(AST_FORALL_HEADER, NULL, $2, $4, $1.token_file, $1.token_line, NULL);
}
| '(' type_spec ':' ':' forall_triplet_spec_list ')'
{
    $$ = ASTMake3(AST_FORALL_HEADER, $2, NULL, $5, $1.token_file, $1.token_line, NULL);
}
| '(' forall_triplet_spec_list ')'
{
    $$ = ASTMake3(AST_FORALL_HEADER, NULL, NULL, $2, $1.token_file, $1.token_line, NULL);
}
;
forall_triplet_spec : name '=' forall_limit ':' forall_limit ':' forall_step
{
    $$ = ASTMake4(AST_FORALL_TRIPLET_SPEC, $1, $3, $5, $7, ASTFileName($1), ASTLine($1), NULL);
}
| name '=' forall_limit ':' forall_limit
{
    $$ = ASTMake4(AST_FORALL_TRIPLET_SPEC, $1, $3, $5, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
forall_limit : int_expr
;
forall_step : int_expr
;
forall_body_construct : forall_assignment_stmts
| where_stmt
| where_construct
| forall_construct
| forall_stmt
;
forall_assignment_stmts : assignment_stmt
| pointer_assignment_stmt
;
end_forall_stmt : labeldef TOK_END TOK_FORALL name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_FORALL eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
;
forall_stmt : labeldef TOK_FORALL forall_header forall_assignment_stmts 
{
    $$ = ASTMake3Label(AST_FORALL_STATEMENT, $1, $3, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
top_level_block : top_level_program_unit_stmts_seq
{
    $$ = ASTMake1(AST_COMPOUND_STATEMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
| /* empty */
{
    AST empty = ASTListLeaf(ASTLeaf(AST_EMPTY_STATEMENT, NULL, 0, NULL));
    $$ = ASTMake1(AST_COMPOUND_STATEMENT, empty, ASTFileName(empty), ASTLine(empty), NULL);
}
;
block : non_top_level_program_unit_stmts_seq
{
    $$ = ASTMake1(AST_COMPOUND_STATEMENT, $1, ASTFileName($1), ASTLine($1), NULL);
}
| /* empty */
{
    AST empty = ASTListLeaf(ASTLeaf(AST_EMPTY_STATEMENT, NULL, 0, NULL));
    $$ = ASTMake1(AST_COMPOUND_STATEMENT, empty, ASTFileName(empty), ASTLine(empty), NULL);
}
;
opt_statement_seq : non_top_level_program_unit_stmts_seq
| /* empty */
{
    $$ = NULL;
}
;
associate_construct : associate_stmt block end_associate_stmt
{
    $$ = ASTMake3(AST_ASSOCIATE_CONSTRUCT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
associate_stmt : labeldef name ':' TOK_ASSOCIATE '(' association_list ')' eos
{
    $$ = ASTMake3Label(AST_ASSOCIATE_STATEMENT, $1, $2, $6, $4.token_file, $4.token_line, $4.token_text);
}
| labeldef TOK_ASSOCIATE '(' association_list ')' eos
{
    $$ = ASTMake3Label(AST_ASSOCIATE_STATEMENT, $1, NULL, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
association : name TOK_POINTER_ACCESS selector
{
    $$ = ASTMake2(AST_RENAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
selector : expr
;
end_associate_stmt : labeldef TOK_END TOK_ASSOCIATE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_ASSOCIATE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDASSOCIATE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDASSOCIATE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
block_construct : block_stmt block end_block_stmt
{
    $$ = ASTMake3(AST_BLOCK_CONSTRUCT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
block_stmt : labeldef name ':' TOK_BLOCK eos
{
    $$ = ASTMake2Label(AST_BLOCK_STATEMENT, $1, $2, $4.token_file, $4.token_line, $4.token_text);
}
| labeldef TOK_BLOCK eos
{
    $$ = ASTMake2Label(AST_BLOCK_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
end_block_stmt : labeldef TOK_END TOK_BLOCK name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_BLOCK eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
;
critical_construct : critical_stmt block end_critical_stmt
{
    $$ = ASTMake3(AST_CRITICAL_CONSTRUCT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
critical_stmt : labeldef name ':' TOK_CRITICAL eos
{
    $$ = ASTMake2Label(AST_CRITICAL_STATEMENT, $1, $2, $4.token_file, $4.token_line, $4.token_text);
}
| labeldef TOK_CRITICAL eos
{
    $$ = ASTMake2Label(AST_CRITICAL_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
end_critical_stmt : labeldef TOK_END TOK_CRITICAL name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_CRITICAL eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDCRITICAL name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDCRITICAL eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
do_construct : nonlabel_do_stmt block end_do_stmt
{
    AST do_statement = $1;
    if (ASTType(do_statement) == AST_LABELED_STATEMENT)
    {
        do_statement = ASTSon1(do_statement);
    }

    ast_set_child(do_statement, 1, $2);
    ast_set_child(do_statement, 2, $3);

    $$ = $1;
}
| nonblock_do_construct
;
nonblock_do_construct : action_term_do_construct
| outer_shared_do_construct
;
action_term_do_construct : label_do_stmt block do_term_action_stmt
{
    AST do_statement = $1;
    if (ASTType(do_statement) == AST_LABELED_STATEMENT)
    {
        do_statement = ASTSon1(do_statement);
    }

    append_statement_to_block($2, $3);
    ast_set_child(do_statement, 1, $2);

    $$ = $1;
}
;
// This token is introduced artificially by the lexer to help the parser grasp
// the structure, it does not exist anywhere else
do_term_action_stmt : TOK_END_NONBLOCK_DO non_top_level_program_unit_stmts
{
    $$ = $2;
}
;
outer_shared_do_construct : label_do_stmt block shared_term_do_construct
{
    AST do_statement = $1;
    if (ASTType(do_statement) == AST_LABELED_STATEMENT)
    {
        do_statement = ASTSon1(do_statement);
    }

    append_statement_to_block($2, $3);
    ast_set_child(do_statement, 1, $2);

    $$ = $1;
}
;
outer_shared_do_construct_2 : label_do_shared_stmt block shared_term_do_construct
{
    AST do_statement = $1;
    if (ASTType(do_statement) == AST_LABELED_STATEMENT)
    {
        do_statement = ASTSon1(do_statement);
    }

    append_statement_to_block($2, $3);
    ast_set_child(do_statement, 1, $2);

    $$ = $1;
}
;
shared_term_do_construct : outer_shared_do_construct_2
| inner_shared_do_construct
;
inner_shared_do_construct : label_do_shared_stmt block do_term_action_stmt
{
    AST do_statement = $1;
    if (ASTType(do_statement) == AST_LABELED_STATEMENT)
    {
        do_statement = ASTSon1(do_statement);
    }

    append_statement_to_block($2, $3);
    ast_set_child(do_statement, 1, $2);

    $$ = $1;
}
;
nonlabel_do_stmt : labeldef name_colon_opt TOK_DO loop_control eos
{
    $$ = ASTMake4Label(AST_FOR_STATEMENT, $1, $4, NULL, NULL, $3.token_file, $3.token_line, NULL);
}
| labeldef name_colon_opt TOK_DO while_loop_control eos
{
    $$ = ASTMake4Label(AST_WHILE_STATEMENT, $1, $4, NULL, NULL, $3.token_file, $3.token_line, NULL);
}
| labeldef name_colon_opt TOK_DO label concurrent_loop_control eos
{
    running_error("%s:%d: sorry: DO CONCURRENT not supported\n", $3.token_file, $3.token_line);
}
| labeldef name_colon_opt TOK_DO eos
{
    AST empty_loop_control = ASTMake3(AST_LOOP_CONTROL, NULL, NULL, NULL, $3.token_file, $3.token_line, NULL);
    $$ = ASTMake4Label(AST_FOR_STATEMENT, $1, empty_loop_control, NULL, NULL, $3.token_file, $3.token_line, NULL);
}
;
label_do_stmt : labeldef name_colon_opt TOK_DO label loop_control eos
{
    $$ = ASTMake5Label(AST_FOR_STATEMENT, $1, $5, NULL, NULL, $4, $3.token_file, $3.token_line, NULL);
}
| labeldef name_colon_opt TOK_DO label while_loop_control eos
{
    $$ = ASTMake5Label(AST_WHILE_STATEMENT, $1, $5, NULL, NULL, $4, $3.token_file, $3.token_line, NULL);
}
| labeldef name_colon_opt TOK_DO label concurrent_loop_control eos
{
    running_error("%s:%d: sorry: DO CONCURRENT not supported\n", $3.token_file, $3.token_line);
}
| labeldef name_colon_opt TOK_DO label eos
{
    $$ = ASTMake5Label(AST_FOR_STATEMENT, $1, NULL, NULL, NULL, $4, $3.token_file, $3.token_line, NULL);
}
;
label_do_shared_stmt : labeldef name_colon_opt TOK_DO do_shared_label loop_control eos
{
    $$ = ASTMake5Label(AST_FOR_STATEMENT, $1, $5, NULL, NULL, $4, $3.token_file, $3.token_line, NULL);
}
| labeldef name_colon_opt TOK_DO do_shared_label while_loop_control eos
{
    $$ = ASTMake5Label(AST_WHILE_STATEMENT, $1, $5, NULL, NULL, $4, $3.token_file, $3.token_line, NULL);
}
| labeldef name_colon_opt TOK_DO do_shared_label concurrent_loop_control eos
{
    running_error("%s:%d: sorry: DO CONCURRENT not supported\n", $3.token_file, $3.token_line);
}
| labeldef name_colon_opt TOK_DO do_shared_label eos
{
    $$ = ASTMake5Label(AST_FOR_STATEMENT, $1, NULL, NULL, NULL, $4, $3.token_file, $3.token_line, NULL);
}
;
do_shared_label : TOK_SHARED_LABEL
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
comma_int_expr_opt : ',' int_expr
{
    $$ = $2;
}
| /* empty */
{
    $$ = NULL;
}
;
comma_opt : ','
{
}
| /* empty */
{
}
;
loop_control : comma_opt do_variable '=' int_expr ',' int_expr comma_int_expr_opt
{
    AST assig = ASTMake2(AST_ASSIGNMENT, $2, $4, ASTFileName($2), ASTLine($2), NULL);
    $$ = ASTMake3(AST_LOOP_CONTROL, assig, $6, $7, ASTFileName($2), ASTLine($2), "fortran");
}
;
while_loop_control : ',' TOK_WHILE '(' logical_expr ')'
{
    $$ = $4;
}
| TOK_WHILE '(' logical_expr ')'
{
    $$ = $3;
}
;
concurrent_loop_control : ',' TOK_CONCURRENT forall_header
{
    $$ = $3;
}
| TOK_CONCURRENT forall_header
{
    $$ = $2;
}
;
do_variable : name
;
end_do_stmt : labeldef TOK_END TOK_DO name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_DO eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDDO name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDDO eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
cycle_stmt : labeldef TOK_CYCLE name eos
{
    $$ = ASTMake2Label(AST_CONTINUE_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_CYCLE eos
{
    $$ = ASTMake2Label(AST_CONTINUE_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
name_opt : name
| /* empty */
{
    $$ = NULL;
}
;
name_colon_opt : name ':' 
{
    $$ = $1;
}
| /* empty */
{
    $$ = NULL;
}
;
if_construct : labeldef name_colon_opt TOK_IF '(' logical_expr ')' TOK_THEN eos block end_if_stmt
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $5, $9, NULL, $10, $3.token_file, $3.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
| labeldef name_colon_opt TOK_IF '(' logical_expr ')' TOK_THEN eos block labeldef TOK_ELSE name_opt eos block end_if_stmt
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $5, $9, $14, $15, $3.token_file, $3.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
| labeldef name_colon_opt TOK_IF '(' logical_expr ')' TOK_THEN eos block elseif_seq 
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $5, $9, $10, NULL, $3.token_file, $3.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
;
elseif_toks : TOK_ELSE TOK_IF
{
    $$ = $1;
}
| TOK_ELSEIF
;
elseif_seq : labeldef elseif_toks '(' logical_expr ')' name_opt eos block elseif_seq
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $4, $8, $9, NULL, $2.token_file, $2.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
| labeldef elseif_toks '(' logical_expr ')' name_opt eos block labeldef TOK_ELSE name_opt eos block end_if_stmt
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $4, $8, $13, $14, $2.token_file, $2.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
| labeldef elseif_toks '(' logical_expr ')' name_opt eos block end_if_stmt
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $4, $8, NULL, $9, $2.token_file, $2.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
;
end_if_stmt : labeldef TOK_END TOK_IF name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_END TOK_IF eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_ENDIF name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDIF eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
if_stmt : labeldef TOK_IF '(' logical_expr ')' action_stmts 
{
    AST result = ASTMake4(AST_IF_ELSE_STATEMENT, $4, $6, NULL, NULL, $2.token_file, $2.token_line, NULL);
    if ($1 != NULL)
    {
        result = ASTMake2(AST_LABELED_STATEMENT, $1, result, ASTFileName($1), ASTLine($1), NULL);
    }
    $$ = result;
}
;
case_construct : select_case_stmt case_part_seq end_select_stmt
{
    AST result = $1;
    AST switch_tree = result;
    if (ASTType(switch_tree) == AST_LABELED_STATEMENT)
    {
        switch_tree = ASTSon1(switch_tree);
    }

    // Store the block
    ast_set_child(switch_tree, 1, 
            ASTMake1(AST_COMPOUND_STATEMENT, $2, ASTFileName($2), ASTLine($2), NULL));

    // Store the ending statement, if any
    if ($3 != NULL)
    {
        ast_set_child(switch_tree, 2, $3);
    }

    $$ = result;
}
;
case_part : case_stmt block
{
    AST returned_tree = $1;
    // Because a block is a compound statement, we want its list
    AST block = ASTSon0($2);

    // Mold the tree to match that of C/C++
    AST case_stmt = returned_tree;
    if (ASTType(case_stmt) == AST_LABELED_STATEMENT)
    {
        case_stmt = ASTSon1(case_stmt);
    }
    AST head = NULL; 
    AST tail = NULL;
    ast_list_split_head_tail(block, &head, &tail);

    int son = 0;
    if (ASTType(case_stmt) == AST_CASE_STATEMENT)
    {
        son = 1;
    }
    else if (ASTType(case_stmt) == AST_DEFAULT_STATEMENT)
    {
        son = 0;
    }
    else
    {
        internal_error("Unexpected node '%s'\n", 
                ast_print_node_type(ASTType(case_stmt)));
    }

    ast_set_child(case_stmt, son, ASTSon1(head));

    ast_set_child(head, 1, NULL);
    ast_free(head);

    block = tail;

    $$ = ast_list_concat(ASTListLeaf(returned_tree), block);
}
;
case_part_seq : case_part
{
  $$ = $1;
}
| case_part_seq case_part
{
  $$ = ast_list_concat($1, $2);
}
;
select_case_stmt : labeldef name ':' selectcase_toks '(' case_expr ')' eos
{
    $$ = ASTMake4Label(AST_SWITCH_STATEMENT, $1, $6, NULL, NULL, $4.token_file, $4.token_line, $4.token_text);
}
| labeldef selectcase_toks '(' case_expr ')' eos
{
    $$ = ASTMake4Label(AST_SWITCH_STATEMENT, $1, $4, NULL, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
selectcase_toks : TOK_SELECT TOK_CASE
{
    $$ = $1;
}
| TOK_SELECTCASE
{
    $$ = $1;
}
;

case_stmt : labeldef TOK_CASE case_selector name eos
{
    AST case_selector = $3;
    if (ASTText(case_selector) == NULL)
    {
        $$ = ASTMake3Label(AST_CASE_STATEMENT, $1, $3, NULL, $2.token_file, $2.token_line, $2.token_text);
    }
    else
    {
        $$ = ASTMake2Label(AST_DEFAULT_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
        ast_free($3);
    }
}
| labeldef TOK_CASE case_selector eos
{
    AST case_selector = $3;
    if (ASTText(case_selector) == NULL)
    {
        $$ = ASTMake3Label(AST_CASE_STATEMENT, $1, $3, NULL, $2.token_file, $2.token_line, $2.token_text);
    }
    else
    {
        $$ = ASTMake2Label(AST_DEFAULT_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
        ast_free($3);
    }
}
;
end_select_stmt : labeldef TOK_END TOK_SELECT name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_SELECT eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDSELECT name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDSELECT eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
case_expr : expr
;
case_selector : '(' case_value_range_list ')'
{
    $$ = ASTMake1(AST_CASE_SELECTOR, $2, $1.token_file, $1.token_line, NULL);
}
| TOK_DEFAULT
{
    $$ = ASTMake1(AST_CASE_SELECTOR, NULL, $1.token_file, $1.token_line, $1.token_text);
}
;
case_value_range : case_value
| case_value ':'
{
    $$ = ASTMake2(AST_CASE_VALUE_RANGE, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| ':' case_value
{
    $$ = ASTMake2(AST_CASE_VALUE_RANGE, NULL, $2, ASTFileName($2), ASTLine($2), NULL);
}
| case_value ':' case_value
{
    $$ = ASTMake2(AST_CASE_VALUE_RANGE, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
case_value : constant_expr
;
select_type_construct : select_type_stmt type_guard_part_seq end_select_type_stmt
{
    $$ = ASTMake3(AST_SELECT_TYPE_CONSTRUCT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| select_type_stmt end_select_type_stmt
{
    $$ = ASTMake3(AST_SELECT_TYPE_CONSTRUCT, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
type_guard_part : type_guard_stmt block
{
    $$ = ASTMake2(AST_TYPE_GUARD_PART, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
select_type_stmt : labeldef name ':' TOK_SELECT TOK_TYPE '(' name TOK_POINTER_ACCESS selector ')' eos
{
    $$ = ASTMake4Label(AST_SELECT_TYPE_STATEMENT, $1, $2, $7, $9, $4.token_file, $4.token_line, $4.token_text);
}
| labeldef TOK_SELECT TOK_TYPE '(' name TOK_POINTER_ACCESS selector ')' eos
{
    $$ = ASTMake4Label(AST_SELECT_TYPE_STATEMENT, $1, NULL, $5, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef name ':' TOK_SELECT TOK_TYPE '(' selector ')' eos
{
    $$ = ASTMake4Label(AST_SELECT_TYPE_STATEMENT, $1, $2, NULL, $7, $4.token_file, $4.token_line, $4.token_text);
}
| labeldef TOK_SELECT TOK_TYPE '(' selector ')' eos
{
    $$ = ASTMake4Label(AST_SELECT_TYPE_STATEMENT, $1, NULL, NULL, $5, $2.token_file, $2.token_line, $2.token_text);
}
;
type_guard_stmt : labeldef TOK_TYPE TOK_IS '(' type_spec ')' name eos
{
    $$ = ASTMake3Label(AST_TYPE_IS_STATEMENT, $1, $5, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_TYPE TOK_IS '(' type_spec ')' eos
{
    $$ = ASTMake3Label(AST_TYPE_IS_STATEMENT, $1, $5, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_CLASS TOK_IS '(' derived_type_spec ')' name eos
{
    $$ = ASTMake3Label(AST_CLASS_IS_STATEMENT, $1, $5, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_CLASS TOK_IS '(' derived_type_spec ')' eos
{
    $$ = ASTMake3Label(AST_CLASS_IS_STATEMENT, $1, $5, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_CLASS TOK_DEFAULT name eos
{
    $$ = ASTMake2Label(AST_CLASS_DEFAULT_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_CLASS TOK_DEFAULT eos
{
    $$ = ASTMake2Label(AST_CLASS_DEFAULT_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
end_select_type_stmt : labeldef TOK_END TOK_SELECT name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_SELECT eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
;
exit_stmt : labeldef TOK_EXIT name eos
{
    $$ = ASTMake2Label(AST_BREAK_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_EXIT eos
{
    $$ = ASTMake2Label(AST_BREAK_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
goto_stmt : labeldef TOK_GO TOK_TO label eos
{
    $$ = ASTMake2Label(AST_GOTO_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_GOTO label eos
{
    $$ = ASTMake2Label(AST_GOTO_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
label_assign_stmt : labeldef TOK_ASSIGN int_literal_constant TOK_TO name eos
{
    $$ = ASTMake3Label(AST_LABEL_ASSIGN_STATEMENT, $1, $3, $5, $2.token_file, $2.token_line, NULL);
}
;
goto_toks : TOK_GO TOK_TO
| TOK_GOTO
;
computed_goto_stmt : labeldef goto_toks '(' label_list ')' ',' int_expr eos
{
    $$ = ASTMake3Label(AST_COMPUTED_GOTO_STATEMENT, $1, $4, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef goto_toks '(' label_list ')' int_expr eos
{
    $$ = ASTMake3Label(AST_COMPUTED_GOTO_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
;
assigned_goto_stmt : labeldef goto_toks name '(' label_list ')' eos
{
    $$ = ASTMake3Label(AST_ASSIGNED_GOTO_STATEMENT, $1, $3, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef goto_toks name ',' '(' label_list ')' eos
{
    $$ = ASTMake3Label(AST_ASSIGNED_GOTO_STATEMENT, $1, $3, $6, $2.token_file, $2.token_line, $2.token_text);
}
;
arithmetic_if_stmt : labeldef TOK_IF '(' numeric_expr ')' label ',' label ',' label eos
{
    $$ = ASTMake3Label(AST_ARITHMETIC_IF_STATEMENT, $1, $4, 
            ASTMake3(AST_ARITHMETIC_IF_STATEMENT, $6, $8, $10, $2.token_file, $2.token_line, $2.token_text),
            $2.token_file, $2.token_line, $2.token_text);
}
;
continue_stmt : labeldef TOK_CONTINUE eos
{
    $$ = ASTMake1Label(AST_EMPTY_STATEMENT, $1, $2.token_file, $2.token_line, $2.token_text);
}
;
stop_stmt : labeldef TOK_STOP stop_code eos
{
    $$ = ASTMake2Label(AST_STOP_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_STOP eos
{
    $$ = ASTMake2Label(AST_STOP_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
pause_stmt : labeldef TOK_PAUSE int_expr eos
{
    $$ = ASTMake2Label(AST_PAUSE_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PAUSE eos
{
    $$ = ASTMake2Label(AST_PAUSE_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
allstop_stmt : labeldef TOK_ALL TOK_STOP stop_code eos
{
    $$ = ASTMake2Label(AST_ALL_STOP_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ALLSTOP stop_code eos
{
    $$ = ASTMake2Label(AST_ALL_STOP_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ALL TOK_STOP eos
{
    $$ = ASTMake2Label(AST_ALL_STOP_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ALLSTOP eos
{
    $$ = ASTMake2Label(AST_ALL_STOP_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
stop_code : expr
;
sync_all_stmt : labeldef TOK_SYNC TOK_ALL '(' sync_stat_list ')' eos
{
    $$ = ASTMake2Label(AST_SYNC_ALL_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_SYNC TOK_ALL eos
{
    $$ = ASTMake2Label(AST_SYNC_ALL_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_SYNC TOK_ALL '(' ')' eos
{
    $$ = ASTMake2Label(AST_SYNC_ALL_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
sync_stat : TOK_STAT '=' stat_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERRMSG '=' errmsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
sync_images_stmt : labeldef TOK_SYNC TOK_IMAGES '(' image_set ',' sync_stat_list ')' eos
{
    $$ = ASTMake3Label(AST_SYNC_IMAGES_STATEMENT, $1, $5, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_SYNC TOK_IMAGES '(' image_set ')' eos
{
    $$ = ASTMake3Label(AST_SYNC_IMAGES_STATEMENT, $1, $5, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
image_set : int_expr
| '*'
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
sync_memory_stmt : labeldef TOK_SYNC TOK_MEMORY '(' sync_stat_list ')' eos
{
    $$ = ASTMake2Label(AST_SYNC_MEMORY_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_SYNC TOK_MEMORY eos
{
    $$ = ASTMake2Label(AST_SYNC_MEMORY_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_SYNC TOK_MEMORY '(' ')' eos
{
    $$ = ASTMake2Label(AST_SYNC_MEMORY_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
lock_stmt : labeldef TOK_LOCK '(' lock_variable ',' lock_stat_list ')' eos
{
    $$ = ASTMake3Label(AST_LOCK_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_LOCK '(' lock_variable ')' eos
{
    $$ = ASTMake3Label(AST_LOCK_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
lock_stat : TOK_ACQUIRED TOK_LOCK '=' logical_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $4, $1.token_file, $1.token_line, $1.token_text);
}
| sync_stat
;
unlock_stmt : labeldef TOK_UNLOCK '(' lock_variable ',' sync_stat_list ')' eos
{
    $$ = ASTMake3Label(AST_UNLOCK_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_UNLOCK '(' lock_variable ')' eos
{
    $$ = ASTMake3Label(AST_UNLOCK_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
lock_variable : variable
;
io_unit : file_unit_number
| '*'
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
file_unit_number : int_expr
;
open_stmt : labeldef TOK_OPEN '(' connect_spec_list ')' eos
{
    $$ = ASTMake2Label(AST_OPEN_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
connect_spec : TOK_UNIT '=' file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $1,  ASTFileName($1), ASTLine($1), "unit");
}
| TOK_ACCESS '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ACTION '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ASYNCHRONOUS '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_BLANK '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DECIMAL '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DELIM '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ENCODING '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_FILE '=' file_name_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_FORM '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NEWUNIT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PAD '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POSITION '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_RECL '=' int_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ROUND '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SIGN '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_STATUS '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
file_name_expr : default_char_expr
;
iomsg_variable : default_char_variable
;
close_stmt : labeldef TOK_CLOSE '(' close_spec_list ')' eos
{
    $$ = ASTMake2Label(AST_CLOSE_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
close_spec : TOK_UNIT '=' file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $1,  ASTFileName($1), ASTLine($1), "unit");
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_STATUS '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
read_stmt : labeldef TOK_READ '(' io_control_spec_list ')' input_output_item_list eos %dprec 2
{
    $$ = ASTMake3Label(AST_READ_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_READ '(' io_control_spec_list ')' eos %dprec 2
{
    $$ = ASTMake3Label(AST_READ_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_READ format ',' input_output_item_list eos %dprec 1
{
    AST format = ASTMake1(AST_OPT_VALUE, $3, ASTFileName($3), ASTLine($3), "fmt");

    $$ = ASTMake3Label(AST_READ_STATEMENT, $1, ASTListLeaf(format), $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_READ format eos %dprec 1
{
    AST format = ASTMake1(AST_OPT_VALUE, $3, ASTFileName($3), ASTLine($3), "fmt");

    $$ = ASTMake3Label(AST_READ_STATEMENT, $1, ASTListLeaf(format), NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
write_stmt : labeldef TOK_WRITE '(' io_control_spec_list ')' input_output_item_list eos
{
    $$ = ASTMake3Label(AST_WRITE_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_WRITE '(' io_control_spec_list ')' eos
{
    $$ = ASTMake3Label(AST_WRITE_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
print_stmt : labeldef TOK_PRINT format ',' input_output_item_list eos
{
    $$ = ASTMake3Label(AST_PRINT_STATEMENT, $1, $3, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PRINT format eos
{
    $$ = ASTMake3Label(AST_PRINT_STATEMENT, $1, $3, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
io_control_spec : TOK_UNIT '=' io_unit
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| io_unit %merge<ambig_io_control_spec>
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "unit");
}
| TOK_FMT '=' format
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| format %merge<ambig_io_control_spec>
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "fmt");
}
| TOK_NML '=' name
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| name %merge<ambig_io_control_spec>
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "nml");
}
| TOK_ADVANCE '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ASYNCHRONOUS '=' default_char_constant_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_BLANK '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DECIMAL '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DELIM '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_END '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_EOR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ID '=' id_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PAD '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POS '=' int_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_REC '=' int_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ROUND '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SIGN '=' default_char_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SIZE '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
id_variable : int_variable
;
format : expr
| '*'
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
input_output_item : expr
| io_implied_do
;
io_implied_do : '(' io_implied_do_object_list ',' io_implied_do_control ')'
{
    $$ = ASTMake2(AST_IMPLIED_DO, $2, $4, $1.token_file, $1.token_line, NULL);
}
;
io_implied_do_object : input_output_item
;
io_implied_do_control : do_variable '=' int_expr ',' int_expr comma_int_expr_opt
{
    $$ = ASTMake4(AST_IMPLIED_DO_CONTROL, $1, $3, $5, $6, ASTFileName($1), ASTLine($1), NULL);
}
;
wait_stmt : labeldef TOK_WAIT '(' wait_spec_list ')' eos
{
    $$ = ASTMake2Label(AST_WAIT_STATEMENT, $1, $4, $2.token_file, $2.token_line, NULL);
}
;
wait_spec : TOK_UNIT '=' file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "unit");
}
| TOK_END '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_EOR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ID '=' int_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
backspace_stmt : labeldef TOK_BACKSPACE file_unit_number eos %dprec 1
{
    AST file_unit = ASTMake1(AST_OPT_VALUE, $3, ASTFileName($3), ASTLine($3), "UNIT");

    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, ASTListLeaf(file_unit), $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_BACKSPACE '(' position_spec_list ')' eos %dprec 2
{
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
endfile_stmt : labeldef TOK_ENDFILE file_unit_number eos %dprec 1
{
    AST file_unit = ASTMake1(AST_OPT_VALUE, $3, ASTFileName($3), ASTLine($3), "UNIT");
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, ASTListLeaf(file_unit), $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDFILE '(' position_spec_list ')' eos %dprec 2
{
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
rewind_stmt : labeldef TOK_REWIND file_unit_number eos %dprec 1
{
    AST file_unit = ASTMake1(AST_OPT_VALUE, $3, ASTFileName($3), ASTLine($3), "unit");
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, ASTListLeaf(file_unit), $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_REWIND '(' position_spec_list ')' eos %dprec 2
{
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
position_spec : TOK_UNIT '=' file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "unit");
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
flush_stmt : labeldef TOK_FLUSH file_unit_number eos %dprec 1
{
    AST file_unit = ASTMake1(AST_OPT_VALUE, $3, ASTFileName($3), ASTLine($3), "unit");
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, ASTListLeaf(file_unit), $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_FLUSH '(' flush_spec_list ')' eos %dprec 2
{
    $$ = ASTMake2Label(AST_IO_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
flush_spec : TOK_UNIT '=' file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "unit");
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
inquire_stmt : labeldef TOK_INQUIRE '(' inquire_spec_list ')' eos
{
    $$ = ASTMake3Label(AST_IO_STATEMENT, $1, $4, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_INQUIRE '(' TOK_IOLENGTH '=' int_variable ')' input_output_item_list eos
{
    AST iolength = ASTMake1(AST_OPT_VALUE, $6, $4.token_file, $4.token_line, $4.token_text);

    $$ = ASTMake3Label(AST_IO_STATEMENT, $1, ASTListLeaf(iolength), $8, $2.token_file, $2.token_line, $2.token_text);
}
;
inquire_spec : TOK_UNIT '=' file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| file_unit_number
{
    $$ = ASTMake1(AST_OPT_VALUE, $1, ASTFileName($1), ASTLine($1), "unit");
}
| TOK_FILE '=' file_name_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ACCESS '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ACTION '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ASYNCHRONOUS '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_BLANK '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DECIMAL '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DELIM '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_DIRECT '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ENCODING '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ERR '=' label
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_EXIST '=' logical_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_FORM '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_FORMATTED '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ID '=' int_expr
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOMSG '=' iomsg_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IOSTAT '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NAME '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NAMED '=' logical_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NEXTREC '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NUMBER '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_OPENED '=' logical_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PAD '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PENDING '=' logical_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POS '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POSITION '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_READ '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_READWRITE '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_RECL '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_ROUND '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SEQUENTIAL '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SIGN '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SIZE '=' int_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_STREAM '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_UNFORMATTED '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_WRITE '=' default_char_variable
{
    $$ = ASTMake1(AST_OPT_VALUE, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
// Note the use of label instead of labeldef
format_stmt : label TOK_FORMAT FORMAT_SPEC eos
{
    $$ = ASTMake2Label(AST_FORMAT_STATEMENT, $1, 
            ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text),
            $2.token_file, $2.token_line, $2.token_text);
}
;
main_program : program_stmt program_body end_program_stmt
{
    $$ = ASTMake3(AST_MAIN_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| program_body end_program_stmt
{
    $$ = ASTMake3(AST_MAIN_PROGRAM_UNIT, NULL, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
non_top_level_program_unit_stmts_seq : non_top_level_program_unit_stmts
{
    $$ = ASTListLeaf($1);
}
| non_top_level_program_unit_stmts_seq non_top_level_program_unit_stmts
{
    $$ = ASTList($1, $2);
}
;
top_level_program_unit_stmts_seq : top_level_program_unit_stmts
{
    $$ = ASTListLeaf($1);
}
| top_level_program_unit_stmts_seq top_level_program_unit_stmts
{
    $$ = ASTList($1, $2);
}
;
// All Fortran statements meant to appear inside a program unit (of any kind) should be here
action_stmts : non_top_level_program_unit_stmts;
top_level_program_unit_stmts : non_top_level_program_unit_stmts %merge<ambig_assignment_statement_function>
| stmt_function_stmt %merge<ambig_assignment_statement_function>
;
non_top_level_program_unit_stmts : access_stmt
| assignment_stmt 
| allocatable_stmt
| allocate_stmt
| allstop_stmt
| arithmetic_if_stmt
| associate_construct
| asynchronous_stmt
| backspace_stmt
| bind_stmt
| block_construct
| call_stmt
| case_construct
| close_stmt
| codimension_stmt
| common_stmt
| computed_goto_stmt
| assigned_goto_stmt
| label_assign_stmt
| continue_stmt
| critical_construct
| cycle_stmt
| data_stmt
| deallocate_stmt
| derived_type_def
| dimension_stmt
| do_construct
| endfile_stmt
| entry_stmt
| enum_def
| equivalence_stmt
| exit_stmt
| external_stmt
| flush_stmt
| forall_construct
| forall_stmt
| format_stmt
| goto_stmt
| if_construct
| if_stmt
| implicit_stmt
| import_stmt
| inquire_stmt
| intent_stmt
| interface_block
| intrinsic_stmt
| lock_stmt
| namelist_stmt
| nullify_stmt
| open_stmt
| optional_stmt
| parameter_stmt
| pointer_assignment_stmt
| pointer_stmt
| print_stmt
| procedure_declaration_stmt
| protected_stmt
| read_stmt
| return_stmt
| rewind_stmt
| save_stmt
| select_type_construct
| stop_stmt
| pause_stmt
| sync_all_stmt
| sync_images_stmt
| sync_memory_stmt
| target_stmt
| type_declaration_stmt
| unlock_stmt
| use_stmt
| value_stmt
| volatile_stmt
| wait_stmt
| where_construct
| where_stmt
| write_stmt
| unknown_pragma
;
unknown_pragma : UNKNOWN_PRAGMA eos
{
	$$ = ASTLeaf(AST_UNKNOWN_PRAGMA, $1.token_file, $1.token_line, $1.token_text);
}
;
program_body : top_level_block internal_subprogram_part 
{
    $$ = ASTMake2(AST_BODY_PROGRAM_UNIT, $1, $2, ASTFileName($1), ASTLine($1), NULL);
}
| top_level_block
{
    $$ = ASTMake2(AST_BODY_PROGRAM_UNIT, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
program_stmt : labeldef TOK_PROGRAM name eos
{
    $$ = ASTMake2Label(AST_PROGRAM_STATEMENT, $1, $3, $2.token_file, $2.token_line, NULL);
}
;
end_program_stmt : labeldef TOK_END TOK_PROGRAM name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_END TOK_PROGRAM eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDPROGRAM name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDPROGRAM eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
module : module_stmt opt_statement_seq module_subprogram_part end_module_stmt
{
    AST module_body = NULL;
    if ($2 != NULL)
    { 
        module_body = ASTMake2(AST_BODY_PROGRAM_UNIT, $2, $3, ASTFileName($2), ASTLine($2), NULL);
    }
    else
    {
        module_body = ASTMake2(AST_BODY_PROGRAM_UNIT, $2, $3, ASTFileName($3), ASTLine($3), NULL);
    }

    $$ = ASTMake3(AST_MODULE_PROGRAM_UNIT, $1, module_body, $4, ASTFileName($1), ASTLine($1), NULL);
}
| module_stmt opt_statement_seq end_module_stmt
{
    AST module_body = NULL;
    if ($2 != NULL)
    { 
        module_body = ASTMake2(AST_BODY_PROGRAM_UNIT, $2, NULL, ASTFileName($2), ASTLine($2), NULL);
    }
    else
    {
        module_body = ASTMake2(AST_BODY_PROGRAM_UNIT, $2, NULL, ASTFileName($1), ASTLine($1), NULL);
    }


    $$ = ASTMake3(AST_MODULE_PROGRAM_UNIT, $1, module_body, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
module_stmt : labeldef TOK_MODULE name eos
{
    $$ = ASTMake2Label(AST_MODULE_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
end_module_stmt : labeldef TOK_END TOK_MODULE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_MODULE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDMODULE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDMODULE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
module_subprogram_part : contains_stmt module_subprogram_seq
{
    $$ = $2;
}
| contains_stmt
{
    $$ = NULL;
}
;
module_subprogram : function_subprogram
| subroutine_subprogram
| separate_module_subprogram
;
use_stmt : labeldef TOK_USE ',' module_nature ':' ':' name ',' rename_list eos
{
    $$ = ASTMake4Label(AST_USE_STATEMENT, $1, $4, $7, $9, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE name ',' rename_list eos
{
    $$ = ASTMake4Label(AST_USE_STATEMENT, $1, NULL, $3, $5, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ':' ':' name ',' rename_list eos
{
    $$ = ASTMake4Label(AST_USE_STATEMENT, $1, NULL, $5, $7, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ',' module_nature ':' ':' name eos
{
    $$ = ASTMake4Label(AST_USE_STATEMENT, $1, $4, $7, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ':' ':' name eos
{
    $$ = ASTMake4Label(AST_USE_STATEMENT, $1, NULL, $5, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE name eos
{
    $$ = ASTMake4Label(AST_USE_STATEMENT, $1, NULL, $3, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ',' module_nature ':' ':' name ',' TOK_ONLY ':' only_list eos
{
    $$ = ASTMake4Label(AST_USE_ONLY_STATEMENT, $1, $4, $7, $11, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE name ',' TOK_ONLY ':' only_list eos
{
    $$ = ASTMake4Label(AST_USE_ONLY_STATEMENT, $1, NULL, $3, $7, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ':' ':' name ',' TOK_ONLY ':' only_list eos
{
    $$ = ASTMake4Label(AST_USE_ONLY_STATEMENT, $1, NULL, $5, $9, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ',' module_nature ':' ':' name ',' TOK_ONLY ':' eos
{
    $$ = ASTMake4Label(AST_USE_ONLY_STATEMENT, $1, $4, $7, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE ':' ':' name ',' TOK_ONLY ':' eos
{
    $$ = ASTMake4Label(AST_USE_ONLY_STATEMENT, $1, NULL, $5, NULL, $2.token_file, $2.token_line, NULL);
}
| labeldef TOK_USE name ',' TOK_ONLY ':' eos
{
    $$ = ASTMake4Label(AST_USE_ONLY_STATEMENT, $1, NULL, $3, NULL, $2.token_file, $2.token_line, NULL);
}
;
module_nature : TOK_INTRINSIC
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_NON_INTRINSIC
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
defined_operator_name : intrinsic_operator_name
| user_defined_operator_name
;
intrinsic_operator_name : TOK_OPERATOR '(' extended_intrinsic_op ')'
{
    $$ = ASTLeaf(AST_OPERATOR_NAME, $1.token_file, $1.token_line, $3.token_text);
}
;
user_defined_operator_name : TOK_OPERATOR '(' local_defined_operator ')'
{
    $$ = ASTLeaf(AST_OPERATOR_NAME, $1.token_file, $1.token_line, $3.token_text);
}
;
rename : name TOK_POINTER_ACCESS name
{
    $$ = ASTMake2(AST_RENAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| user_defined_operator_name TOK_POINTER_ACCESS user_defined_operator_name
{
    $$ = ASTMake2(AST_RENAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
only : generic_spec
| rename
;
local_defined_operator : user_defined_op
;
submodule : submodule_stmt opt_statement_seq module_subprogram_part end_submodule_stmt
{
    AST module_body = ASTMake2(AST_BODY_PROGRAM_UNIT, $2, $3, ASTFileName($2), ASTLine($2), NULL);

    $$ = ASTMake3(AST_SUBMODULE_PROGRAM_UNIT, $1, module_body, $4, ASTFileName($1), ASTLine($1), NULL);
}
| submodule_stmt opt_statement_seq end_submodule_stmt
{
    AST module_body = ASTMake2(AST_BODY_PROGRAM_UNIT, $2, NULL, ASTFileName($2), ASTLine($2), NULL);

    $$ = ASTMake3(AST_SUBMODULE_PROGRAM_UNIT, $1, module_body, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
submodule_stmt : labeldef TOK_SUBMODULE '(' parent_identifier ')' name eos
{
    $$ = ASTMake3Label(AST_SUBMODULE_STATEMENT, $1, $4, $6, $2.token_file, $2.token_line, $2.token_text);
}
;
parent_identifier : name ':' name
{
    $$ = ASTMake2(AST_SUBSCRIPT_TRIPLET, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
end_submodule_stmt : labeldef TOK_END TOK_SUBMODULE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_END TOK_SUBMODULE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDSUBMODULE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDSUBMODULE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
block_data : block_data_stmt block end_block_data_stmt
{
    $$ = ASTMake3(AST_BLOCK_DATA_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
block_data_stmt : labeldef TOK_BLOCK TOK_DATA name eos
{
    $$ = ASTMake2Label(AST_BLOCK_DATA_STATEMENT, $1, $4, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_BLOCK TOK_DATA eos
{
    $$ = ASTMake2Label(AST_BLOCK_DATA_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_BLOCKDATA name eos
{
    $$ = ASTMake2Label(AST_BLOCK_DATA_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_BLOCKDATA eos
{
    $$ = ASTMake2Label(AST_BLOCK_DATA_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;

end_block_data_stmt : labeldef end_block_data_toks name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef end_block_data_toks eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;

end_block_data_toks: TOK_END TOK_BLOCK TOK_DATA
| TOK_END
| TOK_END TOK_BLOCK TOK_DATA
| TOK_ENDBLOCK TOK_DATA
| TOK_ENDBLOCK TOK_DATA
| TOK_END TOK_BLOCKDATA
| TOK_END TOK_BLOCKDATA
| TOK_ENDBLOCKDATA
| TOK_ENDBLOCKDATA
;
interface_block : interface_stmt interface_specification_seq end_interface_stmt
{
    $$ = ASTMake3(AST_INTERFACE_BLOCK, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| interface_stmt end_interface_stmt
{
    $$ = ASTMake3(AST_INTERFACE_BLOCK, $1, NULL, $2, ASTFileName($1), ASTLine($1), NULL);
}
;
interface_specification : interface_body
| procedure_stmt
;
interface_stmt : labeldef TOK_INTERFACE generic_spec eos
{
    $$ = ASTMake3Label(AST_INTERFACE_STATEMENT, $1, NULL, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_INTERFACE eos
{
    $$ = ASTMake3Label(AST_INTERFACE_STATEMENT, $1, NULL, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ABSTRACT TOK_INTERFACE eos
{
    AST abstract = ASTLeaf(AST_SYMBOL, $2.token_file, $2.token_line, $2.token_text);

    $$ = ASTMake3Label(AST_INTERFACE_STATEMENT, $1, abstract, NULL, $3.token_file, $3.token_line, $3.token_text);
}
;
end_interface_stmt : labeldef TOK_END TOK_INTERFACE generic_spec eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END TOK_INTERFACE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDINTERFACE generic_spec eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDINTERFACE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;

interface_program_body : block 
{
    $$ = ASTMake2(AST_BODY_PROGRAM_UNIT, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;

interface_body : function_stmt interface_program_body end_function_stmt
{
    $$ = ASTMake3(AST_FUNCTION_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
| subroutine_stmt interface_program_body end_subroutine_stmt
{
    $$ = ASTMake3(AST_SUBROUTINE_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;

procedure_stmt : labeldef TOK_MODULE TOK_PROCEDURE ':' ':' procedure_name_list eos
{
    char c[] = "module procedure";
    sprintf(c, "%s %s", $2.token_text, $3.token_text);

    $$ = ASTMake2Label(AST_MODULE_PROCEDURE, $1, $6, $2.token_file, $2.token_line, c);
}
| labeldef TOK_PROCEDURE ':' ':' procedure_name_list eos
{
    $$ = ASTMake2Label(AST_PROCEDURE, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_MODULE TOK_PROCEDURE procedure_name_list eos
{
    char c[] = "module procedure";
    sprintf(c, "%s %s", $2.token_text, $3.token_text);

    $$ = ASTMake2Label(AST_MODULE_PROCEDURE, $1, $4, $2.token_file, $2.token_line, c);
}
| labeldef TOK_PROCEDURE procedure_name_list eos
{
    $$ = ASTMake2Label(AST_PROCEDURE, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
generic_spec : defined_operator_name
| TOK_ASSIGNMENT '(' '=' ')'
{
    $$ = ASTLeaf(AST_OPERATOR_NAME, $1.token_file, $1.token_line, $3.token_text);
}
| defined_io_generic_spec
| name
;
defined_io_generic_spec_fmt : TOK_FORMATTED
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_UNFORMATTED
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
defined_io_generic_spec : TOK_READ '(' defined_io_generic_spec_fmt ')'
{
    $$ = ASTMake1(AST_IO_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_WRITE '(' defined_io_generic_spec_fmt ')'
{
    $$ = ASTMake1(AST_IO_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
;
import_stmt : labeldef TOK_IMPORT ':' ':' import_name_list eos
{
    $$ = ASTMake2Label(AST_IMPORT_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_IMPORT eos
{
    $$ = ASTMake2Label(AST_IMPORT_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_IMPORT import_name_list eos
{
    $$ = ASTMake2Label(AST_IMPORT_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
external_stmt : labeldef TOK_EXTERNAL ':' ':' external_name_list eos
{
    $$ = ASTMake2Label(AST_EXTERNAL_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_EXTERNAL external_name_list eos
{
    $$ = ASTMake2Label(AST_EXTERNAL_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
procedure_declaration_stmt : labeldef TOK_PROCEDURE '(' proc_interface ')' ',' proc_attr_spec_list ':' ':' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROCEDURE_DECL_STATEMENT, $1, $4, $7, $10, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE '(' ')' ',' proc_attr_spec_list ':' ':' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROCEDURE_DECL_STATEMENT, $1, NULL, $6, $9, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE '(' proc_interface ')' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROCEDURE_DECL_STATEMENT, $1, $4, NULL, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE '(' proc_interface ')' ':' ':' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROCEDURE_DECL_STATEMENT, $1, $4, NULL, $8, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE '(' ')' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROCEDURE_DECL_STATEMENT, $1, NULL, NULL, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_PROCEDURE '(' ')' ':' ':' proc_decl_list eos
{
    $$ = ASTMake4Label(AST_PROCEDURE_DECL_STATEMENT, NULL, NULL, NULL, $7, $2.token_file, $2.token_line, $2.token_text);
}
;
proc_interface : name
| declaration_type_spec
;
proc_attr_spec : access_spec
| proc_language_binding_spec
| TOK_INTENT '(' intent_spec ')'
{
    $$ = ASTMake1(AST_ATTR_SPEC, $3, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_OPTIONAL
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_POINTER
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_SAVE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;
proc_decl : name TOK_POINTER_ACCESS proc_pointer_init
{
    $$ = ASTMake2(AST_RENAME, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| name
;
proc_pointer_init : data_ref
;
intrinsic_stmt : labeldef TOK_INTRINSIC ':' ':' intrinsic_procedure_name_list eos
{
    $$ = ASTMake2Label(AST_INTRINSIC_STATEMENT, $1, $5, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_INTRINSIC intrinsic_procedure_name_list eos
{
    $$ = ASTMake2Label(AST_INTRINSIC_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
;
function_reference : procedure_designator '(' actual_arg_spec_list ')'
{
    $$ = ASTMake2(AST_FUNCTION_CALL, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| procedure_designator '(' ')'
{
    $$ = ASTMake2(AST_FUNCTION_CALL, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
;
call_stmt : labeldef TOK_CALL function_reference eos
{
    ast_set_text($3, "call");
    $$ = ASTMake2Label(AST_EXPRESSION_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_CALL procedure_designator eos
{
    AST function_ref = ASTMake2(AST_FUNCTION_CALL, $3, NULL, ASTFileName($3), ASTLine($3), "call");
    $$ = ASTMake2Label(AST_EXPRESSION_STATEMENT, $1, function_ref, $2.token_file, $2.token_line, $2.token_text);
}
;
procedure_designator : data_ref_no_array
;
actual_arg_spec : name '=' actual_arg
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, $1, $3, ASTFileName($1), ASTLine($1), NULL);
}
| actual_arg
{
    $$ = ASTMake2(AST_NAMED_PAIR_SPEC, NULL, $1, ASTFileName($1), ASTLine($1), NULL);
}
;
actual_arg : expr
| alt_return_spec
;
alt_return_spec : '*' label
{
    $$ = ASTMake1(AST_ALTERNATE_RESULT_SPEC, $2, $1.token_file, $1.token_line, NULL);
}
;
prefix : prefix_spec_seq
;
prefix_spec : declaration_type_spec
{
    $$ = ASTMake1(AST_ATTR_SPEC, $1, ASTFileName($1), ASTLine($1), "__declaration__");
}
| TOK_ELEMENTAL
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_IMPURE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_MODULE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_PURE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
| TOK_RECURSIVE
{
    $$ = ASTLeaf(AST_ATTR_SPEC, $1.token_file, $1.token_line, $1.token_text);
}
;
function_subprogram : function_stmt program_body end_function_stmt
{
    $$ = ASTMake3(AST_FUNCTION_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
function_stmt : labeldef prefix TOK_FUNCTION name function_prototype eos
{
    $$ = ASTMake4Label(AST_FUNCTION_STATEMENT, $1, $2, $4, $5, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_FUNCTION name function_prototype eos
{
    $$ = ASTMake4Label(AST_FUNCTION_STATEMENT, $1, NULL, $3, $4, $2.token_file, $2.token_line, $2.token_text);
}
;
function_prototype : '(' dummy_arg_name_list_proto ')' suffix 
{
    $$ = ASTMake2(AST_FUNCTION_PROTOTYPE, $2, $4, $1.token_file, $1.token_line, NULL);
}
| '(' ')' suffix 
{
    $$ = ASTMake2(AST_FUNCTION_PROTOTYPE, NULL, $3, $1.token_file, $1.token_line, NULL);
}
| '(' dummy_arg_name_list_proto ')' 
{
    $$ = ASTMake2(AST_FUNCTION_PROTOTYPE, $2, NULL, $1.token_file, $1.token_line, NULL);
}
| '(' ')' 
{
    $$ = ASTMake2(AST_FUNCTION_PROTOTYPE, NULL, NULL, $1.token_file, $1.token_line, NULL);
}
;
suffix : proc_language_binding_spec TOK_RESULT '(' name ')'
{
    $$ = ASTMake2(AST_PROCEDURE_SUFFIX, $1, $4, ASTFileName($1), ASTLine($1), NULL);
}
| proc_language_binding_spec
{
    $$ = ASTMake2(AST_PROCEDURE_SUFFIX, $1, NULL, ASTFileName($1), ASTLine($1), NULL);
}
| TOK_RESULT '(' name ')' proc_language_binding_spec
{
    $$ = ASTMake2(AST_PROCEDURE_SUFFIX, $5, $3, $1.token_file, $1.token_line, NULL);
}
| TOK_RESULT '(' name ')'
{
    $$ = ASTMake2(AST_PROCEDURE_SUFFIX, NULL, $3, $1.token_file, $1.token_line, NULL);
}
;
end_function_stmt : labeldef TOK_END TOK_FUNCTION name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_END eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_END TOK_FUNCTION eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDFUNCTION name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDFUNCTION eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
subroutine_subprogram : subroutine_stmt program_body end_subroutine_stmt
{
    $$ = ASTMake3(AST_SUBROUTINE_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
subroutine_stmt : labeldef prefix TOK_SUBROUTINE name function_prototype eos
{
    $$ = ASTMake4Label(AST_SUBROUTINE_STATEMENT, $1, $2, $4, $5, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_SUBROUTINE name function_prototype eos
{
    $$ = ASTMake4Label(AST_SUBROUTINE_STATEMENT, $1, NULL, $3, $4, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef prefix TOK_SUBROUTINE name eos
{
    $$ = ASTMake4Label(AST_SUBROUTINE_STATEMENT, $1, $2, $4, NULL, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_SUBROUTINE name eos
{
    $$ = ASTMake4Label(AST_SUBROUTINE_STATEMENT, $1, NULL, $3, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
dummy_arg : name
| '*'
{
    $$ = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
}
;
end_subroutine_stmt : labeldef TOK_END TOK_SUBROUTINE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_END eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_END TOK_SUBROUTINE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_ENDSUBROUTINE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDSUBROUTINE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
separate_module_subprogram : mp_subprogram_stmt program_body end_mp_subprogram_stmt
{
    $$ = ASTMake3(AST_MODULE_PROCEDURE_PROGRAM_UNIT, $1, $2, $3, ASTFileName($1), ASTLine($1), NULL);
}
;
mp_subprogram_stmt : labeldef TOK_MODULE TOK_PROCEDURE name eos
{
    char c[] = "module procedure";
    sprintf(c, "%s %s", $2.token_text, $3.token_text);

    $$ = ASTMake2Label(AST_MODULE_PROCEDURE_STATEMENT, $1, $4, $2.token_file, $2.token_line, c);
}
;
end_mp_subprogram_stmt : labeldef TOK_END TOK_PROCEDURE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $4, $3.token_file, $3.token_line, $3.token_text);
}
| labeldef TOK_END eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_END TOK_PROCEDURE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $3.token_text);
}
| labeldef TOK_ENDPROCEDURE name eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENDPROCEDURE eos
{
    $$ = ASTMake2Label(AST_END_STATEMENT, $1, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
entry_stmt : labeldef TOK_ENTRY name '(' dummy_arg_list ')' suffix eos
{
    $$ = ASTMake4Label(AST_ENTRY_STATEMENT, $1, $3, $5, $7, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENTRY name eos
{
    $$ = ASTMake4Label(AST_ENTRY_STATEMENT, $1, $3, NULL, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENTRY name '(' ')' suffix eos
{
    $$ = ASTMake4Label(AST_ENTRY_STATEMENT, $1, $3, NULL, $6, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENTRY name '(' dummy_arg_list ')' eos
{
    $$ = ASTMake4Label(AST_ENTRY_STATEMENT, $1, $3, $5, NULL, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_ENTRY name '(' ')' eos
{
    $$ = ASTMake4Label(AST_ENTRY_STATEMENT, $1, $3, NULL, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
return_stmt : labeldef TOK_RETURN int_expr eos
{
    $$ = ASTMake3Label(AST_RETURN_STATEMENT, $1, NULL, $3, $2.token_file, $2.token_line, $2.token_text);
}
| labeldef TOK_RETURN eos
{
    $$ = ASTMake3Label(AST_RETURN_STATEMENT, $1, NULL, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;
contains_stmt : labeldef TOK_CONTAINS eos
{
    // EMPTY, this statement does nothing but act as a separator
}
;
stmt_function_stmt : labeldef name '(' dummy_arg_name_list ')' '=' expr eos
{
    $$ = ASTMake4Label(AST_STATEMENT_FUNCTION_STATEMENT, $1, $2, $4, $7, ASTFileName($2), ASTLine($2), NULL);
}
| labeldef name '(' ')' '=' expr eos
{
    $$ = ASTMake4Label(AST_STATEMENT_FUNCTION_STATEMENT, $1, $2, NULL, $6, ASTFileName($2), ASTLine($2), NULL);
}
;
eos : EOS
{
    // Do nothing
}
;
// Sequence rules
where_body_construct_seq : where_body_construct
{
  $$ = ASTListLeaf($1);
}
| where_body_construct_seq where_body_construct
{
  $$ = ASTList($1, $2);
}
;
mask_elsewhere_part_seq : mask_elsewhere_part
{
  $$ = ASTListLeaf($1);
}
| mask_elsewhere_part_seq mask_elsewhere_part
{
  $$ = ASTList($1, $2);
}
;
private_or_sequence_seq : private_or_sequence
{
  $$ = ASTListLeaf($1);
}
| private_or_sequence_seq private_or_sequence
{
  $$ = ASTList($1, $2);
}
;
prefix_spec_seq : prefix_spec
{
  $$ = ASTListLeaf($1);
}
| prefix_spec_seq prefix_spec
{
  $$ = ASTList($1, $2);
}
;
forall_body_construct_seq : forall_body_construct
{
  $$ = ASTListLeaf($1);
}
| forall_body_construct_seq forall_body_construct
{
  $$ = ASTList($1, $2);
}
;
type_bound_proc_binding_seq : type_bound_proc_binding
{
  $$ = ASTListLeaf($1);
}
| type_bound_proc_binding_seq type_bound_proc_binding
{
  $$ = ASTList($1, $2);
}
;
type_param_def_stmt_seq : type_param_def_stmt
{
  $$ = ASTListLeaf($1);
}
| type_param_def_stmt_seq type_param_def_stmt
{
  $$ = ASTList($1, $2);
}
;
program_unit_seq : program_unit
{
  $$ = ASTListLeaf($1);
}
| program_unit_seq program_unit
{
  $$ = ASTList($1, $2);
}
;
type_guard_part_seq : type_guard_part
{
  $$ = ASTListLeaf($1);
}
| type_guard_part_seq type_guard_part
{
  $$ = ASTList($1, $2);
}
;
component_def_stmts_seq : component_def_stmts
{
  $$ = ASTListLeaf($1);
}
| component_def_stmts_seq component_def_stmts
{
  $$ = ASTList($1, $2);
}
;
module_subprogram_seq : module_subprogram
{
  $$ = ASTListLeaf($1);
}
| module_subprogram_seq module_subprogram
{
  $$ = ASTList($1, $2);
}
;
interface_specification_seq : interface_specification
{
  $$ = ASTListLeaf($1);
}
| interface_specification_seq interface_specification
{
  $$ = ASTList($1, $2);
}
;
internal_subprogram_seq : internal_subprogram
{
  $$ = ASTListLeaf($1);
}
| internal_subprogram_seq internal_subprogram
{
  $$ = ASTList($1, $2);
}
;
enumerator_def_stmt_seq : enumerator_def_stmt
{
  $$ = ASTListLeaf($1);
}
| enumerator_def_stmt_seq enumerator_def_stmt
{
  $$ = ASTList($1, $2);
}
;
// List rules

a_list_of_names : name
{
    $$ = ASTListLeaf($1);
}
| a_list_of_names ',' name
{
    $$ = ASTList($1, $3);
}
;

type_param_name_list : a_list_of_names;
external_name_list : a_list_of_names;
entity_name_list : a_list_of_names;
binding_name_list : a_list_of_names;
object_name_list : a_list_of_names;
final_subroutine_name_list : a_list_of_names;
procedure_name_list : a_list_of_names;
intrinsic_procedure_name_list : a_list_of_names;
dummy_arg_name_list : a_list_of_names;
dummy_arg_name_list_proto : a_list_of_names 
| a_list_of_names ',' '*'
{
    AST symbol = ASTLeaf(AST_SYMBOL, $3.token_file, $3.token_line, $3.token_text);
    $$ = ASTList($1, symbol);
}
| '*'
{
    AST symbol = ASTLeaf(AST_SYMBOL, $1.token_file, $1.token_line, $1.token_text);
    $$ = ASTListLeaf(symbol);
};
import_name_list : a_list_of_names;

data_stmt_set_list : data_stmt_set
{
  $$ = ASTListLeaf($1);
}
| data_stmt_set_list ',' data_stmt_set
{
  $$ = ASTList($1, $3);
}
| data_stmt_set_list data_stmt_set
{
  $$ = ASTList($1, $2);
}
;

position_spec_list : position_spec
{
  $$ = ASTListLeaf($1);
}
| position_spec_list ',' position_spec
{
  $$ = ASTList($1, $3);
}
;
equivalence_set_list : equivalence_set
{
  $$ = ASTListLeaf($1);
}
| equivalence_set_list ',' equivalence_set
{
  $$ = ASTList($1, $3);
}
;
lock_stat_list : lock_stat
{
  $$ = ASTListLeaf($1);
}
| lock_stat_list ',' lock_stat
{
  $$ = ASTList($1, $3);
}
;
close_spec_list : close_spec
{
  $$ = ASTListLeaf($1);
}
| close_spec_list ',' close_spec
{
  $$ = ASTList($1, $3);
}
;
type_attr_spec_list : type_attr_spec
{
  $$ = ASTListLeaf($1);
}
| type_attr_spec_list ',' type_attr_spec
{
  $$ = ASTList($1, $3);
}
;
io_implied_do_object_list : io_implied_do_object
{
  $$ = ASTListLeaf($1);
}
| io_implied_do_object_list ',' io_implied_do_object
{
  $$ = ASTList($1, $3);
}
;
case_value_range_list : case_value_range
{
  $$ = ASTListLeaf($1);
}
| case_value_range_list ',' case_value_range
{
  $$ = ASTList($1, $3);
}
;
namelist_group_object_list : namelist_group_object
{
  $$ = ASTListLeaf($1);
}
| namelist_group_object_list ',' namelist_group_object
{
  $$ = ASTList($1, $3);
}
;
sync_stat_list : sync_stat
{
  $$ = ASTListLeaf($1);
}
| sync_stat_list ',' sync_stat
{
  $$ = ASTList($1, $3);
}
;
implicit_spec_list : implicit_spec
{
  $$ = ASTListLeaf($1);
}
| implicit_spec_list ',' implicit_spec
{
  $$ = ASTList($1, $3);
}
;
letter_spec_list : letter_spec
{
  $$ = ASTListLeaf($1);
}
| letter_spec_list ',' letter_spec
{
  $$ = ASTList($1, $3);
}
;
data_stmt_object_list : data_stmt_object
{
  $$ = ASTListLeaf($1);
}
| data_stmt_object_list ',' data_stmt_object
{
  $$ = ASTList($1, $3);
}
;
component_decl_list : component_decl
{
  $$ = ASTListLeaf($1);
}
| component_decl_list ',' component_decl
{
  $$ = ASTList($1, $3);
}
;
label_list : label
{
  $$ = ASTListLeaf($1);
}
| label_list ',' label
{
  $$ = ASTList($1, $3);
}
;
named_constant_def_list : named_constant_def
{
  $$ = ASTListLeaf($1);
}
| named_constant_def_list ',' named_constant_def
{
  $$ = ASTList($1, $3);
}
;
bind_entity_list : bind_entity
{
  $$ = ASTListLeaf($1);
}
| bind_entity_list ',' bind_entity
{
  $$ = ASTList($1, $3);
}
;
flush_spec_list : flush_spec
{
  $$ = ASTListLeaf($1);
}
| flush_spec_list ',' flush_spec
{
  $$ = ASTList($1, $3);
}
;
io_control_spec_list : io_control_spec
{
  $$ = ASTListLeaf($1);
}
| io_control_spec_list ',' io_control_spec
{
  $$ = ASTList($1, $3);
}
;
proc_component_attr_spec_list : proc_component_attr_spec
{
  $$ = ASTListLeaf($1);
}
| proc_component_attr_spec_list ',' proc_component_attr_spec
{
  $$ = ASTList($1, $3);
}
;
saved_entity_list : saved_entity
{
  $$ = ASTListLeaf($1);
}
| saved_entity_list ',' saved_entity
{
  $$ = ASTList($1, $3);
}
;
input_output_item_list : input_output_item
{
  $$ = ASTListLeaf($1);
}
| input_output_item_list ',' input_output_item
{
  $$ = ASTList($1, $3);
}
;
common_block_object_list : common_block_object
{
  $$ = ASTListLeaf($1);
}
| common_block_object_list ',' common_block_object
{
  $$ = ASTList($1, $3);
}
;
codimension_decl_list : codimension_decl
{
  $$ = ASTListLeaf($1);
}
| codimension_decl_list ',' codimension_decl
{
  $$ = ASTList($1, $3);
}
;
component_spec_list : component_spec
{
  $$ = ASTListLeaf($1);
}
| component_spec_list ',' component_spec
{
  $$ = ASTList($1, $3);
}
;
only_list : only
{
  $$ = ASTListLeaf($1);
}
| only_list ',' only
{
  $$ = ASTList($1, $3);
}
;
binding_attr_list : binding_attr
{
  $$ = ASTListLeaf($1);
}
| binding_attr_list ',' binding_attr
{
  $$ = ASTList($1, $3);
}
;
forall_triplet_spec_list : forall_triplet_spec
{
  $$ = ASTListLeaf($1);
}
| forall_triplet_spec_list ',' forall_triplet_spec
{
  $$ = ASTList($1, $3);
}
;
alloc_opt_list : alloc_opt
{
  $$ = ASTListLeaf($1);
}
| alloc_opt_list ',' alloc_opt
{
  $$ = ASTList($1, $3);
}
;
pointer_object_list : pointer_object
{
  $$ = ASTListLeaf($1);
}
| pointer_object_list ',' pointer_object
{
  $$ = ASTList($1, $3);
}
;
type_param_decl_list : type_param_decl
{
  $$ = ASTListLeaf($1);
}
| type_param_decl_list ',' type_param_decl
{
  $$ = ASTList($1, $3);
}
;
connect_spec_list : connect_spec
{
  $$ = ASTListLeaf($1);
}
| connect_spec_list ',' connect_spec
{
  $$ = ASTList($1, $3);
}
;
section_subscript_list : section_subscript
{
  $$ = ASTListLeaf($1);
}
| section_subscript_list ',' section_subscript
{
  $$ = ASTList($1, $3);
}
;
pointer_decl_list : pointer_decl
{
  $$ = ASTListLeaf($1);
}
| pointer_decl_list ',' pointer_decl
{
  $$ = ASTList($1, $3);
}
;
component_attr_spec_list : component_attr_spec
{
  $$ = ASTListLeaf($1);
}
| component_attr_spec_list ',' component_attr_spec
{
  $$ = ASTList($1, $3);
}
;
enumerator_list : enumerator
{
  $$ = ASTListLeaf($1);
}
| enumerator_list ',' enumerator
{
  $$ = ASTList($1, $3);
}
;
data_i_do_object_list : data_i_do_object
{
  $$ = ASTListLeaf($1);
}
| data_i_do_object_list ',' data_i_do_object
{
  $$ = ASTList($1, $3);
}
;
type_bound_proc_decl_list : type_bound_proc_decl
{
  $$ = ASTListLeaf($1);
}
| type_bound_proc_decl_list ',' type_bound_proc_decl
{
  $$ = ASTList($1, $3);
}
;
wait_spec_list : wait_spec
{
  $$ = ASTListLeaf($1);
}
| wait_spec_list ',' wait_spec
{
  $$ = ASTList($1, $3);
}
;
cosubscript_list : cosubscript
{
  $$ = ASTListLeaf($1);
}
| cosubscript_list ',' cosubscript
{
  $$ = ASTList($1, $3);
}
;
type_param_spec_list : type_param_spec
{
  $$ = ASTListLeaf($1);
}
| type_param_spec_list ',' type_param_spec
{
  $$ = ASTList($1, $3);
}
;
allocation_list : allocation
{
  $$ = ASTListLeaf($1);
}
| allocation_list ',' allocation
{
  $$ = ASTList($1, $3);
}
;
allocate_object_list : allocate_object
{
  $$ = ASTListLeaf($1);
}
| allocate_object_list ',' allocate_object
{
  $$ = ASTList($1, $3);
}
;
proc_attr_spec_list : proc_attr_spec
{
  $$ = ASTListLeaf($1);
}
| proc_attr_spec_list ',' proc_attr_spec
{
  $$ = ASTList($1, $3);
}
;
proc_decl_list : proc_decl
{
  $$ = ASTListLeaf($1);
}
| proc_decl_list ',' proc_decl
{
  $$ = ASTList($1, $3);
}
;
data_stmt_value_list : data_stmt_value
{
  $$ = ASTListLeaf($1);
}
| data_stmt_value_list ',' data_stmt_value
{
  $$ = ASTList($1, $3);
}
;
ac_value_list : ac_value
{
  $$ = ASTListLeaf($1);
}
| ac_value_list ',' ac_value
{
  $$ = ASTList($1, $3);
}
;
association_list : association
{
  $$ = ASTListLeaf($1);
}
| association_list ',' association
{
  $$ = ASTList($1, $3);
}
;
dummy_arg_list : dummy_arg
{
  $$ = ASTListLeaf($1);
}
| dummy_arg_list ',' dummy_arg
{
  $$ = ASTList($1, $3);
}
;
equivalence_object_list : equivalence_object
{
  $$ = ASTListLeaf($1);
}
| equivalence_object_list ',' equivalence_object
{
  $$ = ASTList($1, $3);
}
;
allocatable_decl_list : allocatable_decl
{
  $$ = ASTListLeaf($1);
}
| allocatable_decl_list ',' allocatable_decl
{
  $$ = ASTList($1, $3);
}
;
inquire_spec_list : inquire_spec
{
  $$ = ASTListLeaf($1);
}
| inquire_spec_list ',' inquire_spec
{
  $$ = ASTList($1, $3);
}
;
dealloc_opt_list : dealloc_opt
{
  $$ = ASTListLeaf($1);
}
| dealloc_opt_list ',' dealloc_opt
{
  $$ = ASTList($1, $3);
}
;
actual_arg_spec_list : actual_arg_spec
{
  $$ = ASTListLeaf($1);
}
| actual_arg_spec_list ',' actual_arg_spec
{
  $$ = ASTList($1, $3);
}
;
rename_list : rename
{
  $$ = ASTListLeaf($1);
}
| rename_list ',' rename
{
  $$ = ASTList($1, $3);
}
;
attr_spec_list : attr_spec
{
  $$ = ASTListLeaf($1);
}
| attr_spec_list ',' attr_spec
{
  $$ = ASTList($1, $3);
}
;
target_decl_list : target_decl
{
  $$ = ASTListLeaf($1);
}
| target_decl_list ',' target_decl
{
  $$ = ASTList($1, $3);
}
;
access_id_list : access_id
{
  $$ = ASTListLeaf($1);
}
| access_id_list ',' access_id
{
  $$ = ASTList($1, $3);
}
;
array_name_dim_spec_list : array_name_dim_spec
{
  $$ = ASTListLeaf($1);
}
| array_name_dim_spec_list ',' array_name_dim_spec
{
  $$ = ASTList($1, $3);
}
;
entity_decl_list : entity_decl
{
  $$ = ASTListLeaf($1);
}
| entity_decl_list ',' entity_decl
{
  $$ = ASTList($1, $3);
}
;
namelist_item_list : namelist_item
{
  $$ = ASTListLeaf($1);
}
| namelist_item_list ',' namelist_item
{
  $$ = ASTList($1, $3);
}
;
// Keywords
keyword : TOK_FORMAT
| TOK_GENERIC
| TOK_VOLATILE
| TOK_EQUIVALENCE
| TOK_EOR
| TOK_PROTECTED
| TOK_PAD
| TOK_FILE
| TOK_UNFORMATTED
| TOK_NAMED
| TOK_SUBROUTINE
| TOK_OPENED
| TOK_DELIM
| TOK_SOURCE
| TOK_CRITICAL
| TOK_ACTION
| TOK_IMPORT
| TOK_BLOCK
| TOK_ENUM
| TOK_OVERRIDABLE
| TOK_MODULE
| TOK_SIGN
| TOK_EXTENDS
| TOK_PASS
| TOK_GO
| TOK_ENTRY
| TOK_WHERE
| TOK_PROCEDURE
| TOK_NAME
| TOK_DOUBLE
| TOK_CONTAINS
| TOK_LOGICAL
| TOK_NEWUNIT
| TOK_NULLIFY
| TOK_DEFERRED
| TOK_ONLY
| TOK_EXIST
| TOK_INTERFACE
| TOK_SAVE
| TOK_ADVANCE
| TOK_STAT
| TOK_RETURN
| TOK_READWRITE
| TOK_ASSIGN
| TOK_ASSIGNMENT
| TOK_PRINT
| TOK_IOSTAT
| TOK_SYNC
| TOK_COMPLEX
| TOK_ASYNCHRONOUS
| TOK_IMAGES
| TOK_END
| TOK_FINAL
| TOK_INOUT
| TOK_NEXTREC
| TOK_KIND
| TOK_COMMON
| TOK_BLANK
| TOK_IOLENGTH
| TOK_INTEGER
| TOK_DEALLOCATE
| TOK_FUNCTION
| TOK_C
| TOK_ENUMERATOR
| TOK_RECURSIVE
| TOK_SEQUENCE
| TOK_INQUIRE
| TOK_FLUSH
| TOK_ELSE
| TOK_INTENT
| TOK_EXTERNAL
| TOK_OPERATOR
| TOK_OPTIONAL
| TOK_UNIT
| TOK_SIZE
| TOK_NOPASS
| TOK_TYPE
| TOK_MOLD
| TOK_PRECISION
| TOK_PENDING
| TOK_CONTINUE
| TOK_RESULT
| TOK_REAL
| TOK_THEN
| TOK_STREAM
| TOK_DO
| TOK_DEFAULT
| TOK_CONTIGUOUS
| TOK_STOP
| TOK_WHILE
| TOK_PROGRAM
| TOK_REC
| TOK_OPEN
| TOK_CASE
| TOK_RECL
| TOK_DIMENSION
| TOK_ELEMENTAL
| TOK_FORALL
| TOK_POSITION
| TOK_FMT
| TOK_READ
| TOK_OUT
| TOK_LOCK
| TOK_DECIMAL
| TOK_SELECT
| TOK_SELECTCASE
| TOK_DIRECT
| TOK_WRITE
| TOK_CODIMENSION
| TOK_CLOSE
| TOK_ID
| TOK_WAIT
| TOK_ALL
| TOK_ELSEWHERE
| TOK_LEN
| TOK_IMPURE
| TOK_EXIT
| TOK_REWIND
| TOK_BACKSPACE
| TOK_NML
| TOK_INTRINSIC
| TOK_PUBLIC
| TOK_ERRMSG
| TOK_NAMELIST
| TOK_USE
| TOK_SUBMODULE
| TOK_ERR
| TOK_ENCODING
| TOK_ACQUIRED
| TOK_ABSTRACT
| TOK_CHARACTER
| TOK_NUMBER
| TOK_CONCURRENT
| TOK_ENDFILE
| TOK_PARAMETER
| TOK_DATA
| TOK_POS
| TOK_PRIVATE
| TOK_ROUND
| TOK_TO
| TOK_SEQUENTIAL
| TOK_ALLOCATE
| TOK_TARGET
| TOK_CLASS
| TOK_CYCLE
| TOK_STATUS
| TOK_IOMSG
| TOK_FORM
| TOK_IS
| TOK_NONE
| TOK_VALUE
| TOK_UNLOCK
| TOK_FORMATTED
| TOK_IN
| TOK_IMPLICIT
| TOK_IF
| TOK_ASSOCIATE
| TOK_BIND
| TOK_ALLOCATABLE
| TOK_ACCESS
| TOK_CALL
| TOK_PURE
| TOK_MEMORY
| TOK_POINTER
| TOK_ALLSTOP
| TOK_ENDIF
| TOK_ENDFUNCTION
| TOK_ENDDO
| TOK_BLOCKDATA 
| TOK_ENDMODULE
| TOK_DOUBLEPRECISION 
| TOK_ENDINTERFACE
| TOK_ELSEIF 
| TOK_ENDPROCEDURE
| TOK_ENDPROGRAM
| TOK_ENDASSOCIATE
| TOK_ENDSELECT
| TOK_ENDBLOCK
| TOK_ENDSUBMODULE
| TOK_ENDBLOCKDATA
| TOK_ENDSUBROUTINE
| TOK_ENDCRITICAL
| TOK_ENDTYPE
| TOK_VECTOR
| TOK_PAUSE
| TOK_PIXEL
| TOK_DOUBLECOMPLEX
| TOK_GOTO
;

labeldef : label
|  /* empty */
{
    $$ = NULL;
}
;














program : subparsing
{
    *parsed_tree = $1;
}
;

subparsing : SUBPARSE_STATEMENT block
{
    $$ = $2;
}
| SUBPARSE_EXPRESSION expr
{
    $$ = $2;
}
| SUBPARSE_PROGRAM_UNIT program_unit
{
    $$ = $2;
}
;























































// Grammar entry point
































non_top_level_program_unit_stmts: pragma_custom_construct_statement
{
    $$ = $1;
}
| pragma_custom_directive
{
    $$ = $1;
}
;
program_unit : pragma_custom_construct_program_unit
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





















pragma_custom_construct_statement : PRAGMA_CUSTOM pragma_custom_line_construct pragma_custom_construct_range
{
	$$ = ASTMake3(AST_PRAGMA_CUSTOM_CONSTRUCT, $2, $3[0], $3[1], $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM pragma_custom_noend_line_construct pragma_custom_noend_construct_range
{
	$$ = ASTMake3(AST_PRAGMA_CUSTOM_CONSTRUCT, $2, $3[0], $3[1], $1.token_file, $1.token_line, $1.token_text);
}
;

// This case allows a sequence of statements but forces a end construct to appear
pragma_custom_construct_range : block pragma_custom_end_construct
{
    $$[0] = $1;
    $$[1] = $2;
}
;

// These cases only allows a single statements but does not require an end construct to appear
pragma_custom_noend_construct_range : non_top_level_program_unit_stmts pragma_custom_end_construct
{
    $$[0] = $1;
    $$[1] = $2;
}
| non_top_level_program_unit_stmts
{
    $$[0] = $1;
    $$[1] = NULL;
}
;

pragma_custom_end_construct : PRAGMA_CUSTOM PRAGMA_CUSTOM_END_CONSTRUCT pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $3, NULL, $2.token_file, $2.token_line, $2.token_text);
}
;

pragma_custom_construct_program_unit : PRAGMA_CUSTOM pragma_custom_line_construct program_unit
{
	$$ = ASTMake3(AST_PRAGMA_CUSTOM_CONSTRUCT, $2, $3, NULL, $1.token_file, $1.token_line, $1.token_text);
}
;

pragma_custom_noend_line_construct : PRAGMA_CUSTOM_CONSTRUCT_NOEND pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $2, NULL, $1.token_file, $1.token_line, $1.token_text);
}
| PRAGMA_CUSTOM_CONSTRUCT_NOEND '(' pragma_clause_arg_list ')' pragma_custom_clause_opt_seq PRAGMA_CUSTOM_NEWLINE
{
	$$ = ASTMake2(AST_PRAGMA_CUSTOM_LINE, $5, $3, $1.token_file, $1.token_line, $1.token_text);
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































%%




// Used in fortran-driver.c to determine the maximum size for parser memory
unsigned long long limit_for_parse_memory = SIZE_MAX / sizeof(yyGLRStackItem);

extern char* yytext;
extern char* actual_line;
void yyerror(AST* parsed_tree UNUSED_PARAMETER, const char* c)
{
	fprintf(stderr, "%s:%d: error: %s\n", fortran_scanning_now->current_filename, fortran_scanning_now->line_number, c);
}
