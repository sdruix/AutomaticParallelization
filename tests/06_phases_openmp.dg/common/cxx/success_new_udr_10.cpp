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


/*
<testinfo>
test_generator=config/mercurium-omp

test_exec_fail_nanox_plain_1thread=yes
test_exec_faulty_nanox_plain_1thread=yes
test_exec_fail_nanox_plain_2thread=yes
test_exec_faulty_nanox_plain_2thread=yes
test_exec_fail_nanox_plain_4thread=yes
test_exec_faulty_nanox_plain_4thread=yes

test_exec_fail_nanox_instrument_1thread=yes
test_exec_faulty_nanox_instrument_1thread=yes
test_exec_fail_nanox_instrument_2thread=yes
test_exec_faulty_nanox_instrument_2thread=yes
test_exec_fail_nanox_instrument_4thread=yes
test_exec_faulty_nanox_instrument_4thread=yes

</testinfo>
*/

#include <stdlib.h>
#include "omp.h"

typedef struct {
  int x ;
  int y ;
} point_t;

int max(int x, int y ) 
{
    ( x ) > ( y ) ? ( x ) : ( y ) ;
}

#pragma omp declare reduction( maxarea : point_t : \
_out.x = max(_out.x , _in.x ), _out.y = max(_out.y , _in.y ) ) \
identity( {0 ,0} )

int main (int argc, char* argv[])
{
   point_t pt;

   #pragma omp parallel reduction (maxarea : pt)
   pt;

   abort();

   return 0;
}
