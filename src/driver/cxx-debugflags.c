/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf --language=ANSI-C --hash-function-name=debugflags_hash --struct-type --lookup-function-name=debugflags_lookup --output=cxx-debugflags.c --global-table --word-array-name=debugflags_list --initializer-suffix=',0,""' ./cxx-debugflags.gperf  */
/* Computed positions: -k'7' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 27 "./cxx-debugflags.gperf"

#include <stdlib.h>
#include <string.h>
#include "cxx-driver.h"
#include "cxx-utils.h"

#define DEBUG_OPTION_REF(x) (offsetof(struct debug_options_tag, x))
#line 36 "./cxx-debugflags.gperf"
struct debug_flags_list_t;

#define TOTAL_KEYWORDS 12
#define MIN_WORD_LENGTH 9
#define MAX_WORD_LENGTH 22
#define MIN_HASH_VALUE 9
#define MAX_HASH_VALUE 32
/* maximum key range = 24, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
debugflags_hash (register const char *str, register unsigned int len)
{
  static unsigned char asso_values[] =
    {
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 10, 33,  0, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33,  5, 33,
      33, 10,  5, 33, 33,  0, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
      33, 33, 33, 33, 33, 33
    };
  return len + asso_values[(unsigned char)str[6]];
}

static struct debug_flags_list_t debugflags_list[] =
  {
    {"",0,""}, {"",0,""}, {"",0,""}, {"",0,""}, {"",0,""},
    {"",0,""}, {"",0,""}, {"",0,""}, {"",0,""},
#line 43 "./cxx-debugflags.gperf"
    {"print_ast", DEBUG_OPTION_REF(print_ast_graphviz), "Prints ast in graphviz format (alias for 'print_ast_graphviz')"},
    {"",0,""},
#line 39 "./cxx-debugflags.gperf"
    {"print_scope", DEBUG_OPTION_REF(print_scope), "Prints scope of the translation unit"},
#line 48 "./cxx-debugflags.gperf"
    {"debug_sizeof", DEBUG_OPTION_REF(debug_sizeof), "Enables special debug messages for sizeof"},
    {"",0,""},
#line 45 "./cxx-debugflags.gperf"
    {"print_ast_html", DEBUG_OPTION_REF(print_ast_html), "Prints ast in HTML format (requires Javascript-enabled browser)"},
    {"",0,""},
#line 41 "./cxx-debugflags.gperf"
    {"debug_lexer", DEBUG_OPTION_REF(debug_lexer), "Enables lexer debug"},
#line 42 "./cxx-debugflags.gperf"
    {"debug_parser", DEBUG_OPTION_REF(debug_parser), "Enables parser debug"},
#line 44 "./cxx-debugflags.gperf"
    {"print_ast_graphviz", DEBUG_OPTION_REF(print_ast_graphviz), "Prints ast in graphviz format"},
    {"",0,""}, {"",0,""}, {"",0,""},
#line 38 "./cxx-debugflags.gperf"
    {"abort_on_ice", DEBUG_OPTION_REF(abort_on_ice), "When an error condition is detected, compiler will raise SIGABRT signal. This is useful for debugging"},
#line 46 "./cxx-debugflags.gperf"
    {"memory_report", DEBUG_OPTION_REF(print_memory_report), "Prints a memory report at the end"},
#line 49 "./cxx-debugflags.gperf"
    {"do_not_run_gdb", DEBUG_OPTION_REF(do_not_run_gdb), "Disables the output of a backtrace using 'gdb' debugger when a signal handler is called"},
    {"",0,""}, {"",0,""},
#line 40 "./cxx-debugflags.gperf"
    {"enable_debug_code", DEBUG_OPTION_REF(enable_debug_code), "Enable debug code, in general these are debug messages"},
    {"",0,""}, {"",0,""}, {"",0,""}, {"",0,""},
#line 47 "./cxx-debugflags.gperf"
    {"memory_report_in_bytes", DEBUG_OPTION_REF(print_memory_report_in_bytes), "The memory report is written in bytes"}
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
struct debug_flags_list_t *
debugflags_lookup (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = debugflags_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = debugflags_list[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &debugflags_list[key];
        }
    }
  return 0;
}
#line 50 "./cxx-debugflags.gperf"


static int cmpstringp(const void *p1, const void *p2)
{
    struct debug_flags_list_t** df1 = (struct debug_flags_list_t**) p1;
    struct debug_flags_list_t** df2 = (struct debug_flags_list_t**) p2;

    return strcmp((*df1)->name, (*df2)->name);
}



struct debug_flags_list_t** list_of_debug_flags(void)
{
    struct debug_flags_list_t** result = NULL;

    int i = 0;
    int j = 0;
    while (i < TOTAL_KEYWORDS)
    {
        const char* keyword = debugflags_list[j].name;

        if (keyword != NULL && *keyword != '\0')
        {
            P_LIST_ADD(result, i, &(debugflags_list[j]));
        }

        j++;
    }

    P_LIST_ADD(result, i, NULL);

    qsort(result, i-1, sizeof(struct debug_flags_list_t *), cmpstringp);

    return result;
}
