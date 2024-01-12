#include "hashtable.h"

/* implementing the hash algorithm */
enum { MULTI = 31 } ;
/* here we incorporate a multiplier
 so we can randomly spread the values across the hash table
so that multiple keys don't end up in the same location */ 

unsigned int hash(const char *key, int num_slots){

	/*declaring and initializing int and char variables */
	unsigned int da_hashie = 0;
	const unsigned char *here;


	for (here = (unsigned char *)key; *here != '\0'; here++){
		da_hashie  = MULTI * da_hashie + *here;
	/* what this loop does is randomize the bits using the prime multiplier
	to achieve a more even random distribution of hash values */
	}
	return da_hashie % num_slots;
	/* calculates the final hash */
}

/*implementing empty hashtable */ 
hashtable_t *hashtable_new(const int num_slots){
	//num of slots represents the array of sets//
	//we check if the array of sets are valid or allocation failure//
	if (num_slots <= 0){
		return NULL;
	}

	hashtable_t *ht = (hashtable_t *)malloc(sizeof(hashtable_t));
	/* making the data structure for our hashtable */

	if (ht == NULL){
		return 0;
	}

	ht->num_slots = num_slots;

	/*because we are going to have an array of sets for the slots
	we need to allocate memory for it*/

	ht->slots = (set_hashies **)malloc(num_slots * sizeof(set_hashies));

	if (ht->slots == NULL){
		free(ht);
		return 0;
	}
	// we need to check if the number of slots are valid//
	for(int i = 0; i < num_slots; ++i) {
		ht->slots[i] = NULL;
	}
	return ht;
}	
	

bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	/* if any parameter is null, we need to return */
	if (ht == NULL || key == NULL || item == NULL){
		return false;
	}
	/*to avoid a seg fault,this if statement tells if there already exists a key in ht */
	if(hashtable_find(ht, key) != NULL){
		return false;
	}
       	/* return NULL if hashtable is NULL, key is NULL, key is not found.*/

	unsigned int slot = hash(key, ht-> num_slots);
	/* determining slot with the hash value */

	//just like in set.c we need to allocate memory for the new nodes inserted//
	set_hashies *new_node = (set_hashies *)malloc(sizeof(set_hashies));

	if (new_node == NULL){
		return 0;
	}
	new_node->key = strdup(key);

	// makes sure our item is associated with the newly made node //
	new_node->item = item;

	// links the new nodes with the existing nodes //
	// and inserts in the beginning of the list //
	new_node->next = NULL;

	// proceed to insert new node at the beginning//
	new_node->next = ht->slots[slot];
	ht->slots[slot] = new_node;

	return 1;
}

void *hashtable_find(hashtable_t *ht, const char *key){
	if (ht == NULL || key == NULL){
		return 0;
	}

	unsigned int slot = hash(key, ht->num_slots);
	set_hashies *find = ht->slots[slot];
	/*like wise when we had to have set point to the head in set.c
	 in here we determine the slot with the hash value then traverse in
	 the specific location of that node where it has multiple data */

	/* same thing in set.c  we write a function to return the key
	 with the associated item */

	while (find != NULL) {
		if(strcmp(find->key,key) == 0) {
			return find->item;
		}
		find = find->next;
	}
	return 0;
}

void hashtable_print(hashtable_t *ht, FILE *fp,
		void (*itemprint)(FILE *fp, const char *key, void *item)){
	if (ht == NULL){
		return;
	}
	// checking if ht is null//

	/* we check if the array of sets are valid by iterating through*/
	for(int i = 0; i < ht->num_slots; ++i){

		/*then go through the sets of each slot*/
		set_hashies *print = ht->slots[i];

		/*print key and item */
		while(print != NULL){
			if (itemprint != NULL){
				itemprint(fp, print->key, print->item);
			}
			print = print->next;
		}
	}
	return;
}

void hashtable_iterate(hashtable_t *ht, void *arg,
		void (*itemfunc)(void *arg, const char *key, void *item) ){
	//checking if ht or item func or null, if not they do nothing//
	if (ht == NULL || itemfunc == NULL){
		return;
	}

	/*we need to iterate through the array of sets*/
	for (int i = 0; i < ht->num_slots; ++i){
		set_hashies *iterate = ht->slots[i];
		// call the function on the given item//
		while(iterate != NULL){
			itemfunc(arg, iterate->key, iterate->item);
			iterate = iterate->next;
		}
	}
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)){
	if (ht == NULL){
		return;
	}
	/*iterate through the array of sets*/
	for (int i = 0; i < ht-> num_slots; ++i){
		set_hashies *delete = ht->slots[i];
		while (delete != NULL){
			if (itemdelete != NULL){
				itemdelete(delete->item);
			}
			// free the allocated memory//
			set_hashies *temp = delete;
			delete = delete->next;
			free(temp->key);
			free(temp);
		}

	}

	//finally free the memory for the slots and hashtable//
	free(ht->slots);
	free(ht);
}

