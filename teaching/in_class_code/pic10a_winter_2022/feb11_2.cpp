#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    // nullptr is the pointer literal 
    // signifies the address of 0
    
    // do not:
    // time(0) -- outdated
    // time(NULL)

   time_t now = time(nullptr); // number of seconds since Jan 1, 1970 
  
   cout << now << " seconds elapsed\n"; 
   
   // endl forces the printout before the time updates the value of now 
   cout << "I will time you! Wait some time and then press ENTER. " << endl;
   
   // start timer 
   time(&now); // since now is not nullptr, now will be written to 
   cin.get(); // wait for a single character like \n 
   time_t duration = time(nullptr) - now;
   cout << "It took you " << duration << " seconds to press ENTER.";
   

    return 0;
}
