#include "../curlyqueue.h"

#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void test_curly_curly_advance_iterator(){
	
	curlyqueue_t* queue = curly_create_queue();
	
	/* BEGIN test case: empty queue */
	
    {except_t e;e.thrown=0;
    	curly_advance_iterator( queue, &e );
    	assert( 1 == e.thrown );
    }  
	/* END test case: empty queue */
    
    /* BEGIN test case: items in queue */
    
    /* load q with sequence of integers, 
     * so we can base value assertions on
     * a loop index 
     */
	int j = 4;
	void *value = &j;
	curly_enqueue( queue, value );
	
	int k = 3;
	value = &k;
	curly_enqueue( queue, value );

	int l = 2;
	value = &l;
	curly_enqueue( queue, value );

	int m = 1;
	value = &m;
	curly_enqueue( queue, value );

	int n = 0;
	value = &n;
	curly_enqueue( queue, value );
	
	/* always a good idea */
	curly_reset_iterator( queue );
	
	/* sanity checks, which should pass after reset */
	assert( queue->iterator != NULL );
	assert( *(int*)queue->iterator->value == 0 );
	
	int val;
	int i;
	for( i = 0; i < 10; i++ ){
	    {except_t e1,e2;e1.thrown=e2.thrown=0;
	    	value = curly_get_value_at_iterator( queue, &e2 );
	    	if( e2.thrown ){/* we have adv iter past end of q */
	    		break;
	    	}
	    	curly_advance_iterator( queue, &e1 );
	    	val = *(int*)value;
	    	/* assert that iterator is advancing correctly */
	    	assert( val == i );
	    } 
	}
    /* END test case: items in queue*/
	

    /* BEGIN test case: advance past front */
	curly_reset_iterator( queue );
	
	for( i = 0; i < 10; i++ ){
	    {except_t e;e.thrown=0;
	    	curly_advance_iterator( queue, &e );
	    	if( 1 == e.thrown ){
	    		/* assert exception is thrown at correct place */
	    		assert( 5 == i );
	    		break;
	    	}
	    } 
	}
    /* END test case: advance past front */
	
	curly_destroy_queue( queue );
	
}

void test_curlyqueue_iterator_step_backward(){
	
	curlyqueue_t* queue = curly_create_queue();
	
	/* BEGIN: case: iter is null */
	{except_t e;e.thrown=0;
		curlyqueue_iterator_step_backward( queue, &e );
		assert( e.thrown );
		assert( strcmp( e.type, "null_iter" ) == 0 );
	}
	/* END: case: iter is null */
	
	/* BEGIN: case: iter not null */
	int j = 4;
	value = &j;
	curly_enqueue( queue, value );
	
	curly_reset_iterator( queue );
	
	{except_t e;e.thrown=0;
		curlyqueue_iterator_step_backward( queue, &e );
		
		/* chk for no exception */
		assert( 0 == e.thrown );
	}
	
	/* check for correct iter setting, which
	 * should be null if a single item list iter
	 * is stepped back 
	 */
	assert( NULL == queue->iterator );
	
	/* END: case: iter not null */
	
	curly_destroy_queue( queue );
}

void test_curly_get_value_at_iterator(){
	curlyqueue_t* queue = curly_create_queue();
	void* value;
	/* BEGIN: test case - empty list */
    {except_t e;e.thrown=0;
    	value = curly_get_value_at_iterator( queue, &e );
    	assert( e.thrown );
    }
	/* END: test case - empty list */
    
	/* BEGIN: test case - non-empty list */
	int j = 4;
	value = &j;
	curly_enqueue( queue, value );
	
	int k = 3;
	value = &k;
	curly_enqueue( queue, value );
	
	curly_reset_iterator( queue );
	
	/* assert that get_value does not throw exception 
	 * if called while iterator is pointed at a valid element
	 * in list, as ensured by reset_iter 
	 */
    {except_t e;e.thrown=0;
    	value = curly_get_value_at_iterator( queue, &e );
    	assert( 0 == e.thrown );
    }
    
    /*
     * assert correct value is returned
     */
    assert( 3 == *(int*)value );
    
	/* END: test case - non-empty list */
	curly_destroy_queue( queue );
}

void test_curly_iterator_has_next(){
	
	curlyqueue_t* queue = curly_create_queue();
	void* value;
	
	/* BEGIN: test case - empty list */
    {except_t e;e.thrown=0;
    	curly_iterator_has_next( queue, &e );
    	assert( strcmp( e.type, "empty_q" ) == 0 );
    }
    
	/* END: test case - empty list */
    
	/* BEGIN: test case - uninitialized iter */
	int i = 4;
	value = &i;
	curly_enqueue( queue, value );
	
    {except_t e;e.thrown=0;
    	curly_iterator_has_next( queue, &e );
    	assert( strcmp( e.type, "null_iter" ) == 0 );
    }    
	/* END: test case - uninitialized iter */
	
	/* BEGIN: test case - valid case, no except thrown */
    /* add another value to q */
	int j = 3;
	value = &j;
	curly_enqueue( queue, value );
	
	/* point iter at 3 */
	curly_reset_iterator( queue );
	
    {except_t e;e.thrown=0;
    	curly_iterator_has_next( queue, &e );
    	assert( 0 == e.thrown );
    }
	/* END: test case - valid case, no except thrown */
    
	/* BEGIN: test case - has next */
    {except_t e;e.thrown=0;
    	curly_iterator_has_next( queue, &e );
    	assert( curly_iterator_has_next( queue, &e ) );
    }
	/* END: test case - has next */
    
	/* BEGIN: test case - does not have next */
    /* adv iter to 4 */
    {except_t e;e.thrown=0;
    	curly_advance_iterator( queue, &e );
    } 
    
    {except_t e;e.thrown=0;
    	curly_iterator_has_next( queue, &e );
    	assert( 0 == curly_iterator_has_next( queue, &e ) );
    }
	/* END: test case - does not have next  */
	
	curly_destroy_queue( queue );
}

void test_curly_iterator_has_prev(){
	
	curlyqueue_t* queue = curly_create_queue();
	void* value;
	
	/* BEGIN: test case - empty list */
    {except_t e;e.thrown=0;
    	curly_iterator_has_prev( queue, &e );
    	assert( strcmp( e.type, "empty_q" ) == 0 );
    }
    
	/* END: test case - empty list */
    
	/* BEGIN: test case - uninitialized iter */
	int i = 4;
	value = &i;
	curly_enqueue( queue, value );
	
    {except_t e;e.thrown=0;
    	curly_iterator_has_prev( queue, &e );
    	assert( strcmp( e.type, "null_iter" ) == 0 );
    }    
	/* END: test case - uninitialized iter */
	
	/* BEGIN: test case - valid case, no except thrown */
    /* add another value to q */
	int j = 3;
	value = &j;
	curly_enqueue( queue, value );
	
	/* point iter at 3 */
	curly_reset_iterator( queue );
	
    {except_t e;e.thrown=0;
    	curly_iterator_has_prev( queue, &e );
    	assert( 0 == e.thrown );
    }
	/* END: test case - valid case, no except thrown */
    
	/* BEGIN: test case - does not have prev */    
    {except_t e;e.thrown=0;
    	assert( 0 == curly_iterator_has_prev( queue, &e ) );
    }
	/* END: test case - does not have prev  */

	/* BEGIN: test case - has prev */
    /* adv iter to 3 */
    {except_t e;e.thrown=0;
    	curly_advance_iterator( queue, &e );
    	curly_advance_iterator( queue, &e );
    }
    
    {except_t e;e.thrown=0;
    	assert( curly_iterator_has_prev( queue, &e ) );
    }
	/* END: test case - has prev */
    
	curly_destroy_queue( queue );
}

void test_suite_iterator() {

	test_curly_get_value_at_iterator();
	test_curly_curly_advance_iterator();
	test_curlyqueue_iterator_step_backward();
	test_curly_iterator_has_next();
	test_curly_iterator_has_prev();
	
}