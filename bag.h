#ifndef BAG_H_
#define BAG_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "crawler.h"

typedef struct bagnode_t {
	void* item;
    struct bagnode_t *next;
    struct bagnode_t *prev;
} bagnode_t;

struct bag_t{
	bagnode_t *head;
    bagnode_t *tail;
    bagnode_t *next;
    int length;
}; 

typedef struct bag_t bag_t;

/* Create a new (empty) bag; return NULL if error. */
bag_t* bag_new(void);

/* Insert item, identified by a key (string), into the given bag.
 * The key string is copied for use by the bag.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool bag_insert(bag_t *bag, void *item);

void* bag_remove(bag_t *bag);

void bag_print(bag_t *bag);
/* Delete the whole bag; ignore NULL bag.
 * Provide a function that will delete each item (may be NULL).
 */
void bag_delete(bag_t *bag, void (*itemdelete)(void *item) );

#endif // BAG_H_
