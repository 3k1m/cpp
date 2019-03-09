/**
@file LeakExample.cpp

@details This is an example file in how to check for memory leaks.

Basically: be sure to have SimpleMemory.h and SimpleMemory.cpp in your working
directory. And #include the header file.
Immediately inside of main, write _BEGIN_MEMORY_CHECK_
and just before main terminates, write _END_MEMORY_CHECK_

There will be a display of how many times new allocations and delete operations were
made. The two should match if there were no memory leaks.
*/

#include<string>
#include<iostream>
#include "SimpleMemory.h"

int main()
{
	/* 
	This places subsequent code inside a scope to test for memory leaks
	until the end of the scope
	*/
	_BEGIN_MEMORY_CHECK_	
	
    int *i = new int;
    std::string s("a very very very very very very very long string");
    delete i;
	double *d = new double[53]();
	delete[] d;
	void *v = ::operator new(20);
	
	/* 
	This marks the end of the scope over which we check for memory leaks 
	*/
	_END_MEMORY_CHECK_
	
	/* we forgot to do
	operator delete(v);
	so there will be 4 news: i, s, d, and v
	and 3 deletes */
	return 0;
}