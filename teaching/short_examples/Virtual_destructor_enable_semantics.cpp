#include <iostream>

// just a class so we can document whether it gets copied or moved
struct Foo{
  Foo() {}
  Foo(const Foo&){ std::cout << "Cctor\n";}
  Foo(Foo&&) noexcept { std::cout << "Mctor\n";}
  Foo& operator=(const Foo&){ std::cout << "C=\n"; return *this;}
  Foo& operator=(Foo&&) noexcept { std::cout << "M=\n"; return *this;}
};

// a good base class that has virtual destructor that has move and copy semantics
struct B{
  Foo f{};
  B(){}
  B(const B&) = default;
  B(B&&) = default;
  B& operator=(const B&) = default;
  B& operator=(B&&) = default;
  virtual ~B()=default;
};

// dummy class that inherits from it
struct D : public B {};

// an evil base class that has a virtual destructor but has lost move semantics
struct B2{
  Foo f{};
  virtual ~B2()=default;
};

// dummy class that inherits from it
struct D2 : public B2 {};

int main()
{
    // nice moves
    D x;
    D x2 = std::move(x);
    D x3;
    x3 = std::move(x2);
    
    // evil copies
    D2 y;
    D2 y2 = std::move(y);
    D2 y3;
    y3 = std::move(y2);
    
    return 0;
}