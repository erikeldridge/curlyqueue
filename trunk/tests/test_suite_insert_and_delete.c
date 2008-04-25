
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