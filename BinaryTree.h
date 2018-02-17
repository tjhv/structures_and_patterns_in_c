//
// Created by Thomas Huddleston on 2/16/17.
//

#ifndef DEVPROJ_TREE_H
#define DEVPROJ_TREE_H

#include "../Node.h"

typedef struct
{
	node_t root;
} k_tree_t;

typedef struct
{
	void (* insert)(k_tree_t **, uint16_t, void *);
	void * (* find)(k_tree_t *, uint16_t); //find object with key
	int32_t (* contains)(k_tree_t *, void *); //return key if object exists
	void * (* remove)(k_tree_t **, uint16_t);
	void (* view)(k_tree_t *);
} tree_vtbl_t;

extern const tree_vtbl_t Tree;



#endif //DEVPROJ_TREE_H