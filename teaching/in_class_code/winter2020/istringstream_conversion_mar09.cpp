// Example program
#include <iostream>
#include <string>
#include <limits>
#include <sstream>

template<typename T>
T convert_to(const std::string& s){
 T t; // requires a default constructor
 std::istringstream iss(s);
 iss >> t;
 return t; 
}


int main()
{
//  std::cout << INTMAX << '\n';
  std::cout << std::numeric_limits<int>::max() << '\n';
  
  std::string five("5");
  std::string pi("3.14159");
  
  std::cout << convert_to<int>(five) + 1 << '\n';
  std::cout << convert_to<double>(pi) + 1 << '\n';
  
  
  
  


  return 0;
}
