#include <iostream>
#include <vector>
#include <iterator>
#include <string>

#include <set>

#include <algorithm>

using namespace std;

int main()
{
  int a[] = {1,2,3,4};
  cout << *a << ' ' << *(a+2) << '\n';
  
  vector<int> b{1,2,3,4};
  vector<int>::iterator it1 = b.begin(); // begin returns an iterator ~ pointer
  //int* it2 = b.begin(); -- does not compile, but the compiler already knows what b.begin() is...
  auto it2 = b.begin(); // "points" to the first value in b 
  cout << *it2 << ' ' << *(it2 + 2) << '\n';
  
  // print the values within b, using iterators 
  // b.end() indicates being past-the-end 
  for(auto it = b.begin(); it != b.end(); ++it){
      cout << *it << ' ';
  }
  cout << '\n';
  
  // arrays do not have member functions but we can 
  // use the "free" function versions
  for(auto it = begin(a); it != end(a); ++it){
      cout << *it << ' ';
  }
  cout << '\n';
  
  // use a set...
  set<int> s;
  s.insert(3); // insert ~ push_back 
  s.insert(7);
  s.insert(0);
  s.insert(-5);
  s.insert(0);
  
  // wishful thinking: just like a vector?
  /*for(size_t i=0; i < s.size(); ++i){
      cout << s[i] << ' '; // no [] for sets!
  }
  cout << '\n'; */
  
  // note the ascending order and uniqueness 
  cout << "set contains: ";
  for(auto it = begin(s); it != end(s); ++it){
      cout << *it << ' ';
  }
  cout << '\n';
  
  // we can do even better than a loop with iterators (syntacically)
  cout << "with range based for loop: ";
  for(int i : s){ // int is the type of thing s stores 
      cout << i << ' ';
  }
  cout << '\n';
  
  // range based for loops work across container types 
  for(int i : a){ // int is the type of thing within a 
      cout << i << ' ';
  }
  cout << '\n';
  
  for(int i : b){
      cout << i << ' ';
  }
  cout << '\n';
  
  set<string> s2;
  s2.insert("hello");
  s2.insert("goodbye");
  s2.insert("cat");
  s2.insert("dog");
  
  for(const auto& i : s2){ // int is the type of thing s stores 
      cout << i << ' ';
  }
  cout << '\n';
  
  vector<int> w{3,2,4,0,1,0,0,-3,18,22,90,-90};
  auto w2 = w;
  
  // sort takes two iteratos here 
  // first = beginning of sorting range 
  // last = just past the end of the sorting range 
  // most algorithms with two iterators for ranges use 
  // [first, last)
  sort(begin(w), end(w));
  for(int i : w){ cout << i << ' ';}
  cout << '\n';
  
  sort(begin(w2), begin(w2)+6);
  for(int i : w2){ cout << i << ' ';}
  cout << '\n';
  
  

    return 0;
}
