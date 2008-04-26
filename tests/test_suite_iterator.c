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

void test_suite_iterator() {

	test_curly_curly_advance_iterator();
	
}