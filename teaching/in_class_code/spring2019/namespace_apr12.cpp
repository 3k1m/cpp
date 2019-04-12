#include<iostream>

// could be in .h file

namespace N{

  struct X{
    void foo() const;  
  };
  
  void bar(const X&);
}

int main(){  
  N::X x;
  N::bar(x);

  //using namespace N;
  //X x;
  //bar(x);

  return 0;
}

// in a .cpp file

namespace N{ // open up N again
  void X::foo() const { std::cout << "foo\n"; }
}

// or do it the more brutal way...

void N::bar(const N::X& x) { x.foo(); }
