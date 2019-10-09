// Example program
#include <iostream>
#include <string>

int main()
{
  std::string person;
  std::cout << "What is your name? ";
  
  // does not work as intended... only get first name
  //std::cin >> person;
  
  // this only works to write into a string
  std::getline(std::cin, person);
  
  std::cout << "Nice to meet you, " + person;
  
  std::cout << "What is your favourite number? ";
  int fav_num = 0;
  std::cin >> fav_num; // read their value
  
  // remove the \n from the buffer
  std::cin.ignore();
  
  std::cout << "Why do you like that number? ";
  std::string reason; // try to read in why
  std::getline(std::cin, reason);
  
  std::cout << reason << " is a good reason.";
  
  // add another getline to see there is no
  // \n nonsense going on
  
  std::cout << "Where are you? ";
  
  std::string location;
  std::getline(std::cin, location);
  
  std::cout << "You are at " << location;
  
  
 
  
  return 0;
}
