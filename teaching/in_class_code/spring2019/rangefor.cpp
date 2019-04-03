#include<iostream>
#include<vector>
#include<set>
#include<string>

int main(){
 std::string v[] = {"hello", "world", "how", "are", "you"};
 // std::set<std::string> v{"hello", "world", "how", "are", "you"};    
 
// for(size_t i=0; i < v.size(); ++i){
//  std::cout << v[i] << '\n';   
// }
    
/* for(int i : v){
  std::cout << i << '\n';   
 }     
    
  auto before_start = v.rend();
    
  for( auto it = v.rbegin(); it != v.rend(); ++it){
    std::cout << *it << '\n';   
  } */
    
  for(const auto& s : v){
   std::cout << s << '\n';   
  }
    
  auto past_end =v.end();
  
  for(auto it = std::begin(v); it != past_end; ++it){
   const auto& s = *it;
   std::cout << s << '\n';
  }
    
    
  return 0;
}
