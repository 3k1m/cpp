#include <iostream>
#include <string>

struct Foo{
  Foo() { std::cout << "Foo::Foo()\n"; }  
  Foo(const std::string& s) { std::cout << "Foo::Foo(const std::string&)\n"; }     
};

struct Bad{
  Foo f;
  
  // Foo default constructor will be called before constructor body!!!
  Bad(const std::string& in) {
      f = in;
  }
    
};

struct Good{
  Foo f;
  
  // Foo default constructor will be called before constructor body!!!
  Good(const std::string& in) : f(in) { }
    
};

struct DefaultConstructorNeeded{
  //DefaultConstructorNeeded() : g() {} // compiler tries to do this...  
  
  // the fix...
  //DefaultConstructorNeeded() : g("") {}
  Good g;  
};


int main()
{
    Bad b("hello");
    std::cout << "----\n";
    Good g("hello");
    std::cout << "----\n";
    
    DefaultConstructorNeeded d;

    return 0;
}
