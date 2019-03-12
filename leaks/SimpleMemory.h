/**
@file SimpleMemory.h
@version 2
@date March 2019
@author Mike Lindstrom

@brief This file in conjunction with SimpleMemory.cpp
can be used to help detect memory leaks. See Example.cpp for details
on how to use.
*/

#ifndef _SIMPLE_MEMORY_
#define _SIMPLE_MEMORY_

#include<cstddef>

namespace simple_memory {
	
	/**
	returns the number of calls to operator new
	@param newed whether operator new was just called
	@return the number of times called
	*/
	std::size_t new_count(bool newed);

	/**
	returns the number of calls to operator delete
	@param deleted whether operator delete was just called
	@return the number of times delete has been called
	*/
	std::size_t delete_count(bool deleted);

	/**
	The mem_check function tracks the calls to the new and delete operators,
	which are called from the new and delete expressions
	@param newed whether new was called
	@param deleted whether delete was called
	@param print whether the counts of the calls should be printed
	@param reset whether to reset the counts to zero
	*/
	void mem_check(bool newed, bool deleted, bool print = false, bool reset = false);

	/**
	The Memory_Info structure prints memory leaks when it goes out of scope
	*/
	struct Memory_Info {
		// how many times new and delete operators already called
		std::size_t init_news, init_deletes;		

		/**
		Constructor: stores the initial new and delete calls
		*/
		Memory_Info();

		/**
		Destructor: renders new and delete call counts
		*/
		~Memory_Info();
	};
}


// glue to items together
#define _SIMPLE_MEMORY_GLUE_(x,y) x##y

// given two items, return their glued result
#define _SIMPLE_MEMORY_EXPAND_(x,y) _SIMPLE_MEMORY_GLUE_(x,y)

// expands to: simple_memory::Memory_Info simple_memory_info_objectdd where dd is a counter variable
#define _SIMPLE_MEMORY_CLASS_ simple_memory::Memory_Info _SIMPLE_MEMORY_EXPAND_(simple_memory_info_object, __COUNTER__)

// to allow for multiple statements, begin opens a do loop, and end closes it
#define _BEGIN_MEMORY_CHECK_ do { _SIMPLE_MEMORY_CLASS_; {
#define _END_MEMORY_CHECK_ } } while(0);


#endif
