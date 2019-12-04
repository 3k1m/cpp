#include <iostream>
#include <string>
#include <algorithm>
#include <list>

bool foo(int i) { return (5<i) && (i < 8); }

int main()
{
  std::list<int> L{6, 8, 5, 2, 7, 0};
  
  size_t count = std::count_if( std::begin(L), std::end(L), foo );
  
  std::cout << count;

  return 0;
}
