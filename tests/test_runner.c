#include "unit_test_util.h"

extern void test_suite_core();
extern void test_suite_iterator();
extern void test_suite_insert_and_delete();

int main() {

	ADD_SUITE( test_suite_core );
	ADD_SUITE( test_suite_iterator );
	ADD_SUITE( test_suite_insert_and_delete );
	
	return 0;
}

