#include<iostream>
#include<vector>

int main(){
 std::vector<int> v{1,2,3,4,5};
    
 // beware the beginning below...
 // for(size_t i=v.size()-1; i >= 0; --i) { // <-- bad!
 for(size_t i=v.size()-1; i != static_cast<size_t>(-1); --i){
   std::cout << v[i] << ' ';   
 }
    
 std::cout << "...";
    
  return 0;
    
}
