#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_

#include "stdio.h"

#define ADD_SUITE( suite_name )					\
	printf("BEGIN: suite " #suite_name " \n");	\
	suite_name();								\
	printf("END: suite " #suite_name " \n\n");	

#define ADD_TEST( test_name )					\
	printf(" BEGIN: test " #test_name " \n");	\
	test_name();								\
	printf(" END: test " #test_name " \n\n");	\

#define ADD_CASE( case_name )					\
	printf(" BEGIN: test " #case_name " \n");	\
	case_name();								\
	printf(" END: test " #case_name " \n\n");	\
	
#endif /*UNIT_TEST_H_*/
