#include<iostream>

namespace X{
  struct Foo{
    friend void bah(const Foo&);  
  };
  // unless the line below is uncommented
  //void bah(const Foo&);
}

int main(){
 X::Foo f;
 bah(f);
 // the line below will not compile...
 //X::bah(f);  
 return 0;
}

void X::bah(const X::Foo&) { std::cout << "bah"; }
