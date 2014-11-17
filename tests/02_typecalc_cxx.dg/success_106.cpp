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

template <typename _T, typename _Q>
struct A
{
    typedef _T K1;
    template <bool _K>
        K1* f(K1)
        {
        }

    void g();
};

template <typename _T, typename _Q>
void A<_T, _Q>::g()
{
    int i;
    i = f<true>(3);
}

void h1(int*)
{
}

void h2(float*)
{
}

void m()
{
    A<int, float> c;
    A<float, float> d;

    h1(c.f<true>(3));
    h2(d.f<true>(4.3f));
}
