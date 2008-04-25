#ifndef CURLYQUEUE_H_
#define CURLYQUEUE_H_

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
	curlyqueue_node_value_t value;
	curlyqueue_node_t *prev;
	curlyqueue_node_t *next;
};

/* BEGIN: method list */
curlyqueue_t 		curly_create_queue();
void				curly_destroy_queue( struct DLL * );
void				curly_display_queue( struct DLL );
curlyqueue_node_t* 	curly_create_node( curlyqueue_node_value_t, curlyqueue_node_t *, curlyqueue_node_t * );
void				curly_enqueue( queue_t *, pcb_t );
void				curly_dequeue( queue_t *, pcb_t * );
void				curly_insert_node( queue_t*, pcb_t );
int					curly_delete_node( queue_t*, pcb_t );
int					curly_queue_is_empty( queue_t );
/* END: method list */

#endif /*CURLYQUEUE_H_*/
