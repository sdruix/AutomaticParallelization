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



#ifndef MCXX_REFCOUNT_H
#define MCXX_REFCOUNT_H

#include "libutils-common.h"
#include <stdlib.h>

typedef
enum _mcxx_ref_colour_tag
{
    _MCXX_BLACK, // In use or free
    _MCXX_GRAY, // Possible member of cycle
    _MCXX_WHITE, // Member of garbage cycle
    _MCXX_PURPLE, // Possible root of cycle
} _mcxx_ref_colour_t;

typedef void (*_mcxx_children_fun)(void *, void (*)(void*));

#define MCXX_REFCOUNT_OBJECT \
    int _mcxx_refcount; \
    int _mcxx_buffered; \
    _mcxx_ref_colour_t _mcxx_colour; \
    _mcxx_children_fun _mcxx_children

typedef
struct _mcxx_base_refcount_tag
{
    MCXX_REFCOUNT_OBJECT;
} *_p_mcxx_base_refcount_t, _mcxx_base_refcount_t;

LIBUTILS_EXTERN void *_mcxx_calloc(size_t nmemb, size_t size);

LIBUTILS_EXTERN void _mcxx_increment(void *p);
LIBUTILS_EXTERN void _mcxx_decrement(void *p);

LIBUTILS_EXTERN void _mcxx_collectcycles(void);
LIBUTILS_EXTERN _mcxx_children_fun *_mcxx_children(void *p);

#define MCXX_NEW(_type) (_type*)(_mcxx_calloc(1, sizeof(_type)))

#define MCXX_CHILDREN(x) (*_mcxx_children(x))

#define MCXX_INCREF(x) _mcxx_increment(x)

#define MCXX_DECREF(x) _mcxx_decrement(x)

// Sets 'x' to point 'y'
#define MCXX_UPDATE_TO(x, y) \
    do { \
        if ((x) != NULL) \
        { \
            MCXX_DECREF(x); \
        } \
        (x) = (y); \
        if ((x) != NULL) \
        { \
            MCXX_INCREF(x); \
        } \
    } while (0)

#endif // MCXX_REFCOUNT_H
