#include<iostream>
/* 
tell the preprocessor to include a HEADER file
called iostream

header files declare a bunch of useful functions, 
variables, etc.

iostream = input output stream: printing to the 
console, getting user input, etc.
*/

using namespace std;
/*
namespace is like a regional dialect

want to use the 'std' namespace: tells the compiler
that functions/variables/etc. that we write down
are likely part of this namespace
*/

// now we have our main routine
// the main routine is a function that
// takes no input ()  and
// outputs an int [integer type]
// all C++ programs must have a main routine:
// instructions begin after the { of main
int main() {
	
	cout << "Hello, PIC 10A\nHow is it going?\a";
	/*
	cout: console output - a special variable that
	can display things to the console

	cout << "...": calls a function to print ... to 
	the console window

	stuff in double quotes are STRING LITERALS - just
	a bunch of text: open and close with "

	\n: new line, i.e. go down to the next line
	\: escape character...
	\t = tab
	\\: backslash

	; - all C++ statements terminate in semicolon
	*/

	cin.get();

	/*
	cin: console input - manages user input

	cin.get(): calls a function that waits until
	the user enters a character. until that point,
	the program cannot proceed
	*/

	return 0;
	/*
	main is supposed to return an int value,
	we tell it to return the value 0

	as good practice, this should be included but
	if it is forgotten, on modern compilers, 0
	is returned anyway

	can return other values to signify failure, or
	different return states

	once main (or any function) returns a value,
	no more lines of code in that function are run
	*/

	// ignored because int was already returned
	cout << "what about me?";
}
