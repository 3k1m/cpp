#include<iostream>
#include<string>
#include<sstream>

#ifndef _NICE__HELPFUL_HEADER
#define _NICE__HELPFUL_HEADER

namespace nice{

	/**
	PrintRaw will print whatever it is given, with no fancy formatting 
	@param ... params all the values to print 
	*/
	void PrintRaw(auto&& ... params){
		(std::cout << ... << std::forward<decltype(params)>(params));
	}

	/**
	PrintNice will print whatever it is given with spaces between entries and a new line at the end 
	@param ... params all the values to print 
	*/
	void PrintNice(auto&& ... params){
		auto print_w_space = [](std::ostream& o, auto&& val) {
			o << std::forward<decltype(val)>(val) << ' ';
		};
		(print_w_space(std::cout,std::forward<decltype(params)>(params)),...);
		std::cout << '\n';
	}


	/**
	ReadString will read values stored in a string into a list of values 
	@param str the string 
	@param ... vals the values to set 
	*/
	void ReadString(const std::string& str, auto& ... vals){
		std::istringstream in{str};
		(in >> ... >> vals);
	}

}

#endif 
