# define variables
CC		= gcc
CC_FLAGS	= -Wall -g
TARGET		= test_runner
LIB			= ../libcurlyqueue.a
INC			= -I ../
TEST_SUITES	= test_suite_core.o test_suite_iterator.o test_suite_insert_and_delete.o

# link test runner object and curlyqueue lib
$(TARGET)	: $(TARGET).o $(TEST_SUITES)
			$(CC) $(CC_FLAGS) $(TARGET).o $(TEST_SUITES) $(LIB) -o $(TARGET) 
			rm *.o

# build test runner obj
$(TARGET).o	:
			gcc -c $(TARGET).c -o $(TARGET).o

# BEGIN: build test suite objects
# To add another suite, copy the two lines below, 
# switch out the names, and add the object name as 
# a top-level-target dependency
test_suite_core.o	: 
			gcc -c $(INC) test_suite_core.c -o test_suite_core.o

test_suite_iterator.o	: 
			gcc -c $(INC) test_suite_iterator.c -o test_suite_iterator.o
			
test_suite_insert_and_delete.o	: 
			gcc -c $(INC) test_suite_insert_and_delete.c -o test_suite_insert_and_delete.o
			
# END: build test suite objects

# if valgrind (http://valgrind.org/) is installed, 
# it can be used to verify allocated memory was freed
memchk		: $(TARGET)
			valgrind ./$(TARGET)
			
