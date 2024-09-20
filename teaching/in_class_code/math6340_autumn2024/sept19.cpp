#include <iostream>
#include <string>
#include<vector>
#include<set>
#include<map>
#include<utility>

#include<algorithm>
#include<iterator>

int main()
{
  std::string s{"hello world"};
  std::cout << s.size() << '\n';
  for(char c : s){
      std::cout << c << ' ';
  }
  std::cout << '\n';
  std::cout << s[2] << '\n';
  std::string::iterator it = s.begin(); // pointing to first letter
  std::cout << *it << ' ' << *(it+7) << '\n';
  
  
  
  std::vector v{6,5,4,3,2,1,1,2,3,4,5};
  std::cout << v.size() << '\n';
  for(int i : v){
      std::cout << i << ' ';
  }
  std::cout << '\n';
  std::cout << v[2] << '\n';
  // std::vector<int>::iterator 
  auto it2 = v.begin() + 2;
  std::cout << *it2 << '\n';
  
  // generic algorithm sort 
  // sort from begin up to but not including end(past the end)
  std::sort(v.begin(), v.end());
  for(int i : v){
      std::cout << i << ' ';
  }
  std::cout << '\n';
  
  
  
  // like mathematical sets: items stored uniquely
  // by default, order elements based on <
  // <> not needed if types listed uniquely specify the type of data 
  std::set<int> st{6,5,4,3,2,1,1,2,3,4,5};
  std::cout << st.size() << '\n';
  for(int i : st){
      std::cout << i << ' ';
  }
  std::cout << '\n';
  st.insert(42);
  st.erase(1);
  for(int i : st){
      std::cout << i << ' ';
  }
  std::cout << '\n';
  // std::cout << st[2]; -- no [] operators
  
  // don't use < here because < is not defined for iterators of sets, so use !=
  for(auto it = st.begin(), e = st.end(); it != e; ++it){
      std::cout << *it << ' ';
  }
  std::cout << '\n';
  
  std::pair p{1,3.14};
  // same as 
  // std::pair<int,double> p{1,3.14};
  std::cout << p.first << ' ' << p.second << '\n';
  p.first = -2.99999;
  std::cout << p.first << ' ' << p.second << '\n';
  
  std::pair<int,int> p2; // default constructing
  std::cout << p2.first << ' ' << p2.second << '\n';
  
  // structured bindings 
  // auto [p,q,...] = thing ;
  // auto& [p,q,...] = thing; 
  // etc.
  auto& [a,b] = p;
  std::cout << a << ' ' << b << '\n';
  ++a;
  std::cout << p.first << ' ' << p.second << '\n';
  
  // username -> password
  std::map<std::string, std::string> m;
  m["Bob"] = "bob123";
  m["Connie"] = "c0nn13";
  m["Alice"] = "alice_is_cool";
  
  // in a map, stored in ascending order with < based on the keys 
  for(const auto& [user,pass] : m){ //structured bindings 
   std::cout<< user << ": " << pass << '\n';   
  }
  
  // prior to C++11 
  // C++11 gives auto to replace std::map<std::string,std::string>::iterator
  for(std::map<std::string,std::string>::iterator it = m.begin(), e = m.end();
    it != e; ++it){
      std::cout << (*it).first << ' ' << (*it).second << '\n';   
    }
  
  std::string strings[] = { "cat", "alligator", "elephant", "dog", "bird" };
  std::sort( std::begin(strings), std::end(strings));
  for(const std::string& s : strings){
      std::cout << s << ' ';
  }
  std::cout << '\n';
  if( std::find(std::begin(strings), std::end(strings), "dog" ) != std::end(strings)){
    std::cout<< "dog found";   
  }
  
  return 0;

}
