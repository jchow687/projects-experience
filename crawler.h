#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>
//using a set implementation to a bag_t
#include "bag.h"

// my own hashtable

#include "hashtable.h"
typedef struct {
	char *url;
	char *html;
	size_t length;
	int depth;
} webpage_t;
/*
typedef struct bag_t set_t;

typedef struct bag_t{
    webpage_t *node;
    struct bag_t *next;
}bag_t;

typedef struct hashtable_t hashtable_t;
*
typedef struct hashtable_t{
	webpage_t *node;
    struct hashtable_t *next;
};
*/
#endif // CRAWLER_H
