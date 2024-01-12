#ifndef SET_H_
#define SET_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct setnode {
	char* key;
	void* item;
	struct setnode *next;
	struct setnode *prev;
} setnode_t;

typedef struct lru_t {
	setnode_t *head;
	int current;
	int capacity;
} lru_t;

/* Create a new (empty) set; return NULL if error. */
lru_t* lru_new(int);

/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool lru_insert(lru_t *set, const char *key, void *item);

/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *lru_find(lru_t *set, const char *key);

/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void lru_print(lru_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) );

/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void lru_iterate(lru_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void lru_delete(lru_t *set, void (*itemdelete)(void *item) );

#endif // SET_H_
