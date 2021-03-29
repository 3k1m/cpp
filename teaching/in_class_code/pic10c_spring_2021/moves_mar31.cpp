
#include <iostream>

struct Foo{
  Foo(int) noexcept { std::cout << "Foo(int)\n"; }
  Foo(const Foo&) noexcept { std::cout << "Foo(const Foo&)\n"; }
  Foo(Foo&&) noexcept { std::cout << "Foo(Foo&&)\n"; }
  Foo& operator=(const Foo&) & noexcept { std::cout << "operator=(const Foo&)\n"; }
  Foo& operator=(Foo&&) & noexcept { std::cout << "operator=(Foo&&)\n"; }
    
};

void swap_foos(Foo& x, Foo& y){
    Foo temp = std::move(y);
    y = std::move(x);
    x = std::move(temp);
}

int main()
{
    Foo a{3}, b{4};
    swap_foos(a,b);

    return 0;
}
