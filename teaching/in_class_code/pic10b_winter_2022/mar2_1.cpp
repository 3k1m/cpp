#include <iostream>

struct Foo{
  ~Foo() { std::cout << "~Foo()\n"; }
  Foo() {}
  Foo(int) { throw 11; }
};

struct Bar{
  ~Bar() { std::cout << "~Bar()\n" ; }
  Bar() {}
  Bar(int) : Bar() { throw 11; }
};

int main()
{
    try{
      Foo f{3};
    }
    catch(...){}
    
    try{
      Bar b{3};
    }
    catch(...){}
    

    return 0;
}
