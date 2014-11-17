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

test_exec_fail_nanos4_plain_1thread=yes
test_exec_faulty_nanos4_plain_1thread=yes
test_exec_fail_nanos4_plain_2thread=yes
test_exec_faulty_nanos4_plain_2thread=yes
test_exec_fail_nanos4_plain_4thread=yes
test_exec_faulty_nanos4_plain_4thread=yes

test_compile_fail_nanox_plain=yes
test_compile_faulty_nanox_plain=yes
test_compile_fail_nanox_instrument=yes
test_compile_faulty_nanox_instrument=yes
</testinfo>
*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEMS 100

int main(int argc, char* argv[])
{
    int i;
    int s = 0;

    // Remove me when reductions are working again
    do not compile);
    abort();
    // End of Remove me

    #pragma omp parallel shared(s)
    {
#pragma omp for reduction(+:s)
        for (i = 0; i < NUM_ELEMS; i++)
        {
            s = s + i;
        }
    }

    if (s != (((NUM_ELEMS - 1) * NUM_ELEMS) / 2))
    {
        fprintf(stderr, "s == %d != %d\n", s, (((NUM_ELEMS - 1) * NUM_ELEMS) / 2));
        abort();
    }

    return 0;
}
