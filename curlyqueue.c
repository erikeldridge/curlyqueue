#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curlyqueue.h"

/**
 * A datatype to help implement exception handling
 * @field	thrown	A quasi-Boolean value indicating
 * 			if an exception was thrown (1) 
 * 			or not (0).
 * @field	type	A short string to describe the 
 * 			type of exception thrown
 */
struct except_t {
	int thrown;
	char type[10];
};

/**
 * The head, tail, and count of a doubly linked list (dll).  
 * Used for managing a dll 
 */
struct curlyqueue_t {
	curlyqueue_node back;
	curlyqueue_node front;
	int count;
};

/**
 *  a node in a doubly linked list (dll). 
 */
struct curlyqueue_node_t {
	void*			value;
	curlyqueue_node 	prev;
	curlyqueue_node 	next;
};

/**
 * Creates new list node
 * @pre		calling fn has determined prev and next pointers
 * @post	mem has been allocated for new node and
 * 		and node field values have been assigned
 * @note	calling fn must free mem!
 */
curlyqueue_node curly_create_node( void* value, curlyqueue_node prev, curlyqueue_node next ){
	
	curlyqueue_node node = ( curlyqueue_node )malloc( sizeof( struct curlyqueue_node_t ) );
	
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
curlyqueue curly_create_queue(){
	
	curlyqueue queue = malloc( sizeof( curlyqueue_t ) );
	
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
void curly_destroy_queue( curlyqueue queue ){
	
	/**
	 the current node
	 */
	curlyqueue_node curr = queue->back;
		
	/**
	 the node after current node
	 */
	curlyqueue_node next;
	
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
void curly_enqueue( curlyqueue queue, void* value ){
	
	curlyqueue_node prev = NULL;
	curlyqueue_node next = queue->back;
	
	curlyqueue_node node = curly_create_node( value, prev, next );
	
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

/**
 * @except	throws "empty_q" exception if q is empty
 */
void* curly_dequeue( curlyqueue queue, except_t* e ){
	
	if( curly_queue_is_empty( queue ) ){
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
		curlyqueue_node old_front	= queue->front;
		curlyqueue_node new_front	= queue->front->prev;

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
int curly_queue_is_empty( curlyqueue queue ){
	if( 0 == queue->count ){
		return 1;
	}else{
		return 0;
	}
}


/**
 * Inserts a value into the q at the position before the node pointed at by the marker
 * @post	Mem has been allocated for a new node, a node was created,and the 
 * 		value is now in the queue
 * @note	The calling function is responsible for freeing the memory allocated
 */
void curly_insert_before( curlyqueue queue, curlyqueue_node marker, void* value ){
	

	if( curly_queue_is_empty( queue ) || ( marker == queue->back ) ){

		curly_enqueue( queue, value );

	} else {

		curlyqueue_node_t *prev = marker->prev;
		curlyqueue_node_t *next = marker;

		curlyqueue_node node = curly_create_node( value, prev, marker );

		marker->prev->next	= node;
		marker->prev	 	= node;

		queue->count++;
	}
}

void curly_delete( curlyqueue queue, curlyqueue_node node ){

//	if( DEBUG ){ printf("  END: deletevalue \n"); }
}






