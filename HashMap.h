//
// Created by Thomas Huddleston on 2/16/17.
//

#ifndef DEVPROJ_HASH_H
#define DEVPROJ_HASH_H

//hash, rehash, add, remove, is_empty, empty, find, contains

#include <stdbool.h>
#include <stdint.h>

//hash map implements linked list chaining for collisions

typedef struct
{
	uint16_t size;
	uint16_t count;
} k_hashmap_t;

typedef struct
{
	uint16_t (* hash)    (k_hashmap_t *,
	                      void *);
	void     (* rehash)  (k_hashmap_t *);
	void     (* add)     (k_hashmap_t *,
	                      void *);
	void     (* remove)  (k_hashmap_t *,
	                      void *);
	bool     (* is_empty)(k_hashmap_t *);
	void     (* empty)   (k_hashmap_t *);
	uint16_t (* find)    (k_hashmap_t *,
	                      void *);
	bool     (* contains)(k_hashmap_t *,
	                      void *);
	void *   (* get)     (k_hashmap_t *,
	                      uint16_t);
} k_hashmap_vtbl_t;

extern const k_hashmap_vtbl_t HashMap;

#endif //DEVPROJ_HASH_H
