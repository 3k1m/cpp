#include<iostream>

struct X{
  void foo() const & { std::cout << "L const\n"; }
  void foo() const && { std::cout << "R const\n"; }
  void foo() & { std::cout << "L non const\n"; }
  void foo() && { std::cout << "R non const\n"; }
};

int main()
{
  X x1;
  x1.foo();
  X{}.foo();
  
  const X x3 = x1;
  x3.foo();
  
  std::move(x3).foo();
  
  return 0;
}
