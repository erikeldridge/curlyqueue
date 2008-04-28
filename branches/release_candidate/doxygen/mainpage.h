#ifndef MAINPAGE_H_
#define MAINPAGE_H_

/**
@mainpage

@section intro Introduction
 
<pre>

Curly queue is a simple queue implemented in C.  It uses a doubly-linked list for the back-end storage and offers the following (public) functions:

	- create_queue()
		- to create a queue
	- destroy_queue()
		- to safely destroy the queue
	- is_empty()
		- returns true if empty
	- enqueue()
		- to push onto the queue
	- dequeue()
		- to pop from the queue
	- with more on the way!*

*maybe

Use this code as you like, no need to give credit.  Please refer to the license for nitty-gritty usage details.

</pre>

@section install Installation

<pre>

1) unpack the archive
    a) >tar zxvf curlyqueue-x.x.x.tar.gz

2) go into the new curlyqueue-x.x.x directory
    a) >cd curlyqueue-x.x.x

3) run make to compile the queue
    a) >make

This results in a static library named libcurlyqueue.a 
in the curlyqueue-x.x.x directory

</pre>

@section usage Usage

<pre>

1) Refer to the API given in the documentation in the docs directory 
   for a list of available functions
    a) In your web browser, open curlyqueue-x.x.x/docs/html/index.html
    b) Click on the "files" tab and follow the "curlyqueue.h" link to
       the "curlyqueue.h File Reference"
    c) Scroll down to the "Functions" section

2) Call any of these functions in your program
    a) Remember to include the curlyqueue.h header file in your program
    b) For example, let this be the content of a file "hello_queue.c" 
       located in the same directory as the curlyqueue-x.x.x directory:

#include "curlyqueue-x.x.x/curlyqueue.h"
#include "stdio.h"

</pre>

@verbatim

int main(){

        // create a queue 
        curlyqueue_t* queue = curlyqueue_create_queue();

        // put something in it
        int i = 100;
        void *value = &i; 

        curlyqueue_enqueue( queue, value );

        // pop it back out.
        {except_t e;e.thrown=0;
                value = curlyqueue_dequeue( queue, &e );
                //assume no exception thrown 
                //Note: the docs give info on except_t
        }   

        // print it
        printf( "%d \n", *(int *)value );

        // kill the queue
        curlyqueue_destroy_queue( queue );

        return 0;

}

@endverbatim

<pre>

3) Compile your program and run it
    a) >gcc hello_queue.c curlyqueue-x.x.x/libcurlyqueue.a -o hello_queue
    b) >./hello_queue
       >100

4) More examples of usage can be found in the unit tests in the 
tests directory

</pre>

@section license License

<pre>

The MIT License

Copyright (c) 2008 Erik Eldridge

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

</pre>

*/
#endif
