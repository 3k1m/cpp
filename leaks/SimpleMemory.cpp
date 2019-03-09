/**
@file SimpleMemory.cpp
@version 2
@date March 2019
@author Mike Lindstrom

@brief This file accompanies SimpleMemory.h to help detect memory leaks in simple scenarios
*/

#include "SimpleMemory.h"
#include<iostream>

namespace simple_memory {
	
	size_t new_count(const bool newed) {
		static size_t news = 0;
		if (newed) { // increase count if new was called
			++news;
		}
		return news;
	}

	size_t delete_count(const bool deleted) {
		static size_t deletes = 0;
		if (deleted) { // increase count if delete was called
			++deletes;
		}
		return deletes;
	}

	// at construction, get a count of how many times new and delete have already been called
	Memory_Info::Memory_Info() : init_news(new_count(false)), init_deletes(delete_count(false)) {}

	// at destruction, subract the initial number of news/deletes from the current count
	Memory_Info::~Memory_Info() {
			std::cout << "new called " << new_count(false) - init_news << " times\n";
			std::cout << "delete called " << delete_count(false) - init_deletes << " times\n";
			std::cout << "memory leak checking complete. Press [ENTER]\n";
			std::cin.get();
	}

}

/**
We define (replace) the GLOBAL operator new and delete
We use malloc and free for allocation and deallocation within the new and delete operators
*/

void *operator new(size_t bytes) {	
	void* ptr = malloc(bytes);
	simple_memory::new_count(true); // increase the new count	
	return ptr;
}

void operator delete(void* ptr) noexcept {	
	if (ptr) { // assuming not null
		simple_memory::delete_count(true); // increase the new count	
	}
	free(ptr);
}