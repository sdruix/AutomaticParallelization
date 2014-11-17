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

struct C_tag
{
    float c;
};

typedef struct C_tag C;

typedef C *p_C;

typedef p_C p2_C;

void f(void)
{
    float f = 0.0f;
    double d = 0.0;

    struct C_tag *c1;

    c1->c = 3;
    c1->c = 3.4f;
    c1->c = 3.4;
    c1->c = f;
    c1->c = d;

    C *c2;

    c2->c = 3;
    c2->c = 3.4f;
    c2->c = 3.4;
    c2->c = f;
    c2->c = d;

    p_C c3;

    c3->c = 3;
    c3->c = 3.4f;
    c3->c = 3.4;
    c3->c = f;
    c3->c = d;

    p2_C c4;

    c4->c = 3;
    c4->c = 3.4f;
    c4->c = 3.4;
    c4->c = f;
    c4->c = d;
}
