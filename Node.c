//
// Created by Thomas Huddleston on 2/17/17.
//

#include "Node.h"

static void             k_node_clear            (k_node_t *);

const k_node_vtbl_t     Node = {
	.clear          =       &k_node_clear
};

static void             k_node_clear            (k_node_t *self)
{
	if(!self) return;
	
	self->next      =       NULL;
	self->prev      =       NULL;
	self->object    =       NULL;
	self->rcount    =       0;
}