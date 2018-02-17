//
// Created by Thomas Huddleston on 2/10/17.
//

#include "LinkedList.h"
#include "../Class.h"

#include <assert.h>
#include <stdarg.h>

/*      Constructor and Destructor */
static void *           k_linkedlist_ctor           (void *);
static void *           k_linkedlist_dtor           (void *);

/*      Class Method Prototypes */
static int32_t          k_linkedlist_prepend        (k_linkedlist_t *,
                                                     k_object_t *);
static int32_t          k_linkedlist_insert         (k_linkedlist_t *,
                                                     k_object_t *,
                                                     ...);
static int32_t          k_linkedlist_append         (k_linkedlist_t *,
                                                     k_object_t *);
static int32_t          k_linkedlist_remove         (k_linkedlist_t *,
                                                     k_object_t *);
static k_object_t *     k_linkedlist_first          (k_linkedlist_t *);
static k_object_t *     k_linkedlist_last           (k_linkedlist_t *);
static bool             k_linkedlist_is_empty       (k_linkedlist_t *);
static bool             k_linkedlist_contains       (k_linkedlist_t *,
                                                     k_object_t *);
static void             k_linkedlist_clear          (k_linkedlist_t *);
static uint16_t         k_linkedlist_count          (k_linkedlist_t *);
static uint16_t         k_linkedlist_capacity       (k_linkedlist_t *);
static k_iterator_t *   k_linkedlist_iterator       (k_linkedlist_t *);
static uint16_t         k_linkedlist_truncate       (k_linkedlist_t *);
static int32_t          k_linkedlist_find           (k_linkedlist_t *,
                                                     k_object_t *,
                                                     ...);
static k_object_t *     k_linkedlist_get            (k_linkedlist_t *,
                                                     uint16_t);
static uint16_t         k_linkedlist_available      (k_linkedlist_t *);

/*      Global Variables */
static uint16_t         instances;

const k_linkedlist_vtbl_t   Vector = {
	.prepend        =       &k_linkedlist_prepend,
	.insert         =       &k_linkedlist_insert,
	.append         =       &k_linkedlist_append,
	.remove         =       &k_linkedlist_remove,
	.first          =       &k_linkedlist_first,
	.last           =       &k_linkedlist_last,
	.is_empty       =       &k_linkedlist_is_empty,
	.contains       =       &k_linkedlist_contains,
	.clear          =       &k_linkedlist_clear,
	.count          =       &k_linkedlist_count,
	.capacity       =       &k_linkedlist_capacity,
	.iterator       =       &k_linkedlist_iterator,
	.truncate       =       &k_linkedlist_truncate,
	.find           =       &k_linkedlist_find,
	.get            =       &k_linkedlist_get,
	.available      =       &k_linkedlist_available
};

const k_class_t         k_linkedlist_class = {
	.ctor           =       &k_linkedlist_ctor,
	.dtor           =       &k_linkedlist_dtor,
	.size           =       sizeof(k_linkedlist_t),
	.name           =       "LinkedList",
	.id             =       LinkedList_id
};

/*      Class Method Definitions */
const k_class_t *       k_linkedlist                (void)
{
	return &k_linkedlist_class;
}

static void *           k_linkedlist_ctor           (void *_self)
{
	assert(_self);
	k_linkedlist_t *self    =       _self;
	self->root              =       NULL;
	/**
	 * capacity will be received from va_args passed to the class_t
	 */
	self->capacity          =       0;
	self->count             =       0;
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

static void *           k_linkedlist_dtor           (void *_self)
{
	assert(_self);
	k_linkedlist_t *self = _self;
	self->class             =       NULL;
	k_linkedlist_clear(self);
	self->capacity          =       0;
	self->count             =       0;
	Object.dispose(self->it);
	--instances;
	return _self;
}

static int32_t          k_linkedlist_prepend        (k_linkedlist_t *self,
                                                     k_object_t *obj)
{
	assert(self && obj);
	if(!k_linkedlist_available(self))
		return -1;
	/**
	 * Insert at head of list
	 */
	return -1;
}

static int32_t          k_linkedlist_insert         (k_linkedlist_t *self,
                                                     k_object_t *obj,
                                                     ...)
{
	assert(self && obj);
	if(!k_linkedlist_available(self))
		return -1;
	
	return -1;
}

static int32_t          k_linkedlist_append         (k_linkedlist_t *self,
                                                     k_object_t *obj)
{
	assert(self && obj);
	if(!k_linkedlist_available(self))
		return -1;
	/**
	 * Append to tail of list
	 */
	return 0;
}

static int32_t          k_linkedlist_remove         (k_linkedlist_t *self,
                                                     k_object_t *obj)
{
	assert(self && obj);
	
	int32_t idx;
	if((idx = k_linkedlist_find(self, obj)) >= 0)
	{
		Node.clear(NULL);
		--self->count;
	}
	return idx;
}

static k_object_t *     k_linkedlist_first          (k_linkedlist_t *self)
{
	assert(self);
	/**
	 * Return head of list
	 */
	return self->root.head->object;
}

static k_object_t *     k_linkedlist_last           (k_linkedlist_t *self)
{
	assert(self);
	/**
	 * Return tail of list
	 */
	return self->root.tail->object;
}

static bool             k_linkedlist_is_empty       (k_linkedlist_t *self)
{
	assert(self);
	return (self->count ? false : true);
}

static bool             k_linkedlist_contains       (k_linkedlist_t *self,
                                                     k_object_t *obj)
{
	return (k_linkedlist_find(self, obj) ? true : false);
}

static void             k_linkedlist_clear          (k_linkedlist_t *self)
{
	assert(self);
	
	while(!k_linkedlist_is_empty(self))
		k_linkedlist_remove(self, k_linkedlist_first(self));
}

static uint16_t         k_linkedlist_count          (k_linkedlist_t *self)
{
	assert(self);
	return self->count;
}

static uint16_t         k_linkedlist_capacity       (k_linkedlist_t *self)
{
	assert(self);
	return self->capacity;
}

static k_iterator_t *   k_linkedlist_iterator       (k_linkedlist_t *self)
{
	assert(self && self->it);
	return self->it;
}

static uint16_t         k_linkedlist_truncate       (k_linkedlist_t *self)
{
	assert(self);
	/**
	 * Resize Vector and fill in empty slots,
	 * Leave an additional N slots available.
	 */
	return self->count;
}

static int32_t         k_linkedlist_find           (k_linkedlist_t *self,
                                                    k_object_t *obj,
                                                    ...)
{
	assert(self && obj);
	
	/**
	 * Third parameter is the starting index for where
	 * we offset the search
	 */
	
	if(k_linkedlist_is_empty(self))
		return -1;
	
	return -1;
}

static k_object_t *     k_linkedlist_get            (k_linkedlist_t *self,
                                                     uint16_t idx)
{
	assert(self);
	
	return NULL;
}

static uint16_t         k_linkedlist_available      (k_linkedlist_t *self)
{
	assert(self);
	return (self->capacity - self->count);
}