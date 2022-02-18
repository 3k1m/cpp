#include <iostream>
#include <vector>

struct Foo{
  Foo() noexcept {}
  Foo(Foo&&) noexcept { std::cout << "&&\n"; } // try with and without noexcept
  Foo(const Foo&) { std::cout << "&\n"; }
};


int main()
{
   std::vector<Foo> f;
   f.emplace_back();
   f.emplace_back();
   f.emplace_back();
   f.emplace_back();

    return 0;
}
