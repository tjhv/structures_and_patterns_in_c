//
// Created by Thomas Huddleston on 2/11/17.
//

#ifndef DEVPROJ_ITERATOR_H
#define DEVPROJ_ITERATOR_H

#include "Class.h"
#include "Node.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	k_class_t *     class;
	k_node_t  *     root;
	k_node_t  *     it;
	uint16_t        idx;
	uint16_t  *     size;
} k_iterator_t, Iterator_t;

typedef struct
{
	bool            (* has_next)            (k_iterator_t *);
	bool            (* has_previous)        (k_iterator_t *);
	k_node_t *      (* next)                (k_iterator_t *);
	k_node_t *      (* previous)            (k_iterator_t *);
	k_node_t *      (* peek)                (k_iterator_t *);
	uint16_t        (* peek_index)          (k_iterator_t *);
	void            (* begin)               (k_iterator_t *);
	void            (* end)                 (k_iterator_t *);
	void            (* skip)                (k_iterator_t *,
	                                         uint16_t);
	void            (* skipto)              (k_iterator_t *,
	                                         uint16_t);
} k_iterator_vtbl_t;

extern const k_iterator_vtbl_t Iterator;

#endif //DEVPROJ_ITERATOR_H
