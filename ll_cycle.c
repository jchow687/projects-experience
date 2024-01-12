#include <stddef.h>
#include "ll_cycle.h"

//calls our self referential struct // 
int ll_has_cycle(node *head) {
	// returns the number of nodes //
	
	if (head == NULL){
		return 0;
	} 	
	// returns NULL if the cycle is empty // 
	node *slow_ptr = head;
	node *fast_ptr = head->next;
	// we make the two pointers at the head of the list//
	
	while (fast_ptr != NULL && fast_ptr->next != NULL){
		// checking if there is cycle //
		
		//advancing fast_ptr by two nodes//
		//advancing slow_ptr by one node//

		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;


		if (fast_ptr == slow_ptr){
			return 1;
		}
		// if the nodes ever meet each other, it detects the cycle//
		
	} 
	return 0;
    /* TODO: Implement ll_has_cycle */
}
