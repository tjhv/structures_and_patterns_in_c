//
// Created by Thomas Huddleston on 2/16/17.
//

#include "Vector.h"
#include "../Class.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

		/*      Constructor and Destructor */
static void *           k_vector_ctor           (void *);
static void *           k_vector_dtor           (void *);

		/*      Class Method Prototypes */
static int32_t          k_vector_prepend        (k_vector_t *,
                                                 k_object_t *);
static int32_t          k_vector_insert         (k_vector_t *,
                                                 k_object_t *,
                                                 ...);
static int32_t          k_vector_append         (k_vector_t *,
                                                 k_object_t *);
static int32_t          k_vector_remove         (k_vector_t *,
                                                 k_object_t *);
static k_object_t *     k_vector_first          (k_vector_t *);
static k_object_t *     k_vector_last           (k_vector_t *);
static bool             k_vector_is_empty       (k_vector_t *);
static bool             k_vector_contains       (k_vector_t *,
                                                 k_object_t *);
static void             k_vector_clear          (k_vector_t *);
static uint16_t         k_vector_count          (k_vector_t *);
static uint16_t         k_vector_capacity       (k_vector_t *);
static k_iterator_t *   k_vector_iterator       (k_vector_t *);
static uint16_t         k_vector_truncate       (k_vector_t *);
static int32_t          k_vector_find           (k_vector_t *,
                                                 k_object_t *,
                                                 ...);
static k_object_t *     k_vector_get            (k_vector_t *,
                                                 uint16_t);
static uint16_t         k_vector_available      (k_vector_t *);

		/*      Global Variables */
static uint16_t         instances;

const k_vector_vtbl_t   Vector = {
	.prepend        =       &k_vector_prepend,
	.insert         =       &k_vector_insert,
	.append         =       &k_vector_append,
	.remove         =       &k_vector_remove,
	.first          =       &k_vector_first,
	.last           =       &k_vector_last,
	.is_empty       =       &k_vector_is_empty,
	.contains       =       &k_vector_contains,
	.clear          =       &k_vector_clear,
	.count          =       &k_vector_count,
	.capacity       =       &k_vector_capacity,
	.iterator       =       &k_vector_iterator,
	.truncate       =       &k_vector_truncate,
	.find           =       &k_vector_find,
	.get            =       &k_vector_get,
	.available      =       &k_vector_available
};

const k_class_t         k_vector_class = {
	.ctor           =       &k_vector_ctor,
	.dtor           =       &k_vector_dtor,
	.size           =       sizeof(k_vector_t),
	.name           =       "Vector",
	.id             =       Vector_id
};

		/*      Class Method Definitions */
const k_class_t *       k_vector                (void)
{
	return &k_vector_class;
}

static void *           k_vector_ctor           (void *_self)
{
	assert(_self);
	k_vector_t *self        =       _self;
	self->vector            =       malloc(sizeof(k_node_t)
	                                       * DEFAULT_VECTOR_CAPACITY);
	assert(self->vector);
	/**
	 * capacity will be received from va_args passed to the class_t
	 */
	self->capacity          =       0;
	self->count             =       0;
	self->top               =      -1;
	/**
	 * Pass self to iterator, iterator must manipulate the prev and
	 * next pointers in order to iterator through its data types,
	 * it must check the class_id in order to know how to manipulate
	 * them.
	 */
	self->it                =       Object.new(Class.Iterator());
	++instances;
	return self;
}

static void *           k_vector_dtor           (void *_self)
{
	assert(_self);
	k_vector_t *self = _self;
	self->class             =       NULL;
	free(self->vector);
	self->capacity          =       0;
	self->count             =       0;
	self->top               =      -1;
	Object.dispose(self->it);
	--instances;
	return _self;
}

static int32_t          k_vector_prepend        (k_vector_t *self,
                                                 k_object_t *obj)
{
	assert(self && obj);
	if(!k_vector_available(self))
		return -1;
	/**
	 * Will have to shift entire vector for insertion
	 * at the front.
	 */
	return -1;
}

static int32_t          k_vector_insert         (k_vector_t *self,
                                                 k_object_t *obj,
                                                 ...)
{
	assert(self && obj);
	if(!k_vector_available(self))
		return -1;
	/**
	 * Third parameter is the index we insert at, and shift
	 * vector accordingly.
	 * Perhaps track free slots mid-vector in a linked list,
	 * and check the linked list for default inserts first
	 * before looping through vector.
	 */
	 for(uint16_t i = 0; i < (self->top + 1); ++i)
	 {
		 /* (self->top + 1) may fail */
		 if(!self->vector[i]->object)
		 {
			 if(self->top < i)
				 self->top = i;
			 self->vector[i]->object = obj;
			 ++self->count;
		 }
		 
	 }
	return -1;
}

static int32_t          k_vector_append         (k_vector_t *self,
                                                 k_object_t *obj)
{
	/**
	 * Automatically grow the vector by 50% its current capacity
	 * initially, keep track of the time between growths and if
	 * they are too close between each other, start growing by
	 * double the capacity. If it remains too big then automatically
	 * truncate with N available slots remaining.
	 * Check if class_id equals Queue or PriorityQueue before growing
	 * vector, instead wrap back around to the beginning if possible.
	 * If not possible, grow vector.
	 */
	assert(self && obj);
	if(!k_vector_available(self))
		return -1;
	self->vector[++self->top]->object = obj;
	++self->count;
	return self->top;
}

static int32_t          k_vector_remove         (k_vector_t *self,
                                                 k_object_t *obj)
{
	assert(self && obj);
	
	int32_t idx;
	if((idx = k_vector_find(self, obj)) >= 0)
	{
		if(self->top == idx)
		{
			/**
			 * Top must iterate backwards until it finds the
			 * last non-NULL element
			 */
			--self->top;
		}
		Node.clear(self->vector[idx]);
		--self->count;
	}
	return idx;
}

static k_object_t *     k_vector_first          (k_vector_t *self)
{
	assert(self && self->vector);
	/**
	 * Will need a more powerful first() function in order to
	 * create a seamless Queue adapter. first() must check
	 * for the first non-NULL element and return it
	 */
	return self->vector[0]->object;
}

static k_object_t *     k_vector_last           (k_vector_t *self)
{
	assert(self && self->vector);
	return self->vector[((unsigned)self->top)]->object;
}

static bool             k_vector_is_empty       (k_vector_t *self)
{
	assert(self);
	return (self->count ? false : true);
}

static bool             k_vector_contains       (k_vector_t *self,
                                                 k_object_t *obj)
{
	return (k_vector_find(self, obj) ? true : false);
}

static void             k_vector_clear          (k_vector_t *self)
{
	assert(self && self->vector);
	
	for(uint16_t i = 0; i < self->top; ++i)
		Node.clear(self->vector[i]);
}

static uint16_t         k_vector_count          (k_vector_t *self)
{
	assert(self);
	return self->count;
}

static uint16_t         k_vector_capacity       (k_vector_t *self)
{
	assert(self);
	return self->capacity;
}

static k_iterator_t *   k_vector_iterator       (k_vector_t *self)
{
	assert(self && self->it);
	return self->it;
}

static uint16_t         k_vector_truncate       (k_vector_t *self)
{
	assert(self && self->vector);
	/**
	 * Resize Vector and fill in empty slots,
	 * Leave an additional N slots available.
	 */
	return self->count;
}

static int32_t         k_vector_find           (k_vector_t *self,
                                                 k_object_t *obj,
                                                 ...)
{
	assert(self && self->vector && obj);
	
	/**
	 * Third parameter is the starting index for where
	 * we offset the search
	 */
	
	if(k_vector_is_empty(self))
		return -1;
	
	for(uint16_t i = 0; i < self->top; ++i)
		if(self->vector[i]->object == obj)
			return i;
	return -1;
}

static k_object_t *     k_vector_get            (k_vector_t *self,
                                                 uint16_t idx)
{
	assert(self && self->vector);
	
	if(self->top < idx)
		return NULL;
	
	return self->vector[idx]->object;
}

static uint16_t         k_vector_available      (k_vector_t *self)
{
	assert(self);
	return (self->capacity - self->count);
}