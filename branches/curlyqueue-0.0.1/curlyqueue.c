#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curlyqueue.h"

/**
 * Creates new list node
 * @pre		calling fn has determined prev and next pointers
 * @post	mem has been allocated for new node and
 * 		and node field values have been assigned
 * @note	calling fn must free mem!
 */
curlyqueue_node_t* curlyqueue_create_node( void* value, curlyqueue_node_t* prev, curlyqueue_node_t* next ){
	
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
curlyqueue_t* curlyqueue_create_queue(){
	
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
void curlyqueue_destroy_queue( curlyqueue_t* queue ){
	
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
void curlyqueue_enqueue( curlyqueue_t* queue, void* value ){
	
	curlyqueue_node_t* prev = NULL;
	curlyqueue_node_t* next = queue->back;
	
	curlyqueue_node_t* node = curlyqueue_create_node( value, prev, next );
	
	/* if this is the first node, the tail = the head*/
	if( curlyqueue_is_empty( queue ) ){
		
		queue->front = node;
		
	}else{
		
		queue->back->prev = node;
		
	}
	
	queue->back = node;
	
	/* increment the list's internal count of nodes */
	queue->count++;	
}

/**
 * @except	throws "empty_q" exception if q is empty
 */
void* curlyqueue_dequeue( curlyqueue_t* queue, except_t* e ){
	
	if( curlyqueue_is_empty( queue ) ){
		/* throw exception */
		e->thrown = 1;
		memcpy( e->type, "empty_q", 8 );
		return NULL;
	}

	/* store the value of the node currently at the front of the q */
	void* value = queue->front->value;

	if( 1 == queue->count ){

		free( queue->front );

		/* dedangle pointers */
		queue->front	= NULL;
		queue->back	= NULL;

	}else{
		curlyqueue_node_t* old_front	= queue->front;
		curlyqueue_node_t* new_front	= queue->front->prev;

		queue->front = new_front;
		new_front->next = NULL;

		free( old_front );		
	}

	queue->count--;

	return value;
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
int curlyqueue_is_empty( curlyqueue_t* queue ){
	if( 0 == queue->count ){
		return 1;
	}else{
		return 0;
	}
}





