//
// Created by Thomas Huddleston on 2/16/17.
//

#include "Queue.h"

#include <assert.h>

static void             k_queue_enqueue         (k_queue_t *,
						 k_object_t *);
static k_object_t *     k_queue_dequeue         (k_queue_t *);
static k_object_t *     k_queue_peek            (k_queue_t *);
static bool             k_queue_is_empty        (k_queue_t *);
static bool             k_queue_contains        (k_queue_t *,
						 k_object_t *);
static void             k_queue_clear           (k_queue_t *);
static uint16_t         k_queue_count           (k_queue_t *);
static uint16_t         k_queue_capacity        (k_queue_t *);
static k_iterator_t *   k_queue_iterator        (k_queue_t *);

const k_queue_vtbl_t    Queue = {
	.enqueue        =       &k_queue_enqueue,
	.dequeue        =       &k_queue_dequeue,
	.peek           =       &k_queue_peek,
	.is_empty       =       &k_queue_is_empty,
	.contains       =       &k_queue_contains,
	.clear          =       &k_queue_clear,
	.count          =       &k_queue_count,
	.capacity       =       &k_queue_capacity,
	.iterator       =       &k_queue_iterator
};

static void             k_queue_enqueue         (k_queue_t *self,
                                                 k_object_t *obj)
{
	assert(self && self->vector && obj && Vector.append);
	Vector.append(self->vector, obj);
}

static k_object_t *     k_queue_dequeue         (k_queue_t *self)
{
	assert(self && self->vector && Vector.remove && Vector.get);
	/**
	 * Dequeue removes from front
	 */
	int32_t idx;
	if((idx = Vector.remove(self->vector, k_queue_peek(self))) < 0)
		return NULL;
	return Vector.get(self->vector, (uint16_t)idx);
}

static k_object_t *     k_queue_peek            (k_queue_t *self)
{
	assert(self && self->vector && Vector.first);
	return Vector.first(self->vector);
}

static bool             k_queue_is_empty        (k_queue_t *self)
{
	assert(self && self->vector && Vector.is_empty);
	return Vector.is_empty(self->vector);
}

static bool             k_queue_contains        (k_queue_t *self,
                                                 k_object_t *obj)
{
	assert(self && self->vector && obj && Vector.contains);
	return Vector.contains(self->vector, obj);
}

static void             k_queue_clear           (k_queue_t *self)
{
	assert(self && self->vector && Vector.clear);
	Vector.clear(self->vector);
}

static uint16_t         k_queue_count           (k_queue_t *self)
{
	assert(self && self->vector && Vector.count);
	return Vector.count(self->vector);
}

static uint16_t         k_queue_capacity        (k_queue_t *self)
{
	assert(self && self->vector && Vector.capacity);
	return Vector.capacity(self->vector);
}

static k_iterator_t *   k_queue_iterator        (k_queue_t *self)
{
	assert(self && self->vector && Vector.iterator);
	return Vector.iterator(self->vector);
}