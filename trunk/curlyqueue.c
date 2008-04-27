#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "curlyqueue.h"

struct iterator_t {
	curlyqueue_node_t* node;
};

/**
 * Creates new list node
 * @pre		calling fn has determined prev and next pointers
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
	
	curlyqueue_t* queue = malloc( sizeof( struct curlyqueue_t ) );
	
	queue->back		= NULL;
	queue->front	= NULL;
	queue->iterator	= NULL;
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

/**
 * @except	throws "empty_q" exception if q is empty
 */
void* curly_dequeue( curlyqueue_t* queue, except_t* e ){
	
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
		queue->back		= NULL;

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
int curly_queue_is_empty( curlyqueue_t* queue ){
	if( 0 == queue->count ){
		return 1;
	}else{
		return 0;
	}
}

/**
 * \note
 * You should call this before every iterator walk
 * to obtain predictable results
 */
void curly_reset_iterator( curlyqueue_t* queue ){
	queue->iterator = queue->back;
}

/**
 * @throw	if iterator is currently pointing at NULL, i.e.
 * 			trying to access iter->next would be bad
 * 
 */
void curly_advance_iterator( curlyqueue_t* queue, except_t* e ){
	
	if( NULL == queue->iterator ){
		e->thrown = 1;
		memcpy( e->type, "null_iter", 10 );
		return;
	}
	
	queue->iterator = queue->iterator->next; 
}

/**
 * Moves the iterator backward one item
 * @throws	null_iter	if q iterator is null, which can happen
 * 						if it has not yet been init'd, or if
 * 						q is empty
 */
void curlyqueue_iterator_step_backward( curlyqueue_t* queue, except_t* e ){
	
	/* BEGIN: case: iter is null */
	if( NULL == queue->iterator ){
		e->thrown = 1;
		memcpy( e->type, "null_iter", 10 );
		return;
	}
	/* END: case: iter is null */
	
	/* BEGIN: case: iter not null */
	
	queue->iterator = queue->iterator->prev; 
	
	/* END: case: iter not null */
}

/**
 * Get the value at the point in the queue indicated by the iterator
 */
void* curly_get_value_at_iterator( curlyqueue_t* queue, except_t* e ){
	if( NULL == queue->iterator ){
		/* throw */
		e->thrown = 1;
		memcpy( e->type, "null_iter", 10 );
		return NULL;
	}
	
	return queue->iterator->value;
}

/**
 * Tests if the current list element pointed at by the iterator has 
 * an element after it
 * @throws	empty_q		if queue is empty
 * @throws	null_iter	if iterator is null (use iter_reset to fix if q 
 * 						is non-empty)
 * @return	0	if queue does not have next
 * @return	1	if queue does have next
 * @see	curly_iterator_has_prev
 */
int curly_iterator_has_next( curlyqueue_t* queue, except_t* e ) {
	if( curly_queue_is_empty( queue ) ){
		/* throw */
		e->thrown = 1;
		memcpy( e->type, "empty_q", 10 );
		return -1;
	} else if( NULL == queue->iterator ){
		/* throw */
		e->thrown = 1;
		memcpy( e->type, "null_iter", 10 );
		return -1;
	}
	
	if( NULL == queue->iterator->next ) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * Tests if the current list element pointed at by the iterator has 
 * an element before it
 * @throws	empty_q		if queue is empty
 * @throws	null_iter	if iterator is null (use iter_reset to fix if q 
 * 						is non-empty)
 * @return	0	if queue does not have prev
 * @return	1	if queue does have prev
 * @see	curly_iterator_has_next
 */
int curly_iterator_has_prev( curlyqueue_t* queue, except_t* e ) {
	if( curly_queue_is_empty( queue ) ){
		/* throw */
		e->thrown = 1;
		memcpy( e->type, "empty_q", 10 );
		return -1;
	} else if( NULL == queue->iterator ){
		/* throw */
		e->thrown = 1;
		memcpy( e->type, "null_iter", 10 );
		return -1;
	}
	
	if( NULL == queue->iterator->prev ) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * Inserts a value into the q at the position before the node pointed at by the marker
 * @post	Mem has been allocated for a new node, a node was created,and the 
 * 		value is now in the queue
 * @note	The calling function is responsible for freeing the memory allocated
 */
void curly_insert_before_iterator( curlyqueue_t* queue, curlyqueue_node_t* marker, void* value ){
	

	if( curly_queue_is_empty( queue ) || ( marker == queue->back ) ){

		curly_enqueue( queue, value );

	} else {

		curlyqueue_node_t* prev = marker->prev;

		curlyqueue_node_t* node = curly_create_node( value, prev, marker );

		marker->prev->next	= node;
		marker->prev	 	= node;

		queue->count++;
	}
}

/**
 * @throws	null_iter	if iterator is not set to an element
 */
void curly_delete_value_at_iterator( curlyqueue_t* queue, except_t* e ) {
	
	/* BEGIN: case - iter is uninitialized */
	if ( NULL == queue->iterator ) {
		/* throw */
		e->thrown = 1;
		memcpy( e->type, "null_iter", 10 );
		return;
	}
	/* END: case - iter is uninitialized */
	
	/* BEGIN: case - q count == 1 */
	if ( 1 == queue->count ) {
		{except_t dequeue_exception;dequeue_exception.thrown=0;
			curly_dequeue( queue, &dequeue_exception );
		}
		
		/* dedangle iterator */
		curly_reset_iterator( queue );
	}
	/* END: case - q count == 1 */
	
	/* BEGIN: case - iter points to front */
	else if ( queue->iterator == queue->front ) {
		
		curlyqueue_node_t *old_front = queue->front;
		curlyqueue_node_t *new_front = queue->front->prev;
		
		queue->front	= new_front;
		new_front->next = NULL;
		
		free( old_front );
		
		/* bump iterator back to new front */
	    {except_t e2;e2.thrown=0;
	    	curlyqueue_iterator_step_backward( queue, &e2 );
	    	
	    	if( e2.thrown ){
	    		/* throw */
	    		e->thrown = 1;
	    		memcpy( e->type, e2.type, 10 );
	    		return;
	    	}
	    }
	}
	/* END: case - iter points to front */
	
	/* BEGIN: case - iter points to back */
	else if ( queue->iterator == queue->back ) {
		
		{except_t dequeue_exception;dequeue_exception.thrown=0;
			curly_dequeue( queue, &dequeue_exception );
		}
		
		/* dedangle iterator */
		curly_reset_iterator( queue );
	}
	/* END: case - iter points to back */
	
	/* BEGIN: case - iter points to middle value */
	else {
		curlyqueue_node_t *prev = queue->iterator->prev;
		curlyqueue_node_t *next = queue->iterator->next;
		
		free( queue->iterator );
		
		prev->next = next;
		next->prev = prev;
		
	    {except_t step_back_e;step_back_e.thrown=0;
	    	curlyqueue_iterator_step_backward( queue, &step_back_e );
	    	
	    	if( step_back_e.thrown ){
	    		/* throw */
	    		e->thrown = 1;
	    		memcpy( e->type, step_back_e.type, 10 );
	    		return;
	    	}
	    }
	}
	/* END: case - iter points to middle value */
	
}






