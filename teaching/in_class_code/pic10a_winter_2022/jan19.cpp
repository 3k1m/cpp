#include <iostream>
#include <string>
#include <iomanip>

int main()
{
  std::string s("hello");
  std::cout << std::setw(s.size()+1) << s << '\n';
  
  std::cout << std::setw(8) << std::setfill('*') << '\n';
  
  std::string printout = std::string(5,'-') + "hello" + std::string(s.size(),'-');
  std::cout << printout << '\n';

    return 0;
}
