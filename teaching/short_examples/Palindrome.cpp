#include <iostream>
#include <string_view>
#include <string>

/*
Run this code with a C++17 compiler such as this one: https://wandbox.org/
*/

/**
This function determines if a string of chars is a palindrome
@param s a string_view object, can be constructed from a string literal or char*
@return whether it is a palindrome
*/
bool isPalindrome(const std::string_view& s) {
	if ( s.size() <= 1 ) { // true if empty or a single char
		return true;
	}
	else { // then multiple chars
		// it is false if the first and last chars do not match
		if ( s[0] != s[s.size()-1] ) {
			return false;
		}
	}

	// if here, nip off ends and check again from 2nd to 2nd last char
	return isPalindrome( s.substr(1,s.size()-2) );
}

int main()
{
    std::string s("hello world");
    std::string_view sv(s.c_str()); // c_str returns const char* within the string
	
    std::boolalpha(std::cout); // make it display true as 'true' and false as 'false'
    
    std::cout << isPalindrome(sv) << '\n';    
    std::cout << isPalindrome("abba") << '\n';

    return 0;
}
