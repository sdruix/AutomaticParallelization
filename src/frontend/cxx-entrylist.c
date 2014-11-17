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


#include "cxx-entrylist.h"
#include "cxx-utils.h"
#include <string.h>
#include <stdint.h>

#define NUM_IMMEDIATE 4

unsigned long long _bytes_entry_lists;

struct scope_entry_list_tag
{
    unsigned short num_items_list;
    scope_entry_t* list[NUM_IMMEDIATE];
    scope_entry_list_t* next;
};

static scope_entry_list_t* entry_list_allocate(void)
{
    return counted_calloc(1, sizeof(scope_entry_list_t), &_bytes_entry_lists);
}

scope_entry_list_t* entry_list_new(scope_entry_t* entry)
{
    scope_entry_list_t* result = entry_list_allocate();
    result->num_items_list = 1;
    result->list[0] = entry;

    return result;
}

static void entry_list_add_to_pos(scope_entry_list_t* list, 
        scope_entry_t* entry, int num_pos)
{
    if (num_pos < NUM_IMMEDIATE)
    {
        list->list[num_pos] = entry;
    }
    else
    {
        if (list->next != NULL)
        {
            entry_list_add_to_pos(list->next, entry, num_pos - NUM_IMMEDIATE);
        }
        else
        {
            scope_entry_list_t* new_entry_list = entry_list_allocate();
            list->next = new_entry_list;
            entry_list_add_to_pos(new_entry_list, entry, num_pos - NUM_IMMEDIATE);
        }
    }
}

scope_entry_list_t* entry_list_add(scope_entry_list_t* list, 
        scope_entry_t* entry)
{
    if (list == NULL)
    {
        return entry_list_new(entry);
    }

    entry_list_add_to_pos(list, entry, list->num_items_list);
    list->num_items_list++;

    return list;
}

scope_entry_list_t* entry_list_copy(const scope_entry_list_t* list)
{
    scope_entry_list_t* result = NULL;

    scope_entry_list_iterator_t* it = NULL;
    for (it = entry_list_iterator_begin(list);
            !entry_list_iterator_end(it);
            entry_list_iterator_next(it))
    {
        result = entry_list_add(result, entry_list_iterator_current(it));
    }
    entry_list_iterator_free(it);

    return result;
}

void entry_list_free(scope_entry_list_t* list)
{
    if (list == NULL)
        return;

    entry_list_free(list->next);

    memset(list, 0, sizeof(*list));
    // Magic number to quickly pinpoint double freed lists
    list->num_items_list = 0xCEBA;

    free(list);
}

// -

unsigned int entry_list_size(const scope_entry_list_t* list)
{
    return list->num_items_list;
}

scope_entry_t* entry_list_head(const scope_entry_list_t* list)
{
    return list->list[0];
}

// -

struct scope_entry_list_iterator_tag
{
    int current_pos;
    int total_pos;
    const scope_entry_list_t* current_list;
    const scope_entry_list_t* first_list;
};

static scope_entry_list_iterator_t* entry_list_iterator_allocate(void)
{
    return counted_calloc(1, sizeof(scope_entry_list_iterator_t), &_bytes_entry_lists);
}

scope_entry_list_iterator_t* entry_list_iterator_begin(const scope_entry_list_t* list)
{
    scope_entry_list_iterator_t* result = entry_list_iterator_allocate();
    result->current_list = list;
    result->first_list = list;
    result->current_pos = 0;
    result->total_pos = 0;

    return result;
}

scope_entry_t* entry_list_iterator_current(scope_entry_list_iterator_t* it)
{
    return it->current_list->list[it->current_pos];
}

void entry_list_iterator_next(scope_entry_list_iterator_t* it)
{
    it->current_pos++;
    it->total_pos++;
    if (it->current_pos == NUM_IMMEDIATE)
    {
        it->current_pos = 0;
        it->current_list = it->current_list->next;
    }
}

char entry_list_iterator_end(scope_entry_list_iterator_t* it)
{
    return (it->first_list == NULL
            || (it->total_pos >= it->first_list->num_items_list));
}

void entry_list_iterator_free(scope_entry_list_iterator_t* it)
{
    if (it != NULL)
    {
        memset(it, 0, sizeof(*it));
        free(it);
    }
}

static int ptr_comp(const void* p1, const void* p2)
{
    intptr_t i1 = (intptr_t)p1;
    intptr_t i2 = (intptr_t)p2;
    
    if (i1 < i2)
        return -1;
    else if (i1 > i2)
        return 1;
    else
        return 0;
}

scope_entry_list_t* entry_list_merge(const scope_entry_list_t* list1, 
        const scope_entry_list_t* list2)
{
    int size1 = (list1 != NULL ? entry_list_size(list1) : 0);
    scope_entry_t* elems1[size1 + 1];
    memset(elems1, 0, sizeof(elems1));
    scope_entry_t** p = elems1;

    scope_entry_list_iterator_t* it = NULL;
    for (it = entry_list_iterator_begin(list1);
            !entry_list_iterator_end(it);
            entry_list_iterator_next(it))
    {
        scope_entry_t* entry = entry_list_iterator_current(it);
        *p = entry;
        p++;
    }
    entry_list_iterator_free(it);

    int size2 = (list2 != NULL ? entry_list_size(list2) : 0);
    scope_entry_t* elems2[size2 + 1];
    memset(elems2, 0, sizeof(elems2));
    scope_entry_t** q = elems2;

    for (it = entry_list_iterator_begin(list2);
            !entry_list_iterator_end(it);
            entry_list_iterator_next(it))
    {
        scope_entry_t* entry = entry_list_iterator_current(it);
        *q = entry;
        q++;
    }
    entry_list_iterator_free(it);

    //   void qsort(void *base, size_t nmemb, size_t size,
    //  int(*compar)(const void *, const void *));
    qsort(elems1, size1, sizeof(*list1), ptr_comp);
    qsort(elems2, size2, sizeof(*list2), ptr_comp);

    p = elems1;
    q = elems2;

    scope_entry_list_t* result = NULL;

    while (*p != NULL
            && *q != NULL)
    {
        // Advance repeated elements inside each list
        // (they will be grouped together, right?)
        while (*p == *(p+1))
            p++;
        while (*q == *(q+1))
            q++;

        if (*p < *q)
        {
            result = entry_list_add(result, *p);
            p++;
        }
        else if (*q < *p)
        {
            result = entry_list_add(result, *q);
            q++;
        }
        else
        {
            // They are equal, add it just once
            result = entry_list_add(result, *p);
            p++;
            q++;
        }
    }

    while (*p != NULL)
    {
        result = entry_list_add(result, *p);
        p++;
    }
    while (*q != NULL)
    {
        result = entry_list_add(result, *q);
        q++;
    }

    return result;
}
