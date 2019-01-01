/**
@file SimpleMemory.h
@version 1.0
@author Mike Lindstrom
@date Jan 2019

@brief This is the header file to help check memory leaks in Visual Studio 2017 (and seemingly g++)

@details This is a very simple header file to detect basic memory leaks in code stemming from
new and delete expressions. It has not been tested on other compilers and more elaborate
memory allocation may cause it to fail!!!

To use this: #include this file at the top of the file with you main routine, and 
also ensure the BasicMemory.cpp file is included in your workspace.

For example:

#include "SimpleMemory.h"

int main(){
	int *ip = new int;
	char *cp = new char[7];
	
	delete ip;
	
	// forgot to delete cp...
	
	return 0;	
}

There will be an output:

new called: 2 times 
delete called: 1 times 

indicating a memory leak. At the end of the day, the number of calls to new and delete should match; otherwise there
has been a memory leak.
*/


#ifndef _MEMORY_LEAK_CHECK_
#define _MEMORY_LEAK_CHECK_

namespace simple_memory {
	/**
	The mem_check function tracks the calls to the new and delete operators,
	which are called from the new and delete expressions
	@param newed whether new was called
	@param deleted whether delete was called
	@param print whether the counts of the calls should be printed
	*/
	void mem_check(bool newed, bool deleted, bool print = false);

	/**
	The Memory_Info structure prints memory leaks when it goes out of scope
	*/
	struct Memory_Info {
		~Memory_Info();
	};

	/**
	This is a global variable within the basic_memory namespace so that
	it will be defined before main and destroyed when main is over, allowing us
	to see the counts of allocations and deallocations
	*/
	extern Memory_Info _GLOBAL_MEMORY_OBJECT_;

}

#endif
