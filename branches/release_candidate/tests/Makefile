# define variables
CC		= gcc
CC_FLAGS	= -Wall -g
TARGET		= test_runner
LIB		= -L ../ -l curlyqueue

# link test runner object and curlyqueue lib
$(TARGET)	: $(TARGET).o
			$(CC) $(CC_FLAGS) $(TARGET).o $(LIB) -o $(TARGET) 
			rm $(TARGET).o

# build test runner obj
$(TARGET).o	: 
			gcc -c test_suite_core.c -o $(TARGET).o

# if valgrind (http://valgrind.org/) is installed, 
# it can be used to verify allocated memory was freed
memchk		: $(TARGET)
			valgrind ./$(TARGET)
			
