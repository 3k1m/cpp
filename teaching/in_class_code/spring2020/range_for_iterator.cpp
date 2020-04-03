#include <iostream>
#include <string>
#include <vector>
#include <iterator>

int main()
{
  std::vector<std::string> animals {"cat", "dog", "fish", "bird"};
  
  //for(size_t i=0; i < animals.size(); ++i){
  // std::cout << animals[i] << '\n';   
  //}
  
  for( auto it = std::begin(animals);
    it != std::end(animals); ++it){
      std::cout << it->size() << '\n';    
    }
    
  for( const auto& a : animals ){
      std::cout << a << '\n';    
    }
  
  return 0;
}
