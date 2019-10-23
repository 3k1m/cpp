// Example program
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  // vectors can store anything... so need to
  // say what they store
  
  // can store doubles
  // begins empty
  vector<double> HW_percents;
  
  for(int i=0; i < 10; ++i){
    HW_percents.push_back( i * 10. );   
  }
  
  // will store 0, 10, 20, ... 90
  
  // remove the 90:
  HW_percents.pop_back();
  
  // print out all the HW percents, use []
  for(size_t i=0; i < HW_percents.size(); ++i){
   cout << HW_percents[i] << '\n';   
  }
  
  // different ways to initialize
  vector<string> names {"Alice", "Bob", 
  "Connie", "Doug"};
  
  /*vector<string> names = {"Alice", "Bob", 
  "Connie", "Doug"}; */
  
  names[0][0] = 'a'; // Alice -> alice
  
  for(size_t i=0; i < names.size(); ++i){
   cout << names[i] << '\n';   
  }
  
  // store 40 true's
  vector<bool> x(4, true);
  
  cout << boolalpha; // so true is printed as "true"
  // not just "1"
  
  for(size_t i=0; i < x.size(); ++i){
   cout << x[i] << '\n';   
  }
  
  vector<int> y { 4 };
  y.push_back(9);
  y.push_back(10);
  cout << "size and capacity\n";
  cout << y.size() << '\n' << y.capacity() << '\n';
  
  // way out of range - dangerous, UNDEFINED BEHAVIOUR
  cout << x[53] << '\n';
  
  // to be safer, use "at"
  // throws exception: terminates program
  cout << x.at(53) << '\n';
  
  return 0;
  
  
  
}
