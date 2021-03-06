/* Hash tables with string keys.

   Copyright (C) 2012 Universit√© Paris 13
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


#ifndef EPSILON_STRING_HASH_H_
#define EPSILON_STRING_HASH_H_

/* [...]
 */

#include <stdbool.h>
#include "types.h"

/* String hashes use strings as keys: */
typedef char* epsilon_string_hash_key;

/* Data are just generic pointers.  Usefully if data are always
   non-NULL then epsilon_string_hash_lookup can be used without
   botering to check whether a key is bound. */
typedef epsilon_word epsilon_string_hash_datum;

typedef struct epsilon_string_hash_bucket* epsilon_string_hash_bucket_t;
struct epsilon_string_hash_bucket{
  epsilon_string_hash_key key_copy; // this is a malloc()ed copy
  epsilon_string_hash_datum datum;
  epsilon_string_hash_bucket_t next;
}; // struct

struct epsilon_string_hash{
  epsilon_string_hash_bucket_t *buckets;
  int bucket_no;
  int binding_no;
}; // struct
typedef struct epsilon_string_hash* epsilon_string_hash_t;

/* Initialize or finalize an already allocated struct.  This is useful for
   auto or static structs, which have the potential of being more efficient
   than struct pointers. */
void epsilon_initialize_string_hash(epsilon_string_hash_t hash)
  __attribute__(( cold ));
void epsilon_finalize_string_hash(epsilon_string_hash_t hash)
  __attribute__(( cold ));

/* Finalze the hash.  Before de-allocating items, also call the given destroyer
   function on each datum: */
void epsilon_destroy_string_hash_with_datum_destructor(epsilon_string_hash_t hash,
                                                       void (*destroy_datum)(epsilon_string_hash_datum))
  __attribute__(( cold ));

/* Create or destroy a string hash: */
epsilon_string_hash_t epsilon_make_string_hash(void) __attribute__(( cold ));
void epsilon_destroy_string_hash(epsilon_string_hash_t hash) __attribute__(( cold ));

/* Destroy the hash.  Before de-allocating, also call the given destroyer
   function on each datum: */
void epsilon_destroy_string_hash_with_datum_destructor(epsilon_string_hash_t hash,
                                                       void (*destroy_datum)(epsilon_string_hash_datum))
  __attribute__(( cold ));

/* Add a new binding to a hash: */
void epsilon_add_to_string_hash(epsilon_string_hash_t hash,
                                epsilon_string_hash_key key,
                                epsilon_string_hash_datum datum)
  __attribute__(( hot ));

/* Lookup the given hash by looking for a binding of the given key.
   If at least one binding exists then return one of the keys (it's undefined
   which one); otherwise return NULL. */
epsilon_string_hash_datum epsilon_lookup_string_hash(epsilon_string_hash_t hash,
                                                     epsilon_string_hash_key key)
  __attribute__(( hot ));

/* Return true iff the given hash is bound on the given key.  This may
   be useful for non-NULL data. */
bool epsilon_is_string_hash_bound_on(epsilon_string_hash_t hash,
                                     epsilon_string_hash_key key)
  __attribute__(( hot ));

/* Remove the first binding for the given key from a hash: */
void epsilon_remove_from_string_hash(epsilon_string_hash_t hash,
                                     epsilon_string_hash_key key)
  __attribute__(( hot ));
void epsilon_remove_from_string_hash_with_datum_destructor(epsilon_string_hash_t hash,
                                                           epsilon_string_hash_key key,
                                                           void (*destroy_datum)(epsilon_string_hash_datum))
  __attribute__(( hot ));

#endif // #ifndef EPSILON_STRING_HASH_H_
