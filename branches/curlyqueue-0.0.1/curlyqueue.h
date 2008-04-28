#ifndef CURLYQUEUE_H_
#define CURLYQUEUE_H_

#ifndef NULL
#define NULL	0
#endif

typedef struct	except_t		except_t;
typedef struct	curlyqueue_node_t 	curlyqueue_node_t;
typedef	struct	curlyqueue_t		curlyqueue_t;

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
	curlyqueue_node_t* back;
	curlyqueue_node_t* front;
	int count;
};

/**
 *  a node in a doubly linked list (dll). 
 */
struct curlyqueue_node_t {
	void*			value;
	curlyqueue_node_t* 	prev;
	curlyqueue_node_t* 	next;
};

/* BEGIN: method list */

curlyqueue_node_t* 	curlyqueue_create_node( void* value, curlyqueue_node_t *, curlyqueue_node_t * );

curlyqueue_t* 		curlyqueue_create_queue();
void			curlyqueue_destroy_queue( curlyqueue_t* );

void			curlyqueue_enqueue( curlyqueue_t* queue, void* value );
void*			curlyqueue_dequeue( curlyqueue_t* queue, except_t* e );

int			curlyqueue_is_empty( curlyqueue_t* );

/* END: method list */

#endif /*CURLYQUEUE_H_*/
