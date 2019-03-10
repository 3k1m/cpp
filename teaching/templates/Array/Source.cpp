/**
@file Source.cpp
@author Mike Lindstrom
@brief This code illustrates template syntax
This was written as an example for PIC 10B, UCLA
*/

#include "Array.h"

#include<iostream>
#include<string>

int main() {
	// array stores 3 zeros...
	constexpr basic::Array<int, 3> ints;
	constexpr basic::Array<int, 3>::ArrayView view = ints.get_view();
	print(view);

	std::cout << '\n';

	// array stores 5 strings
	basic::Array<std::string, 5> strings;
	strings[1] = "hello"; // place "hello" as 2nd entry
	strings.emplace(2, 10, 'b'); // emplace string(10,'b'), i.e. "bbbbbbbbbb" as 3rd entry
	strings.emplace(3); // emplace string(), i.e, emptry string as 4th entry
	strings.emplace(4, strings[1]); // emplace strings[1] as 5th entry
	print(strings.get_view(1,5)); // view from 2nd to 5th entries inclusive

	std::cin.get();
	return 0;
}
