/**
@file SimpleMemory.cpp
@version 2.0
@author Mike Lindstrom
@date March 2019
@brief This cpp file to help check for memory leaks in Visual Studio 2017 (and seemingly g++)
@details This is a very simple file to detect basic memory leaks in code stemming from
new and delete expressions, etc. It has not been tested on other compilers and more elaborate
memory allocation may cause it to fail!
To use this: ensure this .cpp file is compiled with other files in your project directory. So in Visual Studio,
just include it as a .cpp file (no need to #include it); with gcc, compile your files with
g++ -std=c++11 SimpleMemory.cpp YourOtherFiles.cpp
etc.


As an example if what it will produce with a file:

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

#include<cstdlib>
#include<iostream>

namespace simple_memory {

	/**
	The mem_check function tracks the calls to the new and delete operators,
	which are called from the new and delete expressions
	@param newed whether new was called
	@param deleted whether delete was called
	@param print whether the counts of the calls should be printed
	*/
	void mem_check(bool newed, bool deleted, bool print = false) {
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

	/**
	The Memory_Info structure prints memory leaks when it goes out of scope
	*/
	struct Memory_Info {
		~Memory_Info() {
			mem_check(false, false, true); // ensure we print the details
			std::cin.ignore(2);
		}

	} _GLOBAL_MEMORY_OBJECT_;

}

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
