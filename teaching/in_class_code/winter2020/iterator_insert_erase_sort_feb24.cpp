// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void print_vec( const std::vector<int>& v){
  for(auto i : v){ // auto ~ int
   std::cout << i << ' ';   
  }
  std::cout << '\n';  
}

void print_vec( 
    const std::vector<std::string>& v){
        // the & here saves us from copying strings
  for(const auto& s : v){ // auto ~ string
   std::cout << s << ' ';   
  }
  std::cout << '\n';  
}

int main()
{
  std::vector<int> v{2,4,8,10};  
  v.insert( std::begin(v) + 2, 6);  
  print_vec(v);
  
  v.erase( std::begin(v) + 3);  
  print_vec(v);
  
  std::vector<std::string> w{"hello", " ", "world"};  
  print_vec(w);
  
  std::vector<int> x{8, -3, 100, -76, 238, 0};
  std::sort( x.begin(), x.end() );
  
  print_vec(x);
    
  return 0;
}
