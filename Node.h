//
// Created by Thomas Huddleston on 2/11/17.
//

#ifndef DEVPROJ_NODE_H
#define DEVPROJ_NODE_H

#include "Object.h"

#include <stdint.h>

typedef struct k_node_s
{
	union {
		struct k_node_s *next;
		struct k_node_s *right;
		struct k_node_s *head;
		struct k_node_s *begin;
	};
	union {
		struct k_node_s *prev;
		struct k_node_s *left;
		struct k_node_s *tail;
		struct k_node_s *end;
	};
	union {
		k_object_t *object;
		uintptr_t objint; /* For Hashing */
		void *block;
	};
	union {
		uint16_t rcount; /* Reference Count */
		uint16_t key;
	};
} k_node_t;

typedef struct
{
	void (* clear)(k_node_t *);
} k_node_vtbl_t;

extern const k_node_vtbl_t Node;


#endif //DEVPROJ_NODE_H
