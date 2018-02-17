//
// Created by Thomas Huddleston on 2/16/17.
//

#ifndef DEVPROJ_QUEUE_H
#define DEVPROJ_QUEUE_H

#include "../Object.h"
#include "../Iterator.h"
#include "Vector.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	k_vector_t *vector;
} k_queue_t, Queue_t;

typedef struct
{
	void            (* enqueue)     (k_queue_t *,
	                                 k_object_t *);
	k_object_t *    (* dequeue)     (k_queue_t *);
	k_object_t *    (* peek)        (k_queue_t *);
	bool            (* is_empty)    (k_queue_t *);
	bool            (* contains)    (k_queue_t *,
	                                 k_object_t *);
	void            (* clear)       (k_queue_t *);
	uint16_t        (* count)       (k_queue_t *);
	uint16_t        (* capacity)    (k_queue_t *);
	k_iterator_t *  (* iterator)    (k_queue_t *);
} k_queue_vtbl_t;

extern const k_queue_vtbl_t Queue;

#endif //DEVPROJ_QUEUE_H
