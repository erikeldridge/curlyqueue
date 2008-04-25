#include "curlyqueue.h"

#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
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

int main(){
	test_case_curly_create_queue();
	test_case_curly_destroy_queue();
	test_case_curly_create_node();
	test_case_curly_enqueue();
	return 0;
}
