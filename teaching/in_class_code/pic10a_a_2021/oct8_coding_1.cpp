#include <iostream>
#include <string>

/*
1. Write a program that requires a user to enter 5 non-whitespace characters.
If the user enters whitespace characters, those should be ignored.
It should then print their characters to the console as an std::string.
*/

int main()
{
   std::cout << "Enter 5 non-whitespace characters. Whitespace characters will be ignored: ";
   
    // cat is the name of the string of characters 
   std::string cat; // starts ""
   
   char dummy; // the dummy char that we read into to add to the cat string 
   
   std::cin >> dummy;
   cat.push_back(dummy); // add the first character 
   
   std::cin >> dummy;
   cat.push_back(dummy); // add the second character 
   
   std::cin >> dummy;
   cat.push_back(dummy); // add the third character 
   
   std::cin >> dummy;
   cat.push_back(dummy); // add the fourth character 
   
   std::cin >> dummy;
   cat.push_back(dummy); // add the fifth character 
   
   std::cout << "The string is: " << cat << '\n';



    return 0;
}
