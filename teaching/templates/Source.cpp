/**
@file Source.cpp
@author Mike Lindstrom

@brief This code illustrates template syntax

This is for PIC 10B, UCLA
*/

#include "Wrapper.h"
#include <iostream>
#include<string>

int main() {

	basic::Wrapper<int> I; // stores 0
	basic::Wrapper<int> I2(1); // stores 1
	
	I.swap(I2); // switch them up!

	const basic::Wrapper<std::string> S("C++");

	auto Iref = I.get_ref();
	++Iref.get();
	std::cout << Iref.get() << '\n';

	auto Iref2 = I2.get_ref();
	std::cout << std::boolalpha << (Iref == Iref) << " " << (Iref2 == Iref) << '\n';

	basic::Wrapper<std::string>::const_ref Sref = S.get_const_ref();
	std::cout << Sref.get() << '\n';

	print_Wrapper(S); // and ADL saves the day: note the lack of the namespace in the function name!

	std::cout << '\n';

	basic::Wrapper<std::string> S2("hi");
	auto Sref2 = S2.get_ref();
	Sref2.emplace(300, '!'); // emplace takes any number of arguments
	std::cout << Sref2.get() << '\n';

	std::cin.get();

	return 0;

}