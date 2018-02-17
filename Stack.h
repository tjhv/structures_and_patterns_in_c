//
// Created by Thomas Huddleston on 2/16/17.
//

#ifndef DEVPROJ_STACK_H
#define DEVPROJ_STACK_H

#include "../Object.h"
#include "../Iterator.h"
#include "Vector.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	k_vector_t *vector;
} k_stack_t, Stack_t;

typedef struct
{
	void            (* push)        (k_stack_t *,
	                                 k_object_t *);
	k_object_t *    (* pop)         (k_stack_t *);
	k_object_t *    (* peek)        (k_stack_t *);
	bool            (* is_empty)    (k_stack_t *);
	bool            (* contains)    (k_stack_t *,
					 k_object_t *);
	void            (* clear)       (k_stack_t *);
	uint16_t        (* count)       (k_stack_t *);
	uint16_t        (* capacity)    (k_stack_t *);
	k_iterator_t *  (* iterator)    (k_stack_t *);
} k_stack_vtbl_t;

extern const k_stack_vtbl_t Stack;

#endif //DEVPROJ_STACK_H
