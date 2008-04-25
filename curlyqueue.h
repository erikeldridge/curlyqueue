#ifndef CURLYQUEUE_H_
#define CURLYQUEUE_H_

#ifndef NULL
#define NULL	0
#endif

#ifdef DEBUG
//int DEBUG = 0;
#else
//int DEBUG = 1;
#endif

typedef struct curlyqueue_node	curlyqueue_node_t;

/**
 * The head, tail, and count of a doubly linked list (dll).  
 * Used for managing a dll 
 */
typedef struct curlyqueue_t {
	curlyqueue_node_t* back;
	curlyqueue_node_t* front;
	int count;
} curlyqueue_t;

/**
 * define this as you need
 */
typedef struct curlyqueue_node_value_t {
	
} curlyqueue_node_value_t;

/**
 *  a node in a doubly linked list (dll). 
 */
struct curlyqueue_node {
	void* 				value;
	curlyqueue_node_t* 	prev;
	curlyqueue_node_t* 	next;
};

/* BEGIN: method list */
curlyqueue_t* 		curly_create_queue();
void				curly_destroy_queue( curlyqueue_t* );
void				curly_display_queue( curlyqueue_t* );
curlyqueue_node_t* 	curly_create_node( void* value, curlyqueue_node_t *, curlyqueue_node_t * );
void				curly_enqueue( curlyqueue_t* queue, void* value );
void*				curly_dequeue( curlyqueue_t* queue );
curlyqueue_node_t*	curly_search( void* value );
void				curly_insert_node( curlyqueue_t* queue, curlyqueue_node_t* node );
void				curly_delete( curlyqueue_t*, curlyqueue_node_t* node );
int					curly_queue_is_empty( curlyqueue_t* );
/* END: method list */

#endif /*CURLYQUEUE_H_*/
