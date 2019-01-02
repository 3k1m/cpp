#include<iostream>
#include<vector>

struct Foo{
  Foo() {} // default constructor
  Foo(const Foo&) { std::cout << "copy Foo\n";} // copy constructor
  Foo(Foo&&) {std::cout << "move Foo\n";} // move constructor NOT MARKED noexcept
};

struct Bar{
  Bar() {} // default constructor
  Bar(const Bar&) { std::cout << "copy Bar\n";} // copy constructor
  Bar(Bar&&) noexcept {std::cout << "move Bar\n";} // move constructor NOT MARKED noexcept
};

int main(){
  std::vector<Foo> vfoo;
  vfoo.emplace_back(); // add a Foo
  vfoo.emplace_back(); // add another Foo: overflows capacity, items are COPIED over
  
  std::vector<Bar> vbar;
  vbar.emplace_back(); // add a Bar
  vbar.emplace_back(); // add another Bar: overflows capacity, items are MOVED over  

  return 0;
}