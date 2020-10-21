#include<iostream>
#include "largest.h"

int main(){
  largest_value v(3);
  
  std::cout << v.get_max() << '\n';
  
  v.add_value(3.14);
  
  std::cout << v.get_max() << '\n';
  
  v.add_value(0);
  
  std::cout << v.get_max() << '\n';
  
  return 0;    
}
