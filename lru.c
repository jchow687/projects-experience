#include "lru.h"
/* we are going to implement an additional function if the cache is full */
void remove_lru(lru_t* set) {
   //first checking the set is null//
   if(set == NULL) return;

    setnode_t* n = set->head;
    // declares the pointer to the struct//
    // thus we 
    // set->head->prev = new_node;
    // }
    //
    // new_node->prev = NULL;next iterate through the set//
    while(n->next != NULL) {
        // goes to the second to last node//
        // which represents the least recently used node//
        if(n->next->next == NULL) {
            // stores the next node in the list//
            setnode_t* temp  = n->next;
            // effectively removes the second to last node//
            n->next = NULL;
            // now we update the current node//
            n = temp;
        } else {
            // else is required to find the second to last node//
            n = n->next;
        }
    }
    // at this point, n is the last node in the list
    // and now we free the allocated memory//
    free(n->key);
    free(n);
    set->current--; 
}


lru_t* lru_new(int capacity){
	// initializing and allocating the memory//
	lru_t *set = (lru_t *)malloc(sizeof(lru_t));
	// checking if the set is at NULL //
	if (set == NULL){
		return 0;
	}
    // sets 
	set->head = NULL;
    set->capacity = capacity;
    set->current = 0;

	return set;
} 

// the purpose of this function is to implement new values/nodes into
// the linked list that will store the key and item //
bool lru_insert(lru_t *set, const char *key, void *item){
	if (set == NULL || key == NULL || item == NULL){
		return false;
	}
    int found = 0;
    setnode_t *find = set->head;
	while (find != NULL) {
		if(strcmp(find->key,key) == 0) {
            found = 1;
            break;
		}
		find = find->next;
	}
    if(found == 1){
        return false;
    }
    // if the current amount of sets exceeds the capacity it holds//
    // then we most use the remove lru function to maintain the capacity//
    if(set->current >= set->capacity) {
        remove_lru(set);
    }

	setnode_t *new_node = (setnode_t *)malloc(sizeof(setnode_t));
	// allocating memory for the new node //
	if (new_node == NULL){
		return false;
	}

	// the key gets copied by the set per the instructions //
	new_node->key = strdup(key);

	// makes sure our item is associated with the newly made node //
	new_node->item = item;
	// links the new nodes with the existing nodes //
	// and inserts in the beginning of the list //
	new_node->next = set->head;
    if(set->head != NULL){
        set->head->prev = new_node;
    }

    new_node->prev = NULL;

	set->head = new_node;
    set->current++;

	return true; 

}

void *lru_find(lru_t *set, const char *key){
	if (set == NULL || key == NULL) {
		return 0;
	}
	// checking if the set or key is NULL//

	setnode_t *find = set->head;
	// this will return the item associated with the key//
	while (find != NULL) {
		if(strcmp(find->key,key) == 0){
            setnode_t *temp = find;
            if(temp != set->head) {
                    if(temp->next != NULL){
                        temp->next->prev = temp->prev;
                    }
                    if(temp->prev != NULL){
                        temp->prev->next = temp->next;
                    }

                    temp->next = set->head;
                    set->head->prev = temp;
                    temp->prev = NULL;
                    set->head = temp;
            }

			return temp->item;
		}
		find = find->next;
	}
	return 0;

}


void lru_print(lru_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) ){
   /*checking if set is NULL*/
	if (set == NULL){
	       return;
	}
    // we first initialize our print variable to the head of the list//
	setnode_t *print = set->head;
    //here we iterate through the set//
	while(print != NULL){
		if (itemprint != NULL){
            //then call the given function to each of the parameters//
			itemprint(fp, print->key, print->item);
		}
        //when we stopped iterating through the set, we update the set//
		print = print->next;
	}
	return;
}

void lru_iterate(lru_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) ){
    //here we check the set or item func is NULL//
	if (set == NULL || itemfunc == NULL){
		return;
	}

    // pointer to front of the list //
	setnode_t *iterate = set->head;
	while(iterate != NULL){
        // calling the function on each item//
		itemfunc(arg, iterate->key, iterate->item);
        //updating the set//
		iterate = iterate->next;
	}
}

void lru_delete(lru_t *set, void (*itemdelete)(void *item) ){
	if (set == NULL){
		return;
	}

    //pointer to the head of the list//
	setnode_t *delete = set->head;
	while (delete != NULL){
		if (itemdelete != NULL){
			itemdelete(delete->item);
		}
        // free allocation of memory// 
		setnode_t *temp = delete;
		delete = delete->next;
		free(temp->key);
		free(temp);
	}
	free(set);
}
