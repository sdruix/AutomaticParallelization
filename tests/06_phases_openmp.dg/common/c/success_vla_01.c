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

#include <stdio.h>
#include <stdlib.h>

void f(int n, int m, int v[n + 1][m * 2])
{
#pragma omp task shared(v)
    {
        v[n-1][m-1] = 4;
    }
#pragma omp taskwait
}

void g(int n, int m, int v[n + 1][m * 2])
{
#pragma omp parallel shared(v) firstprivate(n, m)
    {
        v[n-1][m-1] = 3;
    }
}

int main(int argc, char *argv[])
{
    int c[2+1][3*2] = {0};

    g(2, 3, c);

    if (c[1][2] != 3)
    {
        fprintf(stderr, "c[1][2] != 3\n");
        abort();
    }

    f(2, 3, c);

    if (c[1][2] != 4)
    {
        fprintf(stderr, "c[1][2] != 4\n");
        abort();
    }

    return 0;
}
