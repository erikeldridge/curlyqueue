#ifndef CURLYQUEUE_H_
#define CURLYQUEUE_H_

#ifndef NULL
#define NULL	0
#endif

typedef struct	except_t			except_t;
typedef struct	curlyqueue_node_t* 	curlyqueue_node;
typedef	struct	curlyqueue_t*		curlyqueue;

/* BEGIN: method list */

curlyqueue_node_t* 	curly_create_node( void* value, curlyqueue_node, curlyqueue_node );

curlyqueue	 		curly_create_queue();
void				curly_destroy_queue( curlyqueue );

void				curly_enqueue( curlyqueue queue, void* value );
void*				curly_dequeue( curlyqueue queue, except_t* e );

int					curly_queue_is_empty( curlyqueue );

void				curly_insert_before( curlyqueue queue, curlyqueue_node node, void* value );

/* In the works ...
curlyqueue_node_t*	curly_iterator_next( curlyqueue_node_t* node );
int			curly_iterator_has_next( curlyqueue_node_t* node );
void			curly_delete( curlyqueue_t*, curlyqueue_node_t* node );
*/

/* END: method list */

#endif /*CURLYQUEUE_H_*/
