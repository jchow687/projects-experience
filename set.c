#include "set.h"

//here we need to implement an empty set//

set_t* set_new(void){
	// initializing and allocating the memory//
	set_t *set = (set_t *)malloc(sizeof(set_t));
	// checking if the set is at NULL //
	if (set == NULL){
		return 0;
	}
	set->head = NULL;

	return set;
} 

// the purpose of this function is to implement new values/nodes into
// the linked list that will store the key and item //
bool set_insert(set_t *set, const char *key, void *item){
	if (set == NULL || key == NULL || item == NULL){
		return false;
	}

	if(set_find(set, key) != NULL){
		return false;
	}
	setnode_t *new_node = (setnode_t *)malloc(sizeof(setnode_t));
	// allocating memory for the new node //
	if (new_node == NULL){
		return 0;
	}

	// the key gets copied by the set per the instructions //
	new_node->key = strdup(key);

	// makes sure our item is associated with the newly made node //
	new_node->item = item;

	// links the new nodes with the existing nodes //
	// and inserts in the beginning of the list //
	new_node->next = set->head;
	set->head = new_node;

	return 1; 

}

void *set_find(set_t *set, const char *key){
	if (set == NULL || key == NULL) {
		return 0;
	}
	// checking if the set or key is NULL//

	setnode_t *find = set->head;
	// this will return the item associated with the key//
	while (find != NULL) {
		if(strcmp(find->key,key) == 0) {
			return find->item;
		}
		find = find->next;
	}
	return 0;

}


void set_print(set_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) ){
	if (set == NULL){
	       return;
	}

	setnode_t *print = set->head;
	while(print != NULL){
		if (itemprint != NULL){
			itemprint(fp, print->key, print->item);
		}
		print = print->next;
	}
	return;
}

void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) ){
	if (set == NULL || itemfunc == NULL){
		return;
	}

	setnode_t *iterate = set->head;
	while(iterate != NULL){
		itemfunc(arg, iterate->key, iterate->item);
		iterate = iterate->next;
	}
}

void set_delete(set_t *set, void (*itemdelete)(void *item) ){
	if (set == NULL){
		return;
	}

	setnode_t *delete = set->head;
	while (delete != NULL){
		if (itemdelete != NULL){
			itemdelete(delete->item);
		}
		setnode_t *temp = delete;
		delete = delete->next;
		free(temp->key);
		free(temp);
	}
	free(set);
}
