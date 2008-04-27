extern void test_suite_core();
extern void test_suite_iterator();
extern void test_suite_insert_and_delete();

int main() {

	test_suite_core();
	test_suite_iterator();
	test_suite_insert_and_delete();
	
	return 0;
}

