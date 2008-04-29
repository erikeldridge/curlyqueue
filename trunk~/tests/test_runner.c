#include "unit_test_util.h"

extern void test_suite_core();
extern void test_suite_iterator();
extern void test_suite_insert_and_delete();

int main() {

	BEGIN_RUNNER()
	
		ADD_SUITE( test_suite_core )
		ADD_SUITE( test_suite_iterator )
		ADD_SUITE( test_suite_insert_and_delete )
	
	END_RUNNER()
	
	return 0;
}

