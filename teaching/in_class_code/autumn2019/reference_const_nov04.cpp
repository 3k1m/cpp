
// get the file here: https://github.com/3k1m/cpp/blob/master/timing/Timer.h
#include "Timer.h" 

#include <iostream>
#include <string>

// string in by value
void foo( std::string s ){
 std::cout << s[50] << ' ' << s.size() << '\n';   
}

// string by reference: MUST FASTER
void bar( const std::string& s ){
 std::cout << s[50] << ' ' << s.size() << '\n';   
}

// can ONLY bind to an lvalue of type std::string
void a( std::string& s) {}

// but a reference to const can bind to an rvalue
// string literal -> std::string, which is bound to
void b( const std::string& s) {}

// string literal -> std::string
void d( std::string s) {}


int main()
{
  simple_timer::timer<'n'> timer;

  char c;
  std::cin >> c;
  
  std::string big_string(100000, c);
  
  timer.tick();
  foo(big_string);
  std::cout << timer.tock() << '\n'; // how many ns
  
  timer.tick();
  bar(big_string);
  std::cout << timer.tock(); // how many ns
  
//  a("hello");
  b("hello");
  d("hello");
  
  return 0;
}
