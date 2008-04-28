#include "../curlyqueue.h"
#include "unit_test_util.h"

#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/*
void test_case_curly_insert_before(){
	
	curlyqueue_t* queue = curly_create_queue();

	//assert( 0 == queue->count );	
	//
	// BEGIN: test w/ empty q

	// BEGIN: test insert b4 back
	int i = 1;
	void* value = &i;
	curly_insert_before( queue, queue->back, value );
	
	assert( 1 == *(int*)queue->back->value );
	assert( 1 == *(int*)queue->front->value );

	assert( NULL == queue->back->prev );
	assert( NULL == queue->front->next );

	//assert( 1 == queue->count );
	//printf("%d \n", queue->count);
	
	// clear out q for next test
	{except_t e;e.thrown=0;
		curly_dequeue( queue, &e );
		assert( 0 == e.thrown );// for sanity
	}
	assert( 0 == queue->count );// sanity check
	// END: test insert b4 back

	// BEGIN: test insert b4 front

	int j = 2;
	value = &j;
	curly_insert_before( queue, queue->front, value );
	
	assert( 1 == queue->count );
	assert( 2 == *(int*)queue->back->value );
	assert( 2 == *(int*)queue->front->value );
	assert( NULL == queue->back->prev );
	assert( NULL == queue->front->next );
	// END: test insert b4 front

	// END: test w/ empty q

	// BEGIN: test w/ non-empty q
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

	// assert front and back nodes were note altered
	assert( 6 == *(int*)queue->back->value );
	assert( 2 == *(int*)queue->front->value );

	// assert new value (7) is correctly positioned
	assert( 3 == *(int*)marker->next->value );
	assert( 7 == *(int*)marker->prev->value );
	assert( 5 == *(int*)marker->prev->prev->value );
	
	// END: test empty q
	
	
	curly_destroy_queue( queue );
}
*/

void test_curly_delete_value_at_iterator() {
	
	curlyqueue_t* queue = curly_create_queue();
	void* value;
	
	/* BEGIN: case - iter is uninitialized */
	{except_t e;e.thrown=0;
		//write( 1, "-- suite case: uninit --\n", sizeof( "-- suite case: uninit --\n" ) );
		curlyqueue_delete_value_at_iterator( queue, &e );
		assert( e.thrown );
		assert( strcmp( e.type, "null_iter" ) == 0 );
	}
	
	/* BEGIN: case - q count == 1 */
	int i = 1;
	value = &i;
	curly_enqueue( queue, value );

	curlyqueue_iterator_jump_to_back( queue );
	
	{except_t e;e.thrown=0;
		//write( 1, "-- suite case: 1 --\n", sizeof( "-- suite case: 1 --\n") );
		curlyqueue_delete_value_at_iterator( queue, &e );
		
		/* check except not thrown */
		assert( 0 == e.thrown );
	}
	
	/* chk iter set to back */
	assert( queue->iterator == queue->back );
	
	/* BEGIN: case - iter points to front */
	int j = 2;
	value = &j;
	curly_enqueue( queue, value );

	int h = 3;
	value = &h;
	curly_enqueue( queue, value );
	
	curlyqueue_iterator_jump_to_back( queue );
	
	assert( 3 == *(int*)queue->iterator->value );/* sanity chk */
	
	/* move iter fwd to front */
    {except_t e;e.thrown=0;
    	curlyqueue_iterator_step_forward( queue, &e );
    	
    	/* sanity chk */
    	assert( queue->iterator == queue->front );
    	assert( 2 == *(int*)queue->iterator->value );
    }
    
	{except_t e;e.thrown=0;
		//write( 1, "-- suite case: front --\n", sizeof( "-- suite case: front --\n" ) );
		curlyqueue_delete_value_at_iterator( queue, &e );
		
		/* check except not thrown */
		assert( 0 == e.thrown );
	}
	
	/* chk iter set to new front 
	 * (which happens to be the back 
	 * if only two items were in the queue)
	 */
	assert( queue->iterator == queue->back );
	
	/* BEGIN: case - iter points to back */
	curlyqueue_iterator_jump_to_back( queue );
	
	{except_t e;e.thrown=0;
		//write( 1, "-- suite case: back --\n", sizeof( "-- suite case: back --\n" ) );
		assert( queue->count == 1);
		curlyqueue_delete_value_at_iterator( queue, &e );
		
		/* check except not thrown */
		assert( 0 == e.thrown );
	}
	
	assert( curly_queue_is_empty( queue ) );/* sanity chk */
	
	/* chk iterator correctly reset */
	assert( queue->iterator == queue->back );
	
	curly_destroy_queue( queue );
}

void test_curlyqueue_insert_value_before_iterator() {
//	curlyqueue_insert_value_before_iterator( curlyqueue_t* queue, void* value, except_t* e );

	curlyqueue_t* queue = curly_create_queue();
	void* value;
	
	int i = 7;
	value = & i;
	
	/* BEGIN: case - q empty */
	{except_t e;e.thrown=0;
		curlyqueue_insert_value_before_iterator( queue, value, &e );
		assert( e.thrown );
		assert( strcmp( e.type, "null_iter" ) == 0 );
	}
	
	/* BEGIN: case - count == 1 or iter == back */
	curly_enqueue( queue, value );
	
	int j = 8;
	value = &j;
	
	{except_t e;e.thrown=0;
		curlyqueue_insert_value_before_iterator( queue, value, &e );
		assert( 0 == e.thrown );
	}
	
	/* chk if count has increased */
	assert( 2 == queue->count );
	
	/* chk if back == new value */
	assert( 8 == *(int*)queue->back->value );
	
	/* chk if iter points to back (for sanity; this 
	 * should be ensured by enqueue() tests )
	 */
	assert( queue->iterator == queue->back );
	
	/* for kicks, roll iter fwd and check value */
	{except_t e;e.thrown=0;
		curlyqueue_iterator_step_forward( queue, &e );
	}
	assert( 7 == *(int*)queue->iterator->value );
	
	/* BEGIN: case - iter points to middle */
	
	int k = 9;
	value = &k;
	
	curly_enqueue( queue, value );
	
	int l = 10;
	value = &l;
	
	curly_enqueue( queue, value );
	
	curlyqueue_iterator_jump_to_back( queue );
	
	/* step forward to somewhere between back and front */
	{except_t e;e.thrown=0;
		curlyqueue_iterator_step_forward( queue, &e );
		curlyqueue_iterator_step_forward( queue, &e );
	}
	
	/* sanity chk */
	{except_t e;e.thrown=0;
		int val = *(int*)curly_get_value_at_iterator( queue, &e );
		assert( 8 == val );
	}
	
	/* take a snapshot of the iterator */
	curlyqueue_node_t* iterator_snapshot = queue->iterator;
	
	/* value to insert */
	int m = 11;
	value = &m;
	
	{except_t e;e.thrown=0;
		curlyqueue_insert_value_before_iterator( queue, value, &e );
	}
						
	/* chk that iter hasn't changed */
	assert( queue->iterator == iterator_snapshot );
	
	/* chk iter next is new value */
	{except_t e;e.thrown=0;/* ignored */
		curlyqueue_iterator_step_backward( queue, &e );
		int val = *(int*)curly_get_value_at_iterator( queue, &e );
		assert( 11 == val );
	}
	
	/* BEGIN: test inserting before front in list w/ > 1 elem */
	
	curlyqueue_iterator_jump_to_front( queue );
	
	int n = 12;
	value = &n;
	
	{except_t e;e.thrown=0;
	
		curlyqueue_insert_value_before_iterator( queue, value, &e );
		assert( 0 == e.thrown );/* for sanity */
	
		curlyqueue_iterator_step_backward( queue, &e );
		assert( 0 == e.thrown );
			
		int val = *(int*)curly_get_value_at_iterator( queue, &e );
		assert( 0 == e.thrown );
		
		assert( 12 == val );
	}
	/* END: test inserting before front in list w/ > 1 elem */
	
	/* BEGIN: walk list, printing values 
	curlyqueue_iterator_jump_to_back( queue );
	int val;
	{except_t e;e.thrown=0;//controlled test, so ignore
	
		//print all values except front
		while( curly_iterator_has_next( queue, &e ) ){
	
				val = *(int*)curly_get_value_at_iterator( queue, &e );	
				
				printf("val: %d \n", val );
				
				curlyqueue_iterator_step_forward( queue, &e );
		}
		
		//print front value
		val = *(int*)curly_get_value_at_iterator( queue, &e );	
		
		printf("val: %d \n", val );
	}
	/* END: walk list, printing values */
	
	curly_destroy_queue( queue );
}

/* BEGIN: testing insert_after_iter */
void case_insert_value_after_iterator_in_empty_list(){
	
	curlyqueue_t* queue = curly_create_queue();
	
	void* value;
	
	int i = 0;
	value = &i;
	
	{except_t e;e.thrown=0;
		curlyqueue_insert_value_after_iterator( queue, value, &e );
		assert( e.thrown );
		assert( strcmp( e.type, "null_iter" ) == 0 );
	}
	
	curly_destroy_queue( queue );
}

void case_insert_value_after_iterator_with_single_elem_in_list(){
	
	curlyqueue_t* queue = curly_create_queue();
	
	void* value;
	
	int i = 0;
	value = &i;
	
	curly_enqueue( queue, value );
	
	int j = 1;
	value = &j;
	
	{except_t e;e.thrown=0;
		/* assume enqueue set iter == back */
		curlyqueue_insert_value_after_iterator( queue, value, &e );
		assert( 0 == e.thrown );
	}
	
	/* chk count */
	assert( 2 == queue->count );
	
	/* chk q back == new value */
	assert( 1 == *(int*)queue->back->value );
	
	
	curly_destroy_queue( queue );
}

void test_curlyqueue_insert_value_after_iterator(){
	case_insert_value_after_iterator_in_empty_list();
	case_insert_value_after_iterator_with_single_elem_in_list();
}
/* END: testing insert_after_iter */

void test_suite_insert_and_delete() {

	ADD_TEST( test_curly_delete_value_at_iterator )
	ADD_TEST( test_curlyqueue_insert_value_before_iterator )
	ADD_TEST( test_curlyqueue_insert_value_after_iterator )

}