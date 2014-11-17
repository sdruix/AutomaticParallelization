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
test_generator=config/mercurium
</testinfo>
*/

template <int _N1, typename _T1>
struct A
{
    typedef _T1 T1;
};

template <int _N2, typename _T2>
struct A<_N2, const _T2>
{
    typedef _T2 T2;
};

template <int _N3, typename _T3>
struct A<_N3, volatile _T3>
{
    typedef _T3 T3;
};

template <int _N4, typename _T4>
struct A<_N4, const volatile _T4>
{
    typedef _T4 T4;
};

A<3, int>::T1 t1;
A<3, const int>::T2 t2;
A<3, volatile int>::T3 t3;
A<3, const volatile int>::T4 t4;


