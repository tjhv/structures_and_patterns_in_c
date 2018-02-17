//
// Created by Thomas Huddleston on 2/16/17.
//

#include "HashMap.h"
#include "../Object.h"

#include <assert.h>
#include <stdarg.h>

static uint16_t k_hashmap_hash(k_hashmap_t *, void *);
static void k_hashmap_rehash(k_hashmap_t *);
static void k_hashmap_add(k_hashmap_t *, void *);
static void k_hashmap_remove(k_hashmap_t *, void *);
static bool k_hashmap_is_empty(k_hashmap_t *);
static void k_hashmap_empty(k_hashmap_t *);
static uint16_t k_hashmap_find(k_hashmap_t *, void *);
static bool k_hashmap_contains(k_hashmap_t *, void *);
static void * k_hashmap_get(k_hashmap_t *, uint16_t);

const k_hashmap_vtbl_t HashMap = {
	.hash           =       &k_hashmap_hash,
	.rehash         =       &k_hashmap_rehash,
	.add            =       &k_hashmap_add,
	.remove         =       &k_hashmap_remove,
	.is_empty       =       &k_hashmap_is_empty,
	.empty          =       &k_hashmap_empty,
	.find           =       &k_hashmap_find,
	.contains       =       &k_hashmap_contains,
	.get            =       &k_hashmap_get
};

static void * k_hashmap_ctor(void *_self,
                             va_list *args)
{
	list_t *self = _self;
	assert(self && self->class && self->class->vptr);
	self->node.head = NULL;
	self->node.tail = NULL;
	self->node.objp = NULL;
	self->size = 0;
	self->vptr = &list_vptr;
	self->it   = new(Iterator(), self);
	++instances;
	return self;
}

static void * k_list_dtor(void *_self)
{
	list_t *self = _self;
	assert(self);
	k_list_clear(self);
	self->node.head  = NULL;
	self->node.tail  = NULL;
	self->size  = 0;
	self->class = NULL;
	self->vptr  = NULL;
	delete(self->it);
	--instances;
	return self;
}

static uint16_t k_hashmap_hash(k_hashmap_t *map,
                               void *obj)
{
	assert(map && obj);
	return (uint16_t)((uintptr_t)obj % map->size);
}
static void k_hashmap_rehash(k_hashmap_t *map)
{
	//resize vector
}
static void k_hashmap_add(k_hashmap_t *map,
                          void *obj)
{
	
}
static void k_hashmap_remove(k_hashmap_t *map,
                             void *obj)
{
	
}
static bool k_hashmap_is_empty(k_hashmap_t *map)
{
	assert(map);
	return (map->count ? true : false);
}
static void k_hashmap_empty(k_hashmap_t *map)
{
	//empty hash map and free nodes
}
static uint16_t k_hashmap_find(k_hashmap_t *map,
                               void *obj)
{
	//locate object in hash map
}
static bool k_hashmap_contains(k_hashmap_t *map,
                               void *obj)
{
	
}
static void * k_hashmap_get(k_hashmap_t *map,
                            uint16_t key)
{
	
}
