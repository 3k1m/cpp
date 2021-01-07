// sets
// use of const in functions
// iterators

#include<set>
#include<iostream>
#include<vector>
#include<string>

int main(){
 std::vector<std::string> v{"cat", "apple", "dog", "bunny", "egg", "fries", "egg", "dog"}; 
 std::set<std::string> s{"cat", "apple", "dog", "bunny", "egg", "fries", "egg", "dog"};
 
 for(size_t i=0; i < v.size(); ++i){
  std::cout << v[i] << ' ';   
 }
 std::cout << '\n';
 
  // will not work: no [] for sets
/*  for(size_t i=0; i < s.size(); ++i){
  std::cout << s[i] << ' ';   
 }
 std::cout << '\n'; */
 
 // use iterators instead
 // this is ugly without auto
 for( std::set<std::string>::iterator it = std::begin(s);
   it != std::end(s); ++it){
    std::cout << *it << ' ';   
   }
 std::cout << '\n';
 
 // with auto
 for( auto it = std::begin(s); it != std::end(s); ++it){
    std::cout << *it << ' ';   
   }
 std::cout << '\n';
 
 // use rbegin and rend for reverse
 // use member function on older compilers
  for( auto it = s.rbegin(); it != s.rend(); ++it){
    std::cout << *it << ' ';   
   }
 std::cout << '\n';
 
 s.insert("goose");
 std::cout << "s has " << s.size() << " number of elements.\n";
 
 for(const std::string& w : s){ // would work with "v" instead of "s" too
  std::cout << w << ' ';   
 }
 std::cout << '\n';
 
 int i = 7;
 int* ip = &i; // ip is a pointer to int, pointing to i: & gives the address in memory
 std::cout << i << ' ' << *ip << '\n';
 ++i; // now i is 8 
 ++(*ip); // now i is 9: need the * before pointer to get access to what it points to
 std::cout << i << ' ' << *ip << '\n';
 
 auto v_it = std::begin(v); // so it will point to first string of vector v
 std::cout << *v_it << '\n';
 (*v_it).push_back('.');
 v_it->push_back('!');
 ++v_it; // now v_it points to apple
 (*v_it)[0] = 'A';
 
 // will have first value with extra .!
 for( auto it = std::begin(v); it != std::end(v); ++it){
    std::cout << *it << ' ';   
   }
 std::cout << '\n';
    
 return 0;   
}
