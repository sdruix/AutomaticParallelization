#include "fortran03-intrinsics.h"
#include "cxx-ast.h"
#include "cxx-utils.h"
#include "cxx-scope-decls.h"
#include "cxx-entrylist.h"
#include "cxx-typeutils.h"
#include "cxx-exprtype.h"
#include "cxx-ambiguity.h"
#include "fortran03-typeutils.h"
#include "fortran03-buildscope.h"
#include "fortran03-exprtype.h"
#include "fortran03-scope.h"
#include <string.h>
#include "red_black_tree.h"

typedef
enum intrinsic_kind_tag
{
    INTRINSIC_KIND_NONE = 0,
    INTRINSIC_KIND_ATOMIC_SUBROUTINE,
    INTRINSIC_KIND_ELEMENTAL_FUNCTION,
    INTRINSIC_KIND_ELEMENTAL_SUBROUTINE,
    INTRINSIC_KIND_INQUIRY_FUNCTION,
    INTRINSIC_KIND_PURE_SUBROUTINE,
    INTRINSIC_KIND_IMPURE_SUBROUTINE,
    INTRINSIC_KIND_TRANSFORMATIONAL_FUNCTION,
} intrinsic_kind_t;

#define A  INTRINSIC_KIND_ATOMIC_SUBROUTINE
#define E  INTRINSIC_KIND_ELEMENTAL_FUNCTION
#define ES INTRINSIC_KIND_ELEMENTAL_SUBROUTINE
#define I  INTRINSIC_KIND_INQUIRY_FUNCTION
#define PS INTRINSIC_KIND_PURE_SUBROUTINE
#define S  INTRINSIC_KIND_IMPURE_SUBROUTINE
#define T  INTRINSIC_KIND_TRANSFORMATIONAL_FUNCTION

#define FORTRAN_INTRINSIC_GENERIC_LIST \
FORTRAN_GENERIC_INTRINSIC(abs, "A", E) \
FORTRAN_GENERIC_INTRINSIC(achar, "I,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(acos, "X", E) \
FORTRAN_GENERIC_INTRINSIC(acosh, "X", E) \
FORTRAN_GENERIC_INTRINSIC(adjustl, "STRING", E) \
FORTRAN_GENERIC_INTRINSIC(adjustr, "STRING", E) \
FORTRAN_GENERIC_INTRINSIC(aimag, "Z", E) \
FORTRAN_GENERIC_INTRINSIC(aint, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(all, "MASK,?DIM", T) \
FORTRAN_GENERIC_INTRINSIC_2(allocated, "ARRAY", I, "SCALAR", I) \
FORTRAN_GENERIC_INTRINSIC(anint, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(any, "MASK,?DIM", T) \
FORTRAN_GENERIC_INTRINSIC(asin, "X", E) \
FORTRAN_GENERIC_INTRINSIC(asinh, "X", E) \
FORTRAN_GENERIC_INTRINSIC(associated, "POINTER,?TARGET", I) \
FORTRAN_GENERIC_INTRINSIC_2(atan, "X", E, "Y,X", E) \
FORTRAN_GENERIC_INTRINSIC(atan2, "Y,X", E) \
FORTRAN_GENERIC_INTRINSIC(atanh, "X", E) \
FORTRAN_GENERIC_INTRINSIC(atomic_define, "ATOM,VALUE", A) \
FORTRAN_GENERIC_INTRINSIC(atomic_ref, "VALUE,ATOM", A) \
FORTRAN_GENERIC_INTRINSIC(bessel_j0, "X", E) \
FORTRAN_GENERIC_INTRINSIC(bessel_j1, "X", E) \
FORTRAN_GENERIC_INTRINSIC_2(bessel_jn, "N,X", E, "N1,N2,X", T) \
FORTRAN_GENERIC_INTRINSIC(bessel_y0, "X", E) \
FORTRAN_GENERIC_INTRINSIC(bessel_y1, "X", E) \
FORTRAN_GENERIC_INTRINSIC_2(bessel_yn, "N,X", E, "N1,N2,X", T) \
FORTRAN_GENERIC_INTRINSIC(bge, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC(bgt, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC(ble, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC(blt, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC(bit_size, "I", I) \
FORTRAN_GENERIC_INTRINSIC(btest, "I,POS", E) \
FORTRAN_GENERIC_INTRINSIC(ceiling, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(char, "I,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(cmplx, "X,?Y,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(dcmplx, "X,?Y", E) \
FORTRAN_GENERIC_INTRINSIC(command_argument_count, "", T) \
FORTRAN_GENERIC_INTRINSIC(conjg, "Z", E) \
FORTRAN_GENERIC_INTRINSIC(cos, "X", E) \
FORTRAN_GENERIC_INTRINSIC(cosh, "X", E) \
FORTRAN_GENERIC_INTRINSIC(count, "MASK,?DIM,?KIND", T) \
FORTRAN_GENERIC_INTRINSIC(cpu_time, "TIME", S) \
FORTRAN_GENERIC_INTRINSIC(cshift, "ARRAY,SHIFT,?DIM", T) \
FORTRAN_GENERIC_INTRINSIC(date_and_time, "?DATE,?TIME,?ZONE,?VALUES", S) \
FORTRAN_GENERIC_INTRINSIC(dble, "A", E) \
FORTRAN_GENERIC_INTRINSIC(digits, "X", I) \
FORTRAN_GENERIC_INTRINSIC(dim, "X,Y", E) \
FORTRAN_GENERIC_INTRINSIC(dot_product, "VECTOR_A,VECTOR_B", T) \
FORTRAN_GENERIC_INTRINSIC(dprod, "X,Y", E) \
FORTRAN_GENERIC_INTRINSIC(dshiftl, "I,J,SHIFT", E) \
FORTRAN_GENERIC_INTRINSIC(dshiftr, "I,J,SHIFT", E) \
FORTRAN_GENERIC_INTRINSIC(eoshift, "ARRAY,SHIFT,?BOUNDARY,?DIM", T) \
FORTRAN_GENERIC_INTRINSIC(epsilon, "X", I) \
FORTRAN_GENERIC_INTRINSIC(erf, "X", E) \
FORTRAN_GENERIC_INTRINSIC(erfc, "X", E) \
FORTRAN_GENERIC_INTRINSIC(erfc_scaled, "X", E) \
FORTRAN_GENERIC_INTRINSIC(execute_command_line, "COMMAND,?WAIT,?EXITSTAT,?CMDSTAT,?CMDMSG", S) \
FORTRAN_GENERIC_INTRINSIC(exp, "X", E) \
FORTRAN_GENERIC_INTRINSIC(exponent, "X", E) \
FORTRAN_GENERIC_INTRINSIC(extends_type_of, "A,MOLD", I) \
FORTRAN_GENERIC_INTRINSIC_2(findloc, "ARRAY,VALUE,DIM,?MASK,?KIND,?BACK", T, "ARRAY,VALUE,?MASK,?KIND,?BACK", T) \
FORTRAN_GENERIC_INTRINSIC(floor, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(fraction, "X", E) \
FORTRAN_GENERIC_INTRINSIC(gamma, "X", E) \
FORTRAN_GENERIC_INTRINSIC(get_command, "?COMMAND,?LENGTH,?STATUS", S) \
FORTRAN_GENERIC_INTRINSIC(get_command_argument, "NUMBER,?VALUE,?LENGTH,?STATUS", S) \
FORTRAN_GENERIC_INTRINSIC(get_environment_variable, "NUMBER,?VALUE,?LENGTH,?STATUS", S) \
FORTRAN_GENERIC_INTRINSIC(huge, "X", I) \
FORTRAN_GENERIC_INTRINSIC(hypot, "X,Y", E) \
FORTRAN_GENERIC_INTRINSIC(iachar, "C,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC_2(iall, "ARRAY,DIM,?MASK", E, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(iand, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC_2(iany, "ARRAY,DIM,?MASK", E, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(ibclr, "I,POS", E) \
FORTRAN_GENERIC_INTRINSIC(ibits, "I,POS,LEN", E) \
FORTRAN_GENERIC_INTRINSIC(ibset, "I,POS", E) \
FORTRAN_GENERIC_INTRINSIC(ichar, "C,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(ieor, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC(image_index, "COARRAY,SUB", I) \
FORTRAN_GENERIC_INTRINSIC(index, "STRING,SUBSTRING,?BACK,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(int, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(ior, "I,J", E) \
FORTRAN_GENERIC_INTRINSIC_2(iparity, "ARRAY,DIM,?MASK", T, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(ishft, "I,SHIFT", E) \
FORTRAN_GENERIC_INTRINSIC(ishftc, "I,SHIFT,?SIZE", E) \
FORTRAN_GENERIC_INTRINSIC(is_contiguous, "ARRAY", I) \
FORTRAN_GENERIC_INTRINSIC(is_iostat_end, "I", E) \
FORTRAN_GENERIC_INTRINSIC(is_iostat_eor, "I", E) \
FORTRAN_GENERIC_INTRINSIC(kind, "X", I) \
FORTRAN_GENERIC_INTRINSIC(lbound, "ARRAY,?DIM,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(lcobound, "COARRAY,?DIM,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(leadz, "I", E) \
FORTRAN_GENERIC_INTRINSIC(len, "STRING,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(len_trim, "STRING,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(lge, "STRING_A,STRING_B", E) \
FORTRAN_GENERIC_INTRINSIC(lgt, "STRING_A,STRING_B", E) \
FORTRAN_GENERIC_INTRINSIC(lle, "STRING_A,STRING_B", E) \
FORTRAN_GENERIC_INTRINSIC(llt, "STRING_A,STRING_B", E) \
FORTRAN_GENERIC_INTRINSIC(log, "X", E) \
FORTRAN_GENERIC_INTRINSIC(log_gamma, "X", E) \
FORTRAN_GENERIC_INTRINSIC(log10, "X", E) \
FORTRAN_GENERIC_INTRINSIC(logical, "L,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(maskl, "I,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(maskr, "I,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(matmul, "MATRIX_A,MATRIX_B", T) \
FORTRAN_GENERIC_INTRINSIC(max, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(maxexponent, "X", I) \
FORTRAN_GENERIC_INTRINSIC_2(maxloc, "ARRAY,DIM,?MASK,?KIND,?BACK", T, "ARRAY,?MASK,?KIND,?BACK", T) \
FORTRAN_GENERIC_INTRINSIC_2(maxval, "ARRAY,DIM,?MASK", E, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(merge, "TSOURCE,FSOURCE,MASK", E) \
FORTRAN_GENERIC_INTRINSIC(merge_bits, "I,J,MASK", E) \
FORTRAN_GENERIC_INTRINSIC(min, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(minexponent, "X", I) \
FORTRAN_GENERIC_INTRINSIC_2(minloc, "ARRAY,DIM,?MASK,?KIND,?BACK", E, "ARRAY,?MASK,?KIND,?BACK", T) \
FORTRAN_GENERIC_INTRINSIC_2(minval, "ARRAY,DIM,?MASK", E, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(mod, "A,P", E) \
FORTRAN_GENERIC_INTRINSIC(modulo, "A,P", E) \
FORTRAN_GENERIC_INTRINSIC(move_alloc, "FROM,TO", PS) \
FORTRAN_GENERIC_INTRINSIC(mvbits, "FROM,FROMPOS,LEN,TO,TOPOS", ES) \
FORTRAN_GENERIC_INTRINSIC(nearest, "X,S", E) \
FORTRAN_GENERIC_INTRINSIC(new_line, "A", I) \
FORTRAN_GENERIC_INTRINSIC(nint, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(not, "I", E) \
FORTRAN_GENERIC_INTRINSIC(norm2, "X,?DIM", T) \
FORTRAN_GENERIC_INTRINSIC(null, "?MOLD", T) \
FORTRAN_GENERIC_INTRINSIC(num_images, "", T) \
FORTRAN_GENERIC_INTRINSIC(pack, "ARRAY,MASK,?VECTOR", T) \
FORTRAN_GENERIC_INTRINSIC(parity, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(popcnt, "I", E) \
FORTRAN_GENERIC_INTRINSIC(poppar, "I", E) \
FORTRAN_GENERIC_INTRINSIC(precision, "X", I) \
FORTRAN_GENERIC_INTRINSIC(present, "A", I) \
FORTRAN_GENERIC_INTRINSIC_2(product, "ARRAY,DIM,?MASK", T, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(radix, "X", I) \
FORTRAN_GENERIC_INTRINSIC(random_number, "HARVEST", S) \
FORTRAN_GENERIC_INTRINSIC(random_seed, "SIZE,PUT,GET", S) \
FORTRAN_GENERIC_INTRINSIC(range, "X", I) \
FORTRAN_GENERIC_INTRINSIC(real, "A,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(repeat, "STRING,NCOPIES", T) \
FORTRAN_GENERIC_INTRINSIC(reshape, "SOURCE,SHAPE,?PAD,?ORDER", T) \
FORTRAN_GENERIC_INTRINSIC(rrspacing, "X", E) \
FORTRAN_GENERIC_INTRINSIC(same_type_as, "A,B", I) \
FORTRAN_GENERIC_INTRINSIC(scale, "X,I", E) \
FORTRAN_GENERIC_INTRINSIC(scan, "STRING,SET,?BACK,?KIND", E) \
FORTRAN_GENERIC_INTRINSIC(selected_char_kind, "NAME", T) \
FORTRAN_GENERIC_INTRINSIC(selected_int_kind, "R", T) \
FORTRAN_GENERIC_INTRINSIC(selected_real_kind, "?P,?R,?RADIX", T) \
FORTRAN_GENERIC_INTRINSIC(set_exponent, "X,I", E) \
FORTRAN_GENERIC_INTRINSIC(shape, "SOURCE,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(shifta, "I,SHIFT", E) \
FORTRAN_GENERIC_INTRINSIC(shiftl, "I,SHIFT", E) \
FORTRAN_GENERIC_INTRINSIC(shiftr, "I,SHIFT", E) \
FORTRAN_GENERIC_INTRINSIC(sign, "A,B", E) \
FORTRAN_GENERIC_INTRINSIC(sin, "X", E) \
FORTRAN_GENERIC_INTRINSIC(sinh, "X", E) \
FORTRAN_GENERIC_INTRINSIC(size, "ARRAY,?DIM,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(spacing, "X", E) \
FORTRAN_GENERIC_INTRINSIC(spread, "SOURCE,DIM,NCOPIES", T) \
FORTRAN_GENERIC_INTRINSIC(sqrt, "X", E) \
FORTRAN_GENERIC_INTRINSIC(storage_size, "A,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC_2(sum, "ARRAY,DIM,?MASK", T, "ARRAY,?MASK", T) \
FORTRAN_GENERIC_INTRINSIC(system_clock, "?COUNT,?COUNT_RATE,?COUNT_MAX", S) \
FORTRAN_GENERIC_INTRINSIC(tan, "X", E) \
FORTRAN_GENERIC_INTRINSIC(tanh, "X", E) \
FORTRAN_GENERIC_INTRINSIC_2(this_image, "", T, "COARRAY,?DIM", T) \
FORTRAN_GENERIC_INTRINSIC(tiny, "X", I) \
FORTRAN_GENERIC_INTRINSIC(trailz, "I", T) \
FORTRAN_GENERIC_INTRINSIC(transfer, "SOURCE,MOLD,SIZE", T) \
FORTRAN_GENERIC_INTRINSIC(transpose, "MATRIX", T) \
FORTRAN_GENERIC_INTRINSIC(trim, "STRING", T) \
FORTRAN_GENERIC_INTRINSIC(ubound, "ARRAY,?DIM,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(ucobound, "COARRAY,?DIM,?KIND", I) \
FORTRAN_GENERIC_INTRINSIC(unpack, "VECTOR,MASK,FIELD", T) \
FORTRAN_GENERIC_INTRINSIC(verify, "STRING,SET,?BACK,?KIND", E)  \
FORTRAN_GENERIC_INTRINSIC(max0, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(max1, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(min0, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(min1, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(amax0, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(amax1, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(amin0, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(amin1, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(dmax1, NULL, E) \
FORTRAN_GENERIC_INTRINSIC(dmin1, NULL, E) \


#define MAX_KEYWORDS_INTRINSICS 10

typedef struct intrinsic_variant_info_tag
{
    int num_keywords;
    const char* keyword_names[MAX_KEYWORDS_INTRINSICS];
    char is_optional[MAX_KEYWORDS_INTRINSICS];
} intrinsic_variant_info_t;

static intrinsic_variant_info_t get_variant(const char* keywords)
{
    int keyword_index = 0;
    intrinsic_variant_info_t result;
    memset(&result, 0, sizeof(result));
    if (keywords != NULL)
    {
        char *c = strdup(keywords);
        char *p = strtok(c, ",");
        while (p != NULL)
        {
            ERROR_CONDITION(keyword_index == MAX_KEYWORDS_INTRINSICS, 
                    "Too many keywords for intrinsic!\n", 0);

            char is_optional = (*p == '?');
            if (is_optional)
                p++;

            result.keyword_names[keyword_index] = uniquestr(strtolower(p));
            result.is_optional[keyword_index] = is_optional;

            p = strtok(NULL, ",");
            keyword_index++;
        }
        result.num_keywords = keyword_index;
        free(c);
    }
    else
    {
        // Special case, we allow anything
        result.num_keywords = -1;
    }

    return result;
}

typedef
struct intrinsic_descr_tag
{
    const char* name;
    type_t* result_type;
    int num_types;
    type_t** parameter_types;
} intrinsic_descr_t;

static int compare_types(type_t* t1, type_t* t2)
{
    if (equivalent_types(get_unqualified_type(t1), get_unqualified_type(t2)))
        return 0;
    else if (t1 < t2)
        return -1;
    else
        return 1;
}

static int intrinsic_descr_cmp(const void* i1, const void* i2)
{
    const intrinsic_descr_t* d1 = (const intrinsic_descr_t*)i1;
    const intrinsic_descr_t* d2 = (const intrinsic_descr_t*)i2;

    int c; 
    if ((c = strcasecmp(d1->name, d2->name)) != 0)
        return c;

    if ((c = compare_types(d1->result_type, d2->result_type)) != 0)
        return c;

    if (d1->num_types != d2->num_types)
    {
        if (d1->num_types < d2->num_types)
            return -1;
        else
            return 1;
    }

    int i;
    for (i = 0; i < d1->num_types; i++)
    {
        if ((c = compare_types(d1->parameter_types[i], d2->parameter_types[i])) != 0)
            return c;
    }

    return 0;
}

static rb_red_blk_tree* intrinsic_map = NULL;

static char generic_keyword_check(
        scope_entry_t* symbol,
        int *num_arguments,
        AST *argument_expressions,
        const char* keywords,
        type_t** argument_types,
        type_t** reordered_types,
        AST* reordered_exprs)
{
    intrinsic_variant_info_t current_variant = get_variant(keywords);
    DEBUG_CODE()
    {
        fprintf(stderr, "INTRINSIC: Checking intrinsic '%s'\n",
                symbol->symbol_name);
        fprintf(stderr, "INTRINSICS: Keywords of this intrinsic\n");
        int i;
        for (i = 0; i < current_variant.num_keywords; i++)
        {
            fprintf(stderr, "INTRINSICS:     %-10s   %s\n",
                    strtoupper(current_variant.keyword_names[i]),
                    current_variant.is_optional[i] ? "[OPTIONAL]" : "");
        }
        if (current_variant.num_keywords < 0)
        {
            fprintf(stderr, "INTRINSICS:     unlimited keyword list\n");
        }
    }

    if (argument_expressions == NULL)
    {
        if (argument_types != NULL)
        {
            int i;
            for (i = 0; i < current_variant.num_keywords; i++)
            {
                reordered_types[i] = argument_types[i];
            }
        }

        DEBUG_CODE()
        {
            fprintf(stderr, "INTRINSICS: Invocation to intrinsic '%s' suceeds trivially because there are no expressions given\n",
                    symbol->symbol_name);
        }
        return 1;
    }

    if (current_variant.num_keywords < 0)
    {
        int i;
        for (i = 0; i < (*num_arguments); i++)
        {
            reordered_types[i] = argument_types[i];
        }
        DEBUG_CODE()
        {
            fprintf(stderr, "INTRINSICS: Invocation to intrinsic '%s' suceeds trivially because it is an unbounded parameter function\n",
                    symbol->symbol_name);
        }
        return 1;
    }

    char ok = 1;
    int i;
    int position = 0;
    char seen_keywords = 0;
    for (i = 0; i < (*num_arguments) && ok; i++)
    {
        AST argument = argument_expressions[i];

        AST keyword = ASTSon0(argument);
        AST expr = ASTSon1(argument);

        if (keyword != NULL)
        {
            char found = 0;
            int j;
            for (j = 0; j < current_variant.num_keywords && !found; j++)
            {
                if (strcasecmp(current_variant.keyword_names[j], ASTText(keyword)) == 0)
                {
                    position = j;
                    found = 1;
                }
            }

            if (!found)
            {
                // fprintf(stderr, "%s: warning: no keyword '%s' for intrinsic '%s'\n",
                //         ast_location(keyword),
                //         ASTText(keyword),
                //         intrinsic_info->intrinsic_name);
                DEBUG_CODE()
                {
                    fprintf(stderr, "INTRINSICS: Intrinsic '%s' does not have any keyword '%s'\n",
                            symbol->symbol_name,
                            ASTText(keyword));
                }
                ok = 0;
                break;
            }
            seen_keywords = 1;
        }
        else
        {
            ERROR_CONDITION(seen_keywords, "Invalid argument list", 0);
            if (position > current_variant.num_keywords)
            {
                ok = 0;
                DEBUG_CODE()
                {
                    fprintf(stderr, "INTRINSICS: Too many parameters (%d) for intrinsic '%s' (maximum is %d)\n",
                            position,
                            symbol->symbol_name,
                            current_variant.num_keywords);
                }
                break;
            }
        }
        if (reordered_exprs[position] == NULL)
        {
            if (is_error_type(expression_get_type(expr)))
            {
                DEBUG_CODE()
                {
                    fprintf(stderr, "INTRINSICS: Dummy argument '%s' of intrinsic '%s' but be associated to an invalid expression\n",
                            current_variant.keyword_names[position],
                            symbol->symbol_name);
                }
                ok = 0;
                break;
            };
            reordered_exprs[position] = expr;
            reordered_types[position] = expression_get_type(expr);
        }
        else
        {
            // fprintf(stderr, "%s: warning: dummy argument '%d' of intrinsic '%s' already given a value\n",
            //         ast_location(argument),
            //         position,
            //         intrinsic_info->intrinsic_name);
            DEBUG_CODE()
            {
                fprintf(stderr, "INTRINSICS: Dummy argument '%s' (position %d) of intrinsic '%s' already got an actual argument\n",
                        current_variant.keyword_names[position],
                        position,
                        symbol->symbol_name);
            }
            ok = 0;
            break;
        }

        position++;
    }

    // Now check every nonoptional dummy argument has a real argument
    int j;
    for (j = 0; j < current_variant.num_keywords && ok; j++)
    {
        if (reordered_exprs[j] == NULL
                && !current_variant.is_optional[j])
        {
            // fprintf(stderr, "%s: warning: no real argument given for dummy argument '%s' of intrinsic '%s'\n",
            //         ast_location(argument),
            //         current_variant->keyword_names[j],
            //         intrinsic_info->intrinsic_name);
            DEBUG_CODE()
            {
                fprintf(stderr, "INTRINSICS: No real argument given for nonoptional dummy argument '%s' of intrinsic '%s'\n",
                        current_variant.keyword_names[j],
                        symbol->symbol_name);
            }
            ok = 0;
            break;
        }
    }

    if (ok)
    {
        *num_arguments = current_variant.num_keywords;
        DEBUG_CODE()
        {
            fprintf(stderr, "INTRINSICS: Invocation to intrinsic '%s' seems fine\n",
                    symbol->symbol_name);
        }
    }
    else
    {
        DEBUG_CODE()
        {
            fprintf(stderr, "INTRINSICS: Invocation to intrinsic '%s' has failed\n",
                    symbol->symbol_name);
        }
    }

    return ok;
}

static scope_entry_t* get_intrinsic_symbol_(const char* name, 
        type_t* result_type, 
        int num_types, type_t** types, 
        decl_context_t decl_context,
        char is_elemental,
        char is_pure,
        char is_transformational UNUSED_PARAMETER,
        char is_inquiry UNUSED_PARAMETER)
{
    intrinsic_descr_t descr;
    descr.name = name;
    descr.result_type = result_type;
    descr.num_types = num_types;
    descr.parameter_types = types;

    rb_red_blk_node* n = rb_tree_query(intrinsic_map, &descr);
    if (n != NULL)
    {
        scope_entry_t* entry = (scope_entry_t*)rb_node_get_info(n);
        DEBUG_CODE()
        {
            fprintf(stderr, "INTRINSICS: Returning existing intrinsic '%s' of type '%s'\n",
                    entry->symbol_name,
                    print_type_str(entry->type_information, decl_context));
        }
        return entry;
    }
    else
    {
        // Create a new descriptor
        intrinsic_descr_t *p = calloc(1, sizeof(*p));
        p->name = name;
        p->result_type = result_type;
        p->num_types = num_types;
        if (num_types > 0)
        {
            p->parameter_types = calloc(num_types, sizeof(*p->parameter_types));
            memcpy(p->parameter_types, types, num_types * sizeof(*p->parameter_types));
        }

        parameter_info_t param_info[num_types + 1];
        memset(param_info, 0, sizeof(param_info));
        int i;
        for (i = 0; i < num_types; i++)
        {
            ERROR_CONDITION((types[i] == NULL), "Invalid description of builtin", 0);
            param_info[i].type_info = types[i];
        }
        type_t* function_type = get_new_function_type(result_type, param_info, num_types);

        scope_entry_t* new_entry = new_symbol(decl_context, decl_context.current_scope, name);
        new_entry->kind = SK_FUNCTION;
        new_entry->do_not_print = 1;
        new_entry->type_information = function_type;
        new_entry->entity_specs.is_elemental = is_elemental;
        new_entry->entity_specs.is_pure = (is_pure || is_elemental);

        new_entry->entity_specs.is_builtin = 1;
        new_entry->entity_specs.is_builtin_subroutine = (result_type == NULL);

        rb_tree_add(intrinsic_map, p, new_entry);

        DEBUG_CODE()
        {
            fprintf(stderr, "INTRINSICS: Creating new intrinsic '%s' of type '%s'\n",
                    name,
                    print_type_str(function_type, decl_context));
        }

        return new_entry;
    }
}

#define GET_INTRINSIC_ELEMENTAL(name, result, ...) \
({ \
    type_t* _types[] = { __VA_ARGS__ }; \
    const int _size = sizeof(_types) / sizeof(*_types) ; \
    get_intrinsic_symbol_(name, result, _size, _types, symbol->decl_context, \
            /* is_elemental */ 1, \
            /* is_pure */ 1, \
            /* is_transformational */ 0, \
            /* is_inquiry */ 0); \
})

#define GET_INTRINSIC_INQUIRY(name, result, ...) \
({ \
    type_t* _types[] = { __VA_ARGS__ }; \
    const int _size = sizeof(_types) / sizeof(*_types) ; \
    get_intrinsic_symbol_(name, result, _size, _types, symbol->decl_context, \
            /* is_elemental */ 0, \
            /* is_pure */ 0, \
            /* is_transformational */ 0, \
            /* is_inquiry */ 1); \
})

#define GET_INTRINSIC_PURE(name, result, ...) \
({ \
    type_t* _types[] = { __VA_ARGS__ }; \
    const int _size = sizeof(_types) / sizeof(*_types) ; \
    get_intrinsic_symbol_(name, result, _size, _types, symbol->decl_context, \
            /* is_elemental */ 0, \
            /* is_pure */ 1, \
            /* is_transformational */ 0, \
            /* is_inquiry */ 0); \
})

#define GET_INTRINSIC_IMPURE(name, result, ...) \
({ \
    type_t* _types[] = { __VA_ARGS__ }; \
    const int _size = sizeof(_types) / sizeof(*_types) ; \
    get_intrinsic_symbol_(name, result, _size, _types, symbol->decl_context, \
            /* is_elemental */ 0, \
            /* is_pure */ 0, \
            /* is_transformational */ 0, \
            /* is_inquiry */ 0); \
})

#define GET_INTRINSIC_TRANSFORMATIONAL(name, result, ...) \
({ \
    type_t* _types[] = { __VA_ARGS__ }; \
    const int _size = sizeof(_types) / sizeof(*_types) ; \
    get_intrinsic_symbol_(name, result, _size, _types, symbol->decl_context, \
            /* is_elemental */ 0, \
            /* is_pure */ 0, \
            /* is_transformational */ 1, \
            /* is_inquiry */ 0); \
})

#define MAX_ARGUMENTS 128

#define FORTRAN_GENERIC_INTRINSIC(name, keywords0, kind0) \
static scope_entry_t* compute_intrinsic_##name(scope_entry_t* symbol,  \
        type_t** argument_types, \
        AST *argument_expressions, \
        int num_arguments); \
static scope_entry_t* compute_intrinsic_##name##_aux(scope_entry_t* symbol,  \
        type_t** argument_types UNUSED_PARAMETER, \
        AST *argument_expressions, \
        int num_arguments, \
        const_value_t** const_value UNUSED_PARAMETER) \
{ \
    type_t* reordered_types[MAX_ARGUMENTS]; \
    AST reordered_exprs[MAX_ARGUMENTS]; \
    memset(reordered_types, 0, sizeof(reordered_types)); \
    memset(reordered_exprs, 0, sizeof(reordered_exprs)); \
    if (generic_keyword_check(symbol, &num_arguments, argument_expressions, keywords0, argument_types, reordered_types, reordered_exprs)) \
    { \
        return compute_intrinsic_##name (symbol, reordered_types, reordered_exprs, num_arguments); \
    } \
    return NULL; \
}

#define FORTRAN_GENERIC_INTRINSIC_2(name, keywords0, kind0, keywords1, kind1) \
static scope_entry_t* compute_intrinsic_##name##_0(scope_entry_t* symbol,  \
        type_t** argument_types, \
        AST *argument_expressions, \
        int num_arguments); \
static scope_entry_t* compute_intrinsic_##name##_1(scope_entry_t* symbol,  \
        type_t** argument_types, \
        AST *argument_expressions, \
        int num_arguments); \
static scope_entry_t* compute_intrinsic_##name##_aux(scope_entry_t* symbol,  \
        type_t** argument_types UNUSED_PARAMETER, \
        AST *argument_expressions, \
        int num_arguments, \
        const_value_t** const_value UNUSED_PARAMETER) \
{ \
    type_t* reordered_types[MAX_ARGUMENTS]; \
    AST reordered_exprs[MAX_ARGUMENTS]; \
    memset(reordered_types, 0, sizeof(reordered_types)); \
    memset(reordered_exprs, 0, sizeof(reordered_exprs)); \
    if (generic_keyword_check(symbol, &num_arguments, argument_expressions, keywords0, argument_types, reordered_types, reordered_exprs)) \
    { \
        return compute_intrinsic_##name##_0(symbol, reordered_types, reordered_exprs, num_arguments); \
    } \
    memset(reordered_types, 0, sizeof(reordered_types)); \
    memset(reordered_exprs, 0, sizeof(reordered_exprs)); \
    if (generic_keyword_check(symbol, &num_arguments, argument_expressions, keywords1, argument_types, reordered_types, reordered_exprs)) \
    { \
        return compute_intrinsic_##name##_1(symbol, reordered_types, reordered_exprs, num_arguments); \
    } \
    return NULL; \
}

FORTRAN_INTRINSIC_GENERIC_LIST
#undef FORTRAN_GENERIC_INTRINSIC
#undef FORTRAN_GENERIC_INTRINSIC_2

static void null_dtor_func(const void *v UNUSED_PARAMETER) { }

static void fortran_init_specific_names(decl_context_t decl_context);

void fortran_init_intrisics(decl_context_t decl_context)
{
#define FORTRAN_GENERIC_INTRINSIC(name, keywords0, kind0) \
    { \
        scope_entry_t* new_intrinsic = new_symbol(decl_context, decl_context.current_scope, #name); \
        new_intrinsic->kind = SK_FUNCTION; \
        new_intrinsic->do_not_print = 1; \
        new_intrinsic->type_information = get_computed_function_type(compute_intrinsic_##name##_aux); \
        new_intrinsic->entity_specs.is_builtin = 1; \
        if (kind0 == ES || kind0 == PS || kind0 == S) \
           new_intrinsic->entity_specs.is_builtin_subroutine = 1; \
    }

#define FORTRAN_GENERIC_INTRINSIC_2(name, keywords0, kind0, keywords1, kind1) \
    { \
        scope_entry_t* new_intrinsic = new_symbol(decl_context, decl_context.current_scope, #name); \
        new_intrinsic->kind = SK_FUNCTION; \
        new_intrinsic->do_not_print = 1; \
        new_intrinsic->type_information = get_computed_function_type(compute_intrinsic_##name##_aux); \
        new_intrinsic->entity_specs.is_builtin = 1; \
        if (kind0 == ES || kind0 == PS || kind0 == S) \
           new_intrinsic->entity_specs.is_builtin_subroutine = 1; \
    }

FORTRAN_INTRINSIC_GENERIC_LIST
#undef FORTRAN_GENERIC_INTRINSIC
#undef FORTRAN_GENERIC_INTRINSIC_2

    intrinsic_map = rb_tree_create(intrinsic_descr_cmp, null_dtor_func, null_dtor_func);

// Sign in specific names for intrinsics
    fortran_init_specific_names(decl_context);
}

static scope_entry_t* register_specific_intrinsic_name(
        decl_context_t decl_context,
        const char *generic_name, 
        const char *specific_name,
        int num_args,
        type_t* t0, type_t* t1, type_t* t2, type_t* t3, type_t* t4, type_t* t5, type_t* t6)
{
    scope_entry_t* generic_entry = query_name_no_implicit(decl_context, generic_name);
    ERROR_CONDITION(generic_entry == NULL
            || !generic_entry->entity_specs.is_builtin, "Invalid symbol when registering specific intrinsic name\n", 0);
    computed_function_type_t fun = computed_function_type_get_computing_function(generic_entry->type_information);

    type_t* type_list[7] = { t0, t1, t2, t3, t4, t5, t6 };

    const_value_t* const_val;
    scope_entry_t* specific_entry = fun(generic_entry, type_list, NULL, num_args, &const_val);

    ERROR_CONDITION(specific_entry == NULL, "No specific symbol is possible when registering specific intrinsic name '%s' of generic intrinsic '%s'\n", 
            specific_name,
            generic_name);

    // Insert alias only if they are different names
    if (strcasecmp(generic_name, specific_name) != 0)
    {
        insert_alias(generic_entry->decl_context.current_scope, specific_entry, specific_name);
    }
    else
    {
        generic_entry->entity_specs.specific_intrinsic = specific_entry;
    }

    return specific_entry;
}

static scope_entry_t* register_custom_intrinsic(
        decl_context_t decl_context,
        const char* specific_name,
        type_t* result_type,
        int num_types,
        type_t* t0, type_t* t1, type_t* t2)
{
    type_t* types[3] = { t0, t1, t2 };

    return get_intrinsic_symbol_(specific_name,
            result_type, 
            num_types, types, 
            decl_context,
            0, 0, 0, 0);
}

#if 0
The macros below have been generated using this shell script


for i in `seq 0 7`; 
do 
  echo -n "#define REGISTER_SPECIFIC_INTRINSIC_$i(_specific_name, _generic_name"; 
  for p in t_ ; 
  do 
    for j in `seq 0 $(($i - 1))`; 
    do 
      echo -n ", ${p}${j}"; 
    done; 
  done; 
  echo ") \\"; 
  echo -n "  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), $i"; 
  for p in t_ ; 
  do 
    for j in `seq 0 $(($i - 1))`; 
    do 
      echo -n ", (${p}${j})"; 
    done; 
    for j in `seq $i 6`; 
    do 
      echo -n ", NULL"; 
    done; 
  done; 
  echo ")"; 
done;

#endif

#define REGISTER_SPECIFIC_INTRINSIC_0(_specific_name, _generic_name) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
#define REGISTER_SPECIFIC_INTRINSIC_1(_specific_name, _generic_name, t_0) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 1, (t_0), NULL, NULL, NULL, NULL, NULL, NULL)
#define REGISTER_SPECIFIC_INTRINSIC_2(_specific_name, _generic_name, t_0, t_1) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 2, (t_0), (t_1), NULL, NULL, NULL, NULL, NULL)
#define REGISTER_SPECIFIC_INTRINSIC_3(_specific_name, _generic_name, t_0, t_1, t_2) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 3, (t_0), (t_1), (t_2), NULL, NULL, NULL, NULL)
#define REGISTER_SPECIFIC_INTRINSIC_4(_specific_name, _generic_name, t_0, t_1, t_2, t_3) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 4, (t_0), (t_1), (t_2), (t_3), NULL, NULL, NULL)
#define REGISTER_SPECIFIC_INTRINSIC_5(_specific_name, _generic_name, t_0, t_1, t_2, t_3, t_4) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 5, (t_0), (t_1), (t_2), (t_3), (t_4), NULL, NULL)
#define REGISTER_SPECIFIC_INTRINSIC_6(_specific_name, _generic_name, t_0, t_1, t_2, t_3, t_4, t_5) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 6, (t_0), (t_1), (t_2), (t_3), (t_4), (t_5), NULL)
#define REGISTER_SPECIFIC_INTRINSIC_7(_specific_name, _generic_name, t_0, t_1, t_2, t_3, t_4, t_5, t_6) \
  register_specific_intrinsic_name(decl_context, (_generic_name), (_specific_name), 7, (t_0), (t_1), (t_2), (t_3), (t_4), (t_5), (t_6))

#define REGISTER_CUSTOM_INTRINSIC_0(_specific_name, result_type) \
    register_custom_intrinsic(decl_context, (_specific_name), result_type, 0, NULL, NULL, NULL)
#define REGISTER_CUSTOM_INTRINSIC_1(_specific_name, result_type, type_0) \
    register_custom_intrinsic(decl_context, (_specific_name), result_type, 1, type_0, NULL, NULL)
#define REGISTER_CUSTOM_INTRINSIC_2(_specific_name, result_type, type_0, type_1) \
    register_custom_intrinsic(decl_context, (_specific_name), result_type, 2, type_0, type_1, NULL)
#define REGISTER_CUSTOM_INTRINSIC_3(_specific_name, result_type, type_0, type_1, type_2) \
    register_custom_intrinsic(decl_context, (_specific_name), result_type, 3, type_0, type_1, type_2)

static void fortran_init_specific_names(decl_context_t decl_context)
{
    type_t* default_char = get_array_type(get_char_type(), NULL, decl_context);

    REGISTER_SPECIFIC_INTRINSIC_1("abs", "abs", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("acos", "acos", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("aimag", "aimag", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_2("aint", "aint", get_float_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_1("alog", "log", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("alog10", "log10", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_2("amod", "mod", get_float_type(), get_float_type());
    // 'amax0' 'amax1' 'amin0' 'amin1' are defined as generic intrinsics due to their non-fortranish nature of unbounded number of parameters
    REGISTER_SPECIFIC_INTRINSIC_2("anint", "anint", get_float_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_1("asin", "asin", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("atan", "atan", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("atan2", "atan2", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("cabs", "abs", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("ccos", "cos", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("cexp", "exp", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("cexp", "exp", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_2("char", "char", get_signed_int_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_1("clog", "log", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("conjg", "conjg", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("cos", "cos", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("cosh", "cosh", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("csin", "sin", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("csqrt", "sqrt", get_complex_type(get_float_type()));
    REGISTER_SPECIFIC_INTRINSIC_1("dabs", "abs", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dacos", "cos", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dasin", "asin", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("datan", "atan", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("datan2", "atan2", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dcos", "cos", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dcosh", "cosh", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_2("ddim", "dim", get_double_type(), get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dexp", "exp", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_2("dim", "dim", get_float_type(), get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_2("dint", "aint", get_double_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_1("dlog", "log", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dlog10", "log10", get_double_type());
    // dmax1 dmin1 are defined as generic intrinsics
    REGISTER_SPECIFIC_INTRINSIC_2("dmod", "mod", get_double_type(), get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_2("dnint", "anint", get_double_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("dprod", "dprod", get_float_type(), get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_2("dsign", "sign", get_double_type(), get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dsin", "sin", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dsinh", "sinh", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dsqrt", "sqrt", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dtan", "tan", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("dtanh", "tanh", get_double_type());
    REGISTER_SPECIFIC_INTRINSIC_1("exp", "exp", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_2("float", "real", get_signed_int_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_1("iabs", "abs", get_signed_int_type());
    REGISTER_SPECIFIC_INTRINSIC_2("ichar", "ichar", default_char, NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("idim", "dim", get_signed_int_type(), get_signed_int_type());
    REGISTER_SPECIFIC_INTRINSIC_2("idint", "int", get_double_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("idnint", "nint", get_double_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("ifix", "int", get_float_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("index", "index", default_char, default_char);
    REGISTER_SPECIFIC_INTRINSIC_2("int", "int", get_signed_int_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("isign", "sign", get_signed_int_type(), get_signed_int_type());
    REGISTER_SPECIFIC_INTRINSIC_2("len", "len", default_char, NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("lge", "lge", default_char, default_char);
    REGISTER_SPECIFIC_INTRINSIC_2("lgt", "lgt", default_char, default_char);
    REGISTER_SPECIFIC_INTRINSIC_2("lle", "lle", default_char, default_char);
    REGISTER_SPECIFIC_INTRINSIC_2("llt", "llt", default_char, default_char);
    REGISTER_SPECIFIC_INTRINSIC_2("mod", "mod", get_signed_int_type(), get_signed_int_type());
    REGISTER_SPECIFIC_INTRINSIC_2("nint", "nint", get_float_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("real", "real", get_signed_int_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_2("sign", "sign", get_float_type(), get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("sin", "sin", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_2("sngl", "real", get_double_type(), NULL);
    REGISTER_SPECIFIC_INTRINSIC_1("sqrt", "sqrt", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("tan", "tan", get_float_type());
    REGISTER_SPECIFIC_INTRINSIC_1("tanh", "tanh", get_float_type());

    // Very old (normally from g77) intrinsics
    REGISTER_CUSTOM_INTRINSIC_1("dfloat", get_double_type(), get_signed_int_type());
    REGISTER_CUSTOM_INTRINSIC_1("dconjg", get_complex_type(get_double_type()), get_complex_type(get_double_type()));
    REGISTER_CUSTOM_INTRINSIC_1("dimag", get_double_type(), get_complex_type(get_double_type()));
}

scope_entry_t* compute_intrinsic_abs(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0)
            || is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("abs", t0, t0);
    }

    return NULL;
}

static char opt_valid_kind_expr(AST expr, int *val)
{
    if (expr == NULL)
        return 1;

    if (!expression_is_constant(expr))
        return 0;

    int k = const_value_cast_to_4(expression_get_constant(expr));

    if (val != NULL)
        *val = k;

    return 1;
}

scope_entry_t* compute_intrinsic_achar(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    int dc = 1;
    if (is_integer_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &dc))
    {
        // We ignore the character kind here
        return GET_INTRINSIC_ELEMENTAL("achar", 
                get_array_type(get_char_type(), NULL, symbol->decl_context), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_acos(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("acos", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_acosh(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("acosh", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_adjustl(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_fortran_character_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("adjustl", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_adjustr(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_fortran_character_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("adjustr", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_aimag(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("aimag", complex_type_get_base_type(t0), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_aint(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    int dr = 4;
    if (is_floating_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &dr))
    {
        return GET_INTRINSIC_ELEMENTAL("aint", 
                choose_float_type_from_kind(argument_expressions[1], dr), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_all(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    if (is_fortran_array_type(t0)
            && is_bool_type(get_rank0_type(t0))
            && (t1 == NULL || is_integer_type(t1)))
    {
        type_t* return_type = array_type_get_element_type(t0);

        return GET_INTRINSIC_TRANSFORMATIONAL("all", return_type, t0, 
                (t1 == NULL ? get_signed_int_type() : t1));
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_allocated_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    return GET_INTRINSIC_INQUIRY("allocated", get_bool_type(), t0);
}

scope_entry_t* compute_intrinsic_allocated_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_allocated_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_anint(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    int dr = 4;
    if (is_floating_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &dr))
    {
        return GET_INTRINSIC_ELEMENTAL("anint", 
                choose_float_type_from_kind(argument_expressions[1], dr), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_any(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    if (is_fortran_array_type(t0)
            && is_bool_type(get_rank0_type(t0))
            && (t1 == NULL || is_integer_type(t1)))
    {
        type_t* return_type = array_type_get_element_type(t0);

        return GET_INTRINSIC_TRANSFORMATIONAL("any", return_type, t0, 
                (t1 == NULL ? get_signed_int_type() : t1));
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_asin(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("asin", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_asinh(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("asinh", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_associated(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    if (is_pointer_type(t0))
    {
        if (t1 == NULL)
        {
            return GET_INTRINSIC_INQUIRY("associated", get_bool_type(), t0);
        }
        else
        {
            if (is_pointer_type(t1))
                t1 = pointer_type_get_pointee_type(t1);

            if (equivalent_tkr_types(pointer_type_get_pointee_type(t0), t1))
            {
                return GET_INTRINSIC_INQUIRY("associated", get_bool_type(), t0, t1);
            }
        }
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_atan_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (num_arguments == 1)
    {
        if (is_floating_type(t0)
                || is_complex_type(t0))
        {
            return GET_INTRINSIC_ELEMENTAL("atan", t0, t0);
        }
    }
    else if (num_arguments == 2)
    {
        // t0 == Y
        // t1 == X
        type_t* t1 = get_rank0_type(argument_types[1]);
        if (is_floating_type(t0)
                && equivalent_types(get_unqualified_type(t0), get_unqualified_type(t1)))
        {
            return GET_INTRINSIC_ELEMENTAL("atan", t1, t1, t0);
        }
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_atan_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_atan_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_atan2(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_atan_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_atanh(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("atanh", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_atomic_define(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_atomic_ref(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_j0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("bessel_j0", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_j1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("bessel_j1", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_jn_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    if (num_arguments == 2)
    {
        type_t* t0 = get_rank0_type(argument_types[0]);
        type_t* t1 = get_rank0_type(argument_types[1]);
        if (is_integer_type(t0)
                && is_floating_type(t1))
        {
            return GET_INTRINSIC_ELEMENTAL("bessel_jn", t1, t0, t1);
        }
    }
    else if (num_arguments == 3)
    {
        type_t* t0 = argument_types[0];
        type_t* t1 = argument_types[1];
        type_t* t2 = argument_types[2];

        if (is_integer_type(t0)
                && is_integer_type(t1)
                && is_floating_type(t2))
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("bessel_jn", t2, t0, t1, t2);
        }
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_jn_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_bessel_jn_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_bessel_y0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("bessel_y0", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_y1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("bessel_y1", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_yn_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    if (num_arguments == 2)
    {
        type_t* t0 = get_rank0_type(argument_types[0]);
        type_t* t1 = get_rank0_type(argument_types[1]);
        if (is_integer_type(t0)
                && is_floating_type(t1))
        {
            return GET_INTRINSIC_ELEMENTAL("bessel_yn", t1, t0, t1);
        }
    }
    else if (num_arguments == 3)
    {
        type_t* t0 = argument_types[0];
        type_t* t1 = argument_types[1];
        type_t* t2 = argument_types[2];

        if (is_integer_type(t0)
                && is_integer_type(t1)
                && is_floating_type(t2))
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("bessel_yn", t2, t0, t1, t2);
        }
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bessel_yn_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_bessel_yn_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_bge(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("bge", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bgt(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("bgt", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ble(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("ble", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_blt(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("blt", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_bit_size(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_integer_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("bit_size", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_btest(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("btest", get_bool_type(), t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ceiling(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    int dr = 4;
    if (is_floating_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &dr))
    {
        return GET_INTRINSIC_ELEMENTAL("ceiling", 
                choose_int_type_from_kind(argument_expressions[1], dr), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_char(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    int di = 4;
    if (is_integer_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("char", 
                get_array_type(get_char_type(), NULL, symbol->decl_context), 
                t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_cmplx(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = argument_types[1] != NULL ? get_rank0_type(argument_types[1]) : NULL;
    int dr = 4;
    if (opt_valid_kind_expr(argument_expressions[1], &dr))
    {
        if ((is_floating_type(t0)
                    || is_complex_type(t0)
                    || is_integer_type(t0))
                && (t1 == NULL
                    || is_floating_type(t1)
                        || is_complex_type(t1)
                        || is_integer_type(t1)))
        {
            return GET_INTRINSIC_ELEMENTAL("cmplx", 
                    get_complex_type(choose_float_type_from_kind(argument_expressions[1], dr)), 
                    t0, 
                    t1 == NULL ? t0 : t1);
        }
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_dcmplx(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = argument_types[1] != NULL ? get_rank0_type(argument_types[1]) : NULL;
    if ((is_floating_type(t0)
                || is_complex_type(t0)
                || is_integer_type(t0))
            && (t1 == NULL
                || is_floating_type(t1)
                || is_complex_type(t1)
                || is_integer_type(t1)))
    {
        return GET_INTRINSIC_ELEMENTAL("dcmplx", 
                get_complex_type(get_double_type()),
                t0, 
                t1 == NULL ? t0 : t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_command_argument_count(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    get_intrinsic_symbol_("command_argument_count", get_signed_int_type(), 0, NULL, symbol->decl_context, 
            /* is_elemental */ 0, 
            /* is_pure */ 0, 
            /* is_transformational */ 1, 
            /* is_inquiry */ 0); 
    return NULL;
}

scope_entry_t* compute_intrinsic_conjg(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("conjg", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_cos(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("cos", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_cosh(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("cosh", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_count(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    int di = 4;
    if (is_fortran_array_type(t0)
            && is_bool_type(get_rank0_type(t0))
            && (t1 == NULL || is_integer_type(t1))
            && opt_valid_kind_expr(argument_expressions[2], &di))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("count", 
                choose_int_type_from_kind(argument_expressions[2], di),
                t0, 
                (t1 == NULL ? get_signed_int_type() : t1));
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_cpu_time(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_floating_type(t0))
    {
        // NULL because this is a subroutine
        return GET_INTRINSIC_IMPURE("cpu_time", NULL, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_cshift(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if (is_fortran_array_type(t0)
            && is_integer_type(get_rank0_type(t1))
            && (get_rank_of_type(t0) - 1) == get_rank_of_type(t1) 
            && (t2 == NULL || is_integer_type(t2)))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("cshift", t0, t0, t1, 
                t2 == NULL ? get_signed_int_type() : t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_date_and_time(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];
    type_t* t3 = argument_types[3];

    if ((t0 == NULL || is_fortran_character_type(t0))
            && (t1 == NULL || is_fortran_character_type(t1))
            && (t2 == NULL || is_fortran_character_type(t2))
            && (t3 == NULL || 
                (is_integer_type(get_rank0_type(t3)) &&
                 get_rank_of_type(t3) == 1)))
    {
        type_t* char_type = get_array_type(get_char_type(), NULL, symbol->decl_context);
        type_t* int_array = get_n_ranked_type(get_signed_int_type(), 1, symbol->decl_context);
        return GET_INTRINSIC_IMPURE("date_and_time", NULL, char_type, char_type, char_type, int_array);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_dble(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0)
            || is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("dble", get_double_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_digits(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_integer_type(get_rank0_type(t0))
            || is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("digits", get_signed_int_type(), t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_dim(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if ((is_integer_type(t0)
            || is_floating_type(t0))
            && equivalent_types(get_unqualified_type(t0), get_unqualified_type(t1)))
    {
        return GET_INTRINSIC_ELEMENTAL("dim", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_dot_product(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    char is_numeric_0 = is_integer_type(get_rank0_type(t0))
        || is_floating_type(get_rank0_type(t0))
        || is_complex_type(get_rank0_type(t0));

    char is_logical_0 = is_bool_type(get_rank0_type(t0));

    char is_numeric_1 = is_integer_type(get_rank0_type(t1))
        || is_floating_type(get_rank0_type(t1))
        || is_complex_type(get_rank0_type(t1));

    char is_logical_1 = is_bool_type(get_rank0_type(t1));

    if ((is_numeric_0 && is_numeric_1)
            || ((is_logical_0 && is_logical_1)
                && (get_rank_of_type(t0) == 1)
                && (get_rank_of_type(t1) == 1)))
    {
        type_t* res = common_type_of_binary_operation(get_rank0_type(t0), get_rank0_type(t1));
        if (res == NULL)
            return NULL;
        return GET_INTRINSIC_TRANSFORMATIONAL("dot_product", res, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_dprod(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_float_type(t0)
            && is_float_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("dprod", get_double_type(), t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_dshiftl(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    if (is_integer_type(t0)
            && is_integer_type(t1)
            && is_integer_type(t2))
    {
        return GET_INTRINSIC_ELEMENTAL("dshiftl", t0, t0, t1, t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_dshiftr(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    if (is_integer_type(t0)
            && is_integer_type(t1)
            && is_integer_type(t2))
    {
        return GET_INTRINSIC_ELEMENTAL("dshiftr", t0, t0, t1, t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_eoshift(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];
    type_t* t3 = argument_types[3];

    if (is_fortran_array_type(t0)
            && is_integer_type(get_rank0_type(t1))
            && (get_rank_of_type(t0) - 1) == get_rank_of_type(t1)
            && (t2 == NULL
                || (equivalent_types(get_unqualified_type(get_rank0_type(t0)), 
                        get_unqualified_type(get_rank0_type(t2)))
                    && ((get_rank_of_type(t0) - 1) == get_rank_of_type(t2))))
            && (t3 == NULL
                || (is_integer_type(t3))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("eoshift", t0, 
                t0,
                t1,
                t2 == NULL ? get_rank0_type(t0) : t2,
                t3 == NULL ? get_signed_int_type() : t3);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_epsilon(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_integer_type(get_rank0_type(t0))
            || is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("epsilon", get_rank0_type(t0), t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_erf(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("erf", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_erfc(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("erfc", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_erfc_scaled(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("erfc_scaled", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_execute_command_line(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];
    type_t* t3 = argument_types[3];
    type_t* t4 = argument_types[4];
    if (is_fortran_character_type(t0)
            && (t1 == NULL || is_bool_type(t1))
            && (t2 == NULL || is_integer_type(t2))
            && (t3 == NULL || is_integer_type(t3))
            && (t4 == NULL || is_fortran_character_type(t4)))
    {
        return GET_INTRINSIC_IMPURE("execute_command_line", 
                NULL, // It is a subroutine
                t1, 
                t2 == NULL ? get_signed_int_type() : t2,
                t3 == NULL ? get_signed_int_type() : t3,
                t4 == NULL ? get_n_ranked_type(get_char_type(), 1, symbol->decl_context) : t3);

    }

    return NULL;
}

scope_entry_t* compute_intrinsic_exp(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("exp", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_exponent(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("exponent", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_extends_type_of(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_findloc_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = num_arguments == 6 ? argument_types[2] : NULL;
    type_t* t3 = num_arguments == 6 ? argument_types[3] : argument_types[2];
    AST kind = num_arguments == 6 ? argument_expressions[4] : argument_expressions[3];
    type_t* t5 = num_arguments == 6 ? argument_types[5] : argument_types[4];

    int di = 4;

    if (is_fortran_array_type(t0)
            && is_fortran_intrinsic_type(get_rank0_type(t0))
            && (get_rank_of_type(t1) == 0)
            && (common_type_of_equality_operation(get_rank0_type(t0), t1) != NULL)
            && (t2 == NULL || is_integer_type(t2))
            && (t3 == NULL || (is_bool_type(get_rank0_type(t3)) && are_conformable_types(t0, t3)))
            && opt_valid_kind_expr(kind, &di)
            && (t5 == NULL || is_bool_type(t5)))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("findloc", 
                get_n_ranked_type(choose_int_type_from_kind(kind, di), get_rank_of_type(t1) - 1, symbol->decl_context),
                t0,
                t1,
                t2 == NULL ? get_signed_int_type() : t2,
                t3 == NULL ? get_bool_type() : t3,
                t5 == NULL ? get_bool_type() : t5,
                );
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_findloc_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_findloc_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_floor(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    AST kind = argument_expressions[1];

    int dr = 4;
    if (is_floating_type(t0)
            && opt_valid_kind_expr(kind, &dr))
    {
        return GET_INTRINSIC_ELEMENTAL("floor", choose_float_type_from_kind(kind, dr), t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_fraction(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("fraction", t0, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_gamma(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("gamma", t0, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_get_command(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if ((t0 == NULL || is_fortran_character_type(t0))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || is_integer_type(t2)))
    {
        return GET_INTRINSIC_IMPURE("get_command",
                NULL, // Is a subroutine
                t0 == NULL ? get_n_ranked_type(get_char_type(), 1, symbol->decl_context) : t0,
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_signed_int_type() : t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_get_command_argument(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];
    type_t* t3 = argument_types[3];

    if (is_integer_type(t0)
            && (t1 == NULL || is_fortran_character_type(t1))
            && (t2 == NULL || is_integer_type(t2))
            && (t3 == NULL || is_integer_type(t3)))
    {
        return GET_INTRINSIC_IMPURE("get_command_argument",
                NULL, // Is a subroutine
                t0,
                t1 == NULL ? get_n_ranked_type(get_char_type(), 1, symbol->decl_context) : t1,
                t2 == NULL ? get_signed_int_type() : t2,
                t3 == NULL ? get_signed_int_type() : t3);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_get_environment_variable(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];
    type_t* t3 = argument_types[3];
    type_t* t4 = argument_types[4];

    if (is_fortran_character_type(t0)
            && (t1 == NULL || is_fortran_character_type(t1))
            && (t2 == NULL || is_integer_type(t2))
            && (t3 == NULL || is_integer_type(t3))
            && (t4 == NULL || is_bool_type(t4)))
    {
        return GET_INTRINSIC_IMPURE("get_environment_variable", 
                NULL, // is a subroutine
                t0,
                t1 == NULL ? get_n_ranked_type(get_char_type(), 1, symbol->decl_context) : t1,
                t2 == NULL ? get_signed_int_type() : t2,
                t3 == NULL ? get_signed_int_type() : t3,
                t3 == NULL ? get_bool_type() : t4);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_huge(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_integer_type(get_rank0_type(t0))
            || is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("huge", get_rank0_type(t0), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_hypot(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_floating_type(t0)
            && equivalent_types(get_unqualified_type(t0), get_unqualified_type(t1)))
    {
        return GET_INTRINSIC_ELEMENTAL("hypot", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iachar(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int di = 4;
    if (is_fortran_character_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("iachar", 
                choose_int_type_from_kind(argument_expressions[1], di), 
                t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iall_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL ;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];
    if (is_fortran_array_type(t0)
            && is_integer_type(get_rank0_type(t0))
            && is_integer_type(t1)
            && (t2 == NULL
                || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("iall",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iall_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_iall_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_iand(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("iand", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iany_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL ;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];
    if (is_fortran_array_type(t0)
            && is_integer_type(get_rank0_type(t0))
            && is_integer_type(t1)
            && (t2 == NULL
                || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("iany",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iany_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_iany_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_ibclr(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("ibclr", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ibits(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    if (is_integer_type(t0)
            && is_integer_type(t1)
            && is_integer_type(t2))
    {
        return GET_INTRINSIC_ELEMENTAL("ibits", t0, t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ibset(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("ibset", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ichar(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int di = 4;
    if (is_fortran_character_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("ichar",
                choose_int_type_from_kind(argument_expressions[1], di), 
                t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ieor(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("ieor", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_image_index(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_index(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    int di = 4;
    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1)
            && equivalent_types(get_unqualified_type(array_type_get_element_type(t0)), 
                get_unqualified_type(array_type_get_element_type(t1)))
            && (t2 == NULL || is_bool_type(t2))
            && opt_valid_kind_expr(argument_expressions[3], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("index", 
                choose_int_type_from_kind(argument_expressions[3], di),
                t0, t1, 
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_int(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int di = 4;

    if ((is_integer_type(t0)
            || is_floating_type(t0)
            || is_complex_type(t0))
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("int", 
                choose_int_type_from_kind(argument_expressions[1], di),
                t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ior(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("ior", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iparity_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];

    if (is_fortran_array_type(t0)
            && is_integer_type(get_rank0_type(t0))
            && is_integer_type(t1)
            && (t2 == NULL
                || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("iparity",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_iparity_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_iparity_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_ishft(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("ishft", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_ishftc(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    if (is_integer_type(t0)
            && is_integer_type(t1)
            && (t2 == NULL || is_integer_type(t2)))
    {
        return GET_INTRINSIC_ELEMENTAL("ishftc", t0, t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_is_contiguous(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_fortran_array_type(t0))
    {
        return GET_INTRINSIC_INQUIRY("is_contiguous", get_bool_type(), t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_is_iostat_end(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("is_iostat_end", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_is_iostat_eor(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("is_iostat_eor", get_bool_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_kind(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_fortran_intrinsic_type(t0))
    {
        return GET_INTRINSIC_INQUIRY("kind", get_signed_int_type(), t0);
    }
    
    return NULL;
}

scope_entry_t* compute_intrinsic_lbound(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    int di = 4;

    if (is_fortran_array_type(t0)
            && (t1 == NULL || is_integer_type(t1))
            && (opt_valid_kind_expr(argument_expressions[2], &di)))
    {
        if (t1 != NULL)
        {
            return GET_INTRINSIC_INQUIRY("lbound",
                    choose_int_type_from_kind(argument_expressions[2], di),
                    t0, t1);
        }
        else
        {
            return GET_INTRINSIC_INQUIRY("lbound",
                    get_n_ranked_type(choose_int_type_from_kind(argument_expressions[2], di), 
                        get_rank_of_type(t0), 
                        symbol->decl_context),
                    t0);
        }
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_lcobound(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_leadz(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("leadz", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_len(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    int di = 4;
    if (is_fortran_character_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_INQUIRY("len",
                choose_int_type_from_kind(argument_expressions[1], di),
                t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_len_trim(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    int di = 4;
    if (is_fortran_character_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_INQUIRY("len_trim",
                choose_int_type_from_kind(argument_expressions[1], di),
                t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_lge(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("lge", get_bool_type(), t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_lgt(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("lgt", get_bool_type(), t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_lle(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("lle", get_bool_type(), t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_llt(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("llt", get_bool_type(), t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_log(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("log", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_log_gamma(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("log_gamma", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_log10(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("log10", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_logical(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int dl = 4;

    if (is_bool_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &dl))
    {
        return GET_INTRINSIC_ELEMENTAL("logical", choose_logical_type_from_kind(argument_expressions[1], dl), t0); 
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_maskl(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int di = 4;

    if (is_integer_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("maskl", choose_int_type_from_kind(argument_expressions[1], di), t0); 
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_maskr(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int di = 4;

    if (is_integer_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("maskr", choose_int_type_from_kind(argument_expressions[1], di), t0); 
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_matmul(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    char is_numeric_0 = is_integer_type(get_rank0_type(t0))
        || is_floating_type(get_rank0_type(t0))
        || is_complex_type(get_rank0_type(t0));

    char is_logical_0 = is_bool_type(get_rank0_type(t0));

    char is_numeric_1 = is_integer_type(get_rank0_type(t1))
        || is_floating_type(get_rank0_type(t1))
        || is_complex_type(get_rank0_type(t1));

    char is_logical_1 = is_bool_type(get_rank0_type(t1));

    char is_rank1_0 = get_rank_of_type(t0) == 1;
    char is_rank1_1 = get_rank_of_type(t1) == 1;
    char is_rank2_0 = get_rank_of_type(t0) == 2;
    char is_rank2_1 = get_rank_of_type(t1) == 2;

    if (((is_rank2_0 && (is_rank1_1 || is_rank2_1))
                || (is_rank2_1 && (is_rank1_0 || is_rank2_0)))
            && ((is_logical_0 && is_logical_1)
                || (is_numeric_0 && is_numeric_1)))
    {
        type_t* result_type = common_type_of_binary_operation(get_rank0_type(t0), get_rank0_type(t1));

        if (is_rank2_0 && is_rank2_0)
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("matmul", 
                    get_n_ranked_type(result_type, 2, symbol->decl_context),
                    t0, t1);
        }
        else
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("matmul", 
                    get_n_ranked_type(result_type, 1, symbol->decl_context),
                    t0, t1);
        }
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_max_min_aux(
        const char* name,
        type_t* output_type,
        type_t* input_type,
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    if (num_arguments == 0)
        return NULL;

    type_t* t0 = get_rank0_type(argument_types[0]);
    if (input_type == NULL
            && (!is_integer_type(t0)
                && !is_floating_type(t0)
                && !is_fortran_character_type(t0)))
    {
        return NULL;
    }
    else if (input_type != NULL
            && !equivalent_types(get_unqualified_type(input_type), get_unqualified_type(t0)))
    {
        return NULL;
    }

    type_t* ranked_0[num_arguments + 1];
    memset(ranked_0, 0, sizeof(ranked_0));

    ranked_0[0] = input_type == NULL ? t0 : input_type;

    int i;
    for (i = 1; i < num_arguments; i++)
    {
        if (!equivalent_types(
                    get_unqualified_type(get_rank0_type(argument_types[i])), 
                    get_unqualified_type(t0)))
            return NULL;

        if (input_type == NULL)
        {
            ranked_0[i] = get_rank0_type(argument_types[i]);
        }
        else
        {
            ranked_0[i] = input_type;
        }
    }

    return get_intrinsic_symbol_(name, 
            output_type == NULL ? t0 : output_type, 
            num_arguments, ranked_0, symbol->decl_context, 
            /* is_elemental */ 1, 
            /* is_pure */ 1, 
            /* is_transformational */ 0, 
            /* is_inquiry */ 0); 
}

scope_entry_t* compute_intrinsic_max(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("max", /* output_type */ NULL, /* input_type */ NULL, 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_max0(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("max0", /* output_type */ get_signed_int_type(), /* input_type */ get_signed_int_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_max1(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("max1", /* output_type */ get_signed_int_type(), /* input_type */ get_float_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_amax0(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("amax0", /* output_type */ get_float_type(), /* input_type */ get_signed_int_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_amax1(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("amax1", /* output_type */ get_float_type(), /* input_type */ get_float_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_dmax1(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("dmax1", /* output_type */ get_double_type(), /* input_type */ get_double_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_maxexponent(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("maxexponent", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_maxloc_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 5 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 5 ? argument_types[2] : argument_types[1];
    // type_t* t3 = num_arguments == 5 ? argument_types[3] : argument_types[2];
    AST kind = num_arguments == 5 ? argument_expressions[3] : argument_expressions[2];
    type_t* t4 = num_arguments == 5 ? argument_types[4] : argument_types[3];

    int di = 4;

    if (is_fortran_array_type(t0)
            && (is_floating_type(get_rank0_type(t0))
                || is_integer_type(get_rank0_type(t0))
                || is_fortran_character_type(get_rank0_type(t0)))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0)))
            && opt_valid_kind_expr(kind, &di)
            && (t4 == NULL || is_bool_type(t4)))
    {
        int rank = 1;
        if (t1 != NULL)
        {
            rank = get_rank_of_type(t0) - 1;
        }

        return GET_INTRINSIC_TRANSFORMATIONAL("maxloc", 
                get_n_ranked_type(choose_int_type_from_kind(kind, di), rank, symbol->decl_context),
                t0, 
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_bool_type() : t2, 
                t4 == NULL ? get_bool_type() : t4);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_maxloc_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_maxloc_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_maxval_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];

    if (is_fortran_array_type(t0)
            && (is_integer_type(get_rank0_type(t0))
                || is_floating_type(get_rank0_type(t0))
                || is_fortran_character_type(get_rank0_type(t0)))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("maxval",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0,
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_maxval_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_maxval_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_merge(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    if (equivalent_types(get_unqualified_type(t0), 
                get_unqualified_type(t1))
            && is_bool_type(t2))
    {
        return GET_INTRINSIC_ELEMENTAL("merge", t0, t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_merge_bits(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    if (is_integer_type(t0)
            && is_integer_type(t1)
            && is_integer_type(t2))
    {
        return GET_INTRINSIC_ELEMENTAL("merge_bits", t0, t0, t1, t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_min(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("min", /* output_type */ NULL, /* input_type */ NULL, 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_min0(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("min0", /* output_type */ get_signed_int_type(), /* input_type */ get_signed_int_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_min1(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("min1", /* output_type */ get_signed_int_type(), /* input_type */ get_float_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_amin0(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("amin0", /* output_type */ get_float_type(), /* input_type */ get_signed_int_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_amin1(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("amin1", /* output_type */ get_float_type(), /* input_type */ get_float_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_dmin1(
        scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_max_min_aux("dmin1", /* output_type */ get_double_type(), /* input_type */ get_double_type(), 
            symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_minexponent(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("minexponent", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_minloc_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 5 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 5 ? argument_types[2] : argument_types[1];
    // type_t* t3 = num_arguments == 5 ? argument_types[3] : argument_types[2];
    AST kind = num_arguments == 5 ? argument_expressions[3] : argument_expressions[2];
    type_t* t4 = num_arguments == 5 ? argument_types[4] : argument_types[3];

    int di = 4;

    if (is_fortran_array_type(t0)
            && (is_floating_type(get_rank0_type(t0))
                || is_integer_type(get_rank0_type(t0))
                || is_fortran_character_type(get_rank0_type(t0)))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0)))
            && opt_valid_kind_expr(kind, &di)
            && (t4 == NULL || is_bool_type(t4)))
    {
        int rank = 1;
        if (t1 != NULL)
        {
            rank = get_rank_of_type(t0) - 1;
        }

        return GET_INTRINSIC_TRANSFORMATIONAL("minloc", 
                get_n_ranked_type(choose_int_type_from_kind(kind, di), rank, symbol->decl_context),
                t0, 
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_bool_type() : t2, 
                t4 == NULL ? get_bool_type() : t4);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_minloc_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_minloc_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_minval_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];

    if (is_fortran_array_type(t0)
            && (is_integer_type(get_rank0_type(t0))
                || is_floating_type(get_rank0_type(t0))
                || is_fortran_character_type(get_rank0_type(t0)))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("maxval",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0,
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_minval_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_minval_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_mod(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if ((is_integer_type(t0) 
                || is_floating_type(t0))
            && equivalent_types(get_unqualified_type(t0), 
                get_unqualified_type(t1)))
    {
        return GET_INTRINSIC_ELEMENTAL("mod", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_modulo(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if ((is_integer_type(t0) || is_floating_type(t0))
            && equivalent_types(get_unqualified_type(t0), 
                get_unqualified_type(t1)))
    {
        return GET_INTRINSIC_ELEMENTAL("modulo", t0, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_move_alloc(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    if (equivalent_types(get_unqualified_type(get_rank0_type(t0)), 
                get_unqualified_type(get_rank0_type(t1)))
                && (get_rank_of_type(t0) == get_rank_of_type(t1)))
    {
        return GET_INTRINSIC_PURE("move_alloc", /* subroutine */ NULL, t0, t1);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_mvbits(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);
    type_t* t3 = get_rank0_type(argument_types[3]);
    type_t* t4 = get_rank0_type(argument_types[4]);

    if (is_integer_type(t0)
            && is_integer_type(t1)
            && is_integer_type(t2)
            && is_integer_type(t3)
            && is_integer_type(t4))
    {
        return GET_INTRINSIC_ELEMENTAL("mvbits", /* subroutine */ NULL, t0, t1, t2, t3, t4);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_nearest(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_floating_type(t0)
            && is_floating_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("nearest", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_new_line(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_fortran_character_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("new_line", get_rank0_type(t0), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_nint(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int di = 4;

    if (is_floating_type(t0)
            && opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("nint", 
                choose_int_type_from_kind(argument_expressions[1], di), 
                t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_not(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("not", t0, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_norm2(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    if (is_fortran_array_type(t0)
            && is_floating_type(get_rank0_type(t0))
            && (t1 == NULL || is_integer_type(t1)))
    {
        if (t1 == NULL)
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("norm2", get_rank0_type(t0), t0);
        }
        else
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("norm2", 
                    get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context), 
                    t0, 
                    t1);
        }
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_null(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (t0 == NULL)
    {
        // Special case, return a void pointer and hope the receiving user will mold it to its type
        return get_intrinsic_symbol_("null", get_pointer_type(get_void_type()), 0, NULL, symbol->decl_context, 
                /* is_elemental */ 0, 
                /* is_pure */ 0, 
                /* is_transformational */ 1, 
                /* is_inquiry */ 0); 
    }
    else if (is_pointer_type(t0))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("null", t0, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_num_images(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_pack(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if (is_fortran_array_type(t0)
            && is_bool_type(get_rank0_type(t1)) 
            && are_conformable_types(t0, t1)
            && (t2 == NULL || 
                (equivalent_types(get_unqualified_type(get_rank0_type(t0)),
                                 get_unqualified_type(get_rank0_type(t2)))
                 && get_rank_of_type(t2) == 1)))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("pack", 
                t2 == NULL ? get_n_ranked_type(get_rank0_type(t0), 1, symbol->decl_context) : t2,
                t0,
                t1,
                t2 == NULL ? get_n_ranked_type(get_rank0_type(t0), 1, symbol->decl_context) : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_parity(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    if (is_fortran_array_type(t0)
            && is_bool_type(get_rank0_type(t0))
            && (t1 == NULL || is_integer_type(t1)))
    {
        if (t1 == NULL)
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("parity", get_rank0_type(t0), t0);
        }
        else
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("parity", 
                    get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context), 
                    t0, t1);
        }
    }


    return NULL;
}

scope_entry_t* compute_intrinsic_popcnt(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("popcnt", get_signed_int_type(), t0);
    } 

    return NULL;
}

scope_entry_t* compute_intrinsic_poppar(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("poppar", get_signed_int_type(), t0);
    } 

    return NULL;
}

scope_entry_t* compute_intrinsic_precision(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_complex_type(get_rank0_type(t0))
            || is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("precision", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_present(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    return GET_INTRINSIC_INQUIRY("present", get_bool_type(), t0);
}

scope_entry_t* compute_intrinsic_product_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];

    if (is_fortran_array_type(t0)
            && (is_integer_type(get_rank0_type(t0)) 
                || is_floating_type(get_rank0_type(t0)) 
                || is_complex_type(get_rank0_type(t0)))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("product",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0, 
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_product_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_product_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_radix(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_integer_type(get_rank0_type(t0))
            || is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("radix", get_signed_int_type(), t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_random_number(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_IMPURE("random_number", /* subroutine */ NULL, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_random_seed(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    int num_args = (t0 != NULL) + (t1 != NULL) + (t2 != NULL);

    if ((num_args == 0 || num_args == 1)
            && (t0 == NULL || is_integer_type(t0))
            && (t1 == NULL || (is_integer_type(get_rank0_type(t1)) && (get_rank_of_type(t1) == 1)))
            && (t2 == NULL || (is_integer_type(get_rank0_type(t2)) && (get_rank_of_type(t2) == 1))))
    {
        return GET_INTRINSIC_IMPURE("random_seed", 
                /* subroutine */ NULL,
                get_signed_int_type(),
                get_n_ranked_type(get_signed_int_type(), 1, symbol->decl_context),
                get_n_ranked_type(get_signed_int_type(), 1, symbol->decl_context));
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_range(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_integer_type(get_rank0_type(t0))
            || is_floating_type(get_rank0_type(t0))
            || is_complex_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_ELEMENTAL("range", get_signed_int_type(), t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_real(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    int dr = 4;
    if ((is_integer_type(t0)
            || is_floating_type(t0)
            || is_complex_type(t0))
            && opt_valid_kind_expr(argument_expressions[1], &dr))
    {
        return GET_INTRINSIC_ELEMENTAL("real", 
                choose_float_type_from_kind(argument_expressions[1], dr),
                t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_repeat(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    if (is_fortran_character_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("repeat", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_reshape(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // type_t* t0 = argument_types[0];
    // type_t* t1 = argument_types[1];
    // type_t* t2 = argument_types[2];
    // type_t* t3 = argument_types[3];

    // if (is_fortran_array_type(t0)
    //         && is_fortran_array_type(t1)
    //         && (get_rank_of_type(t1) == 1)
    //         && (t2 == NULL || 
    //             (is_fortran_array_type(t2) && equivalent_types(get_unqualified_type(get_rank0_type(t0)), 
    //                                    get_unqualified_type(get_rank0_type(t2)))))
    //         && (t3 == NULL || is_fortran_character_type(t3)))
    // {
    // }

    // FIXME - Needs a constant expression of type array
    // Not supported...
    return NULL;
}

scope_entry_t* compute_intrinsic_rrspacing(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("rrspacing", t0, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_same_type_as(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_scale(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_floating_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("scale", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_scan(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);
    // type_t* t3 = get_rank0_type(argument_types[3]);

    int di = 1;

    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1)
            && (t2 == NULL || is_bool_type(t1))
            && opt_valid_kind_expr(argument_expressions[3], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("scan", 
                choose_int_type_from_kind(argument_expressions[3], di),
                t0,
                t1, 
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_selected_char_kind(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_fortran_character_type(t0))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("selected_char_kind", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_selected_int_kind(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("selected_int_kind", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_selected_real_kind(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    int num_args = (t0 != NULL) + (t1 != NULL) + (t2 != NULL);

    if (num_args != 0
            && (t0 == NULL || is_integer_type(t0))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || is_integer_type(t2)))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("selected_real_kind", get_signed_int_type(), 
                t0 == NULL ? get_signed_int_type() : t0,
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_signed_int_type() : t2);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_set_exponent(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_floating_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("set_exponent", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_shape(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    int di = 4;
    if (opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_INQUIRY("shape", 
                get_n_ranked_type(choose_int_type_from_kind(argument_expressions[1], di), 1, symbol->decl_context),
                t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_shifta(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("shifta", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_shiftl(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("shiftl", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_shiftr(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if (is_integer_type(t0)
            && is_integer_type(t1))
    {
        return GET_INTRINSIC_ELEMENTAL("shiftr", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_sign(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);

    if ((is_integer_type(t0)
            || is_floating_type(t0))
            && (equivalent_types(get_unqualified_type(t0), 
                    get_unqualified_type(t1))))
    {
        return GET_INTRINSIC_ELEMENTAL("sign", t0, t0, t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_sin(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("sin", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_sinh(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("sinh", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_size(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    int di = 4;

    if (is_fortran_array_type(t0)
            && (t1 == NULL || is_integer_type(t1))
            && (opt_valid_kind_expr(argument_expressions[2], &di)))
    {
        return GET_INTRINSIC_INQUIRY("size", 
                choose_int_type_from_kind(argument_expressions[2], di),
                t0,
                t1 == NULL ? get_signed_int_type() : t1);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_spacing(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("spacing", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_spread(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if (is_fortran_array_type(t0)
            && is_integer_type(t1)
            && is_integer_type(t2))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("spread", 
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0), symbol->decl_context),
                t0, t1, t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_sqrt(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("sqrt", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_storage_size(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    int di = 4;
    if (opt_valid_kind_expr(argument_expressions[1], &di))
    {
        return GET_INTRINSIC_INQUIRY("storage_size", 
                choose_int_type_from_kind(argument_expressions[1], di),
                t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_sum_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = num_arguments == 3 ? argument_types[1] : NULL;
    type_t* t2 = num_arguments == 3 ? argument_types[2] : argument_types[1];

    if (is_fortran_array_type(t0)
            && (is_integer_type(get_rank0_type(t0)) 
                || is_floating_type(get_rank0_type(t0)) 
                || is_complex_type(get_rank0_type(t0)))
            && (t1 == NULL || is_integer_type(t1))
            && (t2 == NULL || (is_bool_type(get_rank0_type(t2)) && are_conformable_types(t2, t0))))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("sum",
                get_n_ranked_type(get_rank0_type(t0), get_rank_of_type(t0) - 1, symbol->decl_context),
                t0, 
                t1 == NULL ? get_signed_int_type() : t1,
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_sum_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    return compute_intrinsic_sum_0(symbol, argument_types, argument_expressions, num_arguments);
}

scope_entry_t* compute_intrinsic_system_clock(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if ((t0 == NULL || is_integer_type(t0))
            && (t1 == NULL || is_integer_type(t0) || is_floating_type(t0))
            && (t2 == NULL || is_integer_type(t2)))
    {
        return GET_INTRINSIC_IMPURE("system_clock", /*subroutine*/ NULL, 
                t0 == NULL ? get_signed_int_type() : t0, 
                t1 == NULL ? get_signed_int_type() : t1, 
                t2 == NULL ? get_signed_int_type() : t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_tan(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("tan", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_tanh(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);

    if (is_floating_type(t0)
            || is_complex_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("tanh", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_this_image_0(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_this_image_1(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_tiny(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    if (is_floating_type(get_rank0_type(t0)))
    {
        return GET_INTRINSIC_INQUIRY("tiny", get_rank0_type(t0), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_trailz(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    if (is_integer_type(t0))
    {
        return GET_INTRINSIC_ELEMENTAL("trailz", get_signed_int_type(), t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_transfer(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if (t2 == NULL || (is_integer_type(t2)))
    {
        if (!is_fortran_array_type(t1) 
                && t2 == NULL)
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("transfer", t1, t0, t1, get_signed_int_type());
        }
        else if (is_fortran_array_type(t2)
                && t2 == NULL)
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("transfer", 
                    get_n_ranked_type(get_rank0_type(t1), 1, symbol->decl_context),
                    t0, t1, get_signed_int_type());
        }
        else
        {
            return GET_INTRINSIC_TRANSFORMATIONAL("transfer", 
                    get_n_ranked_type(get_rank0_type(t1), 1, symbol->decl_context),
                    t0, t1, t2);
        }
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_transpose(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_fortran_array_type(t0)
            && get_rank_of_type(t0) == 2)
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("transpose", t0, t0);
    }
    return NULL;
}

scope_entry_t* compute_intrinsic_trim(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];

    if (is_fortran_character_type(t0))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("trim", t0, t0);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_ubound(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];

    int di = 4;

    if (is_fortran_array_type(t0)
            && (t1 == NULL || is_integer_type(t1))
            && (opt_valid_kind_expr(argument_expressions[2], &di)))
    {
        if (t1 != NULL)
        {
            return GET_INTRINSIC_INQUIRY("ubound",
                    choose_int_type_from_kind(argument_expressions[2], di),
                    t0, t1);
        }
        else
        {
            return GET_INTRINSIC_INQUIRY("ubound",
                    get_n_ranked_type(choose_int_type_from_kind(argument_expressions[2], di), 
                        get_rank_of_type(t0), 
                        symbol->decl_context),
                    t0);
        }
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_ucobound(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    // Not supported
    return NULL;
}

scope_entry_t* compute_intrinsic_unpack(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = argument_types[0];
    type_t* t1 = argument_types[1];
    type_t* t2 = argument_types[2];

    if (is_fortran_array_type(t0)
            && (get_rank_of_type(t0) == 1)
            && is_fortran_array_type(t1)
            && is_bool_type(get_rank0_type(t1))
            && equivalent_types(
                get_unqualified_type(get_rank0_type(t2)), 
                get_unqualified_type(get_rank0_type(t0)))
            && are_conformable_types(t2, t0))
    {
        return GET_INTRINSIC_TRANSFORMATIONAL("unpack", t0, t0, t1, t2);
    }

    return NULL;
}

scope_entry_t* compute_intrinsic_verify(scope_entry_t* symbol UNUSED_PARAMETER,
        type_t** argument_types UNUSED_PARAMETER,
        AST *argument_expressions UNUSED_PARAMETER,
        int num_arguments UNUSED_PARAMETER)
{
    type_t* t0 = get_rank0_type(argument_types[0]);
    type_t* t1 = get_rank0_type(argument_types[1]);
    type_t* t2 = get_rank0_type(argument_types[2]);

    int di = 4;
    if (is_fortran_character_type(t0)
            && is_fortran_character_type(t1)
            && (t2 == NULL || is_bool_type(t2))
            && opt_valid_kind_expr(argument_expressions[3], &di))
    {
        return GET_INTRINSIC_ELEMENTAL("verify",
                choose_int_type_from_kind(argument_expressions[3], di),
                t0,
                t1,
                t2 == NULL ? get_bool_type() : t2);
    }

    return NULL;
}


