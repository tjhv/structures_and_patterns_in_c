//
// Created by Thomas Huddleston on 2/16/17.
//

#ifndef DEVPROJ_VECTOR_H
#define DEVPROJ_VECTOR_H

#include "../Object.h"
#include "../Iterator.h"
#include "../Node.h"

#include <stdbool.h>
#include <stdint.h>

#define DEFAULT_VECTOR_CAPACITY 256

typedef struct
{
	k_class_t *     class;
	k_node_t  *     vector[];
	uint16_t        capacity;
	uint16_t        count;
	int32_t         top;
	k_iterator_t *  it;
	//Thread mutex lock
} k_vector_t, Vector_t;

typedef struct
{
	int32_t         (* prepend)     (k_vector_t *,
	                                 k_object_t *);
	int32_t         (* insert)      (k_vector_t *,
	                                 k_object_t *,
	                                 ...);
	int32_t         (* append)      (k_vector_t *,
	                                 k_object_t *);
	int32_t         (* remove)      (k_vector_t *,
					 k_object_t *);
	k_object_t *    (* first)       (k_vector_t *);
	k_object_t *    (* last)        (k_vector_t *);
	bool            (* is_empty)    (k_vector_t *);
	bool            (* contains)    (k_vector_t *,
	                                 k_object_t *);
	void            (* clear)       (k_vector_t *);
	uint16_t        (* count)       (k_vector_t *);
	uint16_t        (* capacity)    (k_vector_t *);
	k_iterator_t *  (* iterator)    (k_vector_t *);
	
	uint16_t        (* truncate)    (k_vector_t *);
	int32_t         (* find)        (k_vector_t *,
	                                 k_object_t *,
	                                 ...);
	k_object_t *    (* get)         (k_vector_t *,
					 uint16_t);
	uint16_t        (* available)   (k_vector_t *);
	
	/**
	 * merge()   - realloc and combine two vectors
	 * split()   - in half
	 * purge()   - reference counts
	 * sort()    - ascending / descending
	 * append_all() - multiple objects to end of vector
	 * remove_all() - multiple objects
	 * purge_all()  - multiple objects reference counts
	 * integrity()  - check mid-vector fragmentation
	 * display()
	 * stats()
	 */
	
} k_vector_vtbl_t;

extern const k_vector_vtbl_t Vector;

extern const k_class_t * k_vector(void);

#endif //DEVPROJ_VECTOR_H
