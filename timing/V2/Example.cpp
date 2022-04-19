/**
@file Example.cpp
@version 2.0
@author Mike Lindstrom
@date Apr 2022
@brief this file is an example usage of the timer class found in Timer.h
*/


#include<iostream>
#include<vector>
#include<numeric>

#include "Timer.h"

/**
This function creates 100 objects that use a constructor initializer list for efficiency
*/
void test_init_list();

/**
This function creates 100 objects that does not use a constructor initializer list and is less efficient
*/
void test_in_body();

/**
This function sums a vector
@param vec the incoming vector passed BY VALUE
@return the sum of its entries
*/
int sum_by_value(std::vector<int> vec);

/**
This function sums a vector
@param vec the incoming vector passed AS REFERENCE TO CONST
@return the sum of its entries
*/
int sum_by_reference(const std::vector<int>& vec);

/**
This function prints numbers 0-999 using endls
*/
void print_endl();

/**
This function prints numbers 0-999 using new lines
*/
void print_newline();

int main() {
	// make a vector
	std::vector<int> v;
	v.reserve(100); // reserve space for 100 entries
	for (int i = 0; i < 100; ++i) { // add values 0-99 into it
		v.push_back(i);
	}

	simple_timer::timer<'s', long double> tim; // timer object for seconds with long double precision
	sum_by_value(v);
	auto time_val = tim.tock(); // time sum by value

	tim.tick();
	sum_by_reference(v);
	auto time_ref = tim.tock(); // time sum by reference

	tim.tick();
	print_endl();
	auto time_endl = tim.tock(); // time with endls

	tim.tick();
	print_newline();
	auto time_n = tim.tock(); // time with \ns

	tim.tick();
	test_in_body();
	auto time_body = tim.tock(); // time without initializer list

	tim.tick();
	test_init_list();
	auto time_list = tim.tock(); // time with initializer list

	std::cout << "Sum by value: " << time_val << '\n';
	std::cout << "Sum by reference: " << time_ref << '\n';
	std::cout << "Print endls: " << time_endl << '\n';
	std::cout << "Print newlines: " << time_n << '\n';
	std::cout << "In body: " << time_body.get_value().first << ' ' <<
		time_body.get_value().second << '\n';
	std::cout << "Constructor list: " << time_list << '\n';

	return 0;
}

struct Foo_init_list {
	std::vector<int> v;
	/**
	default constructor: uses constructor initializer list
	*/
	Foo_init_list() : v(1) {}
};

struct Foo_in_body {
	std::vector<int> v;

	/**
	default constructor: resets member in body
	*/
	Foo_in_body() {
		v = std::vector<int>(1); // does not use constructor initializer list
	}
};

void test_init_list() {
	for (int i = 0; i < 100; ++i) { // create 100 Foo_init_list's
		Foo_init_list f;
	}
}

void test_in_body() {
	for (int i = 0; i < 100; ++i) { // create 100 Foo_in_body's
		Foo_in_body f;
	}
}

int sum_by_value(std::vector<int> vec) { // pass by value inefficient
	return std::accumulate(std::begin(vec), std::end(vec), 0);
}

int sum_by_reference(const std::vector<int>& vec) { // pass by reference efficient
	return std::accumulate(std::begin(vec), std::end(vec), 0);
}

void print_endl() {
	for (int i = 0; i < 1000; ++i) { // print 0 to 999 with endl
		std::cout << i << std::endl;
	}
}

void print_newline() {
	for (int i = 0; i < 1000; ++i) { // print 0 to 999 with \n
		std::cout << i << '\n';
	}
}
