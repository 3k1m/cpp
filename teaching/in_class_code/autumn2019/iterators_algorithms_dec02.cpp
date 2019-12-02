#include <utility>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

// write a predicate function to compare chars...
bool char_comp_less(char a, char b) { return a< b; }
// above is normal alphabetical

bool char_comp_great(char a, char b) { return b< a; }
// above is reverse alphabetical

struct Foo{
  int i;
  Foo(int x) : i(x) {}  
};

// need to compare to find
bool operator==(const Foo& f1, const Foo& f2) { return f1.i == f2.i; }

int main()
{
   // will have members
   // first of type string 
   // second of type int 
    pair<string, int> alice;
    alice.first = "Alice";
    alice.second = 40;

    pair<string, int> bob("Bob", 50);
    
    cout << alice.first << ' ' << alice.second << '\n';

   cout << bob.first << ' ' << bob.second << '\n';
   
   
   string s("olleh");   
   // go backwards
   for(auto it = s.rbegin(); it != s.rend(); ++it){
      cout << *it;   
   }
   cout << '\n';
   for(auto it = s.begin(); it != s.end(); ++it){
      *it += ('A'-'a');   
   }
   cout << s << '\n';
   
   for(auto it = s.cbegin(); it != s.cend(); ++it){
      // *it += ('A'-'a');  ERROR: const_iterators cannot change what they poin to 
   }
   
   list<int> L;
   L.push_back(7);
   L.push_front(3);
   L.push_back(111);
   
   // not all iterators have a < operator defined
   // but != does work for all iterators
  // for(auto it = L.begin(); it < L.cend(); ++it){
   for(auto it = L.begin(); it != L.cend(); ++it){
      cout << *it << ' '; 
   }
   cout << '\n';
 
   // string is a container...
   // does normal sorting based on < for chars
   sort( begin(s), end(s) );
   
   cout << s << '\n';
   
   // does sorting based on char_comp_great for chars
   sort( begin(s), end(s), char_comp_great );
   
   cout << s << '\n';
   
   // does sorting based on char_comp_less for chars
   sort( begin(s), end(s), char_comp_less );
   
   cout << s << '\n';
   
   vector<Foo> vfoos;
   vfoos.emplace_back( 5 );
   vfoos.push_back( Foo(8) );
   vfoos.emplace_back( 10);
   vfoos.emplace_back( 10 );
   
   // find will return an iterator to the first instance
   // of the sought value if found
   // or it will return end (i.e. past the end) if not found
   auto find8 = find( begin(vfoos), end(vfoos), Foo(8) );
   
   if( find8 != end(vfoos) ) { cout << "It was found!\n"; }
    
  return 0;
}
