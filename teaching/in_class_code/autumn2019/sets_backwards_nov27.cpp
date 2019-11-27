// Example program
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
    // set will store things in sorted order, regardless of
    // inputs
    // uses operator< by default
    
  set<int> int_set{ 2, -8, 18, 22, -6, -43, -43};
  
  // and items are only stored with a max multiplicity of 1
  // the -43 is only stored once!
  
  for(int i : int_set){
    cout << i << ' ';   
  }
  cout << '\n';
  
  int_set.insert(0); // insert 0
  int_set.insert(19); 
  
  int_set.erase(18); // to erase a value
  int_set.erase(11111111); // works even if value not there
  
  for(int i : int_set){
    cout << i << ' ';   
  }
  cout << '\n';
  
  
  // going backwards..
  for( auto it = int_set.rbegin(); it != int_set.rend(); ++it){
    cout << *it << ' ';   
  }
  cout << '\n';
  
  // it is a std::set<int>::reverse_iterator
  
  // C++17: free function rbegin, rend, etc.
  // prior to C++17 compilers are
  // limited to member function versions
  
  
  
  return 0;
}
