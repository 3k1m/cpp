/**
@file SimpleMemory.cpp
@version 1.0
@author Mike Lindstrom
@date Jan 2019

@brief This file defines the entities declared in SimpleMemory.h
*/

#include<cstdlib>
#include<iostream>
#include "SimpleMemory.h"

simple_memory::Memory_Info::~Memory_Info() {
	mem_check(false, false, true); // ensure we print the details
	std::cin.ignore(2);
}

void simple_memory::mem_check(bool newed, bool deleted, bool print) {
	static int new_calls = 0; // counts calls to new
	static int delete_calls = 0; // and to delete
	if (newed) { // if new was called, increase its count
		++new_calls;
	}
	if (deleted) { // if delete was called, increase its count
		++delete_calls;
	}
	if (print) { // if we should print, we give all the info
		std::cout << "\nnew called: " << new_calls << " times\ndelete called: " << delete_calls << " times\n";
	}
}

simple_memory::Memory_Info _GLOBAL_MEMORY_OBJECT_;

/**
We define (replace) the GLOBAL operator new and delete

We use malloc and free for allocation and deallocation within the new and delete operators
*/

void *operator new(size_t bytes) { 
	void* ptr = malloc(bytes);
	simple_memory::mem_check(true, false); // increase the new count
	return ptr;
}

void operator delete(void* ptr) noexcept {
	if (ptr) { // assuming not null
		simple_memory::mem_check(false, true); // increase delete count
	}
	free(ptr);	
}