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



#include "tl-omptransform.hpp"

namespace TL
{
    namespace Nanos4
    {
        void OpenMPTransform::ordered_postorder(PragmaCustomConstruct ordered_construct)
        {
            running_error("%s: error: '#pragma omp ordered' is not supported",
                    ordered_construct.get_ast().get_locus().c_str());
            /* 
            Symbol induction_var = induction_var_stack.top();

            Statement construct_body = ordered_construct.get_statement();
            Source ordered_source;

            ordered_source
                << "{"
                <<   "in__tone_enter_ordered_ (& "<< induction_var.get_name() << ");"
                <<   construct_body.prettyprint()
                <<   "in__tone_leave_ordered_ (&" << induction_var.get_name() << ");"
                << "}"
                ;

            AST_t ordered_code = ordered_source.parse_statement(ordered_construct.get_ast(),
                    ordered_construct.get_scope_link());

            ordered_construct.get_ast().replace(ordered_code);
            */
        }
    }
}

