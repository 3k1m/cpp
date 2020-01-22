#include <iostream>
#include <string>

int main()
{
        
  std::cout << "What is your fav num? ";    
  int fav_num = 0;
  std::cin >> fav_num;
  
  std::cout << "Your fav num is: " << fav_num << '\n';
  
  std::cout << "What is your name? ";
  std::string name;
  
  std::cin.ignore(); // skip the \n lingering
  
  std::getline( std::cin, name );
  
  std::cout << "Your name is: " << name << '\n';
  

  return 0;
}
