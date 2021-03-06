##########################################################################
#  (C) Copyright 2006-2011 Barcelona Supercomputing Center               #
#                          Centro Nacional de Supercomputacion           #
#                                                                        #
#  This file is part of Mercurium C/C++ source-to-source compiler.       #
#                                                                        #
#  See AUTHORS file in the top level directory for information           #
#  regarding developers and contributors.                                #
#                                                                        #
#  This library is free software; you can redistribute it and/or         #
#  modify it under the terms of the GNU Lesser General Public            #
#  License as published by the Free Software Foundation; either          #
#  version 3 of the License, or (at your option) any later version.      #
#                                                                        #
#  Mercurium C/C++ source-to-source compiler is distributed in the hope  #
#  that it will be useful, but WITHOUT ANY WARRANTY; without even the    #
#  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       #
#  PURPOSE.  See the GNU Lesser General Public License for more          #
#  details.                                                              #
#                                                                        #
#  You should have received a copy of the GNU Lesser General Public      #
#  License along with Mercurium C/C++ source-to-source compiler; if      #
#  not, write to the Free Software Foundation, Inc., 675 Mass Ave,       #
#  Cambridge, MA 02139, USA.                                             #
##########################################################################

SUBDIRS = . hlt manip @TL_EXTENSIONS@ 

END=

DIST_SUBDIRS=omp \
             superscalar \
             instr \
             instr_pthreads \
             stm_func \
             examples \
             testing \
             hlt \
             ss_valgrind \
             manip \
             $(END)

lib_LTLIBRARIES = libtl.la

BUILT_SOURCES=
BUILT_SOURCES += $(top_builddir)/src/frontend/cxx-asttype.h 
BUILT_SOURCES += tl-lexer-tokens.hpp

CLEANFILES =
CLEANFILES += tl-lexer-tokens.hpp

COMMON_CFLAGS= -DLIBTL_DLL_EXPORT -Wall \
    -I $(top_srcdir)/src/frontend \
    -I $(top_srcdir)/src/frontend/fortran \
    -I $(top_srcdir)/src/driver \
    -I $(top_srcdir)/lib \
    -I $(top_builddir)/src/frontend \
    -I $(top_builddir)/src/frontend/fortran \
    -I $(top_builddir)/src/driver \
    -I $(top_builddir)/lib \
    $(END)

libtl_la_CFLAGS = $(COMMON_CFLAGS)
libtl_la_CXXFLAGS = $(COMMON_CFLAGS)

EXTRA_DIST=Makefile.phases \
           $(END)

libtl_la_SOURCES = \
    tl-object.hpp \
    tl-object.cpp \
    tl-builtin.hpp \
    tl-builtin.cpp \
    tl-ast.hpp \
    tl-ast.cpp \
    tl-scope.hpp \
    tl-scope.cpp \
	tl-scopelink.hpp \
	tl-scopelink.cpp \
    tl-dto.hpp \
    tl-dto.cpp \
	tl-symbol.hpp \
	tl-symbol.cpp \
    tl-compilerphase.hpp \
    tl-compilerphase.cpp \
	tl-lexer.hpp \
	tl-lexer.cpp \
	tl-lexer-tokens.hpp \
	tl-source.hpp \
	tl-source.cpp \
	tl-type.hpp \
	tl-type.cpp \
    tl-overload.cpp \
    tl-overload.hpp \
	tl-traverse.hpp \
	tl-traverse.cpp \
	tl-context.hpp \
	tl-context.cpp \
	tl-objectlist.hpp \
	tl-objectlist.cpp \
	tl-predicate.hpp \
	tl-predicate.cpp \
	tl-functor.hpp \
	tl-functor.cpp \
	tl-predicateutils.hpp \
	tl-predicateutils.cpp \
	tl-langconstruct.hpp \
	tl-langconstruct.cpp \
	tl-statement.hpp \
	tl-statement.cpp \
	tl-externalvars.hpp \
	tl-externalvars.cpp \
	tl-handler.hpp \
	tl-handler.cpp \
	tl-pragmasupport.hpp \
	tl-pragmasupport.cpp \
	tl-refptr.hpp \
	tl-multifile.hpp \
	tl-multifile.cpp \
	tl-compilerpipeline.cpp \
	tl-compilerpipeline.hpp \
	tl-declarationclosure.hpp \
	tl-declarationclosure.cpp \
	tl-static-callgraph.hpp \
	tl-static-callgraph.cpp \
    tl-common.hpp \
    tl-for-nest.hpp \
    tl-for-nest.cpp \
    tl-counters.hpp \
    tl-counters.cpp \
    tl-templates.hpp \
    tl-templates.cpp \
    tl-datareference.hpp \
    tl-datareference.cpp \
    tl-clauses-info.hpp \
    tl-clauses-info.cpp \
    tl-setdto-phase.hpp \
    tl-setdto-phase.cpp \
    tl-fortran.hpp \
    tl-fortran.cpp \
    tl-simd.hpp \
    tl-simd.cpp \
	tl-cuda.hpp \
	tl-cuda.cpp \
	$(END)

if WINDOWS_BUILD
no_undefined=-no-undefined
else
no_undefined=
endif

PARSER_INFO_C=$(builddir)/../frontend/c99-parser-internal.h
PARSER_INFO_CXX=$(builddir)/../frontend/cxx-parser-internal.h
if FORTRAN_SUPPORT
PARSER_INFO_FORTRAN=$(builddir)/../frontend/fortran/fortran03-parser-internal.h
endif

# Flex makes things very difficult
tl-lexer-tokens.hpp : $(PARSER_INFO_C) $(PARSER_INFO_CXX) $(PARSER_INFO_FORTRAN)
	$(AM_V_GEN)((\
	 echo "#ifndef TL_LEXER_TOKENS_HPP" ; \
	 echo "#define TL_LEXER_TOKENS_HPP" ; \
	 echo "namespace TL {"  ; \
	 echo "namespace TokensC {"  ; \
	 $(SED) -n '/enum\s\+yytokentype/,/}/p' $(PARSER_INFO_C) ; \
	 echo "}"  ; \
	 echo "namespace TokensCXX {" ; \
	 $(SED) -n '/enum\s\+yytokentype/,/}/p' $(PARSER_INFO_CXX) ; \
	 echo "}"  ; \
	 if [ -e "$(PARSER_INFO_FORTRAN)" ]; then \
	    echo "namespace TokensFortran {"  ; \
	    $(SED) -n '/enum\s\+yytokentype/,/}/p' $(PARSER_INFO_FORTRAN) ; \
	    echo "}"  ; \
	 fi; \
	 echo "}";  \
	 echo "#endif // TL_LEXER_TOKENS_HPP" ; \
	) > $@)

libtl_la_LDFLAGS = -avoid-version $(no_undefined)
libtl_la_LIBADD = \
	$(top_builddir)/lib/libmcxx-extstruct.la \
	$(top_builddir)/lib/libmcxx-utils.la \
	$(top_builddir)/src/frontend/libmcxx-process.la \
	$(top_builddir)/src/frontend/libmcxx.la \
	$(END)

if FORTRAN_SUPPORT
libtl_la_LIBADD += $(top_builddir)/src/frontend/fortran/libmf03.la
endif
