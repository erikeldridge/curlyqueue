# Builds a static lib out of curlyqueue files

all 		: curlyqueue.o
			ar rcs libcurlyqueue.a curlyqueue.o
			rm curlyqueue.o

curlyqueue.o	: 
			gcc -c curlyqueue.c -o curlyqueue.o
