//
// Created by Thomas Huddleston on 2/11/17.
//

#include "Iterator.h"
#include "Collections/LinkedList.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

static void *           k_iterator_ctor         (void *);
static void *           k_iterator_dtor         (void *);

static uint16_t         instances;

static bool             k_iterator_has_next     (k_iterator_t *);
static bool             k_iterator_has_previous (k_iterator_t *);
static k_node_t *       k_iterator_next         (k_iterator_t *);
static k_node_t *       k_iterator_previous     (k_iterator_t *);
static k_node_t *       k_iterator_peek         (k_iterator_t *);
static uint16_t         k_iterator_peek_index   (k_iterator_t *);
static void             k_iterator_begin        (k_iterator_t *);
static void             k_iterator_end          (k_iterator_t *);
static void             k_iterator_skip         (k_iterator_t *,
                                                 uint16_t);
static void             k_iterator_skipto       (k_iterator_t *,
                                                 uint16_t);

static const k_iterator_vtbl_t Iterator = {
	.has_next       =       &k_iterator_has_next,
	.has_previous   =       &k_iterator_has_previous,
	.next           =       &k_iterator_next,
	.previous       =       &k_iterator_previous,
	.peek           =       &k_iterator_peek,
	.peek_index     =       &k_iterator_peek_index,
	.begin          =       &k_iterator_begin,
	.end            =       &k_iterator_end,
	.skip           =       &k_iterator_skip,
	.skipto         =       &k_iterator_skipto
};

static const k_class_t k_iterator_class = {
	.ctor           =       &k_iterator_ctor,
	.dtor           =       &k_iterator_dtor,
	.size           =       sizeof(k_iterator_t),
	.name           =       "Iterator",
	.id             =       Iterator_id,
};

static void * k_iterator_ctor(void *_self, va_list *args)
{
	/**
	 * Iterator must know which type of list it is working with,
	 * therefore we must pass the list as an argument somehow.
	 */
	k_iterator_t *self = _self;
	assert(self);
	k_linkedlist_t *list;
	if(!(list = va_arg(*args, k_linkedlist_t *)))
		assert(0);
	assert(list);
	self->root  = &(list->root);
	self->it    = NULL;
	self->idx   = 0;
	self->size  = &(list->capacity);
	++instances;
	return self;
}

static void * k_iterator_dtor(void *_self)
{
	k_iterator_t *self = _self;
	assert(self);
	self->root  = NULL;
	self->it    = NULL;
	self->idx   = 0;
	self->size  = 0;
	--instances;
	return self;
}

static bool             k_iterator_has_next     (k_iterator_t *self)
{ /* This is very ugly */
	assert(self);
	if(!*(self->size)) return false;
	if(!self->it) k_iterator_begin(self);
	return (self->it->next ? true : false);
}

static bool             k_iterator_has_previous (k_iterator_t *self)
{ /* This is equally ugly */
	assert(self);
	if(!*(self->size)) return false;
	if(!self->it) k_iterator_begin(self);
	return (self->it->prev ? true : false);
}

static k_node_t *       k_iterator_next         (k_iterator_t *self)
{
	assert(self && self->it);
	if(k_iterator_has_next(self))
	{
		++self->idx;
		self->it = self->it->next;
	}
	return self->it;
}

static k_node_t *       k_iterator_previous     (k_iterator_t *self)
{
	assert(self && self->it);
	if(k_iterator_has_previous(self))
	{
		--self->idx;
		self->it = self->it->prev;
	}
	return self->it;
}

static k_node_t *       k_iterator_peek         (k_iterator_t *self)
{
	assert(self);
	return self->it;
}

static uint16_t         k_iterator_peek_index   (k_iterator_t *self)
{
	assert(self);
	return self->idx;
}

static void             k_iterator_begin        (k_iterator_t *self)
{
	assert(self && self->root);
	self->it  = self->root;
	self->idx = 1;
}

static void             k_iterator_end          (k_iterator_t *self)
{
	assert(self && self->root->end && self->size);
	self->it  = self->root;
	self->idx = *(self->size);
}

/* This function should wrap to beginning if skip > size */
static void             k_iterator_skip         (k_iterator_t *self,
                                                 uint16_t skip)
{
	assert(self);
	if(((self->idx + skip) > *(self->size)))
		return;
	for(int i = 0; i < skip; ++i)
	{
		if(!k_iterator_has_next(self))
			break;
		
		k_iterator_next(self);
	}
}

/* Dual while() is ugly, use function pointers maybe */
static void             k_iterator_skipto       (k_iterator_t *self,
                                                 uint16_t pos)
{
	assert(self && self->size);
	if(*(self->size) < pos)
		return;
	if(pos == 0)
		k_iterator_begin(self);
	else if(pos == *(self->size))
		k_iterator_end(self);
	else
	{
		while(self->idx > pos && k_iterator_has_previous(self))
			k_iterator_previous(self);
		while(self->idx < pos && k_iterator_has_next(self))
			k_iterator_next(self);
	}
}