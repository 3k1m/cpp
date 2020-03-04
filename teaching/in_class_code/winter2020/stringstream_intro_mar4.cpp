#include <iostream>
#include <string>
#include <sstream>

int main()
{
  std::string fav_num;
  std::cout << "Enter your fav num: ";
  std::getline(std::cin, fav_num);
  
  // want this int to store the value
  // of fav_num
  int the_num;
  
  // data type to read from strings
  // iss is the name of a variable
  std::istringstream iss( fav_num );
  iss >> the_num;
  
  std::cout << the_num << '\n';
  

  return 0;
}
