/**
This illustrates ADL and fully-qualified lookup

The friend bah function can be found via ADL, being called even without the X:: scope, provided
it receives an argument within the X:: scope

But unless bah is also declared at namespace scope, it cannot be looked up
via X::bah
*/

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
