// Example program
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
   istringstream iss("hello world");
   
   std::cout << iss.tellg() << '\n';
   
   std::string temp;
   iss >> temp;
   
   std::cout << temp << '\n';
   
   std::cout << iss.tellg() << '\n';
   
   iss.get();
   
   std::cout << iss.tellg() << '\n';
   
   streampos loc = iss.tellg(); // current spot
   streamoff shift = 2; // data type for stream offsets
   loc += shift; // now loc is 8
     
   std::cout << "Loc: " << loc << '\n';
   
   iss.seekg(loc);
   
   // ios::beg ~ beginning
   // ios::cur ~ current location
   // ios::end ~ end of stream   
   //iss.seekg(8, ios::beg);
   
   std::cout << iss.tellg() << '\n';
   
   iss >> temp;
   
   std::cout << temp << '\n';
   
   
   
   
   
   
   return 0;
   
   
}
