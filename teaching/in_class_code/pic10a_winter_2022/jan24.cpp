/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

int main()
{
  const double speedLimit = 60; // mph
  double speed = 0; // mph
  cout << "Enter speed in mph: "; // ask for speed
  cin >> speed; // read in the vehicle speed
  // check if the vehicle speed exceeds the speed limit
  if( speed > speedLimit ) { // and if so, print message
   cout << "The car is speeding!"<< '\n';
   cout << "Give a hefty fine!\n";
  } 
  else{ // not speeding 
      cout << "The car is going the speed limit\n";
  }
  
  if(speed > 0){
      int y = 7;
  }
  
  //cout << "ran an if\n";
 
  else{
      int y = 7;
  }
  
  cout << "program is done\n";

    return 0;
}
