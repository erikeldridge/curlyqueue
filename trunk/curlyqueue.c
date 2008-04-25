#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curlyqueue.h"

/**
 * Creates new list node
 * @pre	calling fn has determined prev and next pointers
 * @post	mem has been allocated for new node and
 * 		and node field values have been assigned
 * @note	calling fn must free mem!
 */
curlyqueue_node_t* curly_create_node( void* value, curlyqueue_node_t* prev, curlyqueue_node_t* next ){
	
	curlyqueue_node_t* node = ( curlyqueue_node_t* )malloc( sizeof( curlyqueue_node_t ) );
	
	node->value	= value;
	node->prev	= prev;
	node->next	= next;
	
	return node;
}

/**
 * Initializes the linked list manager struct.
 * @post	mem has been allocated for queuea and 
 * 		field valies have been initialized to 
 * 		null (if pointers) or zero (if count)
 * @note	calling fn must free mem!
 */
curlyqueue_t* curly_create_queue(){
	
	curlyqueue_t* queue = malloc( sizeof( curlyqueue_t ) );
	
	queue->back		= NULL;
	queue->front	= NULL;
	queue->count	= 0;
	
	return queue;
}

/** 
 * Rolls through list, freeing resources.
 * @param	queue	the q to destroy
 * @pre		the queue pointer is not NULL
 * @post	all nodes in the list are freed
 * @post	the list manager's pointers are set to null
 * @post	the list manager's count is decremented for each freed node
 */
void curly_destroy_queue( curlyqueue_t* queue ){
	
	/**
	 the current node
	 */
	curlyqueue_node_t* curr = queue->back;
		
	/**
	 the node after current node
	 */
	curlyqueue_node_t* next;
	
	/* while the current node isn't the end of the list*/
	while( curr != NULL ){
		
		next = curr->next;
		
		if( NULL != curr->value ){
			//TODO: do we need to free the node value?
			//free( curr->value );
		}
		
		free( curr );
		
		curr = next;
		
		queue->count--;
	}
	
	
	free( queue );
	
	/* dedangle pointer */
	queue = NULL;
}


/**
 * Creates a node for a given value and adds it to the back of a queue
 * @param	queue	The queue to add the value to
 * @param	value	The value to push onto the q
 * @post	The queue's count is incremented
 */
void curly_enqueue( curlyqueue_t* queue, void* value ){
	
	curlyqueue_node_t* prev = NULL;
	curlyqueue_node_t* next = queue->back;
	
	curlyqueue_node_t* node = curly_create_node( value, prev, next );
	
	/* if this is the first node, the tail = the head*/
	if( curly_queue_is_empty( queue ) ){
		
		queue->front = node;
		
	}else{
		
		queue->back->prev = node;
		
	}
	
	queue->back = node;
	
	/* increment the list's internal count of nodes */
	queue->count++;	
}

void* curly_dequeue( curlyqueue_t* queue ){
	
//	if( DEBUG ){ printf("  BEGIN: dequeue \n"); }
	
	if( queue->count > 0 ){

		/* set the value passed in to the value of the tail node */
		void* value = &queue->front->value;
		
		/* BEGIN: removal of node containing value from queue */
		curlyqueue_node_t *old_tail	= queue->front;
		curlyqueue_node_t *new_tail	= queue->front->prev;
		
		/* reassign the tail */
		queue->front = new_tail;
		
		/* reassign next ptr of new tail if tail != NULL */
		if( NULL == new_tail ){
			
			/* if new tail is null, the list is empty, so reassign head too */
			queue->back = NULL;		
			
		}else{
			new_tail->next = NULL;
		}
		
		/* destroy old tail  */
		free( old_tail );		
		
		queue->count--;
	}	
	
//	if( DEBUG ){ printf("  END: dequeue \n"); }
}

void curly_insert_node( curlyqueue_t* queue, curlyqueue_node_t* node ){
	
	curlyqueue_node_t* prev = node->prev;
	curlyqueue_node_t* next = node->next;
	
	if( NULL != prev ){
		prev->next = node;
	}else{
		queue->back = node;
	}
	
	if( NULL != next ){
		next->prev = node;
	}else{
		queue->front = node;
	}
	
	queue->count++;
}

void curly_delete( curlyqueue_t* queue, curlyqueue_node_t* node ){

//	if( DEBUG ){ printf("  END: deletevalue \n"); }
}

/**
 * A simple function that checks if a queue
 * is empty or not
 * 
 * @param	queue The queue to check.
 * 
 * @return	1, if the queue is empty
 * @return 	0 if not empty
 */
int curly_queue_is_empty( curlyqueue_t* queue ){
	if( 0 == queue->count ){
		return 1;
	}else{
		return 0;
	}
}




