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
}

/*implementing empty hash */ 
hashtable_t *hashtable_new(const int num_slots){
	//num of slots represents the array of sets//
	//we check if the array of sets are valid or allocation failure//
	if (num_slots <= 0){
		return NULL;
	}

	hashtable_t *ht = (hashtable_t *)malloc(sizeof(hashtable_t));
	/* making the data structure for our hash */

	if (ht == NULL){
		exit(EXIT_FAILURE);
	}

	ht->num_slots = num_slots;

	/*because we are going to have an array of sets for the slots
	we need to allocate memory for it*/

	ht->slots = (bode **)malloc(num_slots * sizeof(bode));

	if (ht->slots == NULL){
		free(ht);
		exit(EXIT_FAILURE);
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
       	/* return NULL if hash is NULL, key is NULL, key is not found.*/

	unsigned int slot = hash(key, ht-> num_slots);
	/* determining slot with the hash value */

	//just like in set.c we need to allocate memory for the new nodes inserted//
	bode *new_node = (bode *)malloc(sizeof(bode));

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
		return NULL;
	}

	unsigned int slot = hash(key, ht->num_slots);
	bode *find = ht->slots[slot];
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
	return NULL;
}

void* hashtable_remove(hashtable_t *ht, const char *key){
    if(ht == NULL || key == NULL){
        return NULL;
    }
    unsigned int indexo = hash(key, ht->num_slots);
    bode *previous = NULL;
    bode *current = ht->slots[indexo];
    while(current){
        if(current->key != NULL && strcmp(current->key, key) == 0){
            if(previous == NULL){
                ht->slots[indexo] = current->next;
            }else{
                previous->next = current->next;
            }
            void* out = current->item;
            free(current->key);
            free(current);
            return(out);
        }
        previous = current; 
        current = current->next;
    }
    return NULL;
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)){
	if (ht == NULL){
		return;
	}
	/*iterate through the array of sets*/
	for (int i = 0; i < ht-> num_slots; ++i){
		bode *delete = ht->slots[i];
		while (delete != NULL){
			if (itemdelete != NULL){
				itemdelete(delete->item);
			}
			// free the allocated memory//
			bode *temp = delete;
			delete = delete->next;
			free(temp->key);
			free(temp);
		}

	}

	//finally free the memory for the slots and hash//
	free(ht->slots);
	free(ht);
}


/*
int main(){
    
        // Test Case 1: Create a new hashtable
    hashtable_t *ht = hashtable_new(5);

    // Test Case 2: Insert items into the hashtable
    hashtable_insert(ht, "key1", malloc(sizeof(int)));
    hashtable_insert(ht, "key2", malloc(sizeof(double)));
    hashtable_insert(ht, "key3", malloc(sizeof(char)));


    // Test Case 4: Find items in the hashtable
    printf("\nFinding items in the hashtable:\n");
    void *item1 = hashtable_find(ht, "key1");
    void *item2 = hashtable_find(ht, "key2");
    void *item3 = hashtable_find(ht, "key3");

    printf("Item found for key1: %p\n", item1);
    printf("Item found for key2: %p\n", item2);
    printf("Item found for key3: %p\n", item3);

    // Test Case 5: Remove items from the hashtable
    printf("\nRemoving items from the hashtable:\n");
    void *removedItem1 = hashtable_remove(ht, "key1");
    void *removedItem2 = hashtable_remove(ht, "key2");
    void *removedItem3 = hashtable_remove(ht, "key3");

    printf("Removed item for key1: %p\n", removedItem1);
    printf("Removed item for key2: %p\n", removedItem2);
    printf("Removed item for key3: %p\n", removedItem3);

    // Test Case 6: Delete the hashtable
    hashtable_delete(ht, free);

    return 0;
    
}
*/
