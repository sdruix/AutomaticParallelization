/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_MC99_C99_PARSER_INTERNAL_H_INCLUDED
# define YY_MC99_C99_PARSER_INTERNAL_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int mc99debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD_ASSIGN = 258,
    ANDAND = 259,
    AND_ASSIGN = 260,
    ASM = 261,
    AUTO = 262,
    TOKEN_BOOL = 263,
    BOOLEAN_LITERAL = 264,
    BREAK = 265,
    CASE = 266,
    TOKEN_CHAR = 267,
    CHARACTER_LITERAL = 268,
    TOKEN_CONST = 269,
    CONTINUE = 270,
    DECIMAL_LITERAL = 271,
    DEFAULT = 272,
    DIV_ASSIGN = 273,
    DO = 274,
    TOKEN_DOUBLE = 275,
    ELSE = 276,
    ENUM = 277,
    EQUAL = 278,
    EXTERN = 279,
    TOKEN_FLOAT = 280,
    FLOATING_LITERAL = 281,
    HEXADECIMAL_FLOAT = 282,
    FOR = 283,
    GOTO = 284,
    GREATER_OR_EQUAL = 285,
    HEXADECIMAL_LITERAL = 286,
    IDENTIFIER = 287,
    IF = 288,
    INLINE = 289,
    TOKEN_INT = 290,
    LEFT = 291,
    LEFT_ASSIGN = 292,
    LESS_OR_EQUAL = 293,
    TOKEN_LONG = 294,
    MINUSMINUS = 295,
    MOD_ASSIGN = 296,
    MUL_ASSIGN = 297,
    NOT_EQUAL = 298,
    OCTAL_LITERAL = 299,
    OR_ASSIGN = 300,
    OROR = 301,
    PLUSPLUS = 302,
    PTR_OP = 303,
    REGISTER = 304,
    RETURN = 305,
    RIGHT = 306,
    RIGHT_ASSIGN = 307,
    TOKEN_SHORT = 308,
    TOKEN_SIGNED = 309,
    SIZEOF = 310,
    STATIC = 311,
    STRING_LITERAL = 312,
    STRUCT = 313,
    SUB_ASSIGN = 314,
    SWITCH = 315,
    ELLIPSIS = 316,
    TYPEDEF = 317,
    UNION = 318,
    TOKEN_UNSIGNED = 319,
    TOKEN_VOID = 320,
    TOKEN_VOLATILE = 321,
    WHILE = 322,
    XOR_ASSIGN = 323,
    UNKNOWN_PRAGMA = 324,
    PP_COMMENT = 325,
    PP_TOKEN = 326,
    BUILTIN_VA_ARG = 327,
    BUILTIN_OFFSETOF = 328,
    BUILTIN_CHOOSE_EXPR = 329,
    BUILTIN_TYPES_COMPATIBLE_P = 330,
    ALIGNOF = 331,
    EXTENSION = 332,
    REAL = 333,
    IMAG = 334,
    LABEL = 335,
    COMPLEX = 336,
    IMAGINARY = 337,
    TYPEOF = 338,
    RESTRICT = 339,
    ATTRIBUTE = 340,
    THREAD = 341,
    SUBPARSE_EXPRESSION = 342,
    SUBPARSE_EXPRESSION_LIST = 343,
    SUBPARSE_STATEMENT = 344,
    SUBPARSE_DECLARATION = 345,
    SUBPARSE_MEMBER = 346,
    SUBPARSE_TYPE = 347,
    SUBPARSE_TYPE_LIST = 348,
    SUBPARSE_ID_EXPRESSION = 349,
    STATEMENT_PLACEHOLDER = 350,
    VERBATIM_PRAGMA = 351,
    VERBATIM_CONSTRUCT = 352,
    VERBATIM_TYPE = 353,
    VERBATIM_TEXT = 354,
    PRAGMA_CUSTOM = 355,
    PRAGMA_CUSTOM_NEWLINE = 356,
    PRAGMA_CUSTOM_DIRECTIVE = 357,
    PRAGMA_CUSTOM_CONSTRUCT = 358,
    PRAGMA_CUSTOM_CONSTRUCT_NOEND = 359,
    PRAGMA_CUSTOM_END_CONSTRUCT = 360,
    PRAGMA_CUSTOM_CLAUSE = 361,
    PRAGMA_CLAUSE_ARG_TEXT = 362,
    CONSTRUCT = 363,
    SUBPARSE_OMP_UDR_DECLARE = 364,
    SUBPARSE_OMP_UDR_DECLARE_2 = 365,
    SUBPARSE_OMP_UDR_IDENTITY = 366,
    OMP_UDR_CONSTRUCTOR = 367,
    SUBPARSE_OMP_OPERATOR_NAME = 368,
    TWO_DOTS = 369,
    SUBPARSE_SUPERSCALAR_DECLARATOR = 370,
    SUBPARSE_SUPERSCALAR_DECLARATOR_LIST = 371,
    SUBPARSE_SUPERSCALAR_EXPRESSION = 372,
    UPC_MYTHREAD = 373,
    UPC_RELAXED = 374,
    UPC_SHARED = 375,
    UPC_STRICT = 376,
    UPC_THREADS = 377,
    UPC_BARRIER = 378,
    UPC_BLOCKSIZEOF = 379,
    UPC_ELEMSIZEOF = 380,
    UPC_FENCE = 381,
    UPC_FORALL = 382,
    UPC_LOCALSIZEOF = 383,
    UPC_MAX_BLOCKSIZE = 384,
    UPC_NOTIFY = 385,
    UPC_WAIT = 386,
    CUDA_DEVICE = 387,
    CUDA_GLOBAL = 388,
    CUDA_HOST = 389,
    CUDA_CONSTANT = 390,
    CUDA_SHARED = 391,
    CUDA_KERNEL_LEFT = 392,
    CUDA_KERNEL_RIGHT = 393,
    XL_BUILTIN_SPEC = 394
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 51 "c99.y" /* glr.c:2555  */

	token_atrib_t token_atrib;
	AST ast;
	node_t node_type;
    const char *text;

#line 201 "c99-parser-internal.h" /* glr.c:2555  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE mc99lval;

int mc99parse (AST* parsed_tree);

#endif /* !YY_MC99_C99_PARSER_INTERNAL_H_INCLUDED  */
