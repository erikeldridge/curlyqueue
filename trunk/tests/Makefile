# define variables
CC		= gcc
CC_FLAGS	= -Wall -g
TARGET		= test_runner
LIB		= ../libcurlyqueue.a
INC		= -I ../

# link test runner object and curlyqueue lib
$(TARGET)	: $(TARGET).o test_suite_core.o
			$(CC) $(CC_FLAGS) $(TARGET).o test_suite_core.o $(LIB) -o $(TARGET) 
			rm $(TARGET).o
			rm test_suite_core.o

# build test runner obj
$(TARGET).o	:
			gcc -c $(TARGET).c -o $(TARGET).o

# BEGIN: build test suite objects
# To add another suite, copy the two lines below, 
# switch out the names, and add the object name as 
# a top-level-target dependency
test_suite_core.o	: 
			gcc -c $(INC) test_suite_core.c -o test_suite_core.o

# END: build test suite objects

# if valgrind (http://valgrind.org/) is installed, 
# it can be used to verify allocated memory was freed
memchk		: $(TARGET)
			valgrind ./$(TARGET)
			
