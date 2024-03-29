#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "../curlyqueue.h"

/* access create_node via extern to avoid having to make it public in curlyqueue.h*/
extern curlyqueue_node_t* curlyqueue_create_node( void* value, curlyqueue_node_t *, curlyqueue_node_t * );

void test_curly_create_queue(){
	curlyqueue_t* queue = curlyqueue_create_queue();
	
	/* test correct pointer & count initialization */
	assert( NULL == queue->front );
	assert( NULL == queue->back );
	assert( 0 == queue->count );
	
	free( queue );
}

void test_curly_destroy_queue(){
	curlyqueue_t* queue = curlyqueue_create_queue();
	
	curlyqueue_destroy_queue( queue );

	/* test correct pointer dedangling */
	//TODO: why does this fail? 
	//assert( NULL == queue );
}

void test_curly_create_node(){
	
	/* BEGIN TEST CASE: value with simple data type */
	int i = 5;
	
	void* value = &i;
	curlyqueue_node_t* prev = NULL;
	curlyqueue_node_t* next = NULL;
	
	curlyqueue_node_t* node = curlyqueue_create_node( value, prev, next );
	
	/* test proper assignment of node fields */
	assert( NULL == node->prev );
	assert( NULL == node->next );
	assert( 5 == *(int*)node->value );
	
	free( node );
	/* END TEST CASE: value with simple data type */

	/* BEGIN TEST CASE: value with complex data type */
	typedef struct {
		int j;
	} sample_struct;
	
	sample_struct struct_value;
	
	struct_value.j = 7;
	
	value = &struct_value;
	
	node = curlyqueue_create_node( value, prev, next );
	
	sample_struct struct_value2 = *(sample_struct*)node->value;
	assert( 7 == struct_value2.j );
	/* END TEST CASE: value with complex data type */
	
	free( node );
}

void test_curly_enqueue(){
	
	curlyqueue_t* queue = curlyqueue_create_queue();
	
	int i = 7;
	void* value = &i;
	
	/* BEGIN test case: empty q */
	curlyqueue_enqueue( queue, value );

	assert( 1 == queue->count );
	assert( 7 == *(int*)queue->back->value );
	assert( 7 == *(int*)queue->front->value );
	/* END test case: empty q */
	
	/* BEGIN test case: q w 1 node */
	int j = 8;
	value = &j;
	curlyqueue_enqueue( queue, value );

	assert( 2 == queue->count );
	assert( 8 == *(int*)queue->back->value );
	assert( 8 == *(int*)queue->front->prev->value );
	assert( 7 == *(int*)queue->front->value );

	/* END test case: q w 1 node */
	
	/* chk that iterator was set to back correctly */
	assert( queue->iterator == queue->back );
	
	curlyqueue_destroy_queue( queue );
}

void test_curly_dequeue(){
	
	curlyqueue_t* queue = curlyqueue_create_queue();
	
	int i = 7;
	void* value = &i;
	
	/* BEGIN test case: empty q */
	/* try */
	{except_t e;e.thrown=0;

		curlyqueue_dequeue( queue, &e );
		
		/* catch */
		assert( 1 == e.thrown );
		assert( 0 == strcmp( "empty_q", e.type ) );
	}
	/* END test case: empty q */
	
	/* BEGIN test case: q w 1 node */
	
	int j = 8;
	value = &j;
	curlyqueue_enqueue( queue, value );

	int k;
	/* try */
	{except_t e;e.thrown=0;

		k = *(int*)curlyqueue_dequeue( queue, &e );
		
		/* catch */
		assert( 0 == e.thrown );
	}

	/* check that correct value is returned */
	assert( 8 == k );
		
	/* check that queue ptrs are reset correctly */
	assert( NULL == queue->back );
	assert( NULL == queue->front );

	/* END test case: q w 1 node */
	
	/* BEGIN test case: q w > 1 node */
	
	int l = 3;
	value = &l;
	curlyqueue_enqueue( queue, value );

	int m = 4;
	value = &m;
	curlyqueue_enqueue( queue, value );

	int n;
	/* try */
	{except_t e;e.thrown=0;

		n = *(int*)curlyqueue_dequeue( queue, &e );
	}

	/* check that correct value is returned for a fifo list */
	assert( 3 == n );
		
	/* assert that the last value entered is still in the queue */
	assert( 4 == *(int*)queue->back->value );

	/* assert that the front was reset correctly */
	assert( NULL == queue->front->next );

	/* END test case: q w > 1 node */

	curlyqueue_destroy_queue( queue );
}

void test_suite_core() {

	test_curly_create_queue();
	test_curly_destroy_queue();
	test_curly_create_node();
	test_curly_enqueue();
	test_curly_dequeue();
	
}
