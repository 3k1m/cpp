#include<iostream>
#include "Nice.h"
#include <string>

int main(){
	int a = 0;
	double b = 0;
	char c = '0';
	std::cout << "Enter an int, a double, and a char separated by whitespace:\n";
	nice::set_vars_cin(a,b,c);
	nice::print(a,b,c);


	// will generate linker error due to y not being defined, only declared
	//extern int y;
	//nice::print(y);
	//	std::vector<int> v;
	int z; // this defines z, but does not initialize. it is not just a declaration
	int x = 0;
  std::cout << x << '\n';
  ++x;
  std::cout << x << '\n';
  x++;
  std::cout << x << '\n';
  // suffix: make a copy of the current x, increase x, and *evaluate* to the copy
  std::cout << x++ << '\n'; // will print 2, but x becomes 3
  std::cout << x << '\n';
  // prefix: increase x and give us the updated x
  nice::print(++x); // 4
  nice::print(x); // 4

  std::string s{"hello world"};
  nice::print( s[0] , s[ s.size()-1 ] );
  nice::print( s[ s.size() + 4 ] ); // beyond range!
  s.at ( s.size() + 4 );

 // std::cout << s;
}
