/*
2. Write a program that requires a user to enter 5 characters, whitespaces included. 
It should then print their characters to the console as an std::string.
*/

#include<iostream>
#include<string>

int main()
{
   std::cout << "Enter 5 characters. Whitespaces count: ";
   
    // cat is the name of the string of characters 
   std::string cat; // starts ""
   
   char dummy; // the dummy char that we read into to add to the cat string 
   
   // std::cin.get();
   
   dummy = std::cin.get();
   cat.push_back(dummy); // add the first character 
   
   std::cin.get(dummy);
   cat.push_back(dummy); // add the second character 
   
   dummy = std::cin.get();
   cat.push_back(dummy); // add the third character 
   
   dummy = std::cin.get();
   cat.push_back(dummy); // add the fourth character 
   
   dummy = std::cin.get();
   cat.push_back(dummy); // add the fifth character 
   
   std::cout << "The string is: " << cat << '\n';
   
   size_t count = cat.size();



    return 0;
}
