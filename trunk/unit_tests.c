#include "curlyqueue.h"

#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
/*
	char *here = "-----here-----";
	write( 0, here, 15 );
 */
void test_case_curly_create_queue(){
	curlyqueue_t* queue = curly_create_queue();
	
	/* test correct pointer & count initialization */
	assert( NULL == queue->front );
	assert( NULL == queue->back );
	assert( 0 == queue->count );
	
	free( queue );
}

void test_case_curly_destroy_queue(){
	curlyqueue_t* queue = curly_create_queue();
	
	curly_destroy_queue( queue );

	/* test correct pointer dedangling */
	//TODO: why does this fail? 
	//assert( NULL == queue );
}

void test_case_curly_create_node(){
	
	int i = 5;
	
	void* value = &i;
	curlyqueue_node_t* prev = NULL;
	curlyqueue_node_t* next = NULL;
	
	curlyqueue_node_t* node = curly_create_node( value, prev, next );
	
	/* test proper assignment of node fields */
	assert( NULL == node->prev );
	assert( NULL == node->next );
	assert( 5 == *(int*)node->value );
	
	free( node );

	/* test proper assignment of node fields with sample struct value */
	typedef struct {
		int j;
	} sample_struct;
	
	sample_struct struct_value;
	
	struct_value.j = 7;
	
	value = &struct_value;
	
	node = curly_create_node( value, prev, next );
	
	sample_struct struct_value2 = *(sample_struct*)node->value;
	assert( 7 == struct_value2.j );
	
	free( node );
}

void test_case_curly_enqueue(){
	
	curlyqueue_t* queue = curly_create_queue();
	
	int i = 7;
	void* value = &i;
	
	/* BEGIN: test empty q */
	curly_enqueue( queue, value );

	assert( 1 == queue->count );
	assert( 7 == *(int*)queue->back->value );
	assert( 7 == *(int*)queue->front->value );
	/* END: test empty q */
	
	/* BEGIN: test q w 1 node */
	int j = 8;
	value = &j;
	curly_enqueue( queue, value );

	assert( 2 == queue->count );
	assert( 8 == *(int*)queue->back->value );
	assert( 8 == *(int*)queue->front->prev->value );
	assert( 7 == *(int*)queue->front->value );

	/* END: test q w 1 node */
	
	curly_destroy_queue( queue );
}

void test_case_curly_dequeue(){
	
	curlyqueue_t* queue = curly_create_queue();
	
	int i = 7;
	void* value = &i;
	
	/* BEGIN: test empty q */
	/* try */
	{except_t e;e.thrown=0;

		curly_dequeue( queue, &e );
		
		/* catch */
		assert( 1 == e.thrown );
		assert( 0 == strcmp( "empty_q", e.type ) );
	}
	/* END: test empty q */
	
	/* BEGIN: test q w 1 node */
	
	int j = 8;
	value = &j;
	curly_enqueue( queue, value );

	int k;
	/* try */
	{except_t e;e.thrown=0;

		k = *(int*)curly_dequeue( queue, &e );
		
		/* catch */
		assert( 0 == e.thrown );
	}

	/* check that correct value is returned */
	assert( 8 == k );
		
	/* check that queue ptrs are reset correctly */
	assert( NULL == queue->back );
	assert( NULL == queue->front );

	/* END: test q w 1 node */
	
	/* BEGIN: test q w > 1 node */
	
	int l = 3;
	value = &l;
	curly_enqueue( queue, value );

	int m = 4;
	value = &m;
	curly_enqueue( queue, value );

	int n;
	/* try */
	{except_t e;e.thrown=0;

		n = *(int*)curly_dequeue( queue, &e );
	}

	/* check that correct value is returned for a fifo list */
	assert( 3 == n );
		
	/* assert that the last value entered is still in the queue */
	assert( 4 == *(int*)queue->back->value );

	/* assert that the front was reset correctly */
	assert( NULL == queue->front->next );

	/* END: test q w > 1 node */

	curly_destroy_queue( queue );
}


void test_case_curly_insert_before(){
	
	curlyqueue_t* queue = curly_create_queue();

	//assert( 0 == queue->count );	
	//
	/* BEGIN: test w/ empty q */

	/* BEGIN: test insert b4 back */
	int i = 1;
	void* value = &i;
	curly_insert_before( queue, queue->back, value );
	
	assert( 1 == *(int*)queue->back->value );
	assert( 1 == *(int*)queue->front->value );

	assert( NULL == queue->back->prev );
	assert( NULL == queue->front->next );

	//assert( 1 == queue->count );
	//printf("%d \n", queue->count);
	
	/* clear out q for next test */
	{except_t e;e.thrown=0;
		curly_dequeue( queue, &e );
		assert( 0 == e.thrown );/* for sanity */
	}
	assert( 0 == queue->count );/* sanity check */
	/* END: test insert b4 back */

	/* BEGIN: test insert b4 front */

	int j = 2;
	value = &j;
	curly_insert_before( queue, queue->front, value );
	
	assert( 1 == queue->count );
	assert( 2 == *(int*)queue->back->value );
	assert( 2 == *(int*)queue->front->value );
	assert( NULL == queue->back->prev );
	assert( NULL == queue->front->next );
	/* END: test insert b4 front */

	/* END: test w/ empty q */

	/* BEGIN: test w/ non-empty q */
	int k = 3;
	value = &k;
	curly_enqueue( queue, value );

	int l = 4;
	value = &l;
	curly_enqueue( queue, value );

	int m = 5;
	value = &m;
	curly_enqueue( queue, value );

	int n = 6;
	value = &n;
	curly_enqueue( queue, value );

	assert( 5 == queue->count );

	int o = 7;
	value = &o;
	curlyqueue_node_t *marker = queue->back->next->next;
	curly_insert_before( queue, marker, value );

	/* assert front and back nodes were note altered*/
	assert( 6 == *(int*)queue->back->value );
	assert( 2 == *(int*)queue->front->value );

	/* assert new value (7) is correctly positioned */
	assert( 3 == *(int*)marker->next->value );
	assert( 7 == *(int*)marker->prev->value );
	assert( 5 == *(int*)marker->prev->prev->value );
	
	/* END: test empty q */
	
	/* BEGIN: test q w 1 node */
	/*
	int j = 8;
	value = &j;
	curly_enqueue( queue, value );

	assert( 2 == queue->count );
	assert( 8 == *(int*)queue->back->value );
	assert( 8 == *(int*)queue->front->prev->value );
	assert( 7 == *(int*)queue->front->value );
	*/
	/* END: test q w 1 node */
	
	curly_destroy_queue( queue );
}
int main(){
	test_case_curly_create_queue();
	test_case_curly_destroy_queue();
	test_case_curly_create_node();
	test_case_curly_enqueue();
	test_case_curly_dequeue();
	test_case_curly_insert_before();
	return 0;
}
