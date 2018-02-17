//
// Created by Thomas Huddleston on 2/10/17.
//

#ifndef DEVPROJ_LINKEDLIST_H
#define DEVPROJ_LINKEDLIST_H

#include "../Object.h"
#include "../Iterator.h"
#include "../Node.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	k_class_t *     class;
	k_node_t        root;
	uint16_t        capacity;
	uint16_t        count;
	k_iterator_t *  it;
	/**
	 * Perhaps we should track how many objects/nodes total, aswell?
	 * Use uintptr_t instead of indexes, perhaps create a flawless
	 * hash function to create quick mid-list access from nodes??
	 */
} k_linkedlist_t, LinkedList_t;

typedef struct
{
	int32_t         (* prepend)     (k_linkedlist_t *,
	                                 k_object_t *);
	int32_t         (* insert)      (k_linkedlist_t *,
	                                 k_object_t *,
	                                 ...);
	int32_t         (* append)      (k_linkedlist_t *,
	                                 k_object_t *);
	int32_t         (* remove)      (k_linkedlist_t *,
	                                 k_object_t *);
	k_object_t *    (* first)       (k_linkedlist_t *);
	k_object_t *    (* last)        (k_linkedlist_t *);
	bool            (* is_empty)    (k_linkedlist_t *);
	bool            (* contains)    (k_linkedlist_t *,
	                                 k_object_t *);
	void            (* clear)       (k_linkedlist_t *);
	uint16_t        (* count)       (k_linkedlist_t *);
	uint16_t        (* capacity)    (k_linkedlist_t *);
	k_iterator_t *  (* iterator)    (k_linkedlist_t *);
	/* truncate not needed in linked list */
	uint16_t        (* truncate)    (k_linkedlist_t *);
	int32_t         (* find)        (k_linkedlist_t *,
	                                 k_object_t *,
	                                 ...);
	k_object_t *    (* get)         (k_linkedlist_t *,
	                                 uint16_t);
	uint16_t        (* available)   (k_linkedlist_t *);
	
	/**
	 * merge()   - realloc and combine two vectors
	 * split()   - in half
	 * purge()   - reference counts
	 * sort()    - ascending / descending
	 * append_all() - multiple objects to end of vector
	 * remove_all() - multiple objects
	 * purge_all()  - multiple objects reference counts
	 * integrity()
	 * display()
	 * stats()
	 */
	
} k_linkedlist_vtbl_t;

extern const k_linkedlist_vtbl_t LinkedList;

extern const k_class_t * k_linkedlist(void);

#endif //DEVPROJ_LINKEDLIST_H
