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

#include "tl-nanos.hpp"
#include "tl-omp-nanox.hpp"

namespace TL { namespace Nanox {

    void OMPTransform::single_postorder(PragmaCustomConstruct ctr)
    {
        Source transform_code;

        Source final_barrier;

        transform_code
            << "{"
            << get_single_guard("single_guard")
            << "if (err != NANOS_OK) nanos_handle_error(err);"

            << "if (single_guard)"
            << "{"
            <<     ctr.get_statement()
            << "}"

            // Final barrier of the whole team
            << final_barrier
            << "}"
            ;

        if (!ctr.get_clause("nowait").is_defined())
        {
            final_barrier
                << get_barrier_code(ctr.get_ast())
                ;
        }


        AST_t transform_tree 
            = transform_code.parse_statement(ctr.get_ast(), ctr.get_scope_link());

        ctr.get_ast().replace(transform_tree);
    }

    Source OMPTransform::get_single_guard(const std::string& str)
    {
        Source single_guard;
        Source bool_type;
        C_LANGUAGE()
        {
            bool_type << "_Bool";
        }
        CXX_LANGUAGE()
        {
            bool_type << "bool";
        }

        single_guard
            << bool_type << " " << str << ";"
            ;

        if (Nanos::Version::interface_is_at_least("openmp", 1))
        {
            single_guard
                << "nanos_err_t err = nanos_omp_single(&" << str << ");"
                ;
        }
        else
        {
            // Old routine, deprecated
            single_guard
                << "nanos_err_t err = nanos_single_guard(&" << str << ");"
                ;
        }

        return single_guard;
    }

}}

