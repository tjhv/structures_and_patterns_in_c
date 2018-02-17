//
// Created by Thomas Huddleston on 2/16/17.
//

#include "BinaryTree.h"
#include "../mem.h"
#include "../Logger.h"

#include <assert.h>
#include <stdio.h>

static void k_tree_insert(k_tree_t **, uint16_t, void *);
static void * k_tree_find(k_tree_t *, uint16_t);
static int32_t k_tree_contains(k_tree_t *, void *);
static void * k_tree_remove(k_tree_t **, uint16_t);
static void k_tree_view(k_tree_t *);

const tree_vtbl_t Tree = {
	.insert         =       &k_tree_insert,
	.find           =       &k_tree_find,
	.contains       =       &k_tree_contains,
	.remove         =       &k_tree_remove,
	.view           =       &k_tree_view
};

static void k_tree_insert(k_tree_t **tree,
                          uint16_t key,
                          void *obj)
{
	assert(tree && obj);
	printf("insert() attempting\n");
	if(!(*tree))
	{
		printf("insert() null node\r\n");
		(*tree) = mem_alloc(sizeof(**tree));
		
		(*tree)->root.key   = key;
		(*tree)->root.objp  = obj;
		(*tree)->root.left  = NULL;
		(*tree)->root.right = NULL;
		
		return;
	}
	
	if((*(*tree)).root.key > key)
		k_tree_insert((k_tree_t **)&((*tree)->root.left), key, obj);
	else if((*tree)->root.key < key)
		k_tree_insert((k_tree_t **)&((*tree)->root.right), key, obj);
	else
		printf("%d=%d, exact match of key for insert()\r\n",
		       (*tree)->root.key, key);
}

static void * k_tree_find(k_tree_t *tree,
                            uint16_t key)
{
	if(!tree)
	{
		printf("unable to find key=%d for @%p\r\n",
		       key, NULL);
		return NULL;
	}
	
	if(tree->root.key > key)
		k_tree_find((k_tree_t *)tree->root.left, key);
	else if(tree->root.key < key)
		k_tree_find((k_tree_t *)tree->root.right, key);
	else
		return tree->root.objp;
}

static int32_t k_tree_contains(k_tree_t *tree,
                                void *obj)
{
	if(!tree)
	{
		printf("unable to find object=@%p for @%p\r\n",
		       obj, NULL);
		return -1;
	}
	return -1;
}

static void * k_tree_remove(k_tree_t **tree,
                            uint16_t key)
{
	assert(tree);
	
	if(!*tree)
		return NULL;
	
	if((*tree)->root.key > key)
		k_tree_remove((k_tree_t **)&((*tree)->root.left), key);
	else if((*tree)->root.key < key)
		k_tree_remove((k_tree_t **)&((*tree)->root.right), key);
	else
	{
		//exact match
		printf("%d=%d, exact match of key for delete()\r\n",
		       (*tree)->root.key, key);
		//do other clearing operationg and create tmp var for obj
		free(*tree);
	}
	return NULL;
}

static void k_tree_view(k_tree_t *tree)
{
	
}