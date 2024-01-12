#include "bag.h"

//here we need to implement an empty bag//

bag_t* bag_new(void){
	// initializing and allocating the memory//
	bag_t *bag = (bag_t*)malloc(sizeof(bag_t));
	// checking if the bag is at NULL //
	if (bag == NULL){
		return 0;
	}
	bag->head = NULL;
    bag->tail = NULL;
    bag->length = 0;

	return bag;
} 

// the purpose of this function is to implement new values/nodes into
// the linked list that will store the key and item //
bool bag_insert(bag_t *bag, void *item){
	if (bag == NULL || item == NULL){
		return false;
	}

	bagnode_t *new_node = (bagnode_t *)malloc(sizeof(bagnode_t));
	// allocating memory for the new node //
	if (new_node == NULL){
		return 0;
	}

	// makes sure our item is associated with the newly made node //
	new_node->item = item;

	// links the new nodes with the existing nodes //
	// and inserts in the beginning of the list //
	new_node->next = bag->head;
    if(bag->head != NULL) bag->head->prev = new_node;
    else bag->tail = new_node;
    new_node->prev = NULL;
	bag->head = new_node;
    bag->length++;

	return true; 

}
void* bag_remove(bag_t *bag){
    if(bag->tail == NULL) {
        return NULL;
    }
    bagnode_t *PT = bag->tail;
    bag->tail = PT->prev;
    if(bag->tail == NULL) {
        bag->head = NULL;
    } else {
        bag->tail->next = NULL;
    }
    void *out = PT->item;
    free(PT);
    bag->length--;
    return out;
}

void bag_print(bag_t *bag){
    bagnode_t *i = bag->head;
    printf("start\n");
    while(i){
        webpage_t *baggie = (webpage_t *)i->item;
        printf("%s\t", baggie->url);
        i = i->next;
    }
    printf("end\n");
}

void bag_delete(bag_t *bag, void (*itemdelete)(void *item) ){
	if (bag == NULL){
		return;
	}

	bagnode_t *c = bag->head;
    bagnode_t *n;
    //printf(">>1\n");
    while(c){
       // printf(">>2\n");
        n = c->next;
        //printf(">>3\n");
		if (itemdelete != NULL){
			itemdelete(c->item);
		}
        free(c);
        //printf(">>4\n");
        c = n;
	}

	free(bag);
}
/*
int main(){
    
    int* a1 = (int *)malloc(sizeof(int));
    int* a2 = (int *)malloc(sizeof(int));
    int* a3 = (int *)malloc(sizeof(int));
    int* a4 = (int *)malloc(sizeof(int));
    int* a5 = (int *)malloc(sizeof(int));
    *a1 = 1;
    *a2 = 2; 
    *a3 = 3;
    *a4 = 4;
    *a5 = 5;
    bag_t *bb = bag_new();
    bag_insert(bb, &a1);
    bag_insert(bb, &a2);
    bag_insert(bb, &a3);
    bag_insert(bb, &a4);
    bag_insert(bb, &a5);
    assert(bb->length == 5);
    void* p1 = bag_remove(bb);
    void* p2 = bag_remove(bb);
    void* p3 = bag_remove(bb);
    void* p4 = bag_remove(bb);
    void* p5 = bag_remove(bb);
    assert(&a1 == p1);
    assert(&a2 == p2);
    assert(&a3 == p3);
    assert(&a4 == p4);
    assert(&a5 == p5);
    assert(bag_remove(bb) == NULL);
    assert(bb->length == 0);
    bag_delete(bb, NULL);
    free(a1);
    free(a2);
    free(a3);
    free(a4);
    free(a5);
}
*/

