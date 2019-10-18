// Example program
#include <iostream>
#include <string>

using namespace std;

int main()
{
  // find the sum of a user's numbers
  double sum = 0; // the total
  
  bool more = true; // if they have more values to enter
  
  // as long as they have more to give
  while( more ){
      cout << "Enter a number: ";
      
      double num = 0;
      cin >> num; // read in their number
      
      sum += num; // add it to the sum  
      
      cout << "Ya done? y/n: ";
      
      char done = ' ';
      cin >> done;
      
      // beware of single vs double ==!
      if( done == 'y' ){ // they said done with y
          more = false; // no more inputs to read
      }      
  }
  
  cout << "The total is: " << sum << '\n';
  
  return 0;
}
