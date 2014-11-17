/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Skeleton implementation for Bison GLR parsers in C

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0




/* Substitute the variable and function names.  */
#define yyparse mc99parse
#define yylex   mc99lex
#define yyerror mc99error
#define yydebug mc99debug

#define yylval  mc99lval
#define yychar  mc99char
#define yynerrs mc99nerrs

/* First part of user declarations.  */
#line 27 "c99.y" /* glr.c:207  */

/*
   Parser of ISO/IEC 9899:1999 - C

   It parses a superset of the language.

   Must be compiled with rofi-bison-2.1. 
   Ask for it at <rferrer@ac.upc.edu>
 */

#include "c99-parser.h"
#include "cxx-ast.h"
#include "cxx-lexer.h"
#include "cxx-utils.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
// Sometimes we need lots of memory
#define YYMAXDEPTH (10000000)


#line 84 "c99-parser.c" /* glr.c:207  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "c99-parser-internal.h"

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */
#line 64 "c99.y" /* glr.c:230  */

extern int yylex(void);
static AST ambiguityHandler (YYSTYPE x0, YYSTYPE x1);
void yyerror(AST* parsed_tree UNUSED_PARAMETER, const char* c);
#line 486 "c99.y" /* glr.c:230  */

    static AST* decode_placeholder(const char *);

#line 120 "c99-parser.c" /* glr.c:230  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  305
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  164
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  184
/* YYNRULES -- Number of rules.  */
#define YYNRULES  567
/* YYNRULES -- Number of states.  */
#define YYNSTATES  967
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 12
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   394

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,     2,     2,    73,    74,     2,
      75,    76,    77,    78,    79,    80,    81,    82,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    84,
      85,    86,    87,    88,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    89,     2,    90,    91,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,    93,    94,    95,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,  1562,  1562,  1567,  1576,  1580,  1586,  1590,  1596,  1600,
    1606,  1610,  1616,  1621,  1625,  1630,  1635,  1640,  1647,  1653,
    1658,  1667,  1671,  1677,  1681,  1687,  1691,  1698,  1704,  1710,
    1719,  1724,  1730,  1736,  1745,  1748,  1754,  1759,  1765,  1769,
    1775,  1779,  1785,  1793,  1797,  1804,  1808,  1812,  1818,  1824,
    1828,  1832,  1836,  1840,  1847,  1851,  1857,  1861,  1865,  1869,
    1873,  1879,  1883,  1887,  1891,  1895,  1907,  1911,  1915,  1919,
    1925,  1929,  1935,  1939,  1945,  1949,  1954,  1958,  1962,  1967,
    1972,  1976,  1980,  1984,  1989,  1993,  1999,  2003,  2007,  2011,
    2016,  2022,  2028,  2031,  2036,  2042,  2046,  2050,  2056,  2060,
    2064,  2068,  2072,  2078,  2082,  2086,  2090,  2094,  2100,  2104,
    2109,  2113,  2120,  2126,  2130,  2134,  2138,  2142,  2146,  2150,
    2154,  2158,  2162,  2168,  2174,  2181,  2187,  2198,  2202,  2208,
    2212,  2217,  2221,  2225,  2229,  2233,  2237,  2244,  2251,  2255,
    2260,  2264,  2270,  2274,  2284,  2288,  2293,  2297,  2303,  2307,
    2315,  2318,  2324,  2332,  2335,  2340,  2348,  2351,  2355,  2361,
    2365,  2369,  2378,  2383,  2389,  2393,  2399,  2403,  2408,  2414,
    2418,  2424,  2428,  2432,  2436,  2440,  2444,  2450,  2457,  2463,
    2467,  2473,  2478,  2484,  2488,  2494,  2501,  2507,  2512,  2516,
    2522,  2528,  2536,  2540,  2546,  2550,  2554,  2559,  2563,  2567,
    2573,  2577,  2581,  2585,  2591,  2597,  2601,  2605,  2609,  2613,
    2617,  2623,  2628,  2634,  2642,  2646,  2653,  2657,  2663,  2667,
    2671,  2676,  2680,  2686,  2692,  2696,  2700,  2704,  2710,  2714,
    2718,  2724,  2731,  2739,  2749,  2755,  2759,  2765,  2769,  2777,
    2781,  2786,  2790,  2795,  2801,  2805,  2811,  2821,  2825,  2831,
    2835,  2842,  2846,  2854,  2858,  2864,  2868,  2874,  2878,  2882,
    2887,  2892,  2898,  2902,  2908,  2912,  2916,  2920,  2928,  2932,
    2936,  2942,  2948,  2958,  2962,  2966,  2972,  2976,  2980,  2984,
    2988,  2992,  2996,  3003,  3009,  3013,  3018,  3024,  3028,  3035,
    3041,  3045,  3051,  3055,  3063,  3070,  3077,  3081,  3087,  3093,
    3097,  3102,  3108,  3114,  3122,  3126,  3130,  3137,  3142,  3147,
    3152,  3158,  3162,  3168,  3172,  3176,  3180,  3184,  3191,  3201,
    3205,  3209,  3223,  3227,  3231,  3235,  3239,  3252,  3258,  3266,
    3272,  3278,  3282,  3286,  3290,  3294,  3298,  3302,  3306,  3311,
    3315,  3321,  3326,  3333,  3337,  3341,  3345,  3349,  3353,  3358,
    3362,  3366,  3370,  3374,  3378,  3386,  3390,  3394,  3398,  3402,
    3406,  3412,  3416,  3422,  3426,  3430,  3434,  3440,  3444,  3448,
    3454,  3458,  3462,  3468,  3472,  3476,  3480,  3484,  3490,  3494,
    3498,  3504,  3508,  3514,  3518,  3524,  3528,  3534,  3538,  3544,
    3548,  3554,  3558,  3563,  3569,  3573,  3579,  3583,  3591,  3595,
    3599,  3603,  3607,  3611,  3615,  3619,  3623,  3627,  3631,  3637,
    3647,  3651,  3655,  3659,  3663,  3667,  3671,  3675,  3681,  3687,
    3691,  3728,  3734,  3738,  3742,  3746,  3750,  3754,  3758,  3762,
    3766,  3770,  3797,  3801,  3819,  3823,  3830,  3834,  3840,  3846,
    3850,  3856,  3875,  3971,  3975,  3981,  3985,  3991,  3995,  4020,
    4027,  4033,  4039,  4100,  4104,  4108,  4115,  4119,  4126,  4129,
    4135,  4139,  4143,  4149,  4153,  4157,  4163,  4171,  4175,  4181,
    4187,  4195,  4201,  4207,  4213,  4232,  4240,  4245,  4249,  4255,
    4259,  4265,  4309,  4322,  4329,  4347,  4351,  4357,  4361,  4396,
    4402,  4428,  4432,  4438,  4454,  4458,  4462,  4466,  4470,  4474,
    4478,  4482,  4486,  4492,  4498,  4504,  4510,  4516,  4565,  4569,
    4573,  4579,  4584,  4591,  4595,  4603,  4606,  4609,  4613,  4619,
    4623,  4627,  4631,  4666,  4670,  4674,  4678,  4682,  4686,  4692,
    4696,  4702,  4706,  4712,  4716,  4723,  4727,  4733,  4737,  4741,
    4749,  4755,  4759,  4763,  4767,  4773,  4778,  4783,  4792,  4797,
    4801,  4805,  4832,  4838,  4844,  4848,  4852,  4856,  4860,  4866,
    4870,  4876,  4882,  4886,  4890,  4896,  4903,  4925
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"+=\"", "\"&&\"", "\"&=\"",
  "\"__asm__\"", "\"auto\"", "\"_Bool\"", "\"boolean-literal\"",
  "\"break\"", "\"case\"", "\"char\"", "\"character-literal\"",
  "\"const\"", "\"continue\"", "\"decimal-literal\"", "\"default\"",
  "\"/=\"", "\"do\"", "\"double\"", "\"else\"", "\"enum\"", "\"==\"",
  "\"extern\"", "\"float\"", "\"floating-literal\"",
  "\"hexadecimal-floating-literal\"", "\"for\"", "\"goto\"", "\">=\"",
  "\"hexadecimal-integer-literal\"", "\"identifier\"", "\"if\"",
  "\"inline\"", "\"int\"", "\"<<\"", "\"<<=\"", "\"<=\"", "\"long\"",
  "\"--\"", "\"%=\"", "\"*=\"", "\"!=\"", "\"octal-integer-literal\"",
  "\"|=\"", "\"||\"", "\"++\"", "\"->\"", "\"register\"", "\"return\"",
  "\">>\"", "\">>=\"", "\"short\"", "\"signed\"", "\"sizeof\"",
  "\"static\"", "\"string-literal\"", "\"struct\"", "\"-=\"", "\"switch\"",
  "\"...\"", "\"typedef\"", "\"union\"", "\"unsigned\"", "\"void\"",
  "\"volatile\"", "\"while\"", "\"^=\"", "\"<unknown-pragma>\"",
  "\"<preprocessor-comment>\"", "\"<preprocessor-token>\"", "'!'", "'%'",
  "'&'", "'('", "')'", "'*'", "'+'", "','", "'-'", "'.'", "'/'", "':'",
  "';'", "'<'", "'='", "'>'", "'?'", "'['", "']'", "'^'", "'{'", "'|'",
  "'}'", "'~'", "\"__builtin_va_arg\"", "\"__builtin_offsetof\"",
  "\"__builtin_choose_expr\"", "\"__builtin_types_compatible_p\"",
  "\"__alignof__\"", "\"__extension__\"", "\"__real__\"", "\"__imag__\"",
  "\"__label__\"", "\"__complex__\"", "\"__imaginary__\"",
  "\"__typeof__\"", "\"restrict\"", "\"__attribute__\"", "\"__thread\"",
  "\"<subparse-expression>\"", "\"<subparse-expression-list>\"",
  "\"<subparse-statement>\"", "\"<subparse-declaration>\"",
  "\"<subparse-member>\"", "\"<subparse-type>\"",
  "\"<subparse-type-list>\"", "\"<subparse-id-expression>\"",
  "\"<statement-placeholder>\"", "\"<verbatim pragma>\"",
  "\"<verbatim construct>\"", "\"<verbatim type clause>\"",
  "\"<verbatim text>\"", "\"<pragma-custom>\"",
  "\"<pragma-custom-newline>\"", "\"<pragma-custom-directive>\"",
  "\"<pragma-custom-construct>\"", "\"<pragma-custom-construct-noend>\"",
  "\"<pragma-custom-end-construct>\"", "\"<pragma-custom-clause>\"",
  "\"<pragma-clause-argument-text>\"", "\"__construct__\"",
  "\"<subparse-omp-udr-declare>\"", "\"<subparse-omp-udr-declare-2>\"",
  "\"<subparse-omp-udr-identity>\"", "\"constructor\"",
  "\"<subparse_omp_operator_name>\"", "\"..\"",
  "\"<subparse-superscalar-declarator>\"",
  "\"<subparse-superscalar-declarator-list>\"",
  "\"<subparse-superscalar-expression>\"", "\"MYTHREAD (UPC)\"",
  "\"relaxed (UPC)\"", "\"shared (UPC)\"", "\"strict (UPC)\"",
  "\"THREADS (UPC)\"", "\"upc_barrier\"", "\"upc_blocksizeof\"",
  "\"upc_elemsizeof\"", "\"upc_fence\"", "\"upc_forall\"",
  "\"upc_localsizeof\"", "\"UPC_MAX_BLOCKSIZE\"", "\"upc_notify\"",
  "\"upc_wait\"", "\"__device__\"", "\"__global__\"", "\"__host__\"",
  "\"__constant__\"", "\"__shared__\"", "\"<<<\"", "\">>>\"",
  "\"_Builtin\"", "$accept", "translation_unit", "declaration_sequence",
  "declaration", "block_declaration", "non_empty_block_declaration",
  "common_block_declaration", "label_declaration", "label_declarator_seq",
  "attributes", "attribute", "attribute_list", "attribute_value",
  "asm_definition", "volatile_optional", "asm_operand_list",
  "asm_operand_list_nonempty", "asm_operand", "simple_declaration",
  "non_empty_simple_declaration", "old_style_parameter",
  "old_style_decl_specifier_seq",
  "nontype_specifier_without_attribute_seq", "decl_specifier_seq",
  "decl_specifier_seq_may_end_with_declarator", "decl_specifier_alone_seq",
  "nontype_specifier_seq", "nontype_specifier_no_end_attrib_seq",
  "nontype_specifier", "nontype_specifier_without_attribute",
  "storage_class_specifier", "function_specifier", "type_specifier",
  "type_specifier_alone", "type_specifier_seq",
  "type_specifier_seq_may_end_with_attribute", "simple_type_specifier",
  "type_name", "builtin_types", "elaborated_type_specifier",
  "init_declarator_list", "init_declarator", "asm_specification",
  "declarator", "ptr_operator", "functional_declarator",
  "functional_direct_declarator", "optional_array_cv_qualifier_seq",
  "array_cv_qualifier_seq", "optional_array_static_qualif",
  "array_static_qualif", "optional_array_expression",
  "functional_declarator_id", "final_declarator_id", "cv_qualifier_seq",
  "cv_qualifier", "direct_declarator", "declarator_id", "enum_specifier",
  "enumeration_list", "enumeration_list_proper", "enumeration_definition",
  "type_id", "abstract_declarator", "abstract_direct_declarator",
  "identifier_list", "identifier_list_kr", "parameter_type_list",
  "parameter_declaration_list", "parameter_declaration", "initializer",
  "initializer_clause", "initializer_list", "designation",
  "designator_list", "designator", "function_definition",
  "old_style_parameter_list", "function_body", "class_specifier",
  "class_head", "class_key", "member_specification_seq",
  "member_declaration", "member_declarator_list", "member_declarator",
  "constant_initializer", "statement", "no_if_statement",
  "labeled_statement", "expression_statement", "declaration_statement",
  "compound_statement", "statement_seq", "if_statement",
  "if_else_statement", "if_else_eligible_statements",
  "selection_statement", "condition", "iteration_statement",
  "expression_opt", "condition_opt", "for_init_statement",
  "jump_statement", "primary_expression", "offsetof_member_designator",
  "id_expression", "unqualified_id", "postfix_expression",
  "expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "expression",
  "assignment_operator", "constant_expression", "literal",
  "unknown_pragma", "string_literal", "subparsing", "subparse_type_list",
  "noshape_cast_expression", "shape_seq", "shape",
  "pragma_custom_directive", "pragma_custom_construct_declaration",
  "pragma_custom_construct_member_declaration",
  "pragma_custom_construct_statement", "pragma_custom_line_directive",
  "pragma_custom_line_construct", "pragma_custom_clause_opt_seq",
  "pragma_custom_clause_seq", "pragma_custom_clause",
  "pragma_clause_arg_list", "pragma_clause_arg", "pragma_clause_arg_item",
  "pragma_clause_arg_text", "verbatim_construct",
  "custom_construct_statement", "custom_construct_header",
  "custom_construct_parameters_seq", "custom_construct_parameter",
  "omp_udr_declare_arg", "omp_udr_declare_arg_2", "omp_udr_type_specifier",
  "omp_udr_type_specifier_2", "omp_udr_unqualified_operator",
  "omp_udr_expression", "omp_udr_operator_2", "omp_udr_operator_list",
  "omp_udr_operator", "omp_udr_builtin_op", "omp_udr_identity",
  "superscalar_declarator_list", "superscalar_declarator",
  "opt_superscalar_region_spec_list", "superscalar_region_spec_list",
  "superscalar_region_spec", "upc_shared_type_qualifier",
  "upc_reference_type_qualifier", "upc_layout_qualifier",
  "upc_layout_qualifier_element", "upc_synchronization_statement",
  "upc_expression_opt", "upc_affinity_opt", "upc_affinity",
  "cuda_specifiers", "cuda_kernel_call", "cuda_kernel_arguments",
  "cuda_kernel_config_list", "cuda_kernel_config_left",
  "cuda_kernel_config_right", YY_NULLPTR
};
#endif

#define YYPACT_NINF -810
#define YYTABLE_NINF -395

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
    3482,   178,  -810,  -810,  -810,  -810,  -810,    91,  -810,  -810,
    1456,  -810,  -810,  1603,  -810,  1719,  1834,  -810,  -810,  -810,
    -810,  1949,  -810,  -810,  -810,  -810,  -810,   105,   328,  -810,
    3755,    39,  2064,  -810,    86,  -810,   206,  -810,  7518,  7518,
    2538,  3640,  4048,  4749,  4749,   258,   254,   548,   258,   713,
    6618,   713,   258,   258,  7518,  -810,   234,  -810,  -810,  -810,
    -810,  -810,  -810,  -810,   401,  3640,  -810,  -810,  -810,  -810,
     105,    95,  -810,  -810,  -810,   105,   261,  4749,  -810,  -810,
     189,  -810,  -810,  5483,  5356,  -810,  -810,  -810,  -810,    30,
    -810,    43,   105,  4811,  -810,  -810,   280,  -810,   190,   507,
    -810,  -810,  -810,   343,    32,  -810,  -810,  -810,  -810,  -810,
    -810,  -810,  -810,  -810,  -810,  -810,   374,   398,    22,   203,
    -810,  -810,   390,   460,   555,   328,  -810,  -810,  -810,  -810,
     128,  3324,   466,   541,  -810,  -810,  -810,  -810,  -810,  -810,
    7818,  -810,  7818,  7918,  -810,  -810,  -810,  2853,  -810,  -810,
    -810,  7518,  -810,   491,   533,   551,   564,  8018,  7518,  7518,
    7518,  8118,  8218,  8318,  -810,  -810,   528,  -810,  7518,  -810,
     302,   131,   345,   352,   237,   570,   509,   575,   659,  1290,
    -810,  -810,   591,  -810,   622,  7618,  -810,  -810,   604,  -810,
     609,  7518,   610,   605,  2538,   621,    41,  4989,   628,  6718,
     629,   631,  3010,   990,  -810,  2222,  2696,  -810,   548,   676,
    7518,   626,   636,  7518,  7518,  -810,  -810,   243,  -810,   243,
     243,  -810,  -810,  -810,  -810,  -810,  -810,  -810,  2538,  -810,
    -810,  -810,  -810,  -810,   502,   245,  -810,  -810,  -810,  2538,
    -810,  3640,  -810,  -810,  4048,   548,  -810,    45,   630,  4048,
    -810,  -810,  -810,  -810,  -810,  4749,  -810,  5053,  -810,   227,
    -810,  -810,  4749,  5546,  -810,   633,  -810,   640,  -810,  -810,
      21,   100,  -810,  3640,  -810,  -810,   465,  -810,  -810,  -810,
    -810,  -810,  -810,  -810,  -810,  -810,  -810,  -810,  -810,   635,
    -810,  6218,  -810,  -810,  -810,  -810,  -810,  -810,   391,   647,
     391,   363,  6818,   643,  -810,  -810,  -810,  -810,   105,  -810,
     190,   319,  4811,  -810,  -810,   667,  5610,  5419,  -810,  -810,
    -810,  -810,  -810,  5673,  -810,  5673,  -810,   243,  -810,   654,
    6618,    82,    82,  -810,  -810,  -810,  -810,   243,  4926,  -810,
    5737,  4811,  -810,  -810,  4393,  4456,  6112,  3870,   641,    40,
     679,    51,   655,  -810,   646,   664,  -810,   660,    63,  -810,
    -810,  -810,  -810,   721,  -810,   678,   439,    67,  -810,  2853,
    -810,  -810,  2853,  -810,   681,   689,   518,   329,  7518,  4749,
    7518,  4749,  2853,  -810,  -810,  -810,  -810,  2853,  -810,  2853,
    -810,  2853,  -810,  -810,  -810,   258,  6918,   258,  7518,  -810,
     691,  7518,  -810,  7518,  7518,  7518,  7518,  7518,  7518,  7518,
    7518,  7518,  7518,  7518,  7518,  7518,  7518,  7518,  7518,  7518,
    -810,  -810,  -810,  -810,  -810,  -810,  -810,  7518,  -810,  -810,
    -810,  -810,  7018,  7518,  7518,  -810,  2853,  -810,  -810,  -810,
    7518,  -810,   109,  -810,    15,  -810,  2538,   700,  3167,   684,
    7518,  2538,  3324,  -810,   378,  3324,  3324,  -810,  2380,  2538,
     737,   591,   686,  -810,  3167,   687,   690,   243,   243,  -810,
    -810,  -810,  -810,  4048,    -4,  7518,   104,   200,   446,  -810,
    -810,  -810,  5117,  5673,  -810,  4163,  6112,   227,   227,  -810,
     196,  5800,  4749,   741,   644,   702,   653,   -28,  -810,   644,
     656,  -810,   258,  4749,  4749,   696,   754,  7518,  -810,  -810,
     310,  6618,   428,  -810,  7518,  7118,  -810,   697,  -810,   258,
    -810,  -810,   704,  -810,   706,  -810,  -810,  -810,  -810,  4811,
    -810,  -810,  5673,  -810,   679,  -810,  -810,    82,  -810,   447,
    -810,  5864,  5927,  -810,  -810,   525,  -810,   308,  -810,  4749,
    5229,   716,   718,   722,   723,  -810,  -810,   724,   731,  -810,
     711,   756,   328,   729,   328,  -810,  -810,  3985,   734,   194,
    -810,   719,  7518,  -810,   782,    68,  -810,   740,  -810,  -810,
    -810,  -810,   761,   762,   526,  -810,   765,   766,  7218,  -810,
    -810,  -810,   764,   769,   770,   772,   768,   777,   779,   785,
    -810,  -810,   544,  -810,   786,   413,  7318,   783,   708,  -810,
    -810,  -810,   461,   490,   479,   534,   345,   345,   345,   345,
     352,   352,   237,   798,   509,   575,   869,  7518,   501,  -810,
    -810,   799,  -810,  7518,  2538,  -810,   801,  -810,  -810,  3324,
    -810,   449,  -810,   243,   807,   591,  -810,   809,   813,  -810,
    -810,   791,   811,  -810,  -810,  7518,  -810,  -810,  -810,  7518,
       1,  -810,  7518,  7518,   200,  -810,    45,  -810,  5673,  -810,
    -810,   817,   818,   756,   328,   805,   227,   196,  -810,  4571,
    6112,  -810,   820,  -810,   821,   644,  -810,  -810,   114,  -810,
     778,  -810,   823,  -810,  -810,  -810,  -810,  -810,   510,  6618,
    -810,   812,   819,  6318,  -810,  -810,  -810,  7518,  -810,   822,
    -810,    18,  -810,   391,  -810,  -810,  -810,   119,  -810,  -810,
    5991,  4278,   308,   802,   316,   802,  5292,  5673,  -810,   881,
    -810,  4634,  -810,  -810,  7718,  -810,  7718,  -810,  -810,  -810,
     830,   110,  -810,  -810,  -810,  -810,   824,  -810,  7518,  -810,
     843,   355,   828,   831,  6518,  -810,  4749,   890,  7518,  4749,
     834,   835,   836,   837,  -810,  7518,  7518,  -810,  -810,   549,
    7518,  -810,  -810,  -810,  7518,  7218,   850,  -810,  7518,  -810,
     851,  -810,    44,  2538,  2538,  2538,  7518,   902,   852,  -810,
    7518,  -810,  -810,  -810,  -810,  -810,  -810,  7718,  7718,  -810,
    -810,  -810,   862,   756,   328,   854,   825,   778,  -810,  -810,
     864,  -810,   778,  4749,  7518,  -810,  -810,   863,  -810,  -810,
    6618,  -810,  7518,  -810,  7518,  -810,  -810,   341,   802,   802,
    5673,  -810,  -810,  -810,   855,   859,  -810,   920,   267,   875,
    -810,     5,  -810,   573,  -810,  -810,   330,   880,   339,   882,
     878,   883,   872,   591,   432,  -810,   885,  -810,  -810,  2538,
     578,  7518,  7518,   242,   252,  -810,   945,   946,   947,  -810,
    -810,   892,  -810,  7518,  -810,   879,   884,  -810,  7718,  7718,
    -810,  -810,   847,  -810,   856,  -810,   591,  -810,  6618,  -810,
     333,   359,  -810,  -810,   886,   889,   110,   110,  7518,  -810,
    6418,  -810,  -810,   339,  -810,  7518,  -810,  -810,  -810,  7518,
    -810,   891,   901,  -810,  7518,  7518,   277,  2538,   898,  -810,
    -810,   893,   896,  -810,  -810,  -810,  -810,  -810,   679,  -810,
     369,  -810,   580,  -810,   911,   909,  -810,  2538,  -810,  -810,
    7518,  -810,  7418,  -810,  -810,   313,   905,   110,  -810,  -810,
    7518,  -810,  -810,  -810,   591,   914,  -810,  7518,  -810,   915,
    -810,  2538,   593,   910,  -810,  -810,  -810
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short int yydefact[] =
{
       3,    34,    86,   114,   113,   166,   121,     0,    89,   120,
     330,    91,   116,    82,    87,    83,    80,    88,   253,    78,
     254,    81,   122,   167,   418,    16,    17,     0,   142,    44,
       0,     0,    84,    85,     0,   168,     0,    90,     0,     0,
     424,   427,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   533,   531,   534,   554,   555,
     556,   557,   558,   567,     0,     2,     4,     6,     9,    13,
       0,    75,    12,     8,    43,     0,     0,     0,    60,    70,
      74,    76,    77,    59,    92,    93,   108,   109,    97,     0,
     127,   129,     0,     0,   144,   148,     0,    79,   138,   169,
      96,     7,    95,     0,   249,   177,   329,    15,   421,   446,
     445,   473,   529,   530,   552,    35,     0,   124,     0,     0,
      22,   330,     0,     0,     0,   143,   164,    14,   243,    19,
       0,     0,     0,     0,   415,   416,   410,   414,   413,   412,
       0,   411,     0,     0,   419,   359,   356,     0,   355,   357,
     358,     0,   360,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   331,   321,   343,   361,     0,   363,
     367,   370,   373,   378,   381,   383,   385,   387,   389,   391,
     394,   396,   422,   319,   417,     0,   440,   553,   430,   341,
       0,     0,     0,     0,     0,     0,     0,   330,     0,     0,
       0,     0,     0,   355,   288,     0,     0,   442,     0,     0,
     546,     0,     0,   546,   546,   289,    11,     0,    10,     0,
       0,   169,   292,   273,   276,   277,   282,   278,   423,   274,
     275,   279,   280,   281,   321,     0,   444,   443,   475,     0,
     540,   426,   112,   260,     0,     0,    75,     0,     0,   425,
     255,   259,   448,   447,   474,   107,   102,   106,    92,     0,
     192,   428,     0,   101,   432,   429,   431,     0,   472,   455,
     458,   458,   449,     0,   493,   503,     0,   491,   501,   487,
     502,   498,   496,   494,   495,   497,   500,   499,   504,     0,
     488,     0,   507,   224,   505,   490,   506,   513,   515,   509,
     515,   515,     0,   532,   535,     1,     5,    21,     0,   146,
     140,     0,     0,    46,    71,    74,    57,    92,    82,    83,
      80,    81,    84,     0,    58,    68,    74,     0,    47,     0,
       0,   132,   131,   130,   139,   145,   244,     0,    53,    54,
      52,     0,   241,   246,     0,     0,   156,     0,   123,   251,
       0,     0,   190,   181,     0,   186,   189,   126,     0,   176,
     149,   163,   165,     0,    18,     0,     0,     0,   354,     0,
     345,   344,     0,   347,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   350,   349,   352,   353,     0,   525,     0,
     527,     0,   523,   338,   337,     0,     0,     0,   308,   565,
       0,     0,   346,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     401,   405,   400,   403,   408,   399,   406,     0,   404,   402,
     407,   398,     0,     0,     0,   420,     0,   436,   438,   439,
       0,   313,   391,   409,     0,   314,     0,     0,     0,     0,
       0,     0,     0,   315,     0,     0,     0,   291,     0,     0,
     478,   545,     0,   544,     0,     0,     0,     0,     0,   293,
     287,   476,   261,     0,   330,     0,     0,   264,     0,   262,
     258,   256,   104,   105,   100,     0,   156,     0,   194,   193,
     196,    99,     0,     0,     0,   465,     0,   459,   460,     0,
       0,   450,     0,     0,     0,   330,     0,     0,   227,   228,
       0,     0,     0,   235,     0,     0,   508,   516,   517,     0,
     511,   510,   355,   537,     0,   536,   141,   147,    45,     0,
     239,    56,    66,   128,     0,   223,   135,   133,   134,     0,
      55,    50,    51,   245,   242,   112,   161,     0,   219,    65,
      59,     0,   211,     0,   214,   216,   170,     0,     0,   155,
     355,   153,   150,     0,   152,   158,   248,     0,   125,     0,
     180,     0,     0,   179,   187,     0,   185,     0,    20,   111,
     110,    28,    27,     0,     0,    25,     0,     0,     0,   322,
     320,   441,     0,     0,     0,     0,     0,     0,     0,     0,
     336,   333,     0,   335,     0,   307,     0,     0,     0,   366,
     364,   365,   368,   369,   371,   372,   376,   377,   374,   375,
     379,   380,   382,   384,   386,   388,   390,     0,     0,   395,
     397,     0,   342,     0,     0,   285,     0,   312,   311,   310,
     317,     0,   283,     0,     0,   299,   316,     0,     0,   290,
     452,     0,   477,   479,   543,   546,   541,   542,   451,     0,
       0,   266,     0,     0,   268,   265,     0,   257,   103,    98,
     203,     0,     0,   153,   150,     0,   197,   199,   195,     0,
     156,   433,     0,   470,     0,   466,   467,   469,     0,   453,
       0,   462,     0,   456,   492,   484,   482,   485,     0,     0,
     238,   394,     0,     0,   225,   230,   234,     0,   236,     0,
     519,     0,   518,   515,   539,   538,   240,     0,   136,    48,
      49,     0,     0,   218,   194,   220,    57,    63,   160,     0,
     159,     0,   171,   172,   156,   154,   156,   151,   173,   247,
       0,    37,   178,   191,   188,   184,     0,   183,     0,    24,
       0,     0,     0,   348,     0,   362,     0,     0,     0,     0,
     351,   526,   528,   524,   334,   308,     0,   332,   559,     0,
       0,   566,   561,   393,     0,     0,     0,   284,     0,   309,
       0,   318,     0,     0,     0,     0,     0,     0,     0,   267,
       0,   271,   272,   269,   263,   200,   201,   156,   156,   205,
     198,   204,     0,   153,   150,     0,     0,   458,   468,   464,
       0,   461,   458,     0,     0,   232,   237,   330,   226,   229,
       0,   514,     0,   520,     0,   512,   137,   197,   221,   222,
      61,   213,   215,   217,     0,     0,    30,     0,     0,    36,
      38,    42,   182,     0,    23,    26,     0,     0,   328,     0,
       0,     0,     0,   307,     0,   560,   564,   392,   437,     0,
       0,   308,     0,     0,     0,   294,   273,   275,     0,   298,
     304,   481,   480,   546,   270,     0,     0,   202,   156,   156,
     208,   471,     0,   463,     0,   486,   489,   483,     0,   231,
       0,     0,   174,   175,     0,     0,    37,     0,     0,    29,
       0,   339,   323,   327,   324,     0,   326,   434,   435,     0,
     286,     0,     0,   300,     0,     0,     0,     0,     0,   206,
     207,     0,     0,   454,   457,   233,   522,   521,     0,    31,
       0,    39,     0,   340,     0,   563,   305,     0,   302,   303,
       0,   295,   549,   209,   210,     0,     0,    37,    40,   325,
       0,   306,   301,   551,   550,     0,   548,     0,    32,     0,
     562,     0,     0,     0,   547,    41,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -810,  -810,   952,   -12,    12,  -810,    85,  -810,  -810,   133,
       0,  -810,   255,  -810,  -810,  -809,  -810,   111,  -810,    52,
    -307,  -810,  -810,   780,  -810,   -17,   848,  1048,   -22,   919,
    -810,  -810,   907,    48,   -23,  -810,  -810,  -810,  -810,  -810,
     -31,   680,   228,   -24,   454,    11,   943,  -631,  -320,  -626,
    -315,    27,  -810,   988,    35,     7,   -69,  1005,  -810,  -312,
    -810,   442,   -25,  -242,  -472,   672,  -810,  -308,  -810,   288,
    -275,   -48,   266,  -684,   175,  -504,   995,   714,  -280,  -810,
    -810,  -810,   692,  -221,  -810,   362,   370,   -36,   250,  -810,
    -263,  -810,   658,   832,  -810,   253,  -810,  -810,  -396,  -810,
    -696,  -810,   579,  -810,  -810,  -810,    94,  -810,  -810,  -380,
     725,  -810,  -148,   279,   283,   225,   287,   632,   627,   634,
     642,   624,  -158,    57,   244,   448,  -810,    76,  -810,   -13,
    -341,  -810,  -810,  -810,  -810,   874,    66,  -810,  -810,  -810,
    -810,  -134,  -247,  -810,  -475,  -454,  -810,   375,  -810,    25,
    -810,  -810,  -810,   275,  -810,  -810,  -810,  -810,  1012,  -810,
    -810,  -810,   566,  -810,  -810,  -810,   -49,  -287,  -810,   552,
    -810,  -810,  -810,   763,  -810,  -208,  -810,  -810,  -810,  -810,
    -810,  -810,  -810,  -810
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,    64,    65,    66,    67,   215,   216,    69,   130,   217,
     246,   584,   585,    72,   116,   838,   839,   840,    73,   218,
     336,   337,   338,   219,   548,    76,    77,    78,    79,    80,
      81,    82,    83,   258,   259,   260,    85,    86,    87,    88,
      89,    90,   332,    91,   220,    93,    94,   736,   737,   734,
     735,   563,    95,    96,   564,    97,    98,   221,   100,   354,
     355,   356,   374,   671,   490,   551,   552,   672,   554,   555,
     333,   509,   510,   511,   512,   513,   101,   341,   342,   102,
     103,   104,   249,   250,   478,   479,   665,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   868,   231,   644,   232,
     604,   780,   639,   233,   164,   849,   165,   106,   166,   188,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   235,   433,   702,   183,   107,
     184,   108,   265,   438,   185,   186,   236,   110,   253,   237,
     272,   273,   496,   497,   498,   684,   685,   686,   687,   111,
     238,   239,   652,   653,   275,   288,   696,   698,   289,   887,
     296,   276,   277,   290,   294,   299,   298,   516,   517,   518,
     112,   113,   303,   304,   240,   462,   955,   956,   114,   187,
     400,   608,   401,   772
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
      71,   310,   292,   122,   300,   465,   466,   120,   708,   569,
     384,   385,   386,   520,   521,   677,   602,   489,   261,   820,
     402,   264,   691,   472,   500,   248,   561,   120,   481,   251,
      71,   562,   530,   442,   543,   126,   553,   558,   123,   571,
      71,    71,   127,   798,   311,   692,   577,   797,    84,   329,
     329,   690,    74,   306,   352,   314,   536,   538,   384,   647,
     648,   544,   435,   125,   348,    71,   109,   254,   334,   852,
     307,   129,   568,   449,   459,   120,   633,   474,    84,   659,
     898,   581,    74,   352,   790,    68,   312,   930,    84,    84,
      84,   120,   120,    74,   105,   352,   494,   434,   634,   582,
     352,   822,   495,   335,   120,    36,   365,   109,   252,   327,
      36,   473,   823,    84,   328,    68,   353,    74,   450,   307,
     467,   105,    28,   117,   105,   317,    68,   -22,   475,   330,
     862,   109,   362,    70,   234,   105,   121,   121,   959,   266,
     119,    36,   274,   583,   442,   570,   105,   105,   310,    36,
      68,   495,    36,    36,    36,   427,   824,   576,   447,   105,
      70,   131,   745,    70,   105,   912,   673,   144,   330,   105,
     -22,   674,   -22,   879,    70,   499,   435,   878,   122,   467,
      27,    28,    28,   118,   -22,   638,   105,   662,   311,   -72,
     809,    36,   469,   717,    71,   826,   334,   432,    70,   837,
      36,   638,    71,   471,   -22,    71,    71,   363,    70,   406,
     126,   407,   364,    36,    36,   811,   820,   307,   127,   120,
     120,   -72,   543,   477,   331,    70,   769,   248,    71,   306,
     495,   251,   248,   314,   810,   357,   251,   349,   125,    71,
     314,    71,    84,   779,   115,   683,   678,   120,   443,   716,
     677,   435,   658,    84,    84,   609,   610,   611,    74,   120,
     414,   501,   718,   746,   -72,   345,   -72,   444,   -72,   254,
     740,   679,   -72,    71,   254,   121,    84,   741,   -72,   346,
     415,   132,   535,   189,   526,   680,   663,    84,   234,    84,
     121,    68,    84,    74,   293,   358,   234,    84,   -72,   234,
     234,   314,   485,   314,    28,   725,   539,   109,   120,    36,
     252,   105,    36,   105,   105,   252,   486,   442,   467,   527,
      28,    84,   234,   302,   434,    74,    68,   120,   914,   470,
     248,   307,   120,   234,   251,   105,    36,   120,   915,   109,
     121,   105,     5,   895,   586,   313,   481,   587,   121,   307,
     896,    36,    36,   126,   593,   344,   595,   596,    68,   443,
     803,    36,   597,   940,   598,   804,   599,   105,   843,   581,
     435,   802,   254,   121,    70,   403,   267,   268,   524,   404,
     476,   408,   410,   721,   405,    28,    36,   582,   957,   703,
     411,   721,   487,    28,    23,    84,   409,   486,   327,   708,
     841,   305,   105,   528,   704,   486,    70,   310,   434,   900,
     635,   631,   434,   252,   442,   642,   721,    36,    28,   591,
     506,   105,   469,   650,   901,    36,   825,   926,   707,   643,
     486,   105,   643,   643,   800,   347,    35,   412,   434,   413,
     755,    70,   434,   122,   526,   946,    71,   788,    71,   350,
      36,    71,   947,   927,    92,   515,   248,   434,    71,    71,
     251,   314,   646,   705,    71,   537,   359,   120,   120,   681,
     713,    55,    56,    57,   120,   442,   307,   120,   695,   697,
     514,    92,   678,   515,    92,    71,   182,   307,   120,   600,
     351,   603,   434,   126,    84,    92,    84,   766,   254,    84,
     637,   442,   301,   767,   442,   442,    84,    84,  -177,   506,
     314,   434,    84,   675,   706,   580,   637,   707,   434,    92,
     314,    84,   908,   723,   308,   666,   327,   314,   434,    92,
     667,   719,   443,   781,   403,   293,   360,   307,   404,   252,
     234,   367,   234,   405,   502,   234,    92,   120,   503,   442,
     248,   661,   234,   234,   251,   841,   841,   406,   234,   407,
     882,   105,   105,   403,   701,   884,   378,   404,   393,   126,
     105,   362,   405,   368,   293,   394,   395,  -177,  -177,   366,
     434,  -177,  -162,  -162,   774,   800,  -177,   945,  -177,   813,
     565,  -177,   254,   814,   590,   376,   274,   434,   777,   377,
     417,  -112,   750,   396,  -112,   751,   841,   660,   379,   397,
     664,  -177,   406,   105,   407,    84,   643,   398,   487,   782,
     764,   487,   592,   440,   594,   855,   380,   858,   440,   443,
     344,   361,   442,   252,    71,   616,   617,   618,   619,   381,
     189,   105,   477,   120,   416,   607,   314,   454,   743,   899,
     376,   815,   440,   310,   911,   819,   948,   434,   461,   434,
     307,   461,   461,   419,   307,   918,   120,   -73,   418,   965,
     434,   468,   434,   269,   270,   271,   120,   629,   630,   435,
     722,   126,    84,   440,   632,   612,   613,   126,   446,   399,
     443,   614,   615,   441,   445,    92,   448,   122,   314,   -73,
     334,   620,   621,   452,   455,   314,   456,   805,   460,   776,
     463,   464,   492,   488,   480,   493,   443,   278,   504,   443,
     443,    71,   307,   120,   120,   120,   519,    92,   234,   534,
     565,   847,   302,  -250,   851,   789,   144,   105,   791,   792,
     573,   572,   -73,   574,   -73,   279,   -73,   865,   869,   870,
     -73,   343,   575,   578,   579,   293,   -73,   588,   709,   280,
     105,   834,    92,   835,   443,   589,   606,   636,   640,   651,
     654,   656,   889,   682,   657,   683,   -73,   688,   689,   699,
      75,   693,   120,    71,    71,    71,   700,   281,   885,   515,
     282,   283,   728,   284,   714,   285,   715,   729,   730,   476,
     732,  -157,   731,   526,   286,   375,   287,   733,   314,   487,
      75,   126,   559,   742,   352,   105,   105,   376,   105,   738,
     376,    75,   247,   910,   875,   876,  -252,   120,   307,   307,
     376,    84,    84,    84,   747,   376,   748,   376,   749,   376,
     925,   752,   753,   756,   760,    75,   605,   443,   757,   758,
     189,   759,   819,   761,   722,   762,   828,   722,   829,    71,
     375,   763,   770,   307,   120,   370,   874,   371,   373,   765,
     771,   773,   416,   419,   786,   775,   778,   234,   234,   234,
     628,   941,   383,   783,   376,   784,   388,   390,   392,   785,
     787,   255,   262,   795,   796,   799,   806,   807,   641,   812,
     645,   951,  -394,   645,   645,   921,   922,    84,   495,   816,
     437,    36,   821,   831,   836,   863,   307,    71,   842,   844,
     754,   105,   848,   754,   565,   964,   754,   754,   754,   754,
     468,   323,   325,   859,   651,   861,   873,    71,   877,   488,
     883,   676,   488,   293,   880,   892,   888,   293,   881,   893,
     257,   263,   894,   234,   897,   377,   902,   905,   904,   906,
     722,    71,   907,   711,   909,    84,  -273,  -275,   917,   919,
     343,   434,   923,   929,   920,   936,   928,   937,   565,   255,
     565,   924,   942,   943,   316,    84,   944,   949,   950,   958,
     961,   963,   189,   241,   966,   255,   315,   916,   293,   343,
     340,   724,   850,   326,     5,    99,   845,   533,   931,    84,
     864,   234,   339,   309,   856,   124,   744,   557,   857,   833,
     846,    75,  -142,   903,   247,   128,   529,   375,   794,   247,
     375,   234,    99,   866,   793,    99,   867,   458,   257,   567,
     375,   565,   565,   655,   623,   375,    99,   375,   622,   375,
     255,   626,   624,    75,   257,   234,    23,   297,   297,   439,
     808,   625,   872,   295,   293,  -142,   525,  -142,   694,   712,
      99,     0,     0,     0,     0,    99,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,   645,     0,     0,
       0,   256,   256,     0,   375,     0,     0,    99,    35,  -142,
       0,     0,     0,   461,     0,   483,   913,     0,     0,   257,
       0,   323,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   565,   565,   547,   547,     0,   247,     0,     0,
     488,   324,   293,    55,    56,    57,     0,     0,     0,     0,
       0,     0,     0,     0,   293,     0,     0,     0,     0,   934,
       0,     0,     0,   935,     0,     0,     0,     0,   938,   939,
       0,     0,   482,     0,   323,   532,     0,     0,     0,   491,
       0,     0,     0,     0,   315,   724,   827,     0,   724,   256,
       0,   315,     0,     0,   952,     0,     0,   343,   542,     0,
       0,     0,   549,   549,   960,   256,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   853,   854,     0,     0,   255,     0,   340,
     255,     0,     0,     0,     0,     0,   860,   255,     0,   255,
     255,   339,     0,     0,   871,   255,   326,   255,     0,   255,
       0,     0,   315,     0,   326,   541,    99,     0,   340,     0,
     256,   550,   550,   247,     0,     0,     0,   540,     0,   326,
     339,     0,   886,     0,     0,   547,     0,     0,     0,     0,
     890,     0,   891,     0,     0,     0,   257,     0,    99,   257,
       0,   724,     0,     0,   255,     0,   257,     0,   257,   257,
       0,     0,     0,   420,   257,   421,   257,     0,   257,     0,
     262,     0,     0,   262,   262,   484,     0,     0,   422,   853,
       0,   484,     0,    99,     0,     0,     0,     0,     0,     0,
       0,   461,     0,     0,     0,     0,     0,   423,     0,     0,
     668,   424,   425,   549,     0,   426,   427,     0,     0,   323,
     262,     0,   428,   257,     0,     0,   932,   247,     0,   429,
       0,   255,   255,     0,     0,     0,     0,     0,   430,   263,
       0,     0,   263,   263,   531,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   431,     0,   432,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   720,
     954,     0,   550,     0,     0,     0,     0,     0,   727,   263,
       0,     0,   315,     0,     0,   962,     0,     0,     0,     0,
     257,   257,     0,     0,     0,     0,     0,   256,     0,     0,
     256,     0,     0,     0,     0,     0,     0,   256,     0,   256,
     256,     0,     0,     0,     0,   256,   340,   256,     0,   256,
       0,     0,     0,     0,     0,     0,     0,     0,   339,     0,
       0,   326,     0,     0,     0,     0,   726,     0,     0,   547,
     326,   326,     0,  -112,     0,     0,     0,     0,   315,     0,
    -112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -112,     0,     0,     0,   256,     0,     0,   262,  -112,     0,
    -112,     0,     0,     0,     0,  -112,     0,     0,     0,     0,
     256,   547,     0,   256,   256,  -112,     0,     0,     0,  -112,
    -112,   547,  -112,     0,     0,     0,     0,     0,  -112,     0,
    -112,     0,  -112,     0,   297,     0,     0,   549,     0,     0,
     669,  -112,  -112,  -112,     0,  -112,     0,     0,     0,   669,
     256,     0,     0,     0,     0,  -112,   263,     0,     0,     0,
       0,   256,   256,     0,     0,     0,     0,     0,     0,     0,
       0,  -112,  -112,     0,  -112,  -112,  -112,     0,     0,   549,
       0,     0,     0,     0,   830,     0,     0,     0,     0,   549,
       0,     0,     0,     0,     0,     0,   550,   315,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   324,  -112,
    -112,  -112,     0,   -82,   255,     0,     0,   255,     0,     0,
     -82,     0,  -112,  -112,  -112,  -112,  -112,   -82,     0,  -112,
       0,     0,     0,     0,     0,     0,     0,   -82,   550,     0,
       0,     0,     0,     0,     0,   -82,     0,   -82,   550,   326,
       0,     0,   -82,     0,     0,     0,   315,     0,     0,     0,
       0,     0,   -82,     0,     0,     0,   -82,   -82,     0,   -82,
       0,   255,     0,   257,     0,   -82,   257,   -82,     0,   -82,
       0,     0,     0,     0,     0,     0,     0,     0,   -82,   -82,
     -82,     0,   -82,     0,     0,     0,   -82,   256,     0,     0,
       0,     0,   -82,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -82,   -82,
       0,   -82,   -82,   -82,     0,     0,     0,     0,     0,   -83,
     257,     0,     0,     0,     0,     0,   -83,     0,     0,     0,
       0,     0,     0,   -83,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -83,     0,     0,   -82,   -82,   -82,   315,
       0,   -83,     0,   -83,     0,     0,     0,     0,   -83,   -82,
     -82,   -82,   -82,   -82,     0,     0,   -82,     0,   -83,     0,
       0,     0,   -83,   -83,   531,   -83,     0,     0,     0,     0,
       0,   -83,     0,   -83,     0,   -83,     0,     0,     0,     0,
       0,     0,     0,     0,   -83,   -83,   -83,     0,   -83,     0,
       0,     0,   -83,     0,   256,     0,     0,   256,   -83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -83,   -83,     0,   -83,   -83,   -83,
       0,     0,     0,     0,   -80,     0,     0,     0,     0,     0,
       0,   -80,     0,     0,     0,     0,     0,     0,   -80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -80,     0,
       0,   256,   -83,   -83,   -83,     0,   -80,     0,   -80,     0,
       0,     0,     0,   -80,     0,   -83,   -83,   -83,   -83,   -83,
       0,     0,   -83,   -80,     0,     0,     0,   -80,   -80,     0,
     -80,     0,     0,     0,     0,     0,   -80,     0,   -80,     0,
     -80,     0,     0,     0,     0,     0,     0,     0,     0,   -80,
     -80,   -80,     0,   -80,     0,     0,     0,   -80,     0,     0,
       0,     0,     0,   -80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -80,
     -80,     0,   -80,   -80,   -80,     0,     0,     0,     0,   -81,
       0,     0,     0,     0,     0,     0,   -81,     0,     0,     0,
       0,     0,     0,   -81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -81,     0,     0,     0,   -80,   -80,   -80,
       0,   -81,     0,   -81,     0,     0,     0,     0,   -81,     0,
     -80,   -80,   -80,   -80,   -80,     0,     0,   -80,   -81,     0,
       0,     0,   -81,   -81,     0,   -81,     0,     0,     0,     0,
       0,   -81,     0,   -81,     0,   -81,     0,     0,     0,     0,
       0,     0,     0,     0,   -81,   -81,   -81,     0,   -81,     0,
       0,     0,   -81,     0,     0,     0,     0,     0,   -81,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -81,   -81,     0,   -81,   -81,   -81,
       0,     0,     0,     0,   -84,     0,     0,     0,     0,     0,
       0,   -84,     0,     0,     0,     0,     0,     0,   -84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -84,     0,
       0,     0,   -81,   -81,   -81,     0,   -84,     0,   -84,     0,
       0,     0,     0,   -84,     0,   -81,   -81,   -81,   -81,   -81,
       0,     0,   -81,   -84,     0,     0,     0,   -84,   -84,     0,
     -84,     0,     0,     0,     0,     0,   -84,     0,   -84,     0,
     -84,     0,     0,     0,     0,     0,     0,     0,     0,   -84,
     -84,   -84,     0,   -84,     0,     0,     0,   -84,     0,     0,
       0,     0,     0,   -84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -84,
     -84,     0,   -84,   -84,   -84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -84,   -84,   -84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -84,   -84,   -84,   -84,   -84,     0,   133,   -84,     1,     2,
       3,   134,   190,   191,     4,   135,     5,   192,   136,   193,
       0,   194,     6,     0,     7,     0,     8,     9,   137,   138,
     195,   196,     0,   139,   197,   198,    11,    12,     0,     0,
       0,    13,   140,     0,     0,     0,   141,     0,     0,   142,
       0,    14,   199,     0,     0,    15,    16,   143,    17,   144,
      18,     0,   200,     0,    19,    20,    21,    22,    23,   201,
       0,    24,    25,    26,   145,     0,   146,   202,     0,   203,
     149,     0,   150,     0,     0,     0,   204,     0,     0,     0,
       0,   151,     0,     0,   205,     0,   457,   152,   153,   154,
     155,   156,   157,   206,   159,   160,    31,    32,    33,    34,
      35,    36,    37,     0,     0,     0,     0,     0,     0,     0,
       0,   207,    46,     0,     0,     0,   208,     0,     0,     0,
       0,     0,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,    56,    57,     0,   210,
     161,   162,   211,   212,   163,     0,   213,   214,    58,    59,
      60,    61,    62,     0,   133,    63,     1,     2,     3,   134,
     190,   191,     4,   135,     5,   192,   136,   193,     0,   194,
       6,     0,     7,     0,     8,     9,   137,   138,   195,   196,
       0,   139,   197,   198,    11,    12,     0,     0,     0,    13,
     140,     0,     0,     0,   141,     0,     0,   142,     0,    14,
     199,     0,     0,    15,    16,   143,    17,   144,    18,     0,
     200,     0,    19,    20,    21,    22,    23,   201,     0,    24,
      25,    26,   145,     0,   146,   202,     0,   203,   149,     0,
     150,     0,     0,     0,   204,     0,     0,     0,     0,   151,
       0,     0,   205,     0,   649,   152,   153,   154,   155,   156,
     157,   206,   159,   160,    31,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,   207,
      46,     0,     0,     0,   208,     0,     0,     0,     0,     0,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    56,    57,     0,   210,   161,   162,
     211,   212,   163,     0,   213,   214,    58,    59,    60,    61,
      62,     0,   133,    63,     1,     2,     3,   134,   190,   191,
       4,   135,     5,   192,   136,   193,     0,   194,     6,     0,
       7,     0,     8,     9,   137,   138,   195,   196,     0,   139,
     197,   198,    11,    12,     0,     0,     0,    13,   140,     0,
       0,     0,   141,     0,     0,   142,     0,    14,   199,     0,
       0,    15,    16,   143,    17,   144,    18,     0,   200,     0,
      19,    20,    21,    22,    23,   201,     0,    24,    25,    26,
     145,     0,   146,   202,     0,   203,   149,     0,   150,     0,
       0,     0,   204,     0,     0,     0,     0,   151,     0,     0,
     205,     0,     0,   152,   153,   154,   155,   156,   157,   206,
     159,   160,    31,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,   207,    46,     0,
       0,     0,   208,     0,     0,     0,     0,     0,     0,     0,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    55,    56,    57,     0,   210,   161,   162,   211,   212,
     163,     0,   213,   214,    58,    59,    60,    61,    62,     0,
     133,    63,     1,     2,     3,   134,     0,     0,     4,   135,
       5,     0,   136,     0,     0,     0,     6,     0,     7,     0,
       8,     9,   137,   138,     0,     0,     0,   139,    10,     0,
      11,    12,     0,     0,     0,    13,   140,     0,     0,     0,
     141,     0,     0,   142,     0,    14,     0,     0,     0,    15,
      16,   143,    17,   144,    18,     0,     0,     0,    19,    20,
      21,    22,    23,     0,     0,    24,    25,    26,   145,     0,
     146,   202,     0,   203,   149,     0,   150,     0,     0,     0,
      29,     0,     0,     0,     0,   151,     0,     0,     0,     0,
       0,   152,   153,   154,   155,   156,   157,   206,   159,   160,
      31,    32,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
      56,    57,     0,     0,   161,   162,     0,     0,   163,     0,
       0,     0,    58,    59,    60,    61,    62,   133,     0,    63,
       2,     3,   134,     0,     0,     4,   135,     5,     0,   136,
       0,     0,     0,     6,     0,     7,     0,     8,     9,   137,
     138,     0,     0,     0,   139,    10,     0,    11,    12,     0,
       0,     0,    13,   140,     0,     0,     0,   141,     0,     0,
     142,     0,    14,     0,     0,     0,    15,    16,   143,    17,
     144,    18,     0,     0,     0,    19,    20,    21,    22,    23,
       0,     0,     0,     0,     0,   145,     0,   146,   147,     0,
     148,   149,     0,   150,     0,     0,     0,     0,     0,     0,
       0,     0,   151,     0,     0,   205,     0,     0,   152,   153,
     154,   155,   156,   157,   158,   159,   160,     0,    32,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,    56,    57,     0,
       0,   161,   162,     0,     0,   163,     0,     0,     0,    58,
      59,    60,    61,    62,   133,     0,    63,     2,     3,   134,
       0,     0,     4,   135,     5,     0,   136,     0,     0,     0,
       6,     0,     7,     0,     8,     9,   137,   138,     0,     0,
       0,   139,    10,     0,    11,    12,     0,     0,     0,    13,
     140,     0,     0,     0,   141,     0,     0,   142,     0,    14,
       0,     0,     0,    15,    16,   143,    17,   144,    18,     0,
       0,     0,    19,    20,    21,    22,    23,     0,     0,     0,
       0,     0,   145,     0,   146,   202,     0,   203,   149,     0,
     150,     0,     0,     0,     0,     0,     0,     0,     0,   151,
       0,     0,   205,     0,     0,   152,   153,   154,   155,   156,
     157,   158,   159,   160,     0,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    56,    57,     0,     0,   161,   162,
       0,     0,   163,     0,     0,     0,    58,    59,    60,    61,
      62,   133,     0,    63,     2,     3,   134,     0,     0,     4,
     135,     5,     0,   136,     0,     0,     0,     6,     0,     7,
       0,     8,     9,   137,   138,     0,     0,     0,   139,    10,
       0,    11,    12,     0,     0,     0,    13,   140,     0,     0,
       0,   141,     0,     0,   142,     0,    14,     0,     0,     0,
      15,    16,   143,    17,   144,    18,     0,     0,     0,    19,
      20,    21,    22,    23,     0,     0,     0,     0,     0,   145,
       0,   146,   202,     0,   203,   149,     0,   150,     0,     0,
       0,   204,     0,     0,     0,     0,   151,     0,     0,     0,
       0,     0,   152,   153,   154,   155,   156,   157,   158,   159,
     160,     0,    32,    33,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    56,    57,     0,     0,   161,   162,     0,     0,   163,
       0,     0,     0,    58,    59,    60,    61,    62,   133,     0,
      63,     2,     3,   134,     0,     0,     4,   135,     5,     0,
     136,     0,     0,     0,     6,     0,     7,     0,     8,     9,
     137,   138,     0,     0,     0,   139,    10,     0,    11,    12,
       0,     0,     0,    13,   140,     0,     0,     0,   141,     0,
       0,   142,     0,    14,     0,     0,     0,    15,    16,   143,
      17,   144,    18,     0,     0,     0,    19,    20,    21,    22,
      23,     0,     0,     0,     0,     0,   145,     0,   146,   147,
       0,   148,   149,     0,   150,     0,     0,     0,     0,     0,
       0,     0,     0,   151,     0,     0,     0,     0,     0,   152,
     153,   154,   155,   156,   157,   158,   159,   160,     0,    32,
      33,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    55,    56,    57,
       0,     0,   161,   162,     0,     0,   163,     0,     0,     0,
      58,    59,    60,    61,    62,     0,     0,    63,     1,     2,
       3,     0,     0,     0,     4,     0,     5,     0,     0,     0,
       0,     0,     6,     0,     7,     0,     8,     9,     0,     0,
       0,     0,     0,     0,    10,     0,    11,    12,     0,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    15,    16,     0,    17,     0,
      18,     0,     0,     0,    19,    20,    21,    22,    23,     0,
       0,    24,    25,    26,     0,     0,     0,    27,     0,    28,
       0,     0,     0,     0,     0,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,     0,    46,     0,     0,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    50,     0,    51,
       0,    52,    53,    54,     0,    55,    56,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    59,
      60,    61,    62,     0,     0,    63,     1,     2,     3,     0,
       0,     0,     4,     0,     5,     0,     0,     0,     0,     0,
       6,     0,     7,     0,     8,     9,     0,     0,     0,     0,
       0,     0,    10,     0,    11,    12,     0,     0,     0,    13,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,     0,    15,    16,     0,    17,     0,    18,     0,
       0,     0,    19,    20,    21,    22,    23,     0,     0,    24,
      25,    26,     0,     0,     0,    27,     0,    28,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,     0,     0,    31,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     1,     2,     3,    47,     0,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     6,     0,     7,     0,     8,
       9,     0,     0,    55,    56,    57,     0,    10,     0,    11,
      12,     0,     0,     0,    13,     0,    58,    59,    60,    61,
      62,     0,     0,    63,    14,     0,     0,     0,    15,    16,
       0,    17,     0,    18,     0,     0,     0,    19,    20,    21,
      22,    23,     0,     0,    24,    25,    26,     0,     0,     0,
      27,     0,    28,     0,     0,     0,     0,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,     0,     0,    31,
      32,    33,    34,    35,    36,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     2,     3,     0,
       0,     0,     4,     0,     5,     0,     0,     0,     0,     0,
       6,     0,     7,     0,     8,     9,     0,     0,    55,    56,
      57,     0,   242,     0,    11,    12,     0,     0,     0,    13,
       0,    58,    59,    60,    61,    62,     0,     0,    63,    14,
       0,     0,     0,    15,    16,     0,    17,     0,    18,     0,
       0,     0,    19,    20,    21,    22,    23,     0,     0,    24,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   243,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   566,     0,     0,     0,     0,     0,
       0,   244,     0,     0,     0,    32,    33,    34,    35,    36,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,     2,     3,   245,     0,     0,     4,     0,     5,
       0,     0,     0,     0,     0,     6,     0,     7,     0,     8,
       9,     0,     0,    55,    56,    57,     0,   242,     0,    11,
      12,     0,     0,     0,    13,     0,    58,    59,    60,    61,
      62,     0,     0,    63,    14,     0,     0,     0,    15,    16,
       0,    17,     0,    18,     0,     0,     0,    19,    20,    21,
      22,    23,     0,     0,    24,     2,     3,     0,     0,     0,
       4,     0,     5,     0,     0,     0,     0,     0,     6,   243,
       7,     0,     8,     9,     0,     0,     0,     0,     0,   739,
     242,     0,    11,    12,     0,     0,   244,    13,     0,     0,
      32,    33,    34,    35,    36,    37,     0,    14,     0,     0,
       0,    15,    16,     0,    17,    46,    18,     0,     0,   245,
      19,    20,    21,    22,    23,     0,     0,    24,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    55,    56,
      57,     0,   243,     0,     0,     0,     0,     0,     0,     0,
       0,    58,    59,    60,    61,    62,     0,     0,    63,   244,
       0,     0,     0,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,     0,
       2,     3,   245,     0,     0,     4,     0,     5,     0,     0,
       0,     0,     0,     6,     0,     7,     0,     8,     9,     0,
       0,    55,    56,    57,     0,   242,     0,    11,    12,     0,
       0,     0,    13,     0,    58,    59,    60,    61,    62,     0,
       0,    63,    14,     0,     0,     0,    15,    16,     0,    17,
       0,    18,     0,     0,     0,    19,    20,    21,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     0,   485,   670,
      28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   486,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    32,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     0,     0,     0,
       4,     0,     5,     0,     0,     0,     0,     0,     6,     0,
       7,     0,     8,     9,     0,     0,    55,    56,    57,     0,
      10,     0,    11,    12,     0,     0,     0,    13,     0,    58,
      59,    60,    61,    62,     0,     0,    63,    14,     0,     0,
       0,    15,    16,     0,    17,     0,    18,     0,     0,     0,
      19,    20,    21,    22,    23,     0,     0,     0,     0,     0,
       0,     0,     0,   721,   670,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   486,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     3,     0,     0,     0,     4,     0,     5,     0,     0,
       0,     0,     0,     6,     0,     7,     0,     8,     9,     0,
       0,    55,    56,    57,     0,   545,     0,    11,    12,     0,
       0,     0,    13,     0,    58,    59,    60,    61,    62,     0,
       0,    63,    14,     0,     0,     0,    15,    16,     0,    17,
       0,    18,     0,     0,     0,    19,    20,    21,    22,    23,
       0,     0,     0,     2,     3,     0,     0,     0,     4,   546,
       5,     0,     0,     0,     0,     0,     6,     0,     7,     0,
       8,     9,     0,     0,     0,     0,     0,     0,   545,     0,
      11,    12,     0,     0,     0,    13,     0,     0,    32,    33,
      34,    35,    36,    37,     0,    14,     0,     0,     0,    15,
      16,     0,    17,     0,    18,     0,     0,     0,    19,    20,
      21,    22,    23,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   556,     0,     0,     0,    55,    56,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      59,    60,    61,    62,     0,     0,    63,     0,     0,     0,
       0,    32,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       0,     0,     0,     4,     0,     5,     0,     0,     0,     0,
       0,     6,     0,     7,     0,     8,     9,     0,     0,    55,
      56,    57,     0,   242,     0,    11,    12,     0,     0,     0,
      13,     0,    58,    59,    60,    61,    62,     0,     0,    63,
      14,     0,     0,     0,    15,    16,     0,    17,     0,    18,
       0,     0,     0,    19,    20,    21,    22,    23,     0,     0,
       0,     2,     3,     0,     0,     0,     4,   801,     5,     0,
       0,     0,     0,     0,     6,     0,     7,     0,     8,     9,
       0,     0,     0,     0,     0,     0,   242,     0,    11,    12,
       0,     0,     0,    13,     0,     0,    32,    33,    34,    35,
      36,    37,     0,    14,     0,     0,     0,    15,    16,     0,
      17,     0,    18,     0,     0,   832,    19,    20,    21,    22,
      23,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    56,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    59,    60,
      61,    62,     0,     0,    63,     0,     0,     0,     0,    32,
      33,    34,    35,    36,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,     4,     0,     5,     0,     0,     0,     0,     0,     6,
       0,     7,     0,     8,     9,     0,     0,    55,    56,    57,
       0,   242,     0,    11,    12,     0,     0,     0,    13,     0,
      58,    59,    60,    61,    62,     0,     0,    63,    14,     0,
       0,     0,    15,    16,     0,    17,     0,    18,     0,     0,
       0,    19,    20,    21,    22,    23,     0,     0,     2,     3,
       0,     0,     0,     4,     0,     5,     0,     0,     0,     0,
       0,     6,     0,     7,     0,     8,     9,     0,     0,     0,
       0,     0,     0,   242,     0,    11,    12,     0,     0,     0,
      13,     0,     0,     0,    32,    33,    34,    35,    36,    37,
      14,     0,     0,     0,    15,    16,     0,    17,     0,    18,
       0,     0,     0,    19,    20,    21,    22,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    55,    56,    57,     0,     0,     0,     0,     0,
       0,     0,     0,   205,     0,    58,    59,    60,    61,    62,
       0,     0,    63,     0,     0,     0,    32,    33,    34,    35,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     0,     0,     0,     4,     0,
       5,     0,     0,     0,     0,     0,     6,     0,     7,     0,
       8,     9,     0,     0,    55,    56,    57,     0,   242,     0,
      11,    12,     0,     0,     0,    13,     0,    58,    59,    60,
      61,    62,     0,     0,    63,    14,     0,     0,     0,    15,
      16,     0,    17,     0,    18,     0,     0,     0,    19,    20,
      21,    22,    23,     0,     0,     0,  -112,     0,     0,     0,
       0,     0,     0,  -112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -112,     0,     0,     0,     0,     0,     0,
       0,  -112,     0,  -112,     0,     0,     0,     0,  -112,     0,
       0,    32,    33,    34,    35,     0,    37,     0,  -112,     0,
       0,     0,  -112,  -112,     0,  -112,     0,     0,     0,     0,
       0,  -112,     0,  -112,     0,  -112,     0,     0,     0,     0,
       2,     0,     0,     0,  -112,     0,  -112,     5,     0,    55,
      56,    57,   451,     0,     0,     0,     0,     8,     0,     0,
       0,     0,    58,    59,    60,    61,    62,    11,     0,    63,
       0,     0,   318,     0,  -112,  -112,     0,  -112,  -112,  -112,
       0,     0,    14,     0,     0,     0,   319,   320,     0,    17,
       0,     0,     0,     0,     0,    19,     0,   321,     0,    23,
       0,     0,     0,     0,     2,     0,     0,     0,  -101,     0,
    -101,     5,  -112,  -112,  -112,     0,     0,     0,     0,     0,
       0,     8,  -101,     0,     0,  -112,  -112,  -112,  -112,  -112,
       0,    11,  -112,     0,     0,     0,   318,     0,   322,    33,
       0,    35,    36,    37,     0,     0,    14,     0,     0,     0,
     319,   320,     0,    17,     0,     0,     0,     0,     0,    19,
       0,   321,     0,    23,     0,     0,     0,     0,     0,     0,
       0,     0,   -99,     0,   -99,     0,    55,    56,    57,     0,
       0,     0,     0,     0,     0,     0,   -99,     0,     0,    58,
      59,    60,    61,    62,     0,     0,    63,     0,     0,     0,
       0,     0,   322,    33,     0,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,     0,     0,     0,     0,
      55,    56,    57,    11,     0,     0,     0,     0,   318,     0,
       0,     0,     0,    58,    59,    60,    61,    62,    14,     0,
      63,     0,   319,   320,     0,    17,     0,     0,     0,     0,
       0,    19,     0,   321,     0,    23,     0,     0,     0,     2,
       0,     0,     0,     0,     0,   -64,     5,     0,   -64,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     0,     0,     0,
       0,   318,     0,     0,   322,    33,     0,    35,    36,    37,
       0,    14,     0,     0,     0,   319,   320,     0,    17,     0,
       0,     0,     0,     0,    19,     0,   321,     0,    23,     0,
       0,     0,     0,     2,     0,     0,     0,     0,   -62,     0,
       5,   -62,    55,    56,    57,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      11,     0,    63,     0,     0,   318,     0,   322,    33,     0,
      35,    36,    37,     0,     0,    14,     0,     0,     0,   319,
     320,     0,    17,     0,     0,     0,     0,     0,    19,     0,
     321,     0,    23,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     5,     0,    55,    56,    57,     0,     0,
     -69,     0,     0,     8,     0,     0,     0,     0,    58,    59,
      60,    61,    62,    11,     0,    63,     0,     0,   318,     0,
       0,   322,    33,     0,    35,    36,    37,     0,    14,     0,
       0,     0,   319,   320,     0,    17,     0,     0,     0,     0,
       0,    19,     0,   321,     0,    23,     0,     0,     0,     0,
       2,     0,     0,     0,     0,     0,     0,     5,     0,    55,
      56,    57,     0,   -67,     0,     0,     0,     8,     0,     0,
       0,     0,    58,    59,    60,    61,    62,    11,     0,    63,
       0,     0,   318,     0,   322,    33,     0,    35,    36,    37,
       0,     0,    14,     0,     0,     0,   319,   320,     0,    17,
       0,     0,     0,     0,     0,    19,     0,   321,     0,    23,
       0,     0,     0,     2,     0,     0,     0,     0,     0,     0,
       5,     0,    55,    56,    57,     0,     0,     0,     0,     0,
       8,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      11,     0,    63,     0,     0,   318,     0,     0,   322,    33,
       0,    35,    36,    37,     0,    14,     0,     0,     0,   319,
     320,     0,    17,     0,     0,     0,     0,     0,    19,     0,
     321,     0,    23,     0,     0,     0,     0,     2,     0,     0,
       0,     0,     0,     0,     5,     0,    55,    56,    57,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,    58,
      59,    60,    61,    62,    11,     0,    63,     0,     0,   318,
       0,   322,    33,     0,    35,    36,    37,     0,     0,    14,
       0,     0,     0,   319,   320,     0,    17,     0,     0,     0,
       0,     0,    19,     0,   321,     0,    23,     0,     0,     0,
       2,     0,     0,     0,     0,     0,     0,     5,     0,    55,
      56,    57,     0,     0,     0,     0,     0,     8,     0,     0,
       0,     0,    58,    59,    60,    61,    62,    11,     0,    63,
       0,     0,   318,     0,     0,   322,    33,     0,    35,    36,
      37,     0,    14,     0,     0,     0,   319,   320,     0,    17,
       0,     0,     0,     0,     0,    19,     0,   321,     0,    23,
       0,     0,     0,     0,     2,     0,     0,     0,     0,     0,
       0,     5,     0,    55,    56,    57,     0,     0,     0,     0,
       0,     8,     0,     0,     0,     0,    58,    59,    60,    61,
      62,    11,     0,    63,     0,     0,   318,     0,   322,    33,
       0,    35,    36,    37,     0,     0,    14,     0,     0,     0,
     319,   320,     0,    17,     0,     0,     0,     0,     0,    19,
       0,   321,     0,    23,     0,     0,     0,     2,     0,     0,
       0,     0,     0,     0,     5,     0,    55,    56,    57,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,    58,
      59,    60,    61,    62,    11,     0,    63,     0,     0,   318,
       0,     0,   322,    33,     0,    35,    36,    37,     0,    14,
       0,     0,     0,   319,   320,     0,    17,     0,     0,     0,
       0,     0,    19,     0,   321,     0,    23,     0,     0,     0,
       0,     2,     0,     0,     0,     0,     0,     0,     5,     0,
      55,    56,    57,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,    58,    59,    60,    61,    62,    11,     0,
      63,     0,     0,   318,     0,   322,    33,     0,    35,    36,
      37,     0,     0,    14,     0,     0,     0,   319,   320,     0,
      17,     0,     0,     0,     0,     0,    19,     0,   321,     0,
      23,     0,     0,     0,     2,     0,     0,     0,     0,     0,
       0,     5,     0,    55,    56,    57,     0,     0,     0,     0,
       0,     8,     0,     0,     0,     0,    58,    59,    60,    61,
      62,    11,     0,    63,     0,     0,   318,     0,     0,   322,
      33,     0,    35,    36,    37,     0,    14,     0,     0,     0,
     319,   320,     0,    17,     0,     0,     0,     0,     0,    19,
       0,   321,     0,    23,     0,     0,     0,     0,     2,     0,
       0,     0,     0,     0,     0,     5,     0,    55,    56,    57,
       0,     0,     0,     0,     0,     8,     0,     0,     0,     0,
      58,    59,    60,    61,    62,    11,     0,    63,     0,     0,
     318,     0,   322,    33,     0,    35,    36,    37,     0,     0,
      14,     0,     0,     0,   319,   320,     0,    17,     0,     0,
       0,     0,     0,    19,     0,   321,     0,    23,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    56,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    61,    62,     0,     0,
      63,     0,     0,     0,     0,     0,   322,    33,     0,    35,
      36,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,   134,     0,     0,     0,   135,     5,     0,   136,     0,
       0,     0,     0,     0,    55,    56,    57,     0,   137,   138,
       0,     0,     0,   139,   121,     0,     0,    58,    59,    60,
      61,    62,   140,     0,    63,     0,   141,     0,     0,   142,
       0,     0,     0,     0,     0,     0,     0,   143,   559,   144,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
       0,     0,     0,     0,   145,     0,   146,   147,     0,   560,
     149,     0,   150,     0,     0,     0,     0,     0,     0,     0,
       0,   151,     0,     0,     0,     0,     0,   152,   153,   154,
     155,   156,   157,   158,   159,   160,     0,     0,     0,     0,
      35,     0,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     505,     0,     0,     0,     0,    55,    56,    57,   140,     0,
     161,   162,   141,     0,   163,   142,     0,     0,     0,     0,
       0,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,   506,
       0,     0,     0,     0,     0,     0,     0,   507,     0,     0,
     291,     0,   508,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     817,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,   506,
       0,     0,     0,     0,     0,     0,     0,   507,     0,     0,
     291,     0,   818,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     817,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,   506,
       0,     0,     0,     0,     0,     0,     0,   507,     0,     0,
     291,     0,   933,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     505,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,   506,
       0,     0,     0,     0,     0,     0,     0,   507,     0,     0,
     291,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
     291,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,   453,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   522,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,   523,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,   601,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,   627,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,   710,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
     754,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,   768,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,   953,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   436,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   147,     0,   560,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   369,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   372,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   382,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   387,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   389,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   133,     0,     0,     0,     0,   134,     0,     0,
       0,   135,     0,     0,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   138,     0,     0,     0,   139,
     121,     0,     0,     0,     0,     0,     0,     0,   140,     0,
       0,     0,   141,     0,     0,   142,   161,   162,     0,     0,
     163,     0,     0,   143,     0,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,   146,   391,     0,   148,   149,     0,   150,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,   157,   158,
     159,   160,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   161,   162,     0,     0,
     163
};

static const short int yycheck[] =
{
       0,    70,    50,    27,    53,   213,   214,     7,   512,   350,
     158,   159,   160,   300,   301,   487,   396,   259,    43,   703,
     168,    44,   497,   244,   271,    42,   346,    27,   249,    42,
      30,   346,   312,   191,   341,    28,   344,   345,    27,   351,
      40,    41,    30,   674,    75,   499,   358,   673,     0,     6,
       6,    79,     0,    65,    32,    77,   331,   332,   206,   455,
     456,   341,    57,    28,    32,    65,     0,    42,    92,   765,
      70,    32,    32,    32,   208,    75,    61,    32,    30,    83,
      75,    14,    30,    32,    83,     0,    75,   896,    40,    41,
      42,    91,    92,    41,     0,    32,    75,    79,    83,    32,
      32,    83,   130,    92,   104,   109,   131,    41,    42,    79,
     109,   245,    94,    65,    84,    30,    94,    65,    77,   119,
      75,    27,    77,    32,    30,    77,    41,    32,    83,    86,
      86,    65,   125,     0,    40,    41,    32,    32,   947,    45,
       7,   109,    48,    76,   302,    94,    52,    53,   217,   109,
      65,   130,   109,   109,   109,    46,   138,    94,   194,    65,
      27,    75,    94,    30,    70,   861,   486,    57,    86,    75,
      75,   486,    77,   804,    41,    75,    57,   803,   202,    75,
      75,    77,    77,    92,    89,   448,    92,    83,   219,     0,
      76,   109,   228,   534,   194,    76,   220,    88,    65,    89,
     109,   464,   202,   239,   109,   205,   206,    79,    75,    78,
     203,    80,    84,   109,   109,   690,   900,   217,   206,   219,
     220,    32,   529,   247,    91,    92,   606,   244,   228,   241,
     130,   244,   249,   255,   688,    32,   249,   104,   203,   239,
     262,   241,   194,   639,    66,   131,   488,   247,   191,   529,
     722,    57,   473,   205,   206,   403,   404,   405,   206,   259,
      23,   273,   537,   575,    75,    75,    77,   191,    79,   244,
      76,    75,    83,   273,   249,    32,   228,    83,    89,    89,
      43,    75,   330,    39,   308,    89,    86,   239,   194,   241,
      32,   206,   244,   241,    50,    92,   202,   249,   109,   205,
     206,   323,    75,   325,    77,   547,   337,   241,   308,   109,
     244,   217,   109,   219,   220,   249,    89,   475,    75,   308,
      77,   273,   228,    89,    79,   273,   241,   327,    86,    84,
     347,   331,   332,   239,   347,   241,   109,   337,    86,   273,
      32,   247,    14,    76,   369,    84,   567,   372,    32,   349,
      83,   109,   109,   346,   379,    75,   381,   382,   273,   302,
     680,   109,   387,    86,   389,   680,   391,   273,   748,    14,
      57,   679,   347,    32,   241,    73,   122,   123,   302,    77,
     247,    36,    30,    75,    82,    77,   109,    32,    75,    79,
      38,    75,   259,    77,    66,   347,    51,    89,    79,   903,
     741,     0,   308,    84,    94,    89,   273,   476,    79,    79,
     446,   436,    79,   347,   572,   451,    75,   109,    77,    90,
      81,   327,   458,   459,    94,   109,   713,    94,    89,   452,
      89,   337,   455,   456,   676,    92,   108,    85,    79,    87,
     588,   308,    79,   467,   468,    76,   446,   655,   448,    75,
     109,   451,    83,    94,     0,    92,   473,    79,   458,   459,
     473,   483,    84,   511,   464,   332,    76,   467,   468,   492,
     519,   143,   144,   145,   474,   633,   476,   477,   503,   504,
      89,    27,   724,    92,    30,   485,    38,   487,   488,   395,
      92,   397,    79,   486,   446,    41,   448,    84,   473,   451,
     448,   659,    54,    90,   662,   663,   458,   459,     6,    81,
     532,    79,   464,   486,    86,    76,   464,    89,    79,    65,
     542,   473,    90,   547,    70,    79,    79,   549,    79,    75,
      84,    84,   475,    84,    73,   291,    76,   537,    77,   473,
     446,    75,   448,    82,    79,   451,    92,   547,    83,   707,
     567,   475,   458,   459,   567,   896,   897,    78,   464,    80,
     807,   467,   468,    73,   507,   812,    75,    77,    40,   562,
     476,   564,    82,    32,   330,    47,    48,    75,    76,   131,
      79,    79,    75,    76,    83,   827,    84,   928,    86,    79,
     346,    89,   567,    83,    76,   147,   502,    79,   634,   151,
      91,    76,    76,    75,    79,    79,   947,   474,    75,    81,
     477,   109,    78,   519,    80,   567,   639,    89,   485,   643,
      76,   488,   378,    79,   380,    76,    75,   775,    79,   572,
      75,    76,   790,   567,   634,   410,   411,   412,   413,    75,
     396,   547,   666,   643,    74,   401,   668,   199,   572,    76,
     202,   699,    79,   722,    76,   703,    76,    79,   210,    79,
     660,   213,   214,     4,   664,   873,   666,     0,    93,    76,
      79,   217,    79,   125,   126,   127,   676,   433,   434,    57,
     547,   674,   634,    79,   440,   406,   407,   680,    83,   161,
     633,   408,   409,    84,    84,   241,    75,   721,   720,    32,
     724,   414,   415,    75,    75,   727,    75,   680,    32,   633,
      84,    75,    79,   259,    84,    75,   659,     4,    83,   662,
     663,   721,   722,   723,   724,   725,    79,   273,   634,    75,
     486,   756,    89,    92,   759,   659,    57,   643,   662,   663,
      94,    86,    75,    79,    77,    32,    79,   783,   784,   785,
      83,    93,    92,    32,    76,   511,    89,    76,   514,    46,
     666,   734,   308,   736,   707,    76,    75,    67,    84,    32,
      84,    84,   820,    32,    84,   131,   109,    75,   125,    83,
       0,   125,   782,   783,   784,   785,    32,    74,   813,    92,
      77,    78,    76,    80,    90,    82,    90,    79,    76,   666,
      76,    90,    79,   827,    91,   147,    93,    76,   830,   676,
      30,   804,    56,    94,    32,   721,   722,   369,   724,    90,
     372,    41,    42,   859,   797,   798,    92,   827,   828,   829,
     382,   783,   784,   785,    94,   387,    75,   389,    76,   391,
     888,    76,    76,    79,    76,    65,   398,   790,    79,    79,
     606,    79,   900,    76,   721,    76,   723,   724,   725,   859,
     202,    76,    79,   863,   864,   140,   790,   142,   143,    83,
     162,   627,    74,     4,    83,    76,    75,   783,   784,   785,
     432,   917,   157,    76,   436,    76,   161,   162,   163,    76,
      79,    43,    44,    76,    76,    90,    76,    76,   450,    76,
     452,   937,    90,   455,   456,   878,   879,   859,   130,    90,
     185,   109,    90,    32,    84,   782,   916,   917,    94,    76,
      92,   827,    32,    92,   680,   961,    92,    92,    92,    92,
     476,    83,    84,    83,    32,    84,    84,   937,    76,   485,
      76,   487,   488,   699,    90,    90,    83,   703,   123,    90,
      43,    44,    32,   859,    79,   507,    76,    79,    76,    76,
     827,   961,    90,   515,    79,   917,    21,    21,    21,    90,
     312,    79,   125,    84,    90,    84,    90,    76,   734,   131,
     736,   125,    84,    90,    77,   937,    90,    76,    79,    84,
      76,    76,   748,    41,    84,   147,    77,   864,   754,   341,
      93,   547,   758,    84,    14,     0,   751,   327,   897,   961,
     782,   917,    93,    70,   770,    27,   574,   345,   774,   731,
     754,   241,    32,   848,   244,    30,   312,   369,   666,   249,
     372,   937,    27,   783,   664,    30,   783,   205,   131,   347,
     382,   797,   798,   464,   417,   387,    41,   389,   416,   391,
     202,   427,   418,   273,   147,   961,    66,    52,    53,   185,
     685,   419,   787,    51,   820,    75,   303,    77,   502,   517,
      65,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      75,    -1,    -1,    -1,    -1,    -1,    -1,   639,    -1,    -1,
      -1,    43,    44,    -1,   436,    -1,    -1,    92,   108,   109,
      -1,    -1,    -1,   655,    -1,   257,   862,    -1,    -1,   202,
      -1,   263,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   878,   879,   344,   345,    -1,   347,    -1,    -1,
     676,    83,   888,   143,   144,   145,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   900,    -1,    -1,    -1,    -1,   905,
      -1,    -1,    -1,   909,    -1,    -1,    -1,    -1,   914,   915,
      -1,    -1,   255,    -1,   316,   317,    -1,    -1,    -1,   262,
      -1,    -1,    -1,    -1,   255,   721,   722,    -1,   724,   131,
      -1,   262,    -1,    -1,   940,    -1,    -1,   529,   340,    -1,
      -1,    -1,   344,   345,   950,   147,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   765,   766,    -1,    -1,   369,    -1,   312,
     372,    -1,    -1,    -1,    -1,    -1,   778,   379,    -1,   381,
     382,   312,    -1,    -1,   786,   387,   317,   389,    -1,   391,
      -1,    -1,   323,    -1,   325,   338,   241,    -1,   341,    -1,
     202,   344,   345,   473,    -1,    -1,    -1,   338,    -1,   340,
     341,    -1,   814,    -1,    -1,   485,    -1,    -1,    -1,    -1,
     822,    -1,   824,    -1,    -1,    -1,   369,    -1,   273,   372,
      -1,   827,    -1,    -1,   436,    -1,   379,    -1,   381,   382,
      -1,    -1,    -1,     3,   387,     5,   389,    -1,   391,    -1,
     452,    -1,    -1,   455,   456,   257,    -1,    -1,    18,   861,
      -1,   263,    -1,   308,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   873,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
     482,    41,    42,   485,    -1,    45,    46,    -1,    -1,   491,
     492,    -1,    52,   436,    -1,    -1,   898,   567,    -1,    59,
      -1,   503,   504,    -1,    -1,    -1,    -1,    -1,    68,   452,
      -1,    -1,   455,   456,   316,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   541,
     942,    -1,   485,    -1,    -1,    -1,    -1,    -1,   550,   492,
      -1,    -1,   483,    -1,    -1,   957,    -1,    -1,    -1,    -1,
     503,   504,    -1,    -1,    -1,    -1,    -1,   369,    -1,    -1,
     372,    -1,    -1,    -1,    -1,    -1,    -1,   379,    -1,   381,
     382,    -1,    -1,    -1,    -1,   387,   529,   389,    -1,   391,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   529,    -1,
      -1,   532,    -1,    -1,    -1,    -1,   549,    -1,    -1,   679,
     541,   542,    -1,     7,    -1,    -1,    -1,    -1,   549,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,   436,    -1,    -1,   639,    32,    -1,
      34,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
     452,   721,    -1,   455,   456,    49,    -1,    -1,    -1,    53,
      54,   731,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      64,    -1,    66,    -1,   519,    -1,    -1,   679,    -1,    -1,
     482,    75,    76,    77,    -1,    79,    -1,    -1,    -1,   491,
     492,    -1,    -1,    -1,    -1,    89,   639,    -1,    -1,    -1,
      -1,   503,   504,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   105,   106,    -1,   108,   109,   110,    -1,    -1,   721,
      -1,    -1,    -1,    -1,   726,    -1,    -1,    -1,    -1,   731,
      -1,    -1,    -1,    -1,    -1,    -1,   679,   668,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   550,   143,
     144,   145,    -1,     0,   756,    -1,    -1,   759,    -1,    -1,
       7,    -1,   156,   157,   158,   159,   160,    14,    -1,   163,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,   721,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    34,   731,   720,
      -1,    -1,    39,    -1,    -1,    -1,   727,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,   813,    -1,   756,    -1,    62,   759,    64,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    79,    -1,    -1,    -1,    83,   639,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,
      -1,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,     0,
     813,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,   143,   144,   145,   830,
      -1,    32,    -1,    34,    -1,    -1,    -1,    -1,    39,   156,
     157,   158,   159,   160,    -1,    -1,   163,    -1,    49,    -1,
      -1,    -1,    53,    54,   726,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    -1,    79,    -1,
      -1,    -1,    83,    -1,   756,    -1,    -1,   759,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,    -1,   108,   109,   110,
      -1,    -1,    -1,    -1,     0,    -1,    -1,    -1,    -1,    -1,
      -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,   813,   143,   144,   145,    -1,    32,    -1,    34,    -1,
      -1,    -1,    -1,    39,    -1,   156,   157,   158,   159,   160,
      -1,    -1,   163,    49,    -1,    -1,    -1,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    -1,    79,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,   108,   109,   110,    -1,    -1,    -1,    -1,     0,
      -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,   143,   144,   145,
      -1,    32,    -1,    34,    -1,    -1,    -1,    -1,    39,    -1,
     156,   157,   158,   159,   160,    -1,    -1,   163,    49,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    -1,    79,    -1,
      -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,    -1,   108,   109,   110,
      -1,    -1,    -1,    -1,     0,    -1,    -1,    -1,    -1,    -1,
      -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,   143,   144,   145,    -1,    32,    -1,    34,    -1,
      -1,    -1,    -1,    39,    -1,   156,   157,   158,   159,   160,
      -1,    -1,   163,    49,    -1,    -1,    -1,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    -1,    79,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
     106,    -1,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,   144,   145,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,   160,    -1,     4,   163,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    20,    -1,    22,    -1,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    39,    40,    -1,    -1,    -1,    44,    -1,    -1,    47,
      -1,    49,    50,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    60,    -1,    62,    63,    64,    65,    66,    67,
      -1,    69,    70,    71,    72,    -1,    74,    75,    -1,    77,
      78,    -1,    80,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    -1,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   143,   144,   145,    -1,   147,
     148,   149,   150,   151,   152,    -1,   154,   155,   156,   157,
     158,   159,   160,    -1,     4,   163,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      -1,    31,    32,    33,    34,    35,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    44,    -1,    -1,    47,    -1,    49,
      50,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,    -1,    62,    63,    64,    65,    66,    67,    -1,    69,
      70,    71,    72,    -1,    74,    75,    -1,    77,    78,    -1,
      80,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    -1,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   143,   144,   145,    -1,   147,   148,   149,
     150,   151,   152,    -1,   154,   155,   156,   157,   158,   159,
     160,    -1,     4,   163,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,    -1,    49,    50,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    60,    -1,
      62,    63,    64,    65,    66,    67,    -1,    69,    70,    71,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,    -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   143,   144,   145,    -1,   147,   148,   149,   150,   151,
     152,    -1,   154,   155,   156,   157,   158,   159,   160,    -1,
       4,   163,     6,     7,     8,     9,    -1,    -1,    12,    13,
      14,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,    -1,
      24,    25,    26,    27,    -1,    -1,    -1,    31,    32,    -1,
      34,    35,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,
      44,    -1,    -1,    47,    -1,    49,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    69,    70,    71,    72,    -1,
      74,    75,    -1,    77,    78,    -1,    80,    -1,    -1,    -1,
      84,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,
     144,   145,    -1,    -1,   148,   149,    -1,    -1,   152,    -1,
      -1,    -1,   156,   157,   158,   159,   160,     4,    -1,   163,
       7,     8,     9,    -1,    -1,    12,    13,    14,    -1,    16,
      -1,    -1,    -1,    20,    -1,    22,    -1,    24,    25,    26,
      27,    -1,    -1,    -1,    31,    32,    -1,    34,    35,    -1,
      -1,    -1,    39,    40,    -1,    -1,    -1,    44,    -1,    -1,
      47,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    75,    -1,
      77,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    -1,   105,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   143,   144,   145,    -1,
      -1,   148,   149,    -1,    -1,   152,    -1,    -1,    -1,   156,
     157,   158,   159,   160,     4,    -1,   163,     7,     8,     9,
      -1,    -1,    12,    13,    14,    -1,    16,    -1,    -1,    -1,
      20,    -1,    22,    -1,    24,    25,    26,    27,    -1,    -1,
      -1,    31,    32,    -1,    34,    35,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    44,    -1,    -1,    47,    -1,    49,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    74,    75,    -1,    77,    78,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   143,   144,   145,    -1,    -1,   148,   149,
      -1,    -1,   152,    -1,    -1,    -1,   156,   157,   158,   159,
     160,     4,    -1,   163,     7,     8,     9,    -1,    -1,    12,
      13,    14,    -1,    16,    -1,    -1,    -1,    20,    -1,    22,
      -1,    24,    25,    26,    27,    -1,    -1,    -1,    31,    32,
      -1,    34,    35,    -1,    -1,    -1,    39,    40,    -1,    -1,
      -1,    44,    -1,    -1,    47,    -1,    49,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,   105,   106,   107,   108,   109,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     143,   144,   145,    -1,    -1,   148,   149,    -1,    -1,   152,
      -1,    -1,    -1,   156,   157,   158,   159,   160,     4,    -1,
     163,     7,     8,     9,    -1,    -1,    12,    13,    14,    -1,
      16,    -1,    -1,    -1,    20,    -1,    22,    -1,    24,    25,
      26,    27,    -1,    -1,    -1,    31,    32,    -1,    34,    35,
      -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    44,    -1,
      -1,    47,    -1,    49,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    75,
      -1,    77,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,   105,
     106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,   144,   145,
      -1,    -1,   148,   149,    -1,    -1,   152,    -1,    -1,    -1,
     156,   157,   158,   159,   160,    -1,    -1,   163,     6,     7,
       8,    -1,    -1,    -1,    12,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    22,    -1,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    34,    35,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      58,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    69,    70,    71,    -1,    -1,    -1,    75,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,    -1,   120,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   133,   134,   135,    -1,   137,
      -1,   139,   140,   141,    -1,   143,   144,   145,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,
     158,   159,   160,    -1,    -1,   163,     6,     7,     8,    -1,
      -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    22,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    34,    35,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,    69,
      70,    71,    -1,    -1,    -1,    75,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,   104,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     120,     6,     7,     8,   124,    -1,    -1,    12,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    24,
      25,    -1,    -1,   143,   144,   145,    -1,    32,    -1,    34,
      35,    -1,    -1,    -1,    39,    -1,   156,   157,   158,   159,
     160,    -1,    -1,   163,    49,    -1,    -1,    -1,    53,    54,
      -1,    56,    -1,    58,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    69,    70,    71,    -1,    -1,    -1,
      75,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,   104,
     105,   106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,    -1,     7,     8,    -1,
      -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    22,    -1,    24,    25,    -1,    -1,   143,   144,
     145,    -1,    32,    -1,    34,    35,    -1,    -1,    -1,    39,
      -1,   156,   157,   158,   159,   160,    -1,    -1,   163,    49,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,   105,   106,   107,   108,   109,
     110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     120,    -1,     7,     8,   124,    -1,    -1,    12,    -1,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    24,
      25,    -1,    -1,   143,   144,   145,    -1,    32,    -1,    34,
      35,    -1,    -1,    -1,    39,    -1,   156,   157,   158,   159,
     160,    -1,    -1,   163,    49,    -1,    -1,    -1,    53,    54,
      -1,    56,    -1,    58,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    69,     7,     8,    -1,    -1,    -1,
      12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    20,    84,
      22,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,    94,
      32,    -1,    34,    35,    -1,    -1,   101,    39,    -1,    -1,
     105,   106,   107,   108,   109,   110,    -1,    49,    -1,    -1,
      -1,    53,    54,    -1,    56,   120,    58,    -1,    -1,   124,
      62,    63,    64,    65,    66,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,   144,
     145,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,   158,   159,   160,    -1,    -1,   163,   101,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,    -1,
       7,     8,   124,    -1,    -1,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    22,    -1,    24,    25,    -1,
      -1,   143,   144,   145,    -1,    32,    -1,    34,    35,    -1,
      -1,    -1,    39,    -1,   156,   157,   158,   159,   160,    -1,
      -1,   163,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    58,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,
     107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     7,     8,    -1,    -1,    -1,
      12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      22,    -1,    24,    25,    -1,    -1,   143,   144,   145,    -1,
      32,    -1,    34,    35,    -1,    -1,    -1,    39,    -1,   156,
     157,   158,   159,   160,    -1,    -1,   163,    49,    -1,    -1,
      -1,    53,    54,    -1,    56,    -1,    58,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       7,     8,    -1,    -1,    -1,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    22,    -1,    24,    25,    -1,
      -1,   143,   144,   145,    -1,    32,    -1,    34,    35,    -1,
      -1,    -1,    39,    -1,   156,   157,   158,   159,   160,    -1,
      -1,   163,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    58,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,     7,     8,    -1,    -1,    -1,    12,    76,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      34,    35,    -1,    -1,    -1,    39,    -1,    -1,   105,   106,
     107,   108,   109,   110,    -1,    49,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    58,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,   143,   144,   145,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,   158,   159,   160,    -1,    -1,   163,    -1,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,     8,
      -1,    -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    22,    -1,    24,    25,    -1,    -1,   143,
     144,   145,    -1,    32,    -1,    34,    35,    -1,    -1,    -1,
      39,    -1,   156,   157,   158,   159,   160,    -1,    -1,   163,
      49,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,     7,     8,    -1,    -1,    -1,    12,    76,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    22,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,    35,
      -1,    -1,    -1,    39,    -1,    -1,   105,   106,   107,   108,
     109,   110,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,
      56,    -1,    58,    -1,    -1,    61,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   143,   144,   145,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,   157,   158,
     159,   160,    -1,    -1,   163,    -1,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     7,     8,    -1,    -1,
      -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    22,    -1,    24,    25,    -1,    -1,   143,   144,   145,
      -1,    32,    -1,    34,    35,    -1,    -1,    -1,    39,    -1,
     156,   157,   158,   159,   160,    -1,    -1,   163,    49,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    -1,    -1,     7,     8,
      -1,    -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    22,    -1,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    34,    35,    -1,    -1,    -1,
      39,    -1,    -1,    -1,   105,   106,   107,   108,   109,   110,
      49,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    -1,   156,   157,   158,   159,   160,
      -1,    -1,   163,    -1,    -1,    -1,   105,   106,   107,   108,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     7,     8,    -1,    -1,    -1,    12,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    22,    -1,
      24,    25,    -1,    -1,   143,   144,   145,    -1,    32,    -1,
      34,    35,    -1,    -1,    -1,    39,    -1,   156,   157,   158,
     159,   160,    -1,    -1,   163,    49,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    58,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,   105,   106,   107,   108,    -1,   110,    -1,    49,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
       7,    -1,    -1,    -1,    75,    -1,    77,    14,    -1,   143,
     144,   145,    83,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,   160,    34,    -1,   163,
      -1,    -1,    39,    -1,   105,   106,    -1,   108,   109,   110,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    75,    -1,
      77,    14,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    89,    -1,    -1,   156,   157,   158,   159,   160,
      -1,    34,   163,    -1,    -1,    -1,    39,    -1,   105,   106,
      -1,   108,   109,   110,    -1,    -1,    49,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    64,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    77,    -1,   143,   144,   145,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,   156,
     157,   158,   159,   160,    -1,    -1,   163,    -1,    -1,    -1,
      -1,    -1,   105,   106,    -1,   108,   109,   110,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
     143,   144,   145,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,   156,   157,   158,   159,   160,    49,    -1,
     163,    -1,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,     7,
      -1,    -1,    -1,    -1,    -1,    76,    14,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    39,    -1,    -1,   105,   106,    -1,   108,   109,   110,
      -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    66,    -1,
      -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    76,    -1,
      14,    79,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,   156,   157,   158,   159,   160,
      34,    -1,   163,    -1,    -1,    39,    -1,   105,   106,    -1,
     108,   109,   110,    -1,    -1,    49,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      64,    -1,    66,    -1,    -1,    -1,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    -1,   143,   144,   145,    -1,    -1,
      84,    -1,    -1,    24,    -1,    -1,    -1,    -1,   156,   157,
     158,   159,   160,    34,    -1,   163,    -1,    -1,    39,    -1,
      -1,   105,   106,    -1,   108,   109,   110,    -1,    49,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,   143,
     144,   145,    -1,    84,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,   160,    34,    -1,   163,
      -1,    -1,    39,    -1,   105,   106,    -1,   108,   109,   110,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    66,
      -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,   143,   144,   145,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,   156,   157,   158,   159,   160,
      34,    -1,   163,    -1,    -1,    39,    -1,    -1,   105,   106,
      -1,   108,   109,   110,    -1,    49,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      64,    -1,    66,    -1,    -1,    -1,    -1,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    -1,   143,   144,   145,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,   156,
     157,   158,   159,   160,    34,    -1,   163,    -1,    -1,    39,
      -1,   105,   106,    -1,   108,   109,   110,    -1,    -1,    49,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,   143,
     144,   145,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,   156,   157,   158,   159,   160,    34,    -1,   163,
      -1,    -1,    39,    -1,    -1,   105,   106,    -1,   108,   109,
     110,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,    66,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    -1,   143,   144,   145,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
     160,    34,    -1,   163,    -1,    -1,    39,    -1,   105,   106,
      -1,   108,   109,   110,    -1,    -1,    49,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    64,    -1,    66,    -1,    -1,    -1,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    -1,   143,   144,   145,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,   156,
     157,   158,   159,   160,    34,    -1,   163,    -1,    -1,    39,
      -1,    -1,   105,   106,    -1,   108,   109,   110,    -1,    49,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,
      -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,
     143,   144,   145,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,   156,   157,   158,   159,   160,    34,    -1,
     163,    -1,    -1,    39,    -1,   105,   106,    -1,   108,   109,
     110,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    -1,
      66,    -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    -1,   143,   144,   145,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,   156,   157,   158,   159,
     160,    34,    -1,   163,    -1,    -1,    39,    -1,    -1,   105,
     106,    -1,   108,   109,   110,    -1,    49,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    64,    -1,    66,    -1,    -1,    -1,    -1,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    -1,   143,   144,   145,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
     156,   157,   158,   159,   160,    34,    -1,   163,    -1,    -1,
      39,    -1,   105,   106,    -1,   108,   109,   110,    -1,    -1,
      49,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    64,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     143,   144,   145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   156,   157,   158,   159,   160,    -1,    -1,
     163,    -1,    -1,    -1,    -1,    -1,   105,   106,    -1,   108,
     109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,    -1,    -1,    -1,
      -1,     9,    -1,    -1,    -1,    13,    14,    -1,    16,    -1,
      -1,    -1,    -1,    -1,   143,   144,   145,    -1,    26,    27,
      -1,    -1,    -1,    31,    32,    -1,    -1,   156,   157,   158,
     159,   160,    40,    -1,   163,    -1,    44,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    74,    75,    -1,    77,
      78,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
     108,    -1,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,   143,   144,   145,    40,    -1,
     148,   149,    44,    -1,   152,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    76,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    76,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     4,    -1,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,   148,   149,    -1,    -1,
     152,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   148,   149,    -1,    -1,
     152
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned short int yystos[] =
{
       0,     6,     7,     8,    12,    14,    20,    22,    24,    25,
      32,    34,    35,    39,    49,    53,    54,    56,    58,    62,
      63,    64,    65,    66,    69,    70,    71,    75,    77,    84,
     101,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   120,   124,   133,   134,
     135,   137,   139,   140,   141,   143,   144,   145,   156,   157,
     158,   159,   160,   163,   165,   166,   167,   168,   170,   171,
     173,   174,   177,   182,   183,   187,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   200,   201,   202,   203,   204,
     205,   207,   208,   209,   210,   216,   217,   219,   220,   221,
     222,   240,   243,   244,   245,   270,   271,   293,   295,   300,
     301,   313,   334,   335,   342,    66,   178,    32,    92,   173,
     174,    32,   207,   209,   217,   218,   219,   168,   240,    32,
     172,    75,    75,     4,     9,    13,    16,    26,    27,    31,
      40,    44,    47,    55,    57,    72,    74,    75,    77,    78,
      80,    89,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   148,   149,   152,   268,   270,   272,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   292,   294,   298,   299,   343,   273,   288,
      10,    11,    15,    17,    19,    28,    29,    32,    33,    50,
      60,    67,    75,    77,    84,    92,   101,   119,   124,   132,
     147,   150,   151,   154,   155,   169,   170,   173,   183,   187,
     208,   221,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   261,   263,   267,   270,   289,   300,   303,   314,   315,
     338,   166,    32,    84,   101,   124,   174,   187,   189,   246,
     247,   293,   300,   302,   313,   190,   191,   196,   197,   198,
     199,   226,   190,   196,   198,   296,   270,   122,   123,   125,
     126,   127,   304,   305,   270,   318,   325,   326,     4,    32,
      46,    74,    77,    78,    80,    82,    91,    93,   319,   322,
     327,    92,   235,   288,   328,   322,   324,   221,   330,   329,
     330,   289,    89,   336,   337,     0,   167,   174,   208,   210,
     220,   204,   209,    84,   192,   193,   196,   197,    39,    53,
      54,    64,   105,   190,   191,   190,   193,    79,    84,     6,
      86,   173,   206,   234,   207,   209,   184,   185,   186,   193,
     196,   241,   242,   256,    75,    75,    89,    92,    32,   173,
      75,    92,    32,    94,   223,   224,   225,    32,    92,    76,
      76,    76,   219,    79,    84,   226,   289,    75,    32,    75,
     274,   274,    75,   274,   226,   256,   289,   289,    75,    75,
      75,    75,    75,   274,   276,   276,   276,    75,   274,    75,
     274,    75,   274,    40,    47,    48,    75,    81,    89,   161,
     344,   346,   276,    73,    77,    82,    78,    80,    36,    51,
      30,    38,    85,    87,    23,    43,    74,    91,    93,     4,
       3,     5,    18,    37,    41,    42,    45,    46,    52,    59,
      68,    86,    88,   290,    79,    57,    75,   274,   297,   299,
      79,    84,   286,   287,   291,    84,    83,   251,    75,    32,
      77,    83,    75,    84,   289,    75,    75,    94,   257,   305,
      32,   289,   339,    84,    75,   339,   339,    75,   208,   251,
      84,   251,   247,   305,    32,    83,   173,   207,   248,   249,
      84,   247,   196,   190,   191,    75,    89,   173,   208,   227,
     228,   196,    79,    75,    75,   130,   306,   307,   308,    75,
     306,   167,    79,    83,    83,    32,    81,    89,    94,   235,
     236,   237,   238,   239,    89,    92,   331,   332,   333,    79,
     331,   331,    77,    90,   291,   337,   207,   209,    84,   241,
     242,   191,   190,   205,    75,   235,   234,   173,   234,   204,
     193,   196,   190,   184,   242,    32,    76,   187,   188,   190,
     196,   229,   230,   231,   232,   233,    76,   229,   231,    56,
      77,   212,   214,   215,   218,   288,    94,   246,    32,   294,
      94,   223,    86,    94,    79,    92,    94,   223,    32,    76,
      76,    14,    32,    76,   175,   176,   226,   226,    76,    76,
      76,    90,   288,   226,   288,   226,   226,   226,   226,   226,
     270,    76,   273,   270,   264,   289,    75,   288,   345,   276,
     276,   276,   277,   277,   278,   278,   279,   279,   279,   279,
     280,   280,   281,   282,   283,   284,   285,    83,   289,   288,
     288,   226,   288,    61,    83,   251,    67,   183,   254,   266,
      84,   289,   251,   198,   262,   289,    84,   262,   262,    94,
     251,    32,   316,   317,    84,   266,    84,    84,   247,    83,
     173,   291,    83,    86,   173,   250,    79,    84,   190,   191,
      76,   227,   231,   212,   214,   215,   208,   228,   227,    75,
      89,   198,    32,   131,   309,   310,   311,   312,    75,   125,
      79,   308,   309,   125,   326,   226,   320,   226,   321,    83,
      32,   287,   291,    79,    94,   235,    86,    89,   239,   288,
      94,   289,   333,   330,    90,    90,   242,   294,   234,    84,
     190,    75,   173,   207,   208,   227,   196,   190,    76,    79,
      76,    79,    76,    76,   213,   214,   211,   212,    90,    94,
      76,    83,    94,   291,   225,    94,   223,    94,    75,    76,
      76,    79,    76,    76,    92,   276,    79,    79,    79,    79,
      76,    76,    76,    76,    76,    83,    84,    90,    76,   273,
      79,   162,   347,   288,    83,    76,   291,   251,    75,   262,
     265,    84,   207,    76,    76,    76,    83,    79,   339,   291,
      83,   291,   291,   250,   249,    76,    76,   213,   211,    90,
     227,    76,   231,   212,   214,   215,    76,    76,   311,    76,
     309,   308,    76,    79,    83,   235,    90,    32,    94,   235,
     237,    90,    83,    94,   138,   331,    76,   208,   173,   173,
     190,    32,    61,   233,   215,   215,    84,    89,   179,   180,
     181,   294,    94,   273,    76,   176,   236,   226,    32,   269,
     288,   226,   264,   289,   289,    76,   288,   288,   276,    83,
     289,    84,    86,   173,   206,   251,   252,   259,   260,   251,
     251,   289,   317,    84,   291,   215,   215,    76,   213,   211,
      90,   123,   306,    76,   306,   226,   289,   323,    83,   235,
     289,   289,    90,    90,    32,    76,    83,    79,    75,    76,
      79,    94,    76,   238,    76,    79,    76,    90,    90,    79,
     251,    76,   264,   288,    86,    86,   173,    21,   339,    90,
      90,   215,   215,   125,   125,   235,    94,    94,    90,    84,
     179,   181,   289,    94,   288,   288,    84,    76,   288,   288,
      86,   251,    84,    90,    90,   294,    76,    83,    76,    76,
      79,   251,   288,    15,   289,   340,   341,    75,    84,   179,
     288,    76,   289,    76,   251,    76,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short int yyr1[] =
{
       0,   164,   165,   165,   166,   166,   167,   167,   168,   168,
     169,   169,   170,   170,   170,   170,   170,   170,   171,   172,
     172,   173,   173,   174,   174,   175,   175,   176,   176,   176,
     177,   177,   177,   177,   178,   178,   179,   179,   180,   180,
     181,   181,   181,   182,   182,   183,   183,   183,   184,   185,
     185,   185,   185,   185,   186,   186,   187,   187,   187,   187,
     187,   188,   188,   188,   188,   188,   189,   189,   189,   189,
     190,   190,   191,   191,   192,   192,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   194,   194,   194,   194,
     194,   195,   196,   196,   196,   197,   197,   197,   198,   198,
     198,   198,   198,   199,   199,   199,   199,   199,   200,   200,
     200,   200,   201,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   203,   203,   203,   203,   204,   204,   205,
     205,   205,   205,   205,   205,   205,   205,   206,   207,   207,
     207,   207,   208,   208,   209,   209,   209,   209,   210,   210,
     211,   211,   212,   213,   213,   214,   215,   215,   215,   216,
     216,   216,   217,   217,   218,   218,   219,   219,   219,   220,
     220,   220,   220,   220,   220,   220,   220,   221,   222,   222,
     222,   222,   222,   222,   222,   222,   223,   223,   224,   224,
     225,   225,   226,   226,   227,   227,   227,   227,   227,   227,
     228,   228,   228,   228,   228,   228,   228,   228,   228,   228,
     228,   229,   230,   230,   231,   231,   232,   232,   233,   233,
     233,   233,   233,   234,   235,   235,   235,   235,   236,   236,
     236,   236,   236,   236,   237,   238,   238,   239,   239,   240,
     240,   240,   240,   240,   241,   241,   242,   243,   243,   244,
     244,   244,   244,   245,   245,   246,   246,   247,   247,   247,
     247,   247,   248,   248,   249,   249,   249,   249,   249,   249,
     249,   249,   250,   251,   251,   251,   252,   252,   252,   252,
     252,   252,   252,   253,   253,   253,   253,   254,   254,   255,
     256,   256,   257,   257,   258,   259,   260,   260,   261,   262,
     262,   262,   262,   262,   263,   263,   263,   264,   264,   265,
     265,   266,   266,   267,   267,   267,   267,   267,   267,   268,
     268,   268,   268,   268,   268,   268,   268,   269,   269,   270,
     271,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   273,   273,   274,   274,   274,   274,   274,   274,   274,
     274,   274,   274,   274,   274,   275,   275,   275,   275,   275,
     275,   276,   276,   277,   277,   277,   277,   278,   278,   278,
     279,   279,   279,   280,   280,   280,   280,   280,   281,   281,
     281,   282,   282,   283,   283,   284,   284,   285,   285,   286,
     286,   287,   287,   287,   288,   288,   289,   289,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,   291,
     292,   292,   292,   292,   292,   292,   292,   292,   293,   294,
     294,   165,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   296,   296,   272,   272,   297,   297,   276,   298,
     298,   299,   251,   252,   252,   167,   167,   247,   247,   300,
     301,   302,   303,   304,   304,   304,   305,   305,   306,   306,
     307,   307,   307,   308,   308,   308,   309,   310,   310,   311,
     312,   313,   313,   170,   247,   251,   314,   315,   315,   316,
     316,   317,   318,   319,   320,   321,   321,   322,   322,   323,
     324,   325,   325,   326,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   295,   295,   295,   295,   328,   295,   295,
     295,   329,   329,   330,   330,   331,   331,   332,   332,   333,
     333,   333,   333,   274,   274,   274,   274,   274,   274,   219,
     219,   334,   334,   335,   335,   336,   336,   337,   337,   337,
     252,   338,   338,   338,   338,   339,   339,   263,   340,   340,
     341,   341,   193,   272,   342,   342,   342,   342,   342,   343,
     343,   344,   345,   345,   345,   346,   347,   193
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     3,     1,
       3,     2,     1,     6,     5,     1,     3,     1,     1,     4,
       6,     8,    10,    12,     0,     1,     1,     0,     1,     3,
       4,     7,     1,     1,     1,     3,     2,     2,     3,     3,
       2,     2,     1,     1,     1,     2,     3,     2,     2,     1,
       1,     3,     2,     2,     1,     1,     3,     2,     2,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     1,     1,     3,     2,     2,     1,     1,     1,     1,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     3,     1,     3,     1,
       2,     2,     2,     3,     3,     3,     4,     4,     1,     2,
       2,     3,     1,     2,     1,     2,     2,     3,     1,     3,
       0,     1,     1,     0,     1,     1,     0,     1,     1,     4,
       4,     3,     1,     3,     1,     2,     1,     1,     1,     1,
       3,     4,     4,     4,     6,     6,     3,     1,     5,     4,
       4,     3,     6,     5,     5,     4,     1,     2,     3,     1,
       1,     3,     1,     2,     1,     2,     1,     2,     3,     2,
       3,     3,     4,     2,     3,     3,     5,     5,     4,     6,
       6,     1,     1,     3,     1,     3,     1,     3,     2,     1,
       2,     3,     3,     2,     1,     3,     4,     2,     1,     3,
       2,     4,     3,     5,     2,     1,     2,     3,     2,     3,
       4,     2,     3,     2,     1,     2,     1,     4,     3,     1,
       2,     2,     3,     1,     1,     1,     2,     3,     2,     1,
       1,     2,     1,     3,     1,     2,     2,     3,     2,     3,
       4,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     6,     2,     1,     1,
       3,     2,     1,     2,     5,     7,     1,     1,     5,     1,
       4,     6,     5,     5,     5,     7,     8,     1,     0,     1,
       0,     1,     1,     2,     2,     2,     3,     3,     4,     1,
       3,     1,     3,     6,     6,     8,     6,     2,     1,     1,
       1,     1,     4,     3,     4,     3,     3,     2,     2,     6,
       7,     1,     3,     1,     2,     2,     2,     2,     4,     2,
       2,     4,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     4,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       2,     2,     1,     3,     6,     6,     1,     4,     2,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     3,     3,     3,     6,     1,     3,     6,     0,     1,
       1,     3,     2,     4,     3,     1,     1,     1,     2,     1,
       1,     6,     2,     1,     1,     1,     2,     3,     2,     1,
       3,     3,     3,     5,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     1,     3,     2,
       3,     2,     4,     1,     4,     0,     1,     1,     2,     2,
       3,     5,     5,     2,     4,     2,     4,     2,     4,     1,
       1,     1,     2,     1,     1,     1,     2,     2,     3,     3,
       1,     3,     3,     3,     2,     1,     0,    10,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       5,     3,     7,     5,     3,     1,     1,     1
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     1,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       1,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     1,
       1,     1,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     1,     0,
       1,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     1,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned short int yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   547,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   355,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   359,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   357,     0,     0,     0,     0,   437,
       0,   439,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   361,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   363,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   367,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   353,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   435,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   583,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     597,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   563,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   567,     0,   569,
       0,     0,     0,     0,     0,     0,     0,   565,   427,     0,
       0,     0,     0,     0,     0,   429,     0,   459,   461,     0,
       0,   463,   423,   425,     0,     0,   465,     0,   467,     0,
       0,   469,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   557,     0,   431,   559,     0,     0,     0,     0,     0,
       0,     0,   571,     0,   573,     0,     0,   433,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   441,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,     0,   477,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   445,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   479,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   475,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   481,     0,     0,     0,
     483,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   545,
       0,     0,     0,     0,     0,     0,   485,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   575,   577,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   579,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   587,     0,     0,   589,   591,   593,   595,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   599,   601,     0,     0,
       0,   603,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   453,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   455,     0,   457,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     5,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,     0,     0,     0,     0,
      15,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,    21,     0,    23,     0,     0,
       0,     0,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,     0,    29,    31,     0,    33,
       0,     0,     0,     0,     0,    35,     0,    37,     0,    39,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    43,
      45,     0,    47,     0,     0,     0,    49,     0,     0,     0,
       0,     0,    51,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    53,    55,
       0,    57,    59,    61,     0,     0,     0,     0,     0,    81,
       0,     0,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,     0,    63,    65,    67,     0,
       0,    89,     0,    91,     0,     0,     0,     0,    93,    69,
      71,    73,    75,    77,     0,     0,    79,     0,    95,     0,
       0,     0,    97,    99,     0,   101,     0,     0,     0,     0,
       0,   103,     0,   105,     0,   107,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   111,   113,     0,   115,     0,
       0,     0,   117,     0,     0,     0,     0,     0,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   123,     0,   125,   127,   129,
       0,     0,     0,     0,   149,     0,     0,     0,     0,     0,
       0,   151,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,     0,
       0,     0,   131,   133,   135,     0,   157,     0,   159,     0,
       0,     0,     0,   161,     0,   137,   139,   141,   143,   145,
       0,     0,   147,   163,     0,     0,     0,   165,   167,     0,
     169,     0,     0,     0,     0,     0,   171,     0,   173,     0,
     175,     0,     0,     0,     0,     0,     0,     0,     0,   177,
     179,   181,     0,   183,     0,     0,     0,   185,     0,     0,
       0,     0,     0,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   189,
     191,     0,   193,   195,   197,     0,     0,     0,     0,   217,
       0,     0,     0,     0,     0,     0,   219,     0,     0,     0,
       0,     0,     0,   221,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,     0,     0,     0,   199,   201,   203,
       0,   225,     0,   227,     0,     0,     0,     0,   229,     0,
     205,   207,   209,   211,   213,     0,     0,   215,   231,     0,
       0,     0,   233,   235,     0,   237,     0,     0,     0,     0,
       0,   239,     0,   241,     0,   243,     0,     0,     0,     0,
       0,     0,     0,     0,   245,   247,   249,     0,   251,     0,
       0,     0,   253,     0,     0,     0,     0,     0,   255,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   257,   259,     0,   261,   263,   265,
       0,     0,     0,     0,   285,     0,     0,     0,     0,     0,
       0,   287,     0,     0,     0,     0,     0,     0,   289,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   291,     0,
       0,     0,   267,   269,   271,     0,   293,     0,   295,     0,
       0,     0,     0,   297,     0,   273,   275,   277,   279,   281,
       0,     0,   283,   299,     0,     0,     0,   301,   303,     0,
     305,     0,     0,     0,     0,     0,   307,     0,   309,     0,
     311,     0,     0,     0,     0,     0,     0,     0,     0,   313,
     315,   317,     0,   319,     0,     0,     0,   321,     0,     0,
       0,     0,     0,   323,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   325,
     327,     0,   329,   331,   333,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   335,   337,   339,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     341,   343,   345,   347,   349,     0,     0,   351,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   541,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   447,     0,   449,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   451,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   471,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   549,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   561,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,     0,     0,     0,     0,     0,
     373,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     375,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     377,     0,     0,     0,     0,   379,     0,     0,     0,     0,
       0,   585,     0,     0,     0,   381,     0,     0,     0,   383,
     385,     0,   387,     0,     0,     0,     0,     0,   389,     0,
     391,     0,   393,     0,     0,     0,   489,     0,     0,     0,
       0,     0,     0,   491,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   493,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   495,     0,     0,     0,     0,   497,     0,
       0,   395,   397,     0,   399,   401,   403,     0,   499,     0,
       0,     0,   501,   503,     0,   505,     0,     0,     0,     0,
       0,   507,     0,   509,     0,   511,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   405,
     407,   409,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   411,   413,   415,   417,   419,     0,     0,   421,
       0,     0,     0,     0,   513,   515,     0,   517,   519,   521,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   523,   525,   527,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   529,   531,   533,   535,   537,
       0,     0,   539,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   369,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   473,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   487,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   543,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   551,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   553,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   555,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     581,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   330,     0,   330,     0,   330,     0,   330,     0,   330,
       0,   330,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   117,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   117,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   117,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   117,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   117,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   117,     0,   117,     0,   117,     0,   117,     0,   117,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   115,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   115,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   115,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   115,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   115,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   115,
       0,   115,     0,   115,     0,   115,     0,   115,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   118,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   118,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   118,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   118,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   118,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   118,     0,   118,
       0,   118,     0,   118,     0,   118,     0,   119,     0,   119,
       0,   119,     0,   119,     0,   119,     0,   119,     0,   119,
       0,   119,     0,   119,     0,   119,     0,   119,     0,   119,
       0,   119,     0,   119,     0,   119,     0,   119,     0,   119,
       0,   119,     0,   119,     0,   119,     0,   119,     0,   119,
       0,   119,     0,   119,     0,   119,     0,   119,     0,   119,
       0,   119,     0,   119,     0,   119,     0,   119,     0,   119,
       0,   119,     0,   119,     0,    94,     0,    94,     0,    94,
       0,    94,     0,    94,     0,    94,     0,    94,     0,    94,
       0,    94,     0,    94,     0,    94,     0,    94,     0,    94,
       0,    94,     0,    94,     0,    94,     0,    94,     0,    94,
       0,    94,     0,    94,     0,    94,     0,    94,     0,    94,
       0,    94,     0,    94,     0,    94,     0,    94,     0,    94,
       0,    94,     0,    94,     0,    94,     0,    94,     0,    94,
       0,    94,     0,   531,     0,    75,     0,    75,     0,    74,
       0,    74,     0,    74,     0,    74,     0,    74,     0,    59,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,   169,     0,   169,     0,   343,     0,   343,
       0,   343,     0,   343,     0,   367,     0,   370,     0,   370,
       0,   383,     0,   389,     0,   417,     0,   330,     0,   330,
       0,   330,     0,   355,     0,   355,     0,   355,     0,   321,
       0,   321,     0,   321,     0,   321,     0,   321,     0,   321,
       0,   101,     0,   101,     0,   532,     0,    74,     0,    74,
       0,    74,     0,    74,     0,    74,     0,    57,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    92,     0,    92,     0,    92,     0,    92,     0,    92,
       0,    53,     0,    52,     0,   478,     0,   330,     0,    99,
       0,    99,     0,    50,     0,    51,     0,   212,     0,   212,
       0,    59,     0,   368,     0,   369,     0,   371,     0,   371,
       0,   372,     0,   372,     0,   384,     0,   390,     0,   409,
       0,    49,     0,   194,     0,    57,     0,   348,     0,   351,
       0,   526,     0,   528,     0,   524,     0,   197,     0,   296,
       0,   297,     0,   481,     0
};

/* Error token number */
#define YYTERROR 1



YYSTYPE yylval;

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, AST* parsed_tree)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (parsed_tree);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, AST* parsed_tree)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parsed_tree);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value, parsed_tree);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;


  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static _Noreturn void
yyFail (yyGLRStack* yystackp, AST* parsed_tree, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (parsed_tree, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, AST* parsed_tree)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (parsed_tree);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (parsed_tree, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  switch (yyn)
    {
        case 2:
#line 1563 "c99.y" /* glr.c:783  */
    {
	*parsed_tree = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4201 "c99-parser.c" /* glr.c:783  */
    break;

  case 3:
#line 1567 "c99.y" /* glr.c:783  */
    {
	*parsed_tree = NULL;
}
#line 4209 "c99-parser.c" /* glr.c:783  */
    break;

  case 4:
#line 1577 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4217 "c99-parser.c" /* glr.c:783  */
    break;

  case 5:
#line 1581 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4225 "c99-parser.c" /* glr.c:783  */
    break;

  case 6:
#line 1587 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4233 "c99-parser.c" /* glr.c:783  */
    break;

  case 7:
#line 1591 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4241 "c99-parser.c" /* glr.c:783  */
    break;

  case 8:
#line 1597 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4249 "c99-parser.c" /* glr.c:783  */
    break;

  case 9:
#line 1601 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4257 "c99-parser.c" /* glr.c:783  */
    break;

  case 10:
#line 1607 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4265 "c99-parser.c" /* glr.c:783  */
    break;

  case 11:
#line 1611 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4273 "c99-parser.c" /* glr.c:783  */
    break;

  case 12:
#line 1617 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4281 "c99-parser.c" /* glr.c:783  */
    break;

  case 13:
#line 1622 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4289 "c99-parser.c" /* glr.c:783  */
    break;

  case 14:
#line 1626 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_EXTENSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4297 "c99-parser.c" /* glr.c:783  */
    break;

  case 15:
#line 1631 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4305 "c99-parser.c" /* glr.c:783  */
    break;

  case 16:
#line 1636 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_PP_COMMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4313 "c99-parser.c" /* glr.c:783  */
    break;

  case 17:
#line 1641 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_PP_TOKEN, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4321 "c99-parser.c" /* glr.c:783  */
    break;

  case 18:
#line 1648 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_LABEL_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 4329 "c99-parser.c" /* glr.c:783  */
    break;

  case 19:
#line 1654 "c99.y" /* glr.c:783  */
    {
    AST symbol_holder = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
	((*yyvalp).ast) = ASTListLeaf(symbol_holder);
}
#line 4338 "c99-parser.c" /* glr.c:783  */
    break;

  case 20:
#line 1659 "c99.y" /* glr.c:783  */
    {
	AST label = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), label);
}
#line 4347 "c99-parser.c" /* glr.c:783  */
    break;

  case 21:
#line 1668 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4355 "c99-parser.c" /* glr.c:783  */
    break;

  case 22:
#line 1672 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4363 "c99-parser.c" /* glr.c:783  */
    break;

  case 23:
#line 1678 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_ATTRIBUTE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4371 "c99-parser.c" /* glr.c:783  */
    break;

  case 24:
#line 1682 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_ATTRIBUTE, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4379 "c99-parser.c" /* glr.c:783  */
    break;

  case 25:
#line 1688 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4387 "c99-parser.c" /* glr.c:783  */
    break;

  case 26:
#line 1692 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4395 "c99-parser.c" /* glr.c:783  */
    break;

  case 27:
#line 1699 "c99.y" /* glr.c:783  */
    {
	AST identif = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_ATTRIBUTE_EXPR, identif, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 4405 "c99-parser.c" /* glr.c:783  */
    break;

  case 28:
#line 1705 "c99.y" /* glr.c:783  */
    {
	AST identif = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_ATTRIBUTE_EXPR, identif, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 4415 "c99-parser.c" /* glr.c:783  */
    break;

  case 29:
#line 1711 "c99.y" /* glr.c:783  */
    {
	AST identif1 = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);
	
	((*yyvalp).ast) = ASTMake3(AST_GCC_ATTRIBUTE_EXPR, identif1, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 4425 "c99-parser.c" /* glr.c:783  */
    break;

  case 30:
#line 1720 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_ASM_DEFINITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4433 "c99-parser.c" /* glr.c:783  */
    break;

  case 31:
#line 1725 "c99.y" /* glr.c:783  */
    {
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			(((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
	((*yyvalp).ast) = ASTMake2(AST_GCC_ASM_DEFINITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast), asm_parms, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4443 "c99-parser.c" /* glr.c:783  */
    break;

  case 32:
#line 1731 "c99.y" /* glr.c:783  */
    {
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			(((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast)), NULL);
	((*yyvalp).ast) = ASTMake2(AST_GCC_ASM_DEFINITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.ast), asm_parms, (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4453 "c99-parser.c" /* glr.c:783  */
    break;

  case 33:
#line 1737 "c99.y" /* glr.c:783  */
    {
	AST asm_parms = ASTMake4(AST_GCC_ASM_DEF_PARMS, 
			(((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval.ast)), NULL);
	((*yyvalp).ast) = ASTMake2(AST_GCC_ASM_DEFINITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval.ast), asm_parms, (((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4463 "c99-parser.c" /* glr.c:783  */
    break;

  case 34:
#line 1745 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = NULL;
}
#line 4471 "c99-parser.c" /* glr.c:783  */
    break;

  case 35:
#line 1749 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_VOLATILE_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4479 "c99-parser.c" /* glr.c:783  */
    break;

  case 36:
#line 1755 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4487 "c99-parser.c" /* glr.c:783  */
    break;

  case 37:
#line 1759 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = NULL;
}
#line 4495 "c99-parser.c" /* glr.c:783  */
    break;

  case 38:
#line 1766 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4503 "c99-parser.c" /* glr.c:783  */
    break;

  case 39:
#line 1770 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4511 "c99-parser.c" /* glr.c:783  */
    break;

  case 40:
#line 1776 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_ASM_OPERAND, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4519 "c99-parser.c" /* glr.c:783  */
    break;

  case 41:
#line 1780 "c99.y" /* glr.c:783  */
    {
    AST symbol_tree = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_ASM_OPERAND, symbol_tree, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 4529 "c99-parser.c" /* glr.c:783  */
    break;

  case 42:
#line 1786 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4537 "c99-parser.c" /* glr.c:783  */
    break;

  case 43:
#line 1794 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4545 "c99-parser.c" /* glr.c:783  */
    break;

  case 44:
#line 1798 "c99.y" /* glr.c:783  */
    {
    // This is an error but also a common extension
    ((*yyvalp).ast) = ASTLeaf(AST_EMPTY_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4554 "c99-parser.c" /* glr.c:783  */
    break;

  case 45:
#line 1805 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SIMPLE_DECLARATION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4562 "c99-parser.c" /* glr.c:783  */
    break;

  case 46:
#line 1809 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SIMPLE_DECLARATION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4570 "c99-parser.c" /* glr.c:783  */
    break;

  case 47:
#line 1813 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SIMPLE_DECLARATION, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4578 "c99-parser.c" /* glr.c:783  */
    break;

  case 48:
#line 1819 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SIMPLE_DECLARATION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4586 "c99-parser.c" /* glr.c:783  */
    break;

  case 49:
#line 1825 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4594 "c99-parser.c" /* glr.c:783  */
    break;

  case 50:
#line 1829 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4602 "c99-parser.c" /* glr.c:783  */
    break;

  case 51:
#line 1833 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4610 "c99-parser.c" /* glr.c:783  */
    break;

  case 52:
#line 1837 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4618 "c99-parser.c" /* glr.c:783  */
    break;

  case 53:
#line 1841 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4626 "c99-parser.c" /* glr.c:783  */
    break;

  case 54:
#line 1848 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4634 "c99-parser.c" /* glr.c:783  */
    break;

  case 55:
#line 1852 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4642 "c99-parser.c" /* glr.c:783  */
    break;

  case 56:
#line 1858 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4650 "c99-parser.c" /* glr.c:783  */
    break;

  case 57:
#line 1862 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4658 "c99-parser.c" /* glr.c:783  */
    break;

  case 58:
#line 1866 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4666 "c99-parser.c" /* glr.c:783  */
    break;

  case 59:
#line 1870 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4674 "c99-parser.c" /* glr.c:783  */
    break;

  case 60:
#line 1874 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4682 "c99-parser.c" /* glr.c:783  */
    break;

  case 61:
#line 1880 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4690 "c99-parser.c" /* glr.c:783  */
    break;

  case 62:
#line 1884 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4698 "c99-parser.c" /* glr.c:783  */
    break;

  case 63:
#line 1888 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4706 "c99-parser.c" /* glr.c:783  */
    break;

  case 64:
#line 1892 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4714 "c99-parser.c" /* glr.c:783  */
    break;

  case 65:
#line 1896 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4722 "c99-parser.c" /* glr.c:783  */
    break;

  case 66:
#line 1908 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4730 "c99-parser.c" /* glr.c:783  */
    break;

  case 67:
#line 1912 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4738 "c99-parser.c" /* glr.c:783  */
    break;

  case 68:
#line 1916 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4746 "c99-parser.c" /* glr.c:783  */
    break;

  case 69:
#line 1920 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4754 "c99-parser.c" /* glr.c:783  */
    break;

  case 70:
#line 1926 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4762 "c99-parser.c" /* glr.c:783  */
    break;

  case 71:
#line 1930 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4770 "c99-parser.c" /* glr.c:783  */
    break;

  case 72:
#line 1936 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4778 "c99-parser.c" /* glr.c:783  */
    break;

  case 73:
#line 1940 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 4786 "c99-parser.c" /* glr.c:783  */
    break;

  case 74:
#line 1946 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4794 "c99-parser.c" /* glr.c:783  */
    break;

  case 75:
#line 1950 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4802 "c99-parser.c" /* glr.c:783  */
    break;

  case 76:
#line 1955 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4810 "c99-parser.c" /* glr.c:783  */
    break;

  case 77:
#line 1959 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4818 "c99-parser.c" /* glr.c:783  */
    break;

  case 78:
#line 1963 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_TYPEDEF_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4826 "c99-parser.c" /* glr.c:783  */
    break;

  case 79:
#line 1968 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4834 "c99-parser.c" /* glr.c:783  */
    break;

  case 80:
#line 1973 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SIGNED_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4842 "c99-parser.c" /* glr.c:783  */
    break;

  case 81:
#line 1977 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_UNSIGNED_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4850 "c99-parser.c" /* glr.c:783  */
    break;

  case 82:
#line 1981 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_LONG_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4858 "c99-parser.c" /* glr.c:783  */
    break;

  case 83:
#line 1985 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SHORT_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4866 "c99-parser.c" /* glr.c:783  */
    break;

  case 84:
#line 1990 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_GCC_COMPLEX_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4874 "c99-parser.c" /* glr.c:783  */
    break;

  case 85:
#line 1994 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_GCC_IMAGINARY_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4882 "c99-parser.c" /* glr.c:783  */
    break;

  case 86:
#line 2000 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_AUTO_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4890 "c99-parser.c" /* glr.c:783  */
    break;

  case 87:
#line 2004 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_REGISTER_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4898 "c99-parser.c" /* glr.c:783  */
    break;

  case 88:
#line 2008 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_STATIC_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4906 "c99-parser.c" /* glr.c:783  */
    break;

  case 89:
#line 2012 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_EXTERN_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4914 "c99-parser.c" /* glr.c:783  */
    break;

  case 90:
#line 2017 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_THREAD_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4922 "c99-parser.c" /* glr.c:783  */
    break;

  case 91:
#line 2023 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_INLINE_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4930 "c99-parser.c" /* glr.c:783  */
    break;

  case 92:
#line 2029 "c99.y" /* glr.c:783  */
    {
}
#line 4937 "c99-parser.c" /* glr.c:783  */
    break;

  case 93:
#line 2032 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4945 "c99-parser.c" /* glr.c:783  */
    break;

  case 94:
#line 2037 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_GCC_COMPLEX_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 4953 "c99-parser.c" /* glr.c:783  */
    break;

  case 95:
#line 2043 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4961 "c99-parser.c" /* glr.c:783  */
    break;

  case 96:
#line 2047 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4969 "c99-parser.c" /* glr.c:783  */
    break;

  case 97:
#line 2051 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 4977 "c99-parser.c" /* glr.c:783  */
    break;

  case 98:
#line 2057 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4985 "c99-parser.c" /* glr.c:783  */
    break;

  case 99:
#line 2061 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 4993 "c99-parser.c" /* glr.c:783  */
    break;

  case 100:
#line 2065 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5001 "c99-parser.c" /* glr.c:783  */
    break;

  case 101:
#line 2069 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5009 "c99-parser.c" /* glr.c:783  */
    break;

  case 102:
#line 2073 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5017 "c99-parser.c" /* glr.c:783  */
    break;

  case 103:
#line 2079 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5025 "c99-parser.c" /* glr.c:783  */
    break;

  case 104:
#line 2083 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5033 "c99-parser.c" /* glr.c:783  */
    break;

  case 105:
#line 2087 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5041 "c99-parser.c" /* glr.c:783  */
    break;

  case 106:
#line 2091 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5049 "c99-parser.c" /* glr.c:783  */
    break;

  case 107:
#line 2095 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_TYPE_SPECIFIER_SEQ, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5057 "c99-parser.c" /* glr.c:783  */
    break;

  case 108:
#line 2101 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_SIMPLE_TYPE_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5065 "c99-parser.c" /* glr.c:783  */
    break;

  case 109:
#line 2105 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5073 "c99-parser.c" /* glr.c:783  */
    break;

  case 110:
#line 2110 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_TYPEOF_EXPR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5081 "c99-parser.c" /* glr.c:783  */
    break;

  case 111:
#line 2114 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_TYPEOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5089 "c99-parser.c" /* glr.c:783  */
    break;

  case 112:
#line 2121 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5097 "c99-parser.c" /* glr.c:783  */
    break;

  case 113:
#line 2127 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_CHAR_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5105 "c99-parser.c" /* glr.c:783  */
    break;

  case 114:
#line 2131 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_BOOL_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5113 "c99-parser.c" /* glr.c:783  */
    break;

  case 115:
#line 2135 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SHORT_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5121 "c99-parser.c" /* glr.c:783  */
    break;

  case 116:
#line 2139 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_INT_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5129 "c99-parser.c" /* glr.c:783  */
    break;

  case 117:
#line 2143 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_LONG_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5137 "c99-parser.c" /* glr.c:783  */
    break;

  case 118:
#line 2147 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SIGNED_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5145 "c99-parser.c" /* glr.c:783  */
    break;

  case 119:
#line 2151 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_UNSIGNED_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5153 "c99-parser.c" /* glr.c:783  */
    break;

  case 120:
#line 2155 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_FLOAT_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5161 "c99-parser.c" /* glr.c:783  */
    break;

  case 121:
#line 2159 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_DOUBLE_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5169 "c99-parser.c" /* glr.c:783  */
    break;

  case 122:
#line 2163 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_VOID_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5177 "c99-parser.c" /* glr.c:783  */
    break;

  case 123:
#line 2169 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake2(AST_ELABORATED_TYPE_CLASS_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), identifier, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5187 "c99-parser.c" /* glr.c:783  */
    break;

  case 124:
#line 2175 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake1(AST_ELABORATED_TYPE_ENUM_SPEC, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5197 "c99-parser.c" /* glr.c:783  */
    break;

  case 125:
#line 2182 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_ELABORATED_TYPE_CLASS_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5207 "c99-parser.c" /* glr.c:783  */
    break;

  case 126:
#line 2188 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake2(AST_GCC_ELABORATED_TYPE_ENUM_SPEC, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5217 "c99-parser.c" /* glr.c:783  */
    break;

  case 127:
#line 2199 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5225 "c99-parser.c" /* glr.c:783  */
    break;

  case 128:
#line 2203 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5233 "c99-parser.c" /* glr.c:783  */
    break;

  case 129:
#line 2209 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5241 "c99-parser.c" /* glr.c:783  */
    break;

  case 130:
#line 2213 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5249 "c99-parser.c" /* glr.c:783  */
    break;

  case 131:
#line 2218 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5257 "c99-parser.c" /* glr.c:783  */
    break;

  case 132:
#line 2222 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5265 "c99-parser.c" /* glr.c:783  */
    break;

  case 133:
#line 2226 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5273 "c99-parser.c" /* glr.c:783  */
    break;

  case 134:
#line 2230 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5281 "c99-parser.c" /* glr.c:783  */
    break;

  case 135:
#line 2234 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5289 "c99-parser.c" /* glr.c:783  */
    break;

  case 136:
#line 2238 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_INIT_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5297 "c99-parser.c" /* glr.c:783  */
    break;

  case 137:
#line 2245 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_ASM_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5305 "c99-parser.c" /* glr.c:783  */
    break;

  case 138:
#line 2252 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5313 "c99-parser.c" /* glr.c:783  */
    break;

  case 139:
#line 2256 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5321 "c99-parser.c" /* glr.c:783  */
    break;

  case 140:
#line 2261 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_GCC_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5329 "c99-parser.c" /* glr.c:783  */
    break;

  case 141:
#line 2265 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_GCC_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5337 "c99-parser.c" /* glr.c:783  */
    break;

  case 142:
#line 2271 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_SPEC, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5345 "c99-parser.c" /* glr.c:783  */
    break;

  case 143:
#line 2275 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_SPEC, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5353 "c99-parser.c" /* glr.c:783  */
    break;

  case 144:
#line 2285 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5361 "c99-parser.c" /* glr.c:783  */
    break;

  case 145:
#line 2289 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5369 "c99-parser.c" /* glr.c:783  */
    break;

  case 146:
#line 2294 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5377 "c99-parser.c" /* glr.c:783  */
    break;

  case 147:
#line 2298 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5385 "c99-parser.c" /* glr.c:783  */
    break;

  case 148:
#line 2304 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5393 "c99-parser.c" /* glr.c:783  */
    break;

  case 149:
#line 2308 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PARENTHESIZED_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5401 "c99-parser.c" /* glr.c:783  */
    break;

  case 150:
#line 2315 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 5409 "c99-parser.c" /* glr.c:783  */
    break;

  case 151:
#line 2319 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5417 "c99-parser.c" /* glr.c:783  */
    break;

  case 152:
#line 2325 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5425 "c99-parser.c" /* glr.c:783  */
    break;

  case 153:
#line 2332 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 5433 "c99-parser.c" /* glr.c:783  */
    break;

  case 154:
#line 2336 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5441 "c99-parser.c" /* glr.c:783  */
    break;

  case 155:
#line 2341 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_STATIC_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5449 "c99-parser.c" /* glr.c:783  */
    break;

  case 156:
#line 2348 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 5457 "c99-parser.c" /* glr.c:783  */
    break;

  case 157:
#line 2352 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_VLA_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5465 "c99-parser.c" /* glr.c:783  */
    break;

  case 158:
#line 2356 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5473 "c99-parser.c" /* glr.c:783  */
    break;

  case 159:
#line 2362 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5481 "c99-parser.c" /* glr.c:783  */
    break;

  case 160:
#line 2366 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5489 "c99-parser.c" /* glr.c:783  */
    break;

  case 161:
#line 2370 "c99.y" /* glr.c:783  */
    {
	AST empty_parameter = ASTLeaf(AST_EMPTY_PARAMETER_DECLARATION_CLAUSE, NULL, 0, NULL);

	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), empty_parameter, NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5499 "c99-parser.c" /* glr.c:783  */
    break;

  case 162:
#line 2379 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5507 "c99-parser.c" /* glr.c:783  */
    break;

  case 163:
#line 2384 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_PARENTHESIZED_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5515 "c99-parser.c" /* glr.c:783  */
    break;

  case 164:
#line 2390 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5523 "c99-parser.c" /* glr.c:783  */
    break;

  case 165:
#line 2394 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5531 "c99-parser.c" /* glr.c:783  */
    break;

  case 166:
#line 2400 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_CONST_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5539 "c99-parser.c" /* glr.c:783  */
    break;

  case 167:
#line 2404 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_VOLATILE_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5547 "c99-parser.c" /* glr.c:783  */
    break;

  case 168:
#line 2409 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_GCC_RESTRICT_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 5555 "c99-parser.c" /* glr.c:783  */
    break;

  case 169:
#line 2415 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5563 "c99-parser.c" /* glr.c:783  */
    break;

  case 170:
#line 2419 "c99.y" /* glr.c:783  */
    {
	AST empty_parameter = ASTLeaf(AST_EMPTY_PARAMETER_DECLARATION_CLAUSE, NULL, 0, NULL);

	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), empty_parameter, NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5573 "c99-parser.c" /* glr.c:783  */
    break;

  case 171:
#line 2425 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5581 "c99-parser.c" /* glr.c:783  */
    break;

  case 172:
#line 2429 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5589 "c99-parser.c" /* glr.c:783  */
    break;

  case 173:
#line 2433 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL,  ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5597 "c99-parser.c" /* glr.c:783  */
    break;

  case 174:
#line 2437 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast),  ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5605 "c99-parser.c" /* glr.c:783  */
    break;

  case 175:
#line 2441 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast),  ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5613 "c99-parser.c" /* glr.c:783  */
    break;

  case 176:
#line 2445 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PARENTHESIZED_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5621 "c99-parser.c" /* glr.c:783  */
    break;

  case 177:
#line 2451 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_DECLARATOR_ID_EXPR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5629 "c99-parser.c" /* glr.c:783  */
    break;

  case 178:
#line 2458 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake2(AST_ENUM_SPECIFIER, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5639 "c99-parser.c" /* glr.c:783  */
    break;

  case 179:
#line 2464 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_ENUM_SPECIFIER, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5647 "c99-parser.c" /* glr.c:783  */
    break;

  case 180:
#line 2468 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake2(AST_ENUM_SPECIFIER, identifier, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5657 "c99-parser.c" /* glr.c:783  */
    break;

  case 181:
#line 2474 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_ENUM_SPECIFIER, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5665 "c99-parser.c" /* glr.c:783  */
    break;

  case 182:
#line 2479 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_ENUM_SPECIFIER, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5675 "c99-parser.c" /* glr.c:783  */
    break;

  case 183:
#line 2485 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_ENUM_SPECIFIER, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5683 "c99-parser.c" /* glr.c:783  */
    break;

  case 184:
#line 2489 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_ENUM_SPECIFIER, identifier, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5693 "c99-parser.c" /* glr.c:783  */
    break;

  case 185:
#line 2495 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_ENUM_SPECIFIER, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5701 "c99-parser.c" /* glr.c:783  */
    break;

  case 186:
#line 2502 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5709 "c99-parser.c" /* glr.c:783  */
    break;

  case 187:
#line 2508 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast);
}
#line 5717 "c99-parser.c" /* glr.c:783  */
    break;

  case 188:
#line 2513 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5725 "c99-parser.c" /* glr.c:783  */
    break;

  case 189:
#line 2517 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5733 "c99-parser.c" /* glr.c:783  */
    break;

  case 190:
#line 2523 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake2(AST_ENUMERATOR_DEF, identifier, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5743 "c99-parser.c" /* glr.c:783  */
    break;

  case 191:
#line 2529 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake2(AST_ENUMERATOR_DEF, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5753 "c99-parser.c" /* glr.c:783  */
    break;

  case 192:
#line 2537 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_TYPE_ID, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5761 "c99-parser.c" /* glr.c:783  */
    break;

  case 193:
#line 2541 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_TYPE_ID, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5769 "c99-parser.c" /* glr.c:783  */
    break;

  case 194:
#line 2547 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5777 "c99-parser.c" /* glr.c:783  */
    break;

  case 195:
#line 2551 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5785 "c99-parser.c" /* glr.c:783  */
    break;

  case 196:
#line 2555 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5793 "c99-parser.c" /* glr.c:783  */
    break;

  case 197:
#line 2560 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5801 "c99-parser.c" /* glr.c:783  */
    break;

  case 198:
#line 2564 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_POINTER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5809 "c99-parser.c" /* glr.c:783  */
    break;

  case 199:
#line 2568 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5817 "c99-parser.c" /* glr.c:783  */
    break;

  case 200:
#line 2574 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PARENTHESIZED_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5825 "c99-parser.c" /* glr.c:783  */
    break;

  case 201:
#line 2578 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5833 "c99-parser.c" /* glr.c:783  */
    break;

  case 202:
#line 2582 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5841 "c99-parser.c" /* glr.c:783  */
    break;

  case 203:
#line 2586 "c99.y" /* glr.c:783  */
    {
	AST empty_parameter = ASTLeaf(AST_EMPTY_PARAMETER_DECLARATION_CLAUSE, NULL, 0, NULL);

	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, NULL, empty_parameter, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5851 "c99-parser.c" /* glr.c:783  */
    break;

  case 204:
#line 2592 "c99.y" /* glr.c:783  */
    {
	AST empty_parameter = ASTLeaf(AST_EMPTY_PARAMETER_DECLARATION_CLAUSE, NULL, 0, NULL);

	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_FUNC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), empty_parameter, NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5861 "c99-parser.c" /* glr.c:783  */
    break;

  case 205:
#line 2598 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5869 "c99-parser.c" /* glr.c:783  */
    break;

  case 206:
#line 2602 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5877 "c99-parser.c" /* glr.c:783  */
    break;

  case 207:
#line 2606 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 5885 "c99-parser.c" /* glr.c:783  */
    break;

  case 208:
#line 2610 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL,  ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5893 "c99-parser.c" /* glr.c:783  */
    break;

  case 209:
#line 2614 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast),  ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5901 "c99-parser.c" /* glr.c:783  */
    break;

  case 210:
#line 2618 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast),  ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5909 "c99-parser.c" /* glr.c:783  */
    break;

  case 211:
#line 2624 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_KR_PARAMETER_LIST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5917 "c99-parser.c" /* glr.c:783  */
    break;

  case 212:
#line 2629 "c99.y" /* glr.c:783  */
    {
    AST symbol = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

    ((*yyvalp).ast) = ASTListLeaf(symbol);
}
#line 5927 "c99-parser.c" /* glr.c:783  */
    break;

  case 213:
#line 2635 "c99.y" /* glr.c:783  */
    {
    AST symbol = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), symbol);
}
#line 5937 "c99-parser.c" /* glr.c:783  */
    break;

  case 214:
#line 2643 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 5945 "c99-parser.c" /* glr.c:783  */
    break;

  case 215:
#line 2647 "c99.y" /* glr.c:783  */
    {
    AST variadic_arg = ASTLeaf(AST_VARIADIC_ARG, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), variadic_arg);
}
#line 5954 "c99-parser.c" /* glr.c:783  */
    break;

  case 216:
#line 2654 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5962 "c99-parser.c" /* glr.c:783  */
    break;

  case 217:
#line 2658 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 5970 "c99-parser.c" /* glr.c:783  */
    break;

  case 218:
#line 2664 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_PARAMETER_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5978 "c99-parser.c" /* glr.c:783  */
    break;

  case 219:
#line 2668 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_PARAMETER_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5986 "c99-parser.c" /* glr.c:783  */
    break;

  case 220:
#line 2672 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_PARAMETER_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 5994 "c99-parser.c" /* glr.c:783  */
    break;

  case 221:
#line 2677 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_PARAMETER_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6002 "c99-parser.c" /* glr.c:783  */
    break;

  case 222:
#line 2681 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_PARAMETER_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6010 "c99-parser.c" /* glr.c:783  */
    break;

  case 223:
#line 2687 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_EQUAL_INITIALIZER, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6018 "c99-parser.c" /* glr.c:783  */
    break;

  case 224:
#line 2693 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6026 "c99-parser.c" /* glr.c:783  */
    break;

  case 225:
#line 2697 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_INITIALIZER_BRACES, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6034 "c99-parser.c" /* glr.c:783  */
    break;

  case 226:
#line 2701 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_INITIALIZER_BRACES, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6042 "c99-parser.c" /* glr.c:783  */
    break;

  case 227:
#line 2705 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_INITIALIZER_BRACES, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6050 "c99-parser.c" /* glr.c:783  */
    break;

  case 228:
#line 2711 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6058 "c99-parser.c" /* glr.c:783  */
    break;

  case 229:
#line 2715 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6066 "c99-parser.c" /* glr.c:783  */
    break;

  case 230:
#line 2719 "c99.y" /* glr.c:783  */
    {
    AST designated_initializer = ASTMake2(AST_DESIGNATED_INITIALIZER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);

    ((*yyvalp).ast) = ASTListLeaf(designated_initializer);
}
#line 6076 "c99-parser.c" /* glr.c:783  */
    break;

  case 231:
#line 2725 "c99.y" /* glr.c:783  */
    {
    AST designated_initializer = ASTMake2(AST_DESIGNATED_INITIALIZER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);

    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), designated_initializer);
}
#line 6086 "c99-parser.c" /* glr.c:783  */
    break;

  case 232:
#line 2732 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);

	AST gcc_initializer_clause = ASTMake2(AST_GCC_INITIALIZER_CLAUSE, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);

	((*yyvalp).ast) = ASTListLeaf(gcc_initializer_clause);
}
#line 6098 "c99-parser.c" /* glr.c:783  */
    break;

  case 233:
#line 2740 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);

	AST gcc_initializer_clause = ASTMake2(AST_GCC_INITIALIZER_CLAUSE, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);

	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), gcc_initializer_clause);
}
#line 6110 "c99-parser.c" /* glr.c:783  */
    break;

  case 234:
#line 2750 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_DESIGNATION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6118 "c99-parser.c" /* glr.c:783  */
    break;

  case 235:
#line 2756 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6126 "c99-parser.c" /* glr.c:783  */
    break;

  case 236:
#line 2760 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6134 "c99-parser.c" /* glr.c:783  */
    break;

  case 237:
#line 2766 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_INDEX_DESIGNATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6142 "c99-parser.c" /* glr.c:783  */
    break;

  case 238:
#line 2770 "c99.y" /* glr.c:783  */
    {
    AST symbol = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

    ((*yyvalp).ast) = ASTMake1(AST_FIELD_DESIGNATOR, symbol, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6152 "c99-parser.c" /* glr.c:783  */
    break;

  case 239:
#line 2778 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_FUNCTION_DEFINITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6160 "c99-parser.c" /* glr.c:783  */
    break;

  case 240:
#line 2782 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_FUNCTION_DEFINITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6168 "c99-parser.c" /* glr.c:783  */
    break;

  case 241:
#line 2787 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake4(AST_FUNCTION_DEFINITION, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6176 "c99-parser.c" /* glr.c:783  */
    break;

  case 242:
#line 2791 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake4(AST_FUNCTION_DEFINITION, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6184 "c99-parser.c" /* glr.c:783  */
    break;

  case 243:
#line 2796 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_EXTENSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 6192 "c99-parser.c" /* glr.c:783  */
    break;

  case 244:
#line 2802 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6200 "c99-parser.c" /* glr.c:783  */
    break;

  case 245:
#line 2806 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6208 "c99-parser.c" /* glr.c:783  */
    break;

  case 246:
#line 2812 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_FUNCTION_BODY, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6216 "c99-parser.c" /* glr.c:783  */
    break;

  case 247:
#line 2822 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_CLASS_SPECIFIER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6224 "c99-parser.c" /* glr.c:783  */
    break;

  case 248:
#line 2826 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_CLASS_SPECIFIER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6232 "c99-parser.c" /* glr.c:783  */
    break;

  case 249:
#line 2832 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_CLASS_HEAD_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6240 "c99-parser.c" /* glr.c:783  */
    break;

  case 250:
#line 2836 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_CLASS_HEAD_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), identifier, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6250 "c99-parser.c" /* glr.c:783  */
    break;

  case 251:
#line 2843 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_GCC_CLASS_HEAD_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6258 "c99-parser.c" /* glr.c:783  */
    break;

  case 252:
#line 2847 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake4(AST_GCC_CLASS_HEAD_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), identifier, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6268 "c99-parser.c" /* glr.c:783  */
    break;

  case 253:
#line 2855 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_CLASS_KEY_STRUCT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 6276 "c99-parser.c" /* glr.c:783  */
    break;

  case 254:
#line 2859 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_CLASS_KEY_UNION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 6284 "c99-parser.c" /* glr.c:783  */
    break;

  case 255:
#line 2865 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6292 "c99-parser.c" /* glr.c:783  */
    break;

  case 256:
#line 2869 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6300 "c99-parser.c" /* glr.c:783  */
    break;

  case 257:
#line 2875 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MEMBER_DECLARATION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6308 "c99-parser.c" /* glr.c:783  */
    break;

  case 258:
#line 2879 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MEMBER_DECLARATION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6316 "c99-parser.c" /* glr.c:783  */
    break;

  case 259:
#line 2883 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6324 "c99-parser.c" /* glr.c:783  */
    break;

  case 260:
#line 2888 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_EMPTY_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6332 "c99-parser.c" /* glr.c:783  */
    break;

  case 261:
#line 2893 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_EXTENSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 6340 "c99-parser.c" /* glr.c:783  */
    break;

  case 262:
#line 2899 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6348 "c99-parser.c" /* glr.c:783  */
    break;

  case 263:
#line 2903 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6356 "c99-parser.c" /* glr.c:783  */
    break;

  case 264:
#line 2909 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MEMBER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6364 "c99-parser.c" /* glr.c:783  */
    break;

  case 265:
#line 2913 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MEMBER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6372 "c99-parser.c" /* glr.c:783  */
    break;

  case 266:
#line 2917 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_BITFIELD_DECLARATOR, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6380 "c99-parser.c" /* glr.c:783  */
    break;

  case 267:
#line 2921 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
	AST declarator_id_expr = ASTMake1(AST_DECLARATOR_ID_EXPR, identifier, ASTFileName(identifier), ASTLine(identifier), NULL);

	((*yyvalp).ast) = ASTMake2(AST_BITFIELD_DECLARATOR, declarator_id_expr, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6391 "c99-parser.c" /* glr.c:783  */
    break;

  case 268:
#line 2929 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_MEMBER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6399 "c99-parser.c" /* glr.c:783  */
    break;

  case 269:
#line 2933 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_MEMBER_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6407 "c99-parser.c" /* glr.c:783  */
    break;

  case 270:
#line 2937 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake3(AST_GCC_BITFIELD_DECLARATOR, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6417 "c99-parser.c" /* glr.c:783  */
    break;

  case 271:
#line 2943 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_BITFIELD_DECLARATOR, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6425 "c99-parser.c" /* glr.c:783  */
    break;

  case 272:
#line 2949 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6433 "c99-parser.c" /* glr.c:783  */
    break;

  case 273:
#line 2959 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6441 "c99-parser.c" /* glr.c:783  */
    break;

  case 274:
#line 2963 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6449 "c99-parser.c" /* glr.c:783  */
    break;

  case 275:
#line 2967 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6457 "c99-parser.c" /* glr.c:783  */
    break;

  case 276:
#line 2973 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6465 "c99-parser.c" /* glr.c:783  */
    break;

  case 277:
#line 2977 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6473 "c99-parser.c" /* glr.c:783  */
    break;

  case 278:
#line 2981 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6481 "c99-parser.c" /* glr.c:783  */
    break;

  case 279:
#line 2985 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6489 "c99-parser.c" /* glr.c:783  */
    break;

  case 280:
#line 2989 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6497 "c99-parser.c" /* glr.c:783  */
    break;

  case 281:
#line 2993 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6505 "c99-parser.c" /* glr.c:783  */
    break;

  case 282:
#line 2997 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6513 "c99-parser.c" /* glr.c:783  */
    break;

  case 283:
#line 3004 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
	
	((*yyvalp).ast) = ASTMake2(AST_LABELED_STATEMENT, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6523 "c99-parser.c" /* glr.c:783  */
    break;

  case 284:
#line 3010 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_CASE_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6531 "c99-parser.c" /* glr.c:783  */
    break;

  case 285:
#line 3014 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_DEFAULT_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6539 "c99-parser.c" /* glr.c:783  */
    break;

  case 286:
#line 3019 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_GCC_CASE_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6547 "c99-parser.c" /* glr.c:783  */
    break;

  case 287:
#line 3025 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_EXPRESSION_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6555 "c99-parser.c" /* glr.c:783  */
    break;

  case 288:
#line 3029 "c99.y" /* glr.c:783  */
    {
	// Empty statement ...
	((*yyvalp).ast) = ASTLeaf(AST_EMPTY_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6564 "c99-parser.c" /* glr.c:783  */
    break;

  case 289:
#line 3036 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_DECLARATION_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6572 "c99-parser.c" /* glr.c:783  */
    break;

  case 290:
#line 3042 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_COMPOUND_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6580 "c99-parser.c" /* glr.c:783  */
    break;

  case 291:
#line 3046 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_COMPOUND_STATEMENT, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6588 "c99-parser.c" /* glr.c:783  */
    break;

  case 292:
#line 3052 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6596 "c99-parser.c" /* glr.c:783  */
    break;

  case 293:
#line 3056 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 6604 "c99-parser.c" /* glr.c:783  */
    break;

  case 294:
#line 3064 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_IF_ELSE_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6612 "c99-parser.c" /* glr.c:783  */
    break;

  case 295:
#line 3071 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_IF_ELSE_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6620 "c99-parser.c" /* glr.c:783  */
    break;

  case 296:
#line 3078 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6628 "c99-parser.c" /* glr.c:783  */
    break;

  case 297:
#line 3082 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6636 "c99-parser.c" /* glr.c:783  */
    break;

  case 298:
#line 3088 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_SWITCH_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6644 "c99-parser.c" /* glr.c:783  */
    break;

  case 299:
#line 3094 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_CONDITION, NULL, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6652 "c99-parser.c" /* glr.c:783  */
    break;

  case 300:
#line 3098 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_CONDITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6660 "c99-parser.c" /* glr.c:783  */
    break;

  case 301:
#line 3103 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_CONDITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast),
			ASTMake4(AST_GCC_CONDITION_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL),
			ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6670 "c99-parser.c" /* glr.c:783  */
    break;

  case 302:
#line 3109 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_CONDITION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast),
			ASTMake4(AST_GCC_CONDITION_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL),
			ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6680 "c99-parser.c" /* glr.c:783  */
    break;

  case 303:
#line 3115 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_CONDITION, NULL,
			ASTMake4(AST_GCC_CONDITION_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL),
			ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6690 "c99-parser.c" /* glr.c:783  */
    break;

  case 304:
#line 3123 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_WHILE_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6698 "c99-parser.c" /* glr.c:783  */
    break;

  case 305:
#line 3127 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_DO_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6706 "c99-parser.c" /* glr.c:783  */
    break;

  case 306:
#line 3131 "c99.y" /* glr.c:783  */
    {
    AST loop_control = ASTMake3(AST_LOOP_CONTROL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
	((*yyvalp).ast) = ASTMake3(AST_FOR_STATEMENT, loop_control, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6715 "c99-parser.c" /* glr.c:783  */
    break;

  case 307:
#line 3138 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6723 "c99-parser.c" /* glr.c:783  */
    break;

  case 308:
#line 3142 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 6731 "c99-parser.c" /* glr.c:783  */
    break;

  case 309:
#line 3148 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6739 "c99-parser.c" /* glr.c:783  */
    break;

  case 310:
#line 3152 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 6747 "c99-parser.c" /* glr.c:783  */
    break;

  case 311:
#line 3159 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6755 "c99-parser.c" /* glr.c:783  */
    break;

  case 312:
#line 3163 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6763 "c99-parser.c" /* glr.c:783  */
    break;

  case 313:
#line 3169 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_BREAK_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6771 "c99-parser.c" /* glr.c:783  */
    break;

  case 314:
#line 3173 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_CONTINUE_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6779 "c99-parser.c" /* glr.c:783  */
    break;

  case 315:
#line 3177 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_RETURN_STATEMENT, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6787 "c99-parser.c" /* glr.c:783  */
    break;

  case 316:
#line 3181 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_RETURN_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6795 "c99-parser.c" /* glr.c:783  */
    break;

  case 317:
#line 3185 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
	
	((*yyvalp).ast) = ASTMake1(AST_GOTO_STATEMENT, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6805 "c99-parser.c" /* glr.c:783  */
    break;

  case 318:
#line 3192 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_GOTO_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6813 "c99-parser.c" /* glr.c:783  */
    break;

  case 319:
#line 3202 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6821 "c99-parser.c" /* glr.c:783  */
    break;

  case 320:
#line 3206 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PARENTHESIZED_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6829 "c99-parser.c" /* glr.c:783  */
    break;

  case 321:
#line 3210 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6837 "c99-parser.c" /* glr.c:783  */
    break;

  case 322:
#line 3224 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_PARENTHESIZED_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6845 "c99-parser.c" /* glr.c:783  */
    break;

  case 323:
#line 3228 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_BUILTIN_VA_ARG, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6853 "c99-parser.c" /* glr.c:783  */
    break;

  case 324:
#line 3232 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_GCC_BUILTIN_OFFSETOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6861 "c99-parser.c" /* glr.c:783  */
    break;

  case 325:
#line 3236 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_GCC_BUILTIN_CHOOSE_EXPR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6869 "c99-parser.c" /* glr.c:783  */
    break;

  case 326:
#line 3240 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_GCC_BUILTIN_TYPES_COMPATIBLE_P, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6877 "c99-parser.c" /* glr.c:783  */
    break;

  case 327:
#line 3253 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_GCC_OFFSETOF_MEMBER_DESIGNATOR,
            ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text),
            (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6887 "c99-parser.c" /* glr.c:783  */
    break;

  case 328:
#line 3259 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_GCC_OFFSETOF_MEMBER_DESIGNATOR,
            ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text),
            NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6897 "c99-parser.c" /* glr.c:783  */
    break;

  case 329:
#line 3267 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6905 "c99-parser.c" /* glr.c:783  */
    break;

  case 330:
#line 3273 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 6913 "c99-parser.c" /* glr.c:783  */
    break;

  case 331:
#line 3279 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 6921 "c99-parser.c" /* glr.c:783  */
    break;

  case 332:
#line 3283 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_ARRAY_SUBSCRIPT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6929 "c99-parser.c" /* glr.c:783  */
    break;

  case 333:
#line 3287 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_FUNCTION_CALL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6937 "c99-parser.c" /* glr.c:783  */
    break;

  case 334:
#line 3291 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_FUNCTION_CALL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6945 "c99-parser.c" /* glr.c:783  */
    break;

  case 335:
#line 3295 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_CLASS_MEMBER_ACCESS, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6953 "c99-parser.c" /* glr.c:783  */
    break;

  case 336:
#line 3299 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_POINTER_CLASS_MEMBER_ACCESS, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6961 "c99-parser.c" /* glr.c:783  */
    break;

  case 337:
#line 3303 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_POSTINCREMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6969 "c99-parser.c" /* glr.c:783  */
    break;

  case 338:
#line 3307 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_POSTDECREMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 6977 "c99-parser.c" /* glr.c:783  */
    break;

  case 339:
#line 3312 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_POSTFIX_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6985 "c99-parser.c" /* glr.c:783  */
    break;

  case 340:
#line 3316 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_POSTFIX_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 6993 "c99-parser.c" /* glr.c:783  */
    break;

  case 341:
#line 3322 "c99.y" /* glr.c:783  */
    {
    AST expression_holder = ASTMake1(AST_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
	((*yyvalp).ast) = ASTListLeaf(expression_holder);
}
#line 7002 "c99-parser.c" /* glr.c:783  */
    break;

  case 342:
#line 3327 "c99.y" /* glr.c:783  */
    {
    AST expression_holder = ASTMake1(AST_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), expression_holder);
}
#line 7011 "c99-parser.c" /* glr.c:783  */
    break;

  case 343:
#line 3334 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7019 "c99-parser.c" /* glr.c:783  */
    break;

  case 344:
#line 3338 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PREINCREMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7027 "c99-parser.c" /* glr.c:783  */
    break;

  case 345:
#line 3342 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PREDECREMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7035 "c99-parser.c" /* glr.c:783  */
    break;

  case 346:
#line 3346 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node_type), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7043 "c99-parser.c" /* glr.c:783  */
    break;

  case 347:
#line 3350 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_SIZEOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7051 "c99-parser.c" /* glr.c:783  */
    break;

  case 348:
#line 3354 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_SIZEOF_TYPEID, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7059 "c99-parser.c" /* glr.c:783  */
    break;

  case 349:
#line 3359 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_EXTENSION_EXPR, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7067 "c99-parser.c" /* glr.c:783  */
    break;

  case 350:
#line 3363 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_ALIGNOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7075 "c99-parser.c" /* glr.c:783  */
    break;

  case 351:
#line 3367 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_ALIGNOF_TYPE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7083 "c99-parser.c" /* glr.c:783  */
    break;

  case 352:
#line 3371 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_REAL_PART, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7091 "c99-parser.c" /* glr.c:783  */
    break;

  case 353:
#line 3375 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_GCC_IMAG_PART, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7099 "c99-parser.c" /* glr.c:783  */
    break;

  case 354:
#line 3379 "c99.y" /* glr.c:783  */
    {
	AST identifier = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

	((*yyvalp).ast) = ASTMake1(AST_GCC_LABEL_ADDR, identifier, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7109 "c99-parser.c" /* glr.c:783  */
    break;

  case 355:
#line 3387 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_DERREFERENCE;
}
#line 7117 "c99-parser.c" /* glr.c:783  */
    break;

  case 356:
#line 3391 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_REFERENCE;
}
#line 7125 "c99-parser.c" /* glr.c:783  */
    break;

  case 357:
#line 3395 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_PLUS;
}
#line 7133 "c99-parser.c" /* glr.c:783  */
    break;

  case 358:
#line 3399 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_NEG;
}
#line 7141 "c99-parser.c" /* glr.c:783  */
    break;

  case 359:
#line 3403 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_NOT;
}
#line 7149 "c99-parser.c" /* glr.c:783  */
    break;

  case 360:
#line 3407 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_COMPLEMENT;
}
#line 7157 "c99-parser.c" /* glr.c:783  */
    break;

  case 361:
#line 3413 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7165 "c99-parser.c" /* glr.c:783  */
    break;

  case 362:
#line 3417 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_CAST_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7173 "c99-parser.c" /* glr.c:783  */
    break;

  case 363:
#line 3423 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7181 "c99-parser.c" /* glr.c:783  */
    break;

  case 364:
#line 3427 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MULT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7189 "c99-parser.c" /* glr.c:783  */
    break;

  case 365:
#line 3431 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_DIV, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7197 "c99-parser.c" /* glr.c:783  */
    break;

  case 366:
#line 3435 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MOD, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7205 "c99-parser.c" /* glr.c:783  */
    break;

  case 367:
#line 3441 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7213 "c99-parser.c" /* glr.c:783  */
    break;

  case 368:
#line 3445 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_ADD, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7221 "c99-parser.c" /* glr.c:783  */
    break;

  case 369:
#line 3449 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_MINUS, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7229 "c99-parser.c" /* glr.c:783  */
    break;

  case 370:
#line 3455 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7237 "c99-parser.c" /* glr.c:783  */
    break;

  case 371:
#line 3459 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SHL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7245 "c99-parser.c" /* glr.c:783  */
    break;

  case 372:
#line 3463 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SHR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7253 "c99-parser.c" /* glr.c:783  */
    break;

  case 373:
#line 3469 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7261 "c99-parser.c" /* glr.c:783  */
    break;

  case 374:
#line 3473 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_LOWER_THAN, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7269 "c99-parser.c" /* glr.c:783  */
    break;

  case 375:
#line 3477 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GREATER_THAN, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7277 "c99-parser.c" /* glr.c:783  */
    break;

  case 376:
#line 3481 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GREATER_OR_EQUAL_THAN, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7285 "c99-parser.c" /* glr.c:783  */
    break;

  case 377:
#line 3485 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_LOWER_OR_EQUAL_THAN, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7293 "c99-parser.c" /* glr.c:783  */
    break;

  case 378:
#line 3491 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7301 "c99-parser.c" /* glr.c:783  */
    break;

  case 379:
#line 3495 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_EQUAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7309 "c99-parser.c" /* glr.c:783  */
    break;

  case 380:
#line 3499 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_DIFFERENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7317 "c99-parser.c" /* glr.c:783  */
    break;

  case 381:
#line 3505 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7325 "c99-parser.c" /* glr.c:783  */
    break;

  case 382:
#line 3509 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_BITWISE_AND, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7333 "c99-parser.c" /* glr.c:783  */
    break;

  case 383:
#line 3515 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7341 "c99-parser.c" /* glr.c:783  */
    break;

  case 384:
#line 3519 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_BITWISE_XOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7349 "c99-parser.c" /* glr.c:783  */
    break;

  case 385:
#line 3525 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7357 "c99-parser.c" /* glr.c:783  */
    break;

  case 386:
#line 3529 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_BITWISE_OR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7365 "c99-parser.c" /* glr.c:783  */
    break;

  case 387:
#line 3535 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7373 "c99-parser.c" /* glr.c:783  */
    break;

  case 388:
#line 3539 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_LOGICAL_AND, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7381 "c99-parser.c" /* glr.c:783  */
    break;

  case 389:
#line 3545 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7389 "c99-parser.c" /* glr.c:783  */
    break;

  case 390:
#line 3549 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_LOGICAL_OR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7397 "c99-parser.c" /* glr.c:783  */
    break;

  case 391:
#line 3555 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7405 "c99-parser.c" /* glr.c:783  */
    break;

  case 392:
#line 3559 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake3(AST_CONDITIONAL_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7413 "c99-parser.c" /* glr.c:783  */
    break;

  case 393:
#line 3564 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_GCC_CONDITIONAL_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7421 "c99-parser.c" /* glr.c:783  */
    break;

  case 394:
#line 3570 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7429 "c99-parser.c" /* glr.c:783  */
    break;

  case 395:
#line 3574 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node_type), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7437 "c99-parser.c" /* glr.c:783  */
    break;

  case 396:
#line 3580 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7445 "c99-parser.c" /* glr.c:783  */
    break;

  case 397:
#line 3584 "c99.y" /* glr.c:783  */
    {
	AST comma_expression = ASTMake2(AST_COMMA, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);

	((*yyvalp).ast) = ASTMake1(AST_EXPRESSION, comma_expression, ASTFileName(comma_expression), ASTLine(comma_expression), NULL);
}
#line 7455 "c99-parser.c" /* glr.c:783  */
    break;

  case 398:
#line 3592 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_ASSIGNMENT;
}
#line 7463 "c99-parser.c" /* glr.c:783  */
    break;

  case 399:
#line 3596 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_MUL_ASSIGNMENT;
}
#line 7471 "c99-parser.c" /* glr.c:783  */
    break;

  case 400:
#line 3600 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_DIV_ASSIGNMENT;
}
#line 7479 "c99-parser.c" /* glr.c:783  */
    break;

  case 401:
#line 3604 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_ADD_ASSIGNMENT;
}
#line 7487 "c99-parser.c" /* glr.c:783  */
    break;

  case 402:
#line 3608 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_SUB_ASSIGNMENT;
}
#line 7495 "c99-parser.c" /* glr.c:783  */
    break;

  case 403:
#line 3612 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_SHL_ASSIGNMENT;
}
#line 7503 "c99-parser.c" /* glr.c:783  */
    break;

  case 404:
#line 3616 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_SHR_ASSIGNMENT;
}
#line 7511 "c99-parser.c" /* glr.c:783  */
    break;

  case 405:
#line 3620 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_AND_ASSIGNMENT;
}
#line 7519 "c99-parser.c" /* glr.c:783  */
    break;

  case 406:
#line 3624 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_OR_ASSIGNMENT;
}
#line 7527 "c99-parser.c" /* glr.c:783  */
    break;

  case 407:
#line 3628 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_XOR_ASSIGNMENT;
}
#line 7535 "c99-parser.c" /* glr.c:783  */
    break;

  case 408:
#line 3632 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).node_type) = AST_MOD_ASSIGNMENT;
}
#line 7543 "c99-parser.c" /* glr.c:783  */
    break;

  case 409:
#line 3638 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_CONSTANT_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7551 "c99-parser.c" /* glr.c:783  */
    break;

  case 410:
#line 3648 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_DECIMAL_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7559 "c99-parser.c" /* glr.c:783  */
    break;

  case 411:
#line 3652 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_OCTAL_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7567 "c99-parser.c" /* glr.c:783  */
    break;

  case 412:
#line 3656 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_HEXADECIMAL_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7575 "c99-parser.c" /* glr.c:783  */
    break;

  case 413:
#line 3660 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_HEXADECIMAL_FLOAT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7583 "c99-parser.c" /* glr.c:783  */
    break;

  case 414:
#line 3664 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_FLOATING_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7591 "c99-parser.c" /* glr.c:783  */
    break;

  case 415:
#line 3668 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_BOOLEAN_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7599 "c99-parser.c" /* glr.c:783  */
    break;

  case 416:
#line 3672 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_CHARACTER_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7607 "c99-parser.c" /* glr.c:783  */
    break;

  case 417:
#line 3676 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7615 "c99-parser.c" /* glr.c:783  */
    break;

  case 418:
#line 3682 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_UNKNOWN_PRAGMA, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7623 "c99-parser.c" /* glr.c:783  */
    break;

  case 419:
#line 3688 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_STRING_LITERAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7631 "c99-parser.c" /* glr.c:783  */
    break;

  case 420:
#line 3692 "c99.y" /* glr.c:783  */
    {
	// Let's concatenate here, it will ease everything

	const char* str1 = ASTText((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast));
	const char* str2 = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text;
	char* text = calloc(strlen(str1) + strlen(str2) + 1, sizeof(*text));

	strcat(text, str1);

	// Append the second string
	strcat(text, str2);

	((*yyvalp).ast) = ASTLeaf(AST_STRING_LITERAL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), text);
}
#line 7650 "c99-parser.c" /* glr.c:783  */
    break;

  case 421:
#line 3729 "c99.y" /* glr.c:783  */
    {
	*parsed_tree = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7658 "c99-parser.c" /* glr.c:783  */
    break;

  case 422:
#line 3735 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7666 "c99-parser.c" /* glr.c:783  */
    break;

  case 423:
#line 3739 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7674 "c99-parser.c" /* glr.c:783  */
    break;

  case 424:
#line 3743 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = NULL;
}
#line 7682 "c99-parser.c" /* glr.c:783  */
    break;

  case 425:
#line 3747 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7690 "c99-parser.c" /* glr.c:783  */
    break;

  case 426:
#line 3751 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7698 "c99-parser.c" /* glr.c:783  */
    break;

  case 427:
#line 3755 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 7706 "c99-parser.c" /* glr.c:783  */
    break;

  case 428:
#line 3759 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7714 "c99-parser.c" /* glr.c:783  */
    break;

  case 429:
#line 3763 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7722 "c99-parser.c" /* glr.c:783  */
    break;

  case 430:
#line 3767 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7730 "c99-parser.c" /* glr.c:783  */
    break;

  case 431:
#line 3771 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7738 "c99-parser.c" /* glr.c:783  */
    break;

  case 432:
#line 3798 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7746 "c99-parser.c" /* glr.c:783  */
    break;

  case 433:
#line 3802 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7754 "c99-parser.c" /* glr.c:783  */
    break;

  case 434:
#line 3820 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_ARRAY_SECTION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7762 "c99-parser.c" /* glr.c:783  */
    break;

  case 435:
#line 3824 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_ARRAY_SECTION_SIZE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7770 "c99-parser.c" /* glr.c:783  */
    break;

  case 436:
#line 3831 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7778 "c99-parser.c" /* glr.c:783  */
    break;

  case 437:
#line 3835 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_CAST_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7786 "c99-parser.c" /* glr.c:783  */
    break;

  case 438:
#line 3841 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_SHAPING_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 7794 "c99-parser.c" /* glr.c:783  */
    break;

  case 439:
#line 3847 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7802 "c99-parser.c" /* glr.c:783  */
    break;

  case 440:
#line 3851 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7810 "c99-parser.c" /* glr.c:783  */
    break;

  case 441:
#line 3857 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast);
}
#line 7818 "c99-parser.c" /* glr.c:783  */
    break;

  case 442:
#line 3876 "c99.y" /* glr.c:783  */
    {
    // The lexer ensures this has the following form
    // @STATEMENT-PH::0x1234abcd@, where the pointer coded
    // is an 'AST*'
    AST *tree = decode_placeholder((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);

    // This is an empty statement
    ((*yyvalp).ast) = *tree = ASTMake1(AST_DECLARATION_STATEMENT,
            ASTLeaf(AST_EMPTY_DECL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text), 
            (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 7834 "c99-parser.c" /* glr.c:783  */
    break;

  case 443:
#line 3972 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7842 "c99-parser.c" /* glr.c:783  */
    break;

  case 444:
#line 3976 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7850 "c99-parser.c" /* glr.c:783  */
    break;

  case 445:
#line 3982 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7858 "c99-parser.c" /* glr.c:783  */
    break;

  case 446:
#line 3986 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7866 "c99-parser.c" /* glr.c:783  */
    break;

  case 447:
#line 3992 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7874 "c99-parser.c" /* glr.c:783  */
    break;

  case 448:
#line 3996 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7882 "c99-parser.c" /* glr.c:783  */
    break;

  case 449:
#line 4021 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_DIRECTIVE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7890 "c99-parser.c" /* glr.c:783  */
    break;

  case 450:
#line 4028 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_CONSTRUCT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7898 "c99-parser.c" /* glr.c:783  */
    break;

  case 451:
#line 4034 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_CONSTRUCT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7906 "c99-parser.c" /* glr.c:783  */
    break;

  case 452:
#line 4040 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_CONSTRUCT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7914 "c99-parser.c" /* glr.c:783  */
    break;

  case 453:
#line 4101 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_LINE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7922 "c99-parser.c" /* glr.c:783  */
    break;

  case 454:
#line 4105 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_LINE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7930 "c99-parser.c" /* glr.c:783  */
    break;

  case 455:
#line 4109 "c99.y" /* glr.c:783  */
    {
    // This is a degenerated case caused by wrong designed pragmas
    ((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_LINE, NULL, NULL, NULL, 0, NULL);
}
#line 7939 "c99-parser.c" /* glr.c:783  */
    break;

  case 456:
#line 4116 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_LINE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7947 "c99-parser.c" /* glr.c:783  */
    break;

  case 457:
#line 4120 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_PRAGMA_CUSTOM_LINE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 7955 "c99-parser.c" /* glr.c:783  */
    break;

  case 458:
#line 4126 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = NULL;
}
#line 7963 "c99-parser.c" /* glr.c:783  */
    break;

  case 459:
#line 4130 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 7971 "c99-parser.c" /* glr.c:783  */
    break;

  case 460:
#line 4136 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7979 "c99-parser.c" /* glr.c:783  */
    break;

  case 461:
#line 4140 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7987 "c99-parser.c" /* glr.c:783  */
    break;

  case 462:
#line 4144 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 7995 "c99-parser.c" /* glr.c:783  */
    break;

  case 463:
#line 4150 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PRAGMA_CUSTOM_CLAUSE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8003 "c99-parser.c" /* glr.c:783  */
    break;

  case 464:
#line 4154 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PRAGMA_CUSTOM_CLAUSE, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8011 "c99-parser.c" /* glr.c:783  */
    break;

  case 465:
#line 4158 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_PRAGMA_CUSTOM_CLAUSE, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8019 "c99-parser.c" /* glr.c:783  */
    break;

  case 466:
#line 4164 "c99.y" /* glr.c:783  */
    {
    AST node = ASTLeaf(AST_PRAGMA_CLAUSE_ARG, NULL, 0, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text));

    ((*yyvalp).ast) = ASTListLeaf(node);
}
#line 8029 "c99-parser.c" /* glr.c:783  */
    break;

  case 467:
#line 4172 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).text) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
}
#line 8037 "c99-parser.c" /* glr.c:783  */
    break;

  case 468:
#line 4176 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).text) = strappend((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.text), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text));
}
#line 8045 "c99-parser.c" /* glr.c:783  */
    break;

  case 469:
#line 4182 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).text) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.text);
}
#line 8053 "c99-parser.c" /* glr.c:783  */
    break;

  case 470:
#line 4188 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).text) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text;
}
#line 8061 "c99-parser.c" /* glr.c:783  */
    break;

  case 471:
#line 4196 "c99.y" /* glr.c:783  */
    {
    AST ident = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text);

    ((*yyvalp).ast) = ASTMake1(AST_VERBATIM, ident, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8071 "c99-parser.c" /* glr.c:783  */
    break;

  case 472:
#line 4202 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_VERBATIM, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8079 "c99-parser.c" /* glr.c:783  */
    break;

  case 473:
#line 4208 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8087 "c99-parser.c" /* glr.c:783  */
    break;

  case 474:
#line 4214 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8095 "c99-parser.c" /* glr.c:783  */
    break;

  case 475:
#line 4233 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8103 "c99-parser.c" /* glr.c:783  */
    break;

  case 476:
#line 4241 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_CUSTOM_CONSTRUCT_STATEMENT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8111 "c99-parser.c" /* glr.c:783  */
    break;

  case 477:
#line 4246 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_CUSTOM_CONSTRUCT_HEADER, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8119 "c99-parser.c" /* glr.c:783  */
    break;

  case 478:
#line 4250 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_CUSTOM_CONSTRUCT_HEADER, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8127 "c99-parser.c" /* glr.c:783  */
    break;

  case 479:
#line 4256 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8135 "c99-parser.c" /* glr.c:783  */
    break;

  case 480:
#line 4260 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8143 "c99-parser.c" /* glr.c:783  */
    break;

  case 481:
#line 4266 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake2(AST_CUSTOM_CONSTRUCT_PARAMETER,
            ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_text), 
            (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), 
            (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8154 "c99-parser.c" /* glr.c:783  */
    break;

  case 482:
#line 4310 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_OMP_UDR_DECLARE_ARG, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8162 "c99-parser.c" /* glr.c:783  */
    break;

  case 483:
#line 4323 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_OMP_UDR_DECLARE_ARG_2, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8170 "c99-parser.c" /* glr.c:783  */
    break;

  case 484:
#line 4330 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8178 "c99-parser.c" /* glr.c:783  */
    break;

  case 485:
#line 4348 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8186 "c99-parser.c" /* glr.c:783  */
    break;

  case 486:
#line 4352 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8194 "c99-parser.c" /* glr.c:783  */
    break;

  case 487:
#line 4358 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_SYMBOL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8202 "c99-parser.c" /* glr.c:783  */
    break;

  case 488:
#line 4362 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
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
		if ((found = (strcmp(ast_get_text(((*yyvalp).ast)), map[i].op) == 0)))
        {
            ast_set_type(((*yyvalp).ast), AST_SYMBOL);
            ast_set_text(((*yyvalp).ast), map[i].name);
		    break;
        }
	}
	if (!found)
    {
		internal_error("Unhandled operator '%s'", ast_get_text(((*yyvalp).ast)));
    }
}
#line 8239 "c99-parser.c" /* glr.c:783  */
    break;

  case 489:
#line 4397 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8247 "c99-parser.c" /* glr.c:783  */
    break;

  case 490:
#line 4403 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8255 "c99-parser.c" /* glr.c:783  */
    break;

  case 491:
#line 4429 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8263 "c99-parser.c" /* glr.c:783  */
    break;

  case 492:
#line 4433 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8271 "c99-parser.c" /* glr.c:783  */
    break;

  case 493:
#line 4439 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8279 "c99-parser.c" /* glr.c:783  */
    break;

  case 494:
#line 4455 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8287 "c99-parser.c" /* glr.c:783  */
    break;

  case 495:
#line 4459 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8295 "c99-parser.c" /* glr.c:783  */
    break;

  case 496:
#line 4463 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8303 "c99-parser.c" /* glr.c:783  */
    break;

  case 497:
#line 4467 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8311 "c99-parser.c" /* glr.c:783  */
    break;

  case 498:
#line 4471 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8319 "c99-parser.c" /* glr.c:783  */
    break;

  case 499:
#line 4475 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8327 "c99-parser.c" /* glr.c:783  */
    break;

  case 500:
#line 4479 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8335 "c99-parser.c" /* glr.c:783  */
    break;

  case 501:
#line 4483 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8343 "c99-parser.c" /* glr.c:783  */
    break;

  case 502:
#line 4487 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_OMP_UDR_BUILTIN_OP, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8351 "c99-parser.c" /* glr.c:783  */
    break;

  case 503:
#line 4493 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8359 "c99-parser.c" /* glr.c:783  */
    break;

  case 504:
#line 4499 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8367 "c99-parser.c" /* glr.c:783  */
    break;

  case 505:
#line 4505 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8375 "c99-parser.c" /* glr.c:783  */
    break;

  case 506:
#line 4511 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8383 "c99-parser.c" /* glr.c:783  */
    break;

  case 507:
#line 4517 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8391 "c99-parser.c" /* glr.c:783  */
    break;

  case 508:
#line 4566 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SUPERSCALAR_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8399 "c99-parser.c" /* glr.c:783  */
    break;

  case 509:
#line 4570 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8407 "c99-parser.c" /* glr.c:783  */
    break;

  case 510:
#line 4574 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SUPERSCALAR_EXPRESSION, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8415 "c99-parser.c" /* glr.c:783  */
    break;

  case 511:
#line 4580 "c99.y" /* glr.c:783  */
    {
	AST ss_decl = ASTMake2(AST_SUPERSCALAR_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
    ((*yyvalp).ast) = ASTListLeaf(ss_decl);
}
#line 8424 "c99-parser.c" /* glr.c:783  */
    break;

  case 512:
#line 4585 "c99.y" /* glr.c:783  */
    {
	AST ss_decl = ASTMake2(AST_SUPERSCALAR_DECLARATOR, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast)), NULL);
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), ss_decl);
}
#line 8433 "c99-parser.c" /* glr.c:783  */
    break;

  case 513:
#line 4592 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8441 "c99-parser.c" /* glr.c:783  */
    break;

  case 514:
#line 4596 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake4(AST_DECLARATOR_ARRAY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8449 "c99-parser.c" /* glr.c:783  */
    break;

  case 515:
#line 4603 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = NULL;
}
#line 8457 "c99-parser.c" /* glr.c:783  */
    break;

  case 517:
#line 4610 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8465 "c99-parser.c" /* glr.c:783  */
    break;

  case 518:
#line 4614 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8473 "c99-parser.c" /* glr.c:783  */
    break;

  case 519:
#line 4620 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTLeaf(AST_SUPERSCALAR_REGION_SPEC_FULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8481 "c99-parser.c" /* glr.c:783  */
    break;

  case 520:
#line 4624 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake1(AST_SUPERSCALAR_REGION_SPEC_SINGLE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8489 "c99-parser.c" /* glr.c:783  */
    break;

  case 521:
#line 4628 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SUPERSCALAR_REGION_SPEC_RANGE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8497 "c99-parser.c" /* glr.c:783  */
    break;

  case 522:
#line 4632 "c99.y" /* glr.c:783  */
    {
	((*yyvalp).ast) = ASTMake2(AST_SUPERSCALAR_REGION_SPEC_LENGTH, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8505 "c99-parser.c" /* glr.c:783  */
    break;

  case 523:
#line 4667 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_LOCALSIZEOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8513 "c99-parser.c" /* glr.c:783  */
    break;

  case 524:
#line 4671 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_LOCALSIZEOF_TYPEID, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8521 "c99-parser.c" /* glr.c:783  */
    break;

  case 525:
#line 4675 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_BLOCKSIZEOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8529 "c99-parser.c" /* glr.c:783  */
    break;

  case 526:
#line 4679 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_BLOCKSIZEOF_TYPEID, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8537 "c99-parser.c" /* glr.c:783  */
    break;

  case 527:
#line 4683 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_ELEMSIZEOF, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8545 "c99-parser.c" /* glr.c:783  */
    break;

  case 528:
#line 4687 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_ELEMSIZEOF_TYPEID, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8553 "c99-parser.c" /* glr.c:783  */
    break;

  case 529:
#line 4693 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8561 "c99-parser.c" /* glr.c:783  */
    break;

  case 530:
#line 4697 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8569 "c99-parser.c" /* glr.c:783  */
    break;

  case 531:
#line 4703 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_SHARED, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8577 "c99-parser.c" /* glr.c:783  */
    break;

  case 532:
#line 4707 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_SHARED, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8585 "c99-parser.c" /* glr.c:783  */
    break;

  case 533:
#line 4713 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_UPC_RELAXED, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8593 "c99-parser.c" /* glr.c:783  */
    break;

  case 534:
#line 4717 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_UPC_STRICT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8601 "c99-parser.c" /* glr.c:783  */
    break;

  case 535:
#line 4724 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTListLeaf((((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8609 "c99-parser.c" /* glr.c:783  */
    break;

  case 536:
#line 4728 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTList((((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast));
}
#line 8617 "c99-parser.c" /* glr.c:783  */
    break;

  case 537:
#line 4734 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_LAYOUT_QUALIFIER, NULL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8625 "c99-parser.c" /* glr.c:783  */
    break;

  case 538:
#line 4738 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_LAYOUT_QUALIFIER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8633 "c99-parser.c" /* glr.c:783  */
    break;

  case 539:
#line 4742 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_LAYOUT_QUALIFIER, 
            ASTLeaf(AST_UPC_LAYOUT_UNDEF, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL), 
            (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8643 "c99-parser.c" /* glr.c:783  */
    break;

  case 540:
#line 4750 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8651 "c99-parser.c" /* glr.c:783  */
    break;

  case 541:
#line 4756 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_NOTIFY, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8659 "c99-parser.c" /* glr.c:783  */
    break;

  case 542:
#line 4760 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_WAIT, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8667 "c99-parser.c" /* glr.c:783  */
    break;

  case 543:
#line 4764 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake1(AST_UPC_BARRIER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8675 "c99-parser.c" /* glr.c:783  */
    break;

  case 544:
#line 4768 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_UPC_FENCE, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8683 "c99-parser.c" /* glr.c:783  */
    break;

  case 545:
#line 4774 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8691 "c99-parser.c" /* glr.c:783  */
    break;

  case 546:
#line 4778 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 8699 "c99-parser.c" /* glr.c:783  */
    break;

  case 547:
#line 4784 "c99.y" /* glr.c:783  */
    {
    AST upc_forall_header =
        ASTMake4(AST_UPC_FORALL_HEADER, (((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);

    ((*yyvalp).ast) = ASTMake2(AST_UPC_FORALL, upc_forall_header, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8710 "c99-parser.c" /* glr.c:783  */
    break;

  case 548:
#line 4793 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8718 "c99-parser.c" /* glr.c:783  */
    break;

  case 549:
#line 4797 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = NULL;
}
#line 8726 "c99-parser.c" /* glr.c:783  */
    break;

  case 550:
#line 4802 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8734 "c99-parser.c" /* glr.c:783  */
    break;

  case 551:
#line 4806 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_UPC_CONTINUE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, NULL);
}
#line 8742 "c99-parser.c" /* glr.c:783  */
    break;

  case 552:
#line 4833 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8750 "c99-parser.c" /* glr.c:783  */
    break;

  case 553:
#line 4839 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast);
}
#line 8758 "c99-parser.c" /* glr.c:783  */
    break;

  case 554:
#line 4845 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_CUDA_DEVICE, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8766 "c99-parser.c" /* glr.c:783  */
    break;

  case 555:
#line 4849 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_CUDA_GLOBAL, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8774 "c99-parser.c" /* glr.c:783  */
    break;

  case 556:
#line 4853 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_CUDA_HOST, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8782 "c99-parser.c" /* glr.c:783  */
    break;

  case 557:
#line 4857 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_CUDA_CONSTANT, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8790 "c99-parser.c" /* glr.c:783  */
    break;

  case 558:
#line 4861 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_CUDA_SHARED, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8798 "c99-parser.c" /* glr.c:783  */
    break;

  case 559:
#line 4867 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_CUDA_KERNEL_CALL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8806 "c99-parser.c" /* glr.c:783  */
    break;

  case 560:
#line 4871 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake3(AST_CUDA_KERNEL_CALL, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8814 "c99-parser.c" /* glr.c:783  */
    break;

  case 561:
#line 4877 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = (((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.ast);
}
#line 8822 "c99-parser.c" /* glr.c:783  */
    break;

  case 562:
#line 4883 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake4(AST_CUDA_KERNEL_ARGUMENTS, (((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8830 "c99-parser.c" /* glr.c:783  */
    break;

  case 563:
#line 4887 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake4(AST_CUDA_KERNEL_ARGUMENTS, (((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8838 "c99-parser.c" /* glr.c:783  */
    break;

  case 564:
#line 4891 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTMake4(AST_CUDA_KERNEL_ARGUMENTS, (((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast), (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.ast), NULL, NULL, ASTFileName((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), ASTLine((((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.ast)), NULL);
}
#line 8846 "c99-parser.c" /* glr.c:783  */
    break;

  case 565:
#line 4897 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).token_atrib) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib);
}
#line 8854 "c99-parser.c" /* glr.c:783  */
    break;

  case 566:
#line 4904 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).token_atrib) = (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib);
}
#line 8862 "c99-parser.c" /* glr.c:783  */
    break;

  case 567:
#line 4926 "c99.y" /* glr.c:783  */
    {
    ((*yyvalp).ast) = ASTLeaf(AST_XL_BUILTIN_SPEC, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_file, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_line, (((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.token_atrib).token_text);
}
#line 8870 "c99-parser.c" /* glr.c:783  */
    break;


#line 8874 "c99-parser.c" /* glr.c:783  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {
  case 1: yy0->ast = ambiguityHandler (*yy0, *yy1); break;

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, AST* parsed_tree)
{
  YYUSE (yyvaluep);
  YYUSE (parsed_tree);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, AST* parsed_tree)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval, parsed_tree);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, parsed_tree);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-810)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YYASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule, AST* parsed_tree)
{
  int yynrhs = yyrhsLength (yyrule);
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                                              , parsed_tree);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, AST* parsed_tree)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule, parsed_tree));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, parsed_tree);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, parsed_tree));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, parsed_tree);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval, AST* parsed_tree)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, parsed_tree);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULLPTR;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp, AST* parsed_tree);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, AST* parsed_tree)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, parsed_tree));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, parsed_tree));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, AST* parsed_tree)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, parsed_tree);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, parsed_tree);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, parsed_tree);
    yychar = yychar_current;
    yylval = yylval_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, AST* parsed_tree)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (parsed_tree, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, AST* parsed_tree)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              return yyreportAmbiguity (yybest, yyp, parsed_tree);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, parsed_tree);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, parsed_tree);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval, parsed_tree);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, parsed_tree);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, AST* parsed_tree)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , parsed_tree));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn, AST* parsed_tree)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], parsed_tree);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
          if (yychar == YYEMPTY)
            {
              YYDPRINTF ((stderr, "Reading a token: "));
              yychar = yylex ();
            }

          if (yychar <= YYEOF)
            {
              yychar = yytoken = YYEOF;
              YYDPRINTF ((stderr, "Now at end of input.\n"));
            }
          else
            {
              yytoken = YYTRANSLATE (yychar);
              YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            }

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], parsed_tree);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, parsed_tree));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], parsed_tree);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp, AST* parsed_tree)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (parsed_tree, YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;
          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yyarg[yyi++]);
              yyformat += 2;
            }
          else
            {
              yyp++;
              yyformat++;
            }
        }
      yyerror (parsed_tree, yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (parsed_tree, YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, AST* parsed_tree)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, parsed_tree, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, parsed_tree);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex ();
        if (yychar <= YYEOF)
          {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            yytoken = YYTRANSLATE (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
          }
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, parsed_tree, YY_NULLPTR);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, parsed_tree);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, parsed_tree, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (AST* parsed_tree)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {

                  yyreportSyntaxError (&yystack, parsed_tree);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, parsed_tree));
            }
          else
            {
              yySymbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = yylex ();
                }

              if (yychar <= YYEOF)
                {
                  yychar = yytoken = YYEOF;
                  YYDPRINTF ((stderr, "Now at end of input.\n"));
                }
              else
                {
                  yytoken = YYTRANSLATE (yychar);
                  YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
                }

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {

                  yyreportSyntaxError (&yystack, parsed_tree);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, parsed_tree));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, parsed_tree));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, parsed_tree, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, parsed_tree));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));

              yyreportSyntaxError (&yystack, parsed_tree);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, parsed_tree));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, parsed_tree);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (parsed_tree, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, parsed_tree);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, parsed_tree);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs

/* Substitute the variable and function names.  */
#define yyparse mc99parse
#define yylex   mc99lex
#define yyerror mc99error
#define yylval  mc99lval
#define yychar  mc99char
#define yydebug mc99debug
#define yynerrs mc99nerrs

#line 4934 "c99.y" /* glr.c:2551  */






























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
