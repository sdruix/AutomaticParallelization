/* A Bison parser, made by GNU Bison 2.3-rofi.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_FORMAT = 258,
     TOK_GENERIC = 259,
     TOK_VOLATILE = 260,
     TOK_EQUIVALENCE = 261,
     TOK_EOR = 262,
     TOK_PROTECTED = 263,
     TOK_PAD = 264,
     TOK_FILE = 265,
     TOK_UNFORMATTED = 266,
     TOK_NAMED = 267,
     TOK_SUBROUTINE = 268,
     TOK_OPENED = 269,
     TOK_DELIM = 270,
     TOK_SOURCE = 271,
     TOK_CRITICAL = 272,
     TOK_ACTION = 273,
     TOK_IMPORT = 274,
     TOK_BLOCK = 275,
     TOK_ENUM = 276,
     TOK_OVERRIDABLE = 277,
     TOK_MODULE = 278,
     TOK_SIGN = 279,
     TOK_EXTENDS = 280,
     TOK_PASS = 281,
     TOK_GO = 282,
     TOK_ENTRY = 283,
     TOK_WHERE = 284,
     TOK_PROCEDURE = 285,
     TOK_NAME = 286,
     TOK_DOUBLE = 287,
     TOK_CONTAINS = 288,
     TOK_LOGICAL = 289,
     TOK_NEWUNIT = 290,
     TOK_NULLIFY = 291,
     TOK_DEFERRED = 292,
     TOK_ONLY = 293,
     TOK_EXIST = 294,
     TOK_INTERFACE = 295,
     TOK_SAVE = 296,
     TOK_ADVANCE = 297,
     TOK_STAT = 298,
     TOK_RETURN = 299,
     TOK_READWRITE = 300,
     TOK_ASSIGNMENT = 301,
     TOK_ASSIGN = 302,
     TOK_PRINT = 303,
     TOK_IOSTAT = 304,
     TOK_SYNC = 305,
     TOK_COMPLEX = 306,
     TOK_ASYNCHRONOUS = 307,
     TOK_IMAGES = 308,
     TOK_END = 309,
     TOK_FINAL = 310,
     TOK_INOUT = 311,
     TOK_NEXTREC = 312,
     TOK_KIND = 313,
     TOK_COMMON = 314,
     TOK_BLANK = 315,
     TOK_IOLENGTH = 316,
     TOK_INTEGER = 317,
     TOK_DEALLOCATE = 318,
     TOK_FUNCTION = 319,
     TOK_C = 320,
     TOK_ENUMERATOR = 321,
     TOK_RECURSIVE = 322,
     TOK_SEQUENCE = 323,
     TOK_INQUIRE = 324,
     TOK_FLUSH = 325,
     TOK_ELSE = 326,
     TOK_INTENT = 327,
     TOK_EXTERNAL = 328,
     TOK_OPERATOR = 329,
     TOK_OPTIONAL = 330,
     TOK_UNIT = 331,
     TOK_SIZE = 332,
     TOK_NOPASS = 333,
     TOK_TYPE = 334,
     TOK_MOLD = 335,
     TOK_PRECISION = 336,
     TOK_PENDING = 337,
     TOK_CONTINUE = 338,
     TOK_RESULT = 339,
     TOK_REAL = 340,
     TOK_THEN = 341,
     TOK_STREAM = 342,
     TOK_DO = 343,
     TOK_DEFAULT = 344,
     TOK_CONTIGUOUS = 345,
     TOK_STOP = 346,
     TOK_PAUSE = 347,
     TOK_WHILE = 348,
     TOK_PROGRAM = 349,
     TOK_REC = 350,
     TOK_OPEN = 351,
     TOK_CASE = 352,
     TOK_RECL = 353,
     TOK_DIMENSION = 354,
     TOK_ELEMENTAL = 355,
     TOK_FORALL = 356,
     TOK_POSITION = 357,
     TOK_FMT = 358,
     TOK_READ = 359,
     TOK_OUT = 360,
     TOK_LOCK = 361,
     TOK_DECIMAL = 362,
     TOK_SELECT = 363,
     TOK_SELECTCASE = 364,
     TOK_DIRECT = 365,
     TOK_WRITE = 366,
     TOK_CODIMENSION = 367,
     TOK_CLOSE = 368,
     TOK_ID = 369,
     TOK_WAIT = 370,
     TOK_ALL = 371,
     TOK_ELSEWHERE = 372,
     TOK_LEN = 373,
     TOK_IMPURE = 374,
     TOK_EXIT = 375,
     TOK_REWIND = 376,
     TOK_BACKSPACE = 377,
     TOK_NML = 378,
     TOK_INTRINSIC = 379,
     TOK_PUBLIC = 380,
     TOK_ERRMSG = 381,
     TOK_NAMELIST = 382,
     TOK_USE = 383,
     TOK_SUBMODULE = 384,
     TOK_ERR = 385,
     TOK_ENCODING = 386,
     TOK_ACQUIRED = 387,
     TOK_ABSTRACT = 388,
     TOK_CHARACTER = 389,
     TOK_NUMBER = 390,
     TOK_CONCURRENT = 391,
     TOK_ENDFILE = 392,
     TOK_PARAMETER = 393,
     TOK_DATA = 394,
     TOK_POS = 395,
     TOK_PRIVATE = 396,
     TOK_ROUND = 397,
     TOK_TO = 398,
     TOK_SEQUENTIAL = 399,
     TOK_ALLOCATE = 400,
     TOK_TARGET = 401,
     TOK_CLASS = 402,
     TOK_CYCLE = 403,
     TOK_STATUS = 404,
     TOK_IOMSG = 405,
     TOK_FORM = 406,
     TOK_IS = 407,
     TOK_NONE = 408,
     TOK_VALUE = 409,
     TOK_UNLOCK = 410,
     TOK_FORMATTED = 411,
     TOK_IN = 412,
     TOK_IMPLICIT = 413,
     TOK_IF = 414,
     TOK_ASSOCIATE = 415,
     TOK_BIND = 416,
     TOK_ALLOCATABLE = 417,
     TOK_ACCESS = 418,
     TOK_CALL = 419,
     TOK_PURE = 420,
     TOK_MEMORY = 421,
     TOK_POINTER = 422,
     TOK_VECTOR = 423,
     TOK_PIXEL = 424,
     TOK_NON_OVERRIDABLE = 425,
     TOK_NON_INTRINSIC = 426,
     TOK_ALLSTOP = 427,
     TOK_ENDDO = 428,
     TOK_ENDIF = 429,
     TOK_ENDFUNCTION = 430,
     TOK_BLOCKDATA = 431,
     TOK_ENDMODULE = 432,
     TOK_DOUBLEPRECISION = 433,
     TOK_ENDINTERFACE = 434,
     TOK_ELSEIF = 435,
     TOK_ENDPROCEDURE = 436,
     TOK_ENDPROGRAM = 437,
     TOK_ENDASSOCIATE = 438,
     TOK_ENDSELECT = 439,
     TOK_ENDBLOCK = 440,
     TOK_ENDSUBMODULE = 441,
     TOK_ENDBLOCKDATA = 442,
     TOK_ENDSUBROUTINE = 443,
     TOK_ENDCRITICAL = 444,
     TOK_ENDTYPE = 445,
     TOK_DOUBLECOMPLEX = 446,
     TOK_GOTO = 447,
     TOK_LOGICAL_NOT_EQUIVALENT = 448,
     TOK_POINTER_ACCESS = 449,
     TOK_GREATER_THAN = 450,
     TOK_EQUAL = 451,
     TOK_LOGICAL_AND = 452,
     TOK_LOWER_THAN = 453,
     TOK_LOGICAL_NOT = 454,
     TOK_LOGICAL_EQUIVALENT = 455,
     TOK_GREATER_OR_EQUAL_THAN = 456,
     TOK_LOGICAL_OR = 457,
     TOK_LOWER_OR_EQUAL_THAN = 459,
     TOK_NOT_EQUAL = 460,
     TOK_RAISE = 461,
     TOK_DOUBLE_SLASH = 462,
     TOK_TRUE = 463,
     TOK_FALSE = 464,
     DECIMAL_LITERAL = 465,
     FORMAT_SPEC = 466,
     IDENTIFIER = 467,
     EOS = 468,
     BINARY_LITERAL = 469,
     OCTAL_LITERAL = 470,
     REAL_LITERAL = 471,
     CHAR_LITERAL = 472,
     HEX_LITERAL = 473,
     USER_DEFINED_OPERATOR = 474,
     TOK_END_NONBLOCK_DO = 475,
     TOK_SHARED_LABEL = 476,
     SUBPARSE_PROGRAM_UNIT = 477,
     SUBPARSE_EXPRESSION = 478,
     SUBPARSE_STATEMENT = 479,
     PRAGMA_CUSTOM = 480,
     PRAGMA_CUSTOM_NEWLINE = 481,
     PRAGMA_CUSTOM_DIRECTIVE = 482,
     PRAGMA_CUSTOM_CONSTRUCT = 483,
     PRAGMA_CUSTOM_CONSTRUCT_NOEND = 484,
     PRAGMA_CUSTOM_END_CONSTRUCT = 485,
     PRAGMA_CUSTOM_CLAUSE = 486,
     PRAGMA_CLAUSE_ARG_TEXT = 487,
     UNKNOWN_PRAGMA = 488
   };
#endif


/* Copy the first part of user declarations.  */
#line 27 "fortran03.y"

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



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE 
#line 81 "fortran03.y"
{
	token_atrib_t token_atrib;
	AST ast;
	AST ast2[2];
	AST ast3[3];
	AST ast4[4];
	node_t node_type;
    const char *text;
}
/* Line 2604 of glr.c.  */
#line 334 "fortran03-parser-internal.h"
	YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{

  char yydummy;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE mf03lval;



