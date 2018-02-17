//
// Created by Thomas Huddleston on 2/16/17.
//

#include "Stack.h"

#include <assert.h>

static void             k_stack_push            (k_stack_t *,
                                                 k_object_t *);
static k_object_t *     k_stack_pop             (k_stack_t *);
static k_object_t *     k_stack_peek            (k_stack_t *);
static bool             k_stack_is_empty        (k_stack_t *);
static bool             k_stack_contains        (k_stack_t *,
                                                 k_object_t *);
static void             k_stack_clear           (k_stack_t *);
static uint16_t         k_stack_count           (k_stack_t *);
static uint16_t         k_stack_capacity        (k_stack_t *);
static k_iterator_t *   k_stack_iterator        (k_stack_t *);

const k_stack_vtbl_t    Stack = {
	.push           =       &k_stack_push,
	.pop            =       &k_stack_pop,
	.peek           =       &k_stack_peek,
	.is_empty       =       &k_stack_is_empty,
	.contains       =       &k_stack_contains,
	.clear          =       &k_stack_clear,
	.count          =       &k_stack_count,
	.capacity       =       &k_stack_capacity,
	.iterator       =       &k_stack_iterator
};

static void             k_stack_push            (k_stack_t *self,
                                                 k_object_t *obj)
{
	assert(self && self->vector && obj && Vector.append);
	Vector.append(self->vector, obj);
}

static k_object_t *     k_stack_pop             (k_stack_t *self)
{
	assert(self && self->vector && Vector.remove && Vector.get);
	
	int32_t idx;
	if((idx = Vector.remove(self->vector, k_stack_peek(self))) < 0)
		return NULL;
	return Vector.get(self->vector, (uint16_t)idx);
}

static k_object_t *     k_stack_peek            (k_stack_t *self)
{
	assert(self && self->vector && Vector.last);
	return Vector.last(self->vector);
}

static bool             k_stack_is_empty        (k_stack_t *self)
{
	assert(self && self->vector && Vector.is_empty);
	return Vector.is_empty(self->vector);
}

static bool             k_stack_contains        (k_stack_t *self,
                                                 k_object_t *obj)
{
	assert(self && self->vector && obj && Vector.contains);
	return Vector.contains(self->vector, obj);
}

static void             k_stack_clear           (k_stack_t *self)
{
	assert(self && self->vector && Vector.clear);
	Vector.clear(self->vector);
}

static uint16_t         k_stack_count           (k_stack_t *self)
{
	assert(self && self->vector && Vector.count);
	return Vector.count(self->vector);
}

static uint16_t         k_stack_capacity        (k_stack_t *self)
{
	assert(self && self->vector && Vector.capacity);
	return Vector.capacity(self->vector);
}

static k_iterator_t *   k_stack_iterator        (k_stack_t *self)
{
	assert(self && self->vector && Vector.iterator);
	return Vector.iterator(self->vector);
}