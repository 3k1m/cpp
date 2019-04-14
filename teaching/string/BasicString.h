/**
@file BasicString.h
@author Michael Lindstrom

@brief This is the header file for a very simple string class

See Source.cpp for remarks. This is for PIC 10B, UCLA
(c) Michael Lindstrom
*/


#ifndef _BASIC__STRING_
#define _BASIC__STRING_

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
		Copy assignment operator, makes left value same as right value
		@param other the assigned-from string
		@return the updated assigned-to string
		*/
		string& operator=(const string& other);
		
		/**
		Move assignment operator, makes left value same as right value by harvesting its resources
		@param other the assigned-from string
		@return the updated assigned-to string
		*/
		string& operator=(string&& other);

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
		This non-const at function returns the char at the given index by reference
		@param i the index value
		@return the char at that index
		*/
		char& at(size_t i);
		
		/**
		This const at function returns the char at the given index by value
		@param i the index value
		@return the char at that index
		*/
		char at(size_t i) const;

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
