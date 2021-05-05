#include <iostream>

int (&fun( int (&x) [4]))[4]  {
  return x;      
}

int main()
{
  int a[] = {1,2,3,4};
  std::cout << *fun(a);
  
  return 0;
}
