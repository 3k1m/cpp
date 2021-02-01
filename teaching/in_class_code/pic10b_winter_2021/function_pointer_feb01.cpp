#include <iostream>

int doubles(int x){ return 2*x; }
int quadruples(int x){ return 4*x; }

// can also have (&f) instead of (*f) below
void foo(int x, int (*f)(int)){
 std::cout << f(x) << '\n';
}

int main()
{
    foo(3, doubles);
    foo(10, quadruples);
  
  return 0;
}
