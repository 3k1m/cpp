// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool less_than(int a, int b){
 return b < a;   
}

bool range_3_5(int i){
 return (3 <= i) && (i <= 5);   
}

struct range{ // a callable class
  int low, hi;
  range(int _low, int _hi) : low(_low), hi(_hi) {}
  bool operator()(int i) const {
   return (low <= i) && (i <= hi);   
  }
};

int main()
{
  std::vector<int> vec { 2, 3, 8, -6, -14, 22, 50};
  
  std::sort( std::begin(vec), std::end(vec), less_than );
  
  for(int i : vec){
   std::cout << i << ' ';   
  }
  std::cout << '\n';
  
  auto it = std::find_if( std::begin(vec), std::end(vec), 
    range_3_5);
    
  if(it != std::end(vec)){
   std::cout << "found a value " << *it << '\n';   
  }
  
  it = std::find_if( std::begin(vec), std::end(vec), 
    range(-6, -2));
    
  if(it != std::end(vec)){
   std::cout << "found a value " << *it << '\n';   
  }
  
  // is there a value biger than user's number?
  // do we want to write another function? another class?
  int num;
  std::cout << "what number? ";
  std::cin >> num;
  
  it = std::find_if( std::begin(vec), std::end(vec),
    [num](int i) -> bool { return i >= num; } );
    
  if(it != std::end(vec)){
   std::cout << "found a value " << *it << '\n';   
  }    
  
  int count = 0;
  auto counter = [count]() mutable -> void { std::cout << count++
    << '\n'; };
  
  counter();
  counter();
  
  
  return 0;
}
