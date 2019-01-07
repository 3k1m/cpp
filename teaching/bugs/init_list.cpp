#include<iostream>
#include<map>
#include<initializer_list>

int main()
{
  std::map<int, std::initializer_list<int>> m;
 
  for (int i = 0; i < 5; ++i) { // add i and i+1 for i=0..4
  
    // unfortunately, this memory that is allocated is only temporary...
    m[i] = std::initializer_list<int>{ i,i + 1 };
  }

  // certainly not the nice
  // 0 0 1
  // 1 1 2
  // etc. - at least not on all compilers...
  
  for (const auto& pair : m) { // go through all of the map
    std::cout << pair.first << " "; // print the int
    for (auto i : pair.second) { // and its initializer list pair
      std::cout << i << " ";
    }
    std::cout << '\n';
  }
  
  return 0;
}
