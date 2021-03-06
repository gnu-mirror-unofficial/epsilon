/* The main runtime header #include'ing the others.

   Copyright (C) 2012 Universit√© Paris 13
   Copyright (C) 2012 Luca Saiu
   Updated in 2015 by Luca Saiu
   Written by Luca Saiu

   This file is part of GNU epsilon.

   GNU epsilon is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GNU epsilon is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GNU epsilon.  If not, see <http://www.gnu.org/licenses/>. */


#include <stdio.h>

#include "thread-context.h"
#include "utility/malloc.h"

#ifdef EPSILON_EGC
#include "movinggc/movinggc.h"
#endif // #ifdef EPSILON_EGC

#define EPSILON_STACK_ELEMENT_NO (1 << 12)

// FIXME: add support for the epsilon GC

epsilon_thread_context_t epsilon_make_thread_context(void){
#ifdef EPSILON_EGC
  epsilon_thread_context_t result =
    epsilon_xmalloc (sizeof (struct epsilon_thread_context));
  result->stack = epsilon_xmalloc (sizeof(epsilon_value) * EPSILON_STACK_ELEMENT_NO);
#else
  epsilon_thread_context_t result = GC_malloc(sizeof(struct epsilon_thread_context));
  result->stack = GC_malloc(sizeof(epsilon_value) * EPSILON_STACK_ELEMENT_NO);
#endif // #ifdef EPSILON_EGC
  /* int i; */
  /* for(i = 0; i < EPSILON_STACK_ELEMENT_NO; i ++) */
  /*   result->stack[i] = (epsilon_value)(long)0xdead; */

  /* Ensure that stack limits are 8-byte aligned.  This is needed or
     at least recommended for most architectures: */
  char *stack_lowest_address = (char*)result->stack;
  char *stack_highest_address = (char*)(result->stack + EPSILON_STACK_ELEMENT_NO - 1);
  while(((long)stack_lowest_address) % 8) stack_lowest_address ++;
  while(((long)stack_highest_address) % 8) stack_highest_address --;
  result->stack_lowest_address = (epsilon_value*)stack_lowest_address;
  result->stack_highest_address = (epsilon_value*)stack_highest_address;

  return result;
}

void epsilon_destroy_thread_context (epsilon_thread_context_t context){
#ifdef EPSILON_EGC
  free (context->stack);
  free (context);
  printf ("Hoo-hoo\n");
#endif // #ifdef EPSILON_EGC
}
