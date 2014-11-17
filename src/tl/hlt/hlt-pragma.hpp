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



#ifndef HLT_PRAGMA_HPP
#define HLT_PRAGMA_HPP

#include "tl-pragmasupport.hpp"

namespace TL
{
    namespace HLT
    {
        //! \addtogroup HLT High Level Transformations
        //! @{

        //! Compiler phase that implements a pragma interface to the HLT transformations
        /*!
          This class implements several pragmas

          \code
#pragma hlt unroll factor(N)
  regular-for-loop
          \endcode
          \sa TL::HLT::LoopUnroll

          \code
#pragma hlt block factors(expr-list)
  perfect-loop-nest
          \endcode
          \sa TL::HLT::LoopBlocking

          \code
#pragma hlt stripmine amount(expr)
  regular-for-loop
          \endcode
          \sa TL::HLT::StripMine

          \code
#pragma hlt distribute expand(var-list)
  regular-for-loop
          \endcode
          \sa TL::HLT::LoopDistribution

          \code
#pragma hlt fusion
  compound-statement
          \endcode
          \sa TL::HLT::LoopFusion

          \code
#pragma hlt interchange permutation(perm{1..N})
  perfect-loop-nest
          \endcode
          \sa TL::HLT::LoopInterchange

          \code
#pragma hlt collapse
  perfect-loop-nest
          \endcode
          \sa TL::HLT::LoopCollapse
            
          \code
#pragma hlt outline
  statement
          \endcode
          \sa TL::HLT::Outline

          \code
#pragma hlt extend
  function-definition
          \endcode
          \sa TL::HLT::FunctionExtension

          \code
#pragma hlt simd (var-list)
  regular-for-loop
          \endcode
          \sa TL::HLT::LoopSimdization

          */
        class HLTPragmaPhase : public PragmaCustomCompilerPhase
        {
            public:
                HLTPragmaPhase();
                virtual void run(TL::DTO& dto);
            private:
                void unroll_loop(PragmaCustomConstruct construct);
                void block_loop(PragmaCustomConstruct construct);
                void stripmine_loop(PragmaCustomConstruct construct);
                void distribute_loop(PragmaCustomConstruct construct);

                void pre_fuse_loops(PragmaCustomConstruct construct);
                void fuse_loops(PragmaCustomConstruct construct);

                void interchange_loops(PragmaCustomConstruct construct);
                void collapse_loop(PragmaCustomConstruct construct);

                void jam_loops(Statement unrolled_loop);

                void outline_code(PragmaCustomConstruct construct);

                void extend_function(PragmaCustomConstruct construct);

                void peel_loop(PragmaCustomConstruct construct);

                void task_aggregate(PragmaCustomConstruct construct);

                void set_instrument_hlt(const std::string &str);
                void set_acml_hlt(const std::string &str);
                void set_intermediate_simd_prettyprint(const std::string &str);

                void simd_pre_run(AST_t translation_unit, ScopeLink scope_link);
                void simdize(PragmaCustomConstruct construct);

                std::string _enable_hlt_instr_str;
                std::string _enable_hlt_acml_str;
                std::string _enable_hlt_intermediate_simd_prettyprint;
        };

        bool enable_acml_library = false;
        bool enable_interm_simd_prettyprint = false;

        //! @}
    }

}

#endif // HLT_PRAGMA_HPP
