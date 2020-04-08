#include <iostream>

using namespace std;

void foo(const int& x){
    int& y = const_cast<int&>(x);
    
    ++y;
}

int main()
{
  int x = 42;
  const int z = 5;
  
  int* zp = const_cast<int*>(&z);
  ++(*zp);
  
  std::cout << z << ' ' << *zp << ' ' << (zp - &z) << '\n';
  
  foo(x);
  
  std::cout << x << '\n';
  
  return 0;
}
