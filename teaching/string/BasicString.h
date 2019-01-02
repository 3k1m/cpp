/**
@file BasicString.h
@author Mike Lindstrom

@brief This is the header file for a very simple string class

See Source.cpp for remarks. This is for PIC 10B, UCLA
*/


#ifndef ___BASIC_STRING___
#define ___BASIC_STRING___

#include<memory>
#include<iostream>
#include<string>

namespace basic {

	/**
	This class mimics the behaviour of a std::string
	*/
	class string {
	public:

		/**
		Default constructor: makes an empty string storing only the null character
		*/
		string();

		/**
		Constructur accepts a string literal as an input and stores those characters in its dynamic array
		@param char_ptr the string literal
		*/
		string(const char* char_ptr);

		/**
		Copy constructor makes a new independent copy of the other string
		@param other the string to copy from
		*/
		string(const string& other);

		/**
		Move constructor takes data from an rvalue of type string
		@param other the string reaching the end of its lifetime
		*/
		string(string&& other);

		/**
		The destructor
		*/
		~string();

		/**
		This function concatenates two strings, appending the input string to the current string
		@param toAppend the string being appended
		*/
		void concat(const string& rhs);

		/**
		This function prints a string to the console
		*/
		void print() const;

		/**
		The assignment operators are deleted
		*/
		string& operator=(string) = delete;

	private:
		// pay attention to the two members below: they are discussed in lecture and the real backbone of the string class

		char* ptr; // pointer to dynamic array of chars, should include null character!
		std::size_t sz; // the size of the dynamic array, including the null character

		// the members down here aren't part of the working class, but they are helpful for illustration to see what happens
		// as class objects are created and destroyed
		// Later on, we'll discuss static variables, etc.

		std::string type; // the type of construction done
		short id; // the id of the string class: each gets its own id
		static short count; // how many strings have previously been constructed
	};	

}

#endif