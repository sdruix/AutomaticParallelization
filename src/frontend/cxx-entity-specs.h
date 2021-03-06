/* This file has been generated by gen-symbols-attrs.py. */
/* Do not modify it or you'll get what you deserve */

#ifndef CXX_ENTITY_SPECIFIERS_H
#define CXX_ENTITY_SPECIFIERS_H

// Include this file only from cxx-scope-decls.h and not from anywhere else

typedef struct entity_specifiers_tag
{
    // States if this is a static (or SAVEd) variable
    char is_static:1;
    // States if this is a register variable
    char is_register:1;
    // The symbol has an explicit extern linkage
    char is_extern:1;
    // The symbol is a mutable entity of a const-class
    char is_mutable:1;
    // This is an exported template. Not used at all
    char is_export:1;
    // The function has been explicitly set as inline
    char is_inline:1;
    // The function is virtual
    char is_virtual:1;
    // The function has been defined as pure virtual
    char is_pure:1;
    // States that this is a builtin symbol of the compiler
    char is_builtin:1;
    // This function has been deleted (C++1x)
    char is_deleted:1;
    // This function has been defined as default (C++1x)
    char is_defaulted:1;
    // This is a conversion function
    char is_conversion:1;
    // States that this symbol has been trivially defined by the language
    char is_trivial:1;
    // This is a constructor
    char is_constructor:1;
    // This is the default constructor
    char is_default_constructor:1;
    // This is a copy-constructor
    char is_copy_constructor:1;
    // This is a move-constructor (C++1x)
    char is_move_constructor:1;
    // This is a conversor constructor
    char is_conversor_constructor:1;
    // This is a copy assignment operator
    char is_copy_assignment_operator:1;
    // This is a move assignment opeator (C++1x)
    char is_move_assignment_operator:1;
    // This is a destructor
    char is_destructor:1;
    // This constructor has been marked as explicit
    char is_explicit:1;
    // This function is a surrogate fake symbol created during overload resolution
    char is_surrogate_function:1;
    // This is an unnamed entity used for structs and enums
    char is_anonymous:1;
    // This is a template argument
    char is_template_argument:1;
    // This specialization of template has been user declared
    char is_user_declared:1;
    // This is a template parameter
    char is_template_parameter:1;
    // This symbol is a parameter of a function
    char is_parameter:1;
    // This symbol is a member of a class
    char is_member:1;
    // This symbol is a bitfield
    char is_bitfield:1;
    // This symbol is an unnamed bitfield
    char is_unnamed_bitfield:1;
    // States that this function can throw any exception
    char any_exception:1;
    // This symbol is the injected class name
    char is_injected_class_name:1;
    // This is an unnamed struct inside another struct
    char is_nested_unnamed_struct:1;
    // This symbol has been created after a typedef of an anonymous struct type
    char after_typedef:1;
#ifdef FORTRAN_SUPPORT
    // This entity has got an implicit basic type
    char is_implicit_basic_type:1;
    // This entity has the ALLOCATABLE attribute
    char is_allocatable:1;
    // This entity appears in a COMMON construct
    char is_in_common:1;
    // This entity appears in a NAMELIST
    char is_in_namelist:1;
    // This dummy argument has the OPTIONAL attribute
    char is_optional:1;
    // This entity has the TARGET attribute
    char is_target:1;
    // This dummy argument has the VALUE attribute
    char is_value:1;
    // This is an ELEMENTAL function
    char is_elemental:1;
    // This is a RECURSIVE function
    char is_recursive:1;
    // This symbol is the RESULT variable of the function
    char is_result:1;
    // This symbol has been declared after a statement function statement
    char is_stmt_function:1;
    // This symbol is a dummy argument of a statement function
    char is_dummy_arg_stmt_function:1;
    // This symbol is a generic specifier name
    char is_generic_spec:1;
    // This symbol is a builtin subroutine (or function)
    char is_builtin_subroutine:1;
    // This function has been named in an interface construct as a MODULE PROCEDURE
    char is_module_procedure:1;
    // States that this symbol comes from a module
    char is_from_module:1;
    // This symbol has a BIND(C) attribute
    char bind_c:1;
    // The INTENT attribute of this dummy argument
    intent_kind_t intent_kind;
    // The COMMON where this entity belongs. See is_in_common
    scope_entry_t* in_common;
    // The NAMELIST where this entity belongs. See is_in_namelist
    scope_entry_t* namelist;
    // Related symbols for this entity. Meaningful for NAMELIST, COMMON, FUNCTION, SUBROUTINE and MODULE
    int num_related_symbols;
    scope_entry_t** related_symbols;
    // For some INTRINSICs they have a specific function to be used when referenced not in a call. See is_builtin
    scope_entry_t* specific_intrinsic;
#endif // FORTRAN_SUPPORT
    // Accessibility: public, private, protected
    access_specifier_t access;
    // Nesting in the template parameter scoping hierarchy. See is_template_parameter
    int template_parameter_nesting;
    // Position in the template parameter scoping hierarchy. See is_template_parameter
    int template_parameter_position;
    // States the position of this parameter. See is_parameter
    int parameter_position;
    // The class type where a member belongs. See is_member
    type_t* class_type;
    // The original class symbol reachable from the injected class name. See is_injected_class_name
    scope_entry_t* injected_class_referred_symbol;
    // The linkage specifier (C, C++). Currently unused
    const char* linkage_spec;
    // Exception specifier for functions. Can be empty. See any_exception
    int num_exceptions;
    type_t** exceptions;
    // Default arguments for functions
    int num_parameters;
    default_argument_info_t** default_argument_info;
    // Expression of the bitfield
    AST bitfield_expr;
    // Context for the bitfield expression
    decl_context_t bitfield_expr_context;
    // Offsetof of a field/nonstatic data-member
    _size_t field_offset;
    // GCC attributes synthesized for the symbol from the syntax
    int num_gcc_attributes;
    gather_gcc_attribute_t gcc_attributes[MAX_GCC_ATTRIBUTES_PER_SYMBOL];
    // The tree where this function or class has been defined
    AST definition_tree;
} entity_specifiers_t;

#endif
