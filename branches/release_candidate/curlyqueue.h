#ifndef CURLYQUEUE_H_
#define CURLYQUEUE_H_

#ifndef NULL
#define NULL	0
#endif

typedef struct	except_t			except_t;
typedef struct	curlyqueue_node_t 	curlyqueue_node_t;
typedef	struct	curlyqueue_t		curlyqueue_t;
typedef struct 	iterator_t*			curlyqueue_iterator;

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
	curlyqueue_node_t*	back;
	curlyqueue_node_t*	front;
	curlyqueue_node_t*	iterator;
	int count;
};

/**
 *  a node in a doubly linked list (dll). 
 */
struct curlyqueue_node_t {
	void*				value;
	curlyqueue_node_t* 	prev;
	curlyqueue_node_t* 	next;
};

/* BEGIN: method list */

/* BEGIN: queue management */
curlyqueue_t*	curlyqueue_create_queue();
void			curlyqueue_destroy_queue( curlyqueue_t* );

void	curlyqueue_enqueue( curlyqueue_t* queue, void* value );
void*	curlyqueue_dequeue( curlyqueue_t* queue, except_t* e );

int	curlyqueue_is_empty( curlyqueue_t* );
/* END: queue management */

/* BEGIN: iterator */
int curlyqueue_iterator_has_next( curlyqueue_t* queue, except_t* e );
int curlyqueue_iterator_has_prev( curlyqueue_t* queue, except_t* e );

void curlyqueue_iterator_step_forward( curlyqueue_t* queue, except_t* e );
void curlyqueue_iterator_step_backward( curlyqueue_t* queue, except_t* e );

void curlyqueue_iterator_jump_to_front( curlyqueue_t* queue );
void curlyqueue_iterator_jump_to_back( curlyqueue_t* queue );
/* END: iterator */

/* BEGIN: insert, delete, and get value */
void*	curlyqueue_get_value_at_iterator( curlyqueue_t* queue, except_t* e );
void	curlyqueue_delete_value_at_iterator( curlyqueue_t* queue, except_t* e );
void	curlyqueue_insert_value_before_iterator( curlyqueue_t* queue, void* value, except_t* e );
void	curlyqueue_insert_value_after_iterator( curlyqueue_t* queue, void* value, except_t* e );
/* END: insert, delete, and get value */

/* END: method list */

#endif /*CURLYQUEUE_H_*/
