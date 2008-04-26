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
    
	int j = 2;
	void *value = &j;
	curly_enqueue( queue, value );
	
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
	
	curly_reset_iterator( queue );
	
	
	int i;
	for( i = 0; i < 10; i++ ){
	    {except_t e;e.thrown=0;
	    	curly_advance_iterator( queue, &e );
	    	if( 1 == e.thrown ){
	    		assert( 5 == i );
	    		break;
	    	}
	    } 
	}
    /* END test case: items in queue*/
	

    /* BEGIN test case: advance past front */
    /* END test case: advance past front */
	
	curly_destroy_queue( queue );
	
}

void test_suite_iterator() {

	test_curly_curly_advance_iterator();
	
}