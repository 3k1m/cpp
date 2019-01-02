/**
@file Source.cpp
@author Mike Lindstrom

@brief This file has a running main routine for a string class. Read the remarks below, especially item 4 if your are not using
Visual Studio for compilation.

This code illustrates the implementation of a basic string class. This is for PIC 10B, UCLA

This file makes use of a string class defined and implemented in BasicString.h and BasicString.cpp

Important Remarks:

1. The real std::string class has more bells and whistles but this is a hopefully friendly introduction to
RAII classes and memory management.

2. The resulting outputs could vary from compiler to compiler due to various optimizations. There are differences
between Windows Visual Studio 2017 and g++ (C++11), for example, in how well they elide initializations.

3. The .print() commands could be replaced by overloading and defining the << operator
but at this point in time we stick to just using the print function. This implementation
also deletes the implementations of the assignment operators.

We haven't formally covered operator overloading in PIC 10B yet.

4. The try and catch are listed only for illustration in the default constructor; other constructors could also use try
and catch. This is important for more complicated classes and when exceptions have been discussed. Exceptions haven't yet
been discussed in the course.
*/

#include "BasicString.h"

/**
This function returns a basic::string storing "Hello world!". Note that it makes a local variable and then returns
a copy of that local variable.
@return a string with "Hello world!"
*/
basic::string named() {
	basic::string s("Hello world!");
	return s;
}

/**
This function returns a basic::string storing "!dlrow olleH". Note that it does not name its return value - it may
behave differently than named() above on some compilers as a result.
@return a basic::string with "!dlrow olleH"
*/
basic::string unnamed() {
	return "!dlrow olleH";
}

int main() {

	// new scope, stringNumber0 is first on the stack
	basic::string stringNumber0; // default
	std::cout << "stringNumber0: ";
	stringNumber0.print();
	std::cout << '\n';

	{ // new scope, stringNumber1, stringNumber2, stringNumber3, stringNumber4 added to stack
		basic::string stringNumber1 = "A"; // with const char: may optimize away copy
		std::cout << "stringNumber1: ";
		stringNumber1.print();
		std::cout << '\n';

		basic::string stringNumber2("B"); // direct with const char*
		basic::string stringNumber3("CDE");
		basic::string stringNumber4("");

		std::cout << "stringNumber2: ";
		stringNumber2.print();
		std::cout << '\n';

		std::cout << "stringNumber3: ";
		stringNumber3.print();
		std::cout << '\n';

		std::cout << "stringNumber4: ";
		stringNumber4.print();
		std::cout << '\n';

		std::cout << "stringNumber3 after concatenting stringNumber2: ";
		stringNumber3.concat(stringNumber2); // now stringNumber3 is CDEB
		stringNumber3.print();
		std::cout << '\n';

		// but stringNumber2 unchanged
		std::cout << "stringNumber2 still unchanged: ";
		stringNumber2.print();
		std::cout << '\n';
			
		{ // new scope stringNumber5 added to stack
			basic::string stringNumber5 = stringNumber2; // implicitly calls copy constructor when = used!
			std::cout << "stringNumber5: ";
			stringNumber5.print();
			std::cout << '\n';
			std::cout << "leaving a scope: " << '\n';
			std::cout << '\n';
		} // stringNumber5 destroyed

		basic::string stringNumber6 = std::move(stringNumber2); // will implicitly invoke move constructor, move = rvalue
		basic::string stringNumber7(std::move(stringNumber3)); // directly calls move constructor

		std::cout << '\n' << "stringNumber6: ";
		stringNumber6.print();
		std::cout << '\n';

		std::cout << "stringNumber7: ";
		stringNumber7.print();
		std::cout << '\n';

		std::cout << "stringNumber2 after moved from: ";
		stringNumber2.print();
		std::cout << '\n';

		std::cout << "stringNumber3 after moved from: ";
		stringNumber3.print();
		std::cout << '\n';

		// Now we get to the wierd stuff with copy elision: there are no guarantees as to what the
		// string numbers actually will be because the temporary objects within the functions
		// may or may not be used in constructing the strings below...

		basic::string stringW = unnamed(); // the return value was unnamed in this function
		basic::string stringX(unnamed());

		std::cout << "stringW: ";
		stringW.print();
		std::cout << '\n';

		std::cout << "stringX: ";
		stringX.print();
		std::cout << '\n';

		basic::string stringY = named(); // the return value was named in this function
		std::cout << "stringY: ";
		stringY.print();
		std::cout << '\n';

		basic::string stringZ(named());		
		std::cout << "stringZ: ";
		stringZ.print();
		std::cout << '\n';
			
		std::cout << "Now everything goes out of scope: " << '\n';
	} // some descending series of ids will be displayed, but they may not be consecutive
	
	std::cin.get();

	return 0;
}