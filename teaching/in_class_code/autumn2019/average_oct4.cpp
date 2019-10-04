// Example program
#include <iostream>
#include <string>

using namespace std;

int main()
{    
  // instructions
  cout << "Please enter 3 positive integers and I will take the average: ";
  
  int value1 = 0; // start off storing 0
  int value2 = 0, value3 = 0; // two variables of type int both set to 0
  
  cin >> value1 >> value2; // read in the first and second
  cin >> value3; // the third
  
  // v1
  
  /*int sum = value1 + value2 + value3; // sum of the 3 numbers
  double average = sum/3.0; */
  
  // v2
  
  int sum = value1 + value2 + value3; // sum of the numbers
  int num_nums = 3; // how many #'s we avg
  
  double average = static_cast<double>(sum) / num_nums;
  
  cout << "The average is: " << average;
  
  // now let's find the rounded average: average is postive since the #'s are too
  double rounded_average = static_cast<int>( average + 0.5 );
  
  cout << "The rounded average is: " << rounded_average;
  
  return 0;  
  
}
