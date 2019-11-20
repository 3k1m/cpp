#include <iostream>
#include <string>

int main()
{
  int x = 8;
  
  // >> and << were right and left bit shift operators for integers
  // but "operator overloading" ==> now can be used to print to
  // the console or reada input
  std::cout << (x >> 2) << '\n';
  
  x += 4; // x = (x+4)
  
  std::string s("123");
  
  s+=s; // s = (s+s)
  
  std::cout << s << '\n';
  
    
  return 0;
}
