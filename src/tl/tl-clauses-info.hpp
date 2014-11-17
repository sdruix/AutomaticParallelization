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



#ifndef TL_CLAUSESINFO_HPP
#define TL_CLAUSESINFO_HPP

#include <string>

#include "tl-type.hpp"
#include "tl-pragmasupport.hpp"

namespace TL
{
    class PragmaCustomConstruct;

    class LIBTL_CLASS ClausesInfo : public Object
    {
		private:
            //! struct that stores clauses related to a directive
			struct DirectiveClauses
			{
				ObjectList<std::string> referenced_clauses;
				ObjectList<std::string> all_clauses;
                std::string file;
                std::string line;
                std::string pragma;
			};

            //! Keys of clauses for each directive
			std::map<AST_t, DirectiveClauses> _directive_clauses_map;
            
            DirectiveClauses& lookup_map(AST_t a);
            
		public:
            //! Default constructor
            ClausesInfo();

            //! Store in the map 'directive_clauses_map' all possible clauses related to /a directive
            void set_all_clauses(AST_t directive, ObjectList<std::string> all_clauses);

            //! Add clause that is used to /a directive
            /*!
              This method is called each time a PragmaCustomConstruct calls the method get_clause()
              */
		    void add_referenced_clause(AST_t directive, std::string clause_name);
        
            void add_referenced_clause(AST_t directive, const ObjectList<std::string> & clause_names);

            //! Add the locus info (file and line) to the a/ directive entry of _directive_clauses_map
            void set_locus_info(AST_t directive);

            void set_pragma(const PragmaCustomConstruct& directive);

            //! Concludes if /a directive is already defined in _directive_clauses_map
            bool directive_already_defined(AST_t directive);

            //! Return all clauses related to /a directive that hasn't been used during the execution
		    ObjectList<std::string> get_unreferenced_clauses(AST_t directive);

            //! Return the file and line where /a directive was declared
		    std::string get_locus_info(AST_t directive);

            //! Return the pragma for which /a directive was declared
		    std::string get_pragma(AST_t directive);
    };
}

#endif // TL_CLAUSESINFO_HPP
