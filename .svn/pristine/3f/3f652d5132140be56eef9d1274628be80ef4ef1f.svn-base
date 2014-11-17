/* This file is self-generated. DO NOT MODIFY */
/* Changes to cxx-nodecl.def will update this file */

#include "cxx-ast.h"
#include "cxx-asttype.h"
#include "cxx-utils.h"
#include "cxx-exprtype.h"

static void nodecl_check_tree_catch_handler(AST);
static void nodecl_check_tree_pragma_clause_arg(AST);
static void nodecl_check_tree_name(AST);
static void nodecl_check_tree_complex_part(AST);
static void nodecl_check_tree_object_init(AST);
static void nodecl_check_tree_c_cxx_expressions(AST);
static void nodecl_check_tree_expression(AST);
static void nodecl_check_tree_nodecl(AST);
static void nodecl_check_tree_pragma_directive(AST);
static void nodecl_check_tree_argument(AST);
static void nodecl_check_tree_c_cxx_only_statements(AST);
static void nodecl_check_tree_literal(AST);
static void nodecl_check_tree_fortran_expressions(AST);
static void nodecl_check_tree_statement(AST);
static void nodecl_check_tree_function_code(AST);
static void nodecl_check_tree_top_level(AST);
static void nodecl_check_tree_loop_control(AST);
static void nodecl_check_tree_fortran_only_statements(AST);
static void nodecl_check_tree_pragma_line(AST);
static void nodecl_check_tree_subscript(AST);
static void nodecl_check_tree_pragma_custom_clause(AST);

static void nodecl_check_tree_catch_handler(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_CATCH_HANDLER :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_pragma_clause_arg(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_PRAGMA_CLAUSE_ARG :
{
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_name(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_SYMBOL :
{
   ERROR_CONDITION(expression_get_symbol(a) == NULL, "Tree lacks a symbol", 0);
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_complex_part(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_PLUS :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_FLOATING_LITERAL : 
        case AST_COMPLEX_LITERAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_STRING_LITERAL : 
        case AST_DECIMAL_LITERAL : 
        {
               nodecl_check_tree_literal(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_NEG :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_FLOATING_LITERAL : 
        case AST_COMPLEX_LITERAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_STRING_LITERAL : 
        case AST_DECIMAL_LITERAL : 
        {
               nodecl_check_tree_literal(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_object_init(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_OBJECT_INIT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_c_cxx_expressions(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_CONDITIONAL_EXPRESSION :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon2(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon2(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_POINTER_TO_MEMBER :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_REFERENCE :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_DERREFERENCE :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_THROW_EXPRESSION :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_expression(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
   switch (ASTType(a))
   {
        case AST_FLOATING_LITERAL : 
        case AST_COMPLEX_LITERAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_STRING_LITERAL : 
        case AST_DECIMAL_LITERAL : 
        {
               nodecl_check_tree_literal(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(a))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
case AST_FUNCTION_CALL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
AST it;
for_each_element(ASTSon1(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_NAMED_PAIR_SPEC : 
        {
               nodecl_check_tree_argument(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
  break;
}
case AST_ARRAY_SUBSCRIPT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
AST it;
for_each_element(ASTSon1(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_SUBSCRIPT_TRIPLET : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_subscript(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
  break;
}
case AST_CLASS_MEMBER_ACCESS :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_PLUS :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_NEG :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_MULT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_POWER :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_DIV :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_ADD :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_MINUS :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_CONCAT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_EQUAL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_DIFFERENT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_LOWER_THAN :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_LOWER_OR_EQUAL_THAN :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_GREATER_THAN :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_GREATER_OR_EQUAL_THAN :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_NOT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_LOGICAL_AND :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_LOGICAL_OR :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_COMPLEMENT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_BITWISE_AND :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_BITWISE_OR :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_BITWISE_XOR :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_SHL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_SHR :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_ASSIGNMENT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_PARENTHESIZED_EXPRESSION :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
   switch (ASTType(a))
   {
        case AST_DERREFERENCE : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_THROW_EXPRESSION : 
        case AST_POINTER_TO_MEMBER : 
        case AST_REFERENCE : 
        {
               nodecl_check_tree_c_cxx_expressions(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(a))
   {
        case AST_PTR_ASSIGNMENT : 
        {
               nodecl_check_tree_fortran_expressions(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_nodecl(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
AST it;
for_each_element(a, it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_FUNCTION_CODE : 
        case AST_OBJECT_INIT : 
        {
               nodecl_check_tree_top_level(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_pragma_directive(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_PRAGMA_CUSTOM_DIRECTIVE :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_PRAGMA_CUSTOM_LINE : 
        {
               nodecl_check_tree_pragma_line(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_argument(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_NAMED_PAIR_SPEC :
{
if (ASTSon0(a) != NULL)
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_c_cxx_only_statements(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_TRY_BLOCK :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
AST it;
for_each_element(ASTSon1(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_CATCH_HANDLER : 
        {
               nodecl_check_tree_catch_handler(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_literal(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_DECIMAL_LITERAL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
  break;
}
case AST_FLOATING_LITERAL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
  break;
}
case AST_COMPLEX_LITERAL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_PLUS : 
        {
               nodecl_check_tree_complex_part(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_PLUS : 
        {
               nodecl_check_tree_complex_part(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_STRING_LITERAL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
  break;
}
case AST_BOOLEAN_LITERAL :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_fortran_expressions(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_PTR_ASSIGNMENT :
{
   ERROR_CONDITION(expression_get_type(a) == NULL, "Tree lacks a type", 0);
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_statement(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_EXPRESSION_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_COMPOUND_STATEMENT :
{
if (ASTSon0(a) != NULL)
{
AST it;
for_each_element(ASTSon0(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
}
  break;
}
case AST_DO_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_WHILE_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_FOR_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_LOOP_CONTROL : 
        {
               nodecl_check_tree_loop_control(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_IF_ELSE_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
if (ASTSon2(a) != NULL)
{
   switch (ASTType(ASTSon2(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon2(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
  break;
}
case AST_LABELED_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_SWITCH_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_DEFAULT_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_CASE_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_BREAK_STATEMENT :
{
  break;
}
case AST_CONTINUE_STATEMENT :
{
  break;
}
case AST_GOTO_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
case AST_RETURN_STATEMENT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
   switch (ASTType(a))
   {
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        {
               nodecl_check_tree_pragma_directive(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
case AST_PRAGMA_CUSTOM_CONSTRUCT :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        {
               nodecl_check_tree_pragma_directive(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
   switch (ASTType(a))
   {
        case AST_TRY_BLOCK : 
        {
               nodecl_check_tree_c_cxx_only_statements(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(a))
   {
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_READ_STATEMENT : 
        case AST_OPEN_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        {
               nodecl_check_tree_fortran_only_statements(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_function_code(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_FUNCTION_CODE :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_SYMBOL : 
        {
               nodecl_check_tree_name(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
AST it;
for_each_element(ASTSon1(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_READ_STATEMENT : 
        case AST_CLOSE_STATEMENT : 
        case AST_PRAGMA_CUSTOM_DIRECTIVE : 
        case AST_LABELED_STATEMENT : 
        case AST_DEFAULT_STATEMENT : 
        case AST_PAUSE_STATEMENT : 
        case AST_EXPRESSION_STATEMENT : 
        case AST_COMPOUND_STATEMENT : 
        case AST_RETURN_STATEMENT : 
        case AST_PRAGMA_CUSTOM_CONSTRUCT : 
        case AST_TRY_BLOCK : 
        case AST_OPEN_STATEMENT : 
        case AST_ALLOCATE_STATEMENT : 
        case AST_IO_STATEMENT : 
        case AST_LABEL_ASSIGN_STATEMENT : 
        case AST_ARITHMETIC_IF_STATEMENT : 
        case AST_CONTINUE_STATEMENT : 
        case AST_IF_ELSE_STATEMENT : 
        case AST_CASE_STATEMENT : 
        case AST_WRITE_STATEMENT : 
        case AST_ASSIGNED_GOTO_STATEMENT : 
        case AST_STOP_STATEMENT : 
        case AST_BREAK_STATEMENT : 
        case AST_GOTO_STATEMENT : 
        case AST_FOR_STATEMENT : 
        case AST_COMPUTED_GOTO_STATEMENT : 
        case AST_DO_STATEMENT : 
        case AST_DEALLOCATE_STATEMENT : 
        case AST_PRINT_STATEMENT : 
        case AST_WHILE_STATEMENT : 
        case AST_SWITCH_STATEMENT : 
        case AST_NULLIFY_STATEMENT : 
        {
               nodecl_check_tree_statement(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
if (ASTSon2(a) != NULL)
{
   switch (ASTType(ASTSon2(a)))
   {
        case AST_FUNCTION_CODE : 
        {
               nodecl_check_tree_function_code(ASTSon2(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_top_level(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
   switch (ASTType(a))
   {
        case AST_FUNCTION_CODE : 
        {
               nodecl_check_tree_function_code(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(a))
   {
        case AST_OBJECT_INIT : 
        {
               nodecl_check_tree_object_init(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_loop_control(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_LOOP_CONTROL :
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
   switch (ASTType(ASTSon2(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon2(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_fortran_only_statements(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_ALLOCATE_STATEMENT :
{
  break;
}
case AST_ARITHMETIC_IF_STATEMENT :
{
  break;
}
case AST_ASSIGNED_GOTO_STATEMENT :
{
  break;
}
case AST_CLOSE_STATEMENT :
{
  break;
}
case AST_COMPUTED_GOTO_STATEMENT :
{
  break;
}
case AST_DEALLOCATE_STATEMENT :
{
  break;
}
case AST_IO_STATEMENT :
{
  break;
}
case AST_LABEL_ASSIGN_STATEMENT :
{
  break;
}
case AST_NULLIFY_STATEMENT :
{
  break;
}
case AST_OPEN_STATEMENT :
{
  break;
}
case AST_PRINT_STATEMENT :
{
  break;
}
case AST_READ_STATEMENT :
{
  break;
}
case AST_RETURN_STATEMENT :
{
  break;
}
case AST_STOP_STATEMENT :
{
  break;
}
case AST_PAUSE_STATEMENT :
{
  break;
}
case AST_WRITE_STATEMENT :
{
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_pragma_line(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_PRAGMA_CUSTOM_LINE :
{
if (ASTSon0(a) != NULL)
{
AST it;
for_each_element(ASTSon0(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_PRAGMA_CLAUSE_ARG : 
        {
               nodecl_check_tree_pragma_clause_arg(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
}
if (ASTSon1(a) != NULL)
{
AST it;
for_each_element(ASTSon1(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_PRAGMA_CUSTOM_CLAUSE : 
        {
               nodecl_check_tree_pragma_custom_clause(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
}
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_subscript(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
   switch (ASTType(a))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(a);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
case AST_SUBSCRIPT_TRIPLET :
{
if (ASTSon0(a) != NULL)
{
   switch (ASTType(ASTSon0(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon0(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
if (ASTSon1(a) != NULL)
{
   switch (ASTType(ASTSon1(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon1(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
if (ASTSon2(a) != NULL)
{
   switch (ASTType(ASTSon2(a)))
   {
        case AST_NEG : 
        case AST_COMPLEMENT : 
        case AST_POWER : 
        case AST_NOT : 
        case AST_GREATER_THAN : 
        case AST_CONCAT : 
        case AST_LOWER_THAN : 
        case AST_REFERENCE : 
        case AST_LOWER_OR_EQUAL_THAN : 
        case AST_CONDITIONAL_EXPRESSION : 
        case AST_EQUAL : 
        case AST_BOOLEAN_LITERAL : 
        case AST_PLUS : 
        case AST_PARENTHESIZED_EXPRESSION : 
        case AST_ASSIGNMENT : 
        case AST_GREATER_OR_EQUAL_THAN : 
        case AST_SYMBOL : 
        case AST_BITWISE_OR : 
        case AST_MULT : 
        case AST_STRING_LITERAL : 
        case AST_DIFFERENT : 
        case AST_DERREFERENCE : 
        case AST_THROW_EXPRESSION : 
        case AST_ARRAY_SUBSCRIPT : 
        case AST_SHL : 
        case AST_DIV : 
        case AST_BITWISE_XOR : 
        case AST_SHR : 
        case AST_LOGICAL_OR : 
        case AST_BITWISE_AND : 
        case AST_ADD : 
        case AST_MINUS : 
        case AST_FLOATING_LITERAL : 
        case AST_PTR_ASSIGNMENT : 
        case AST_LOGICAL_AND : 
        case AST_POINTER_TO_MEMBER : 
        case AST_DECIMAL_LITERAL : 
        case AST_CLASS_MEMBER_ACCESS : 
        case AST_COMPLEX_LITERAL : 
        case AST_FUNCTION_CALL : 
        {
               nodecl_check_tree_expression(ASTSon2(a));
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
static void nodecl_check_tree_pragma_custom_clause(AST a)
{
   ERROR_CONDITION(a == NULL, "Invalid null tree", 0);
   switch (ASTType(a))
   {
case AST_PRAGMA_CUSTOM_CLAUSE :
{
if (ASTSon0(a) != NULL)
{
AST it;
for_each_element(ASTSon0(a), it)
{
   AST e = ASTSon1(it);
   switch (ASTType(e))
   {
        case AST_PRAGMA_CLAUSE_ARG : 
        {
               nodecl_check_tree_pragma_clause_arg(e);
               break;
        }
        default:
        {
           internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
           break;
        }
   }
}
}
  break;
}
     default:
     {
        internal_error("Invalid tree kind '%s'", ast_print_node_type(ASTType(a)));
        break;
     }
   }
}
void nodecl_check_tree(AST a)
{
   nodecl_check_tree_nodecl(a);
}
