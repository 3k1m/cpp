// Example program
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

int main()
{
 vector<int> vec {2, 4, 6, 88};
 
 for(size_t i=0; i < vec.size(); ++i){
  cout << vec[i] << ' ';   
 }
 cout << '\n';
 
 // vector<int>::iterator is a data type
 // begin(vec) is an iterator type, point to the first element
 // end(vec) is an iterator type pointing PAST THE END
 for( vector<int>::iterator it = begin(vec);
   it != end(vec); ++it){
     cout << *it << ' ';   
   }
  cout << '\n'; 
  
  // auto is special keyword that will
  // set a type according to the right hand side of
  // its initialization
  // since begin(vec) returns std::vector<int>::iterator
  // that's what auto represents
  for( auto it = begin(vec);
   it != end(vec); ++it){
     cout << *it << ' ';   
   }
  cout << '\n'; 
 
 // set is a templated type, like vector
 // this set will store strings
  set<string> names {"Doug", "Connie", "Alice", "Alice",
    "Bob"};
    
  // no [] for sets!
 //for(size_t i=0; i < names.size(); ++i){
 // cout << names[i] << ' ';   
 //}
 //cout << '\n';
 
 for( auto it = begin(names);
   it != end(names); ++it){
     cout << *it << ' ';   
   }
  cout << '\n';
  
 string x = "foo";
 
 for( auto it = begin(x);
   it != end(x); ++it){
     cout << *it << ' ';   
   }
  cout << '\n';
  
  // range-based for loop
  // can only go forwards
  for(int i : vec){
    cout << i << ' '; 
  }
  cout << '\n';
  
  // the above range-for loop really means...  
  for(auto it = begin(vec); it != end(vec); ++it){
    int i = *it;
    cout << i << ' ';
  }
  cout << '\n';
 
 return 0;
}
