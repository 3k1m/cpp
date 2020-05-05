#include <iostream>

template<typename T>
struct Foo{
    void bah() const { std::cout << "bah!"; }
};

template<typename T>
struct Bar{
    using foo_type = Foo<T>;
    
    // the line of could below should not be here!
    // otherwise one has to call upon a templated 
    // conversion operator
    template<typename S>
    explicit operator foo_type() const { return {}; }
   
};

int main()
{
  Bar<double> b;
  Foo<double> f = static_cast<Foo<double>>(b); // ERROR!
  f.bah();
  return 0;
}
