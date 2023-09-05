#include<iostream>
#include<string>
#include<sstream>
#include<limits>

#ifndef _NICE__HELPFUL_HEADER
#define _NICE__HELPFUL_HEADER

namespace nice{

	/**
	print_raw will print whatever it is given, with no fancy formatting 
	@param ... params all the values to print 
	*/
	void print_raw(auto&& ... params){
		(std::cout << ... << std::forward<decltype(params)>(params));
	}

	/**
	print will print whatever it is given with spaces between entries and a new line at the end 
	@param ... params all the values to print 
	*/
	void print(auto&& ... params){
		auto print_w_space = [](std::ostream& o, auto&& val) {
			o << std::forward<decltype(val)>(val) << ' ';
		};
		(print_w_space(std::cout,std::forward<decltype(params)>(params)),...);
		std::cout << '\n';
	}

	/**
 	set_vars will parse a sequence of values, separated by spaces, given by the user
  	and use them to set variables
   	@param ... vals the values to set
  	*/
	void set_vars_cin(auto&&... vals){
		(std::cin >> ... >> vals);
		std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
 	}

	/**
	read_from_string will read values stored in a string into a list of values 
	@param str the string 
	@param ... vals the values to set 
	*/
	void read_from_string(const std::string& str, auto& ... vals){
		std::istringstream in{str};
		(in >> ... >> vals);
	}

}

#endif 
