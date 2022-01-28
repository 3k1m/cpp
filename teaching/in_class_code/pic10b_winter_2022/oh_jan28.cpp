#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

int get_val() {
    return std::rand();
}

struct Foo{
private:
  static int next;    
public:
  int a, b;
  int i;
  virtual ~Foo() = default;
  Foo(std::istringstream& iss) : a(0), b(0), i(next++) {
      iss >> a >> b;
  }  
};

struct Bar : Foo{
  int c;
  Bar(std::istringstream& iss) : Foo(iss), c(0) {
      iss >> c;
  }  
};

struct Baz{
  int i;
  static int get() { return 8; }  
  Baz() : i ( get() ) {}
};

int main()
{
   std::istringstream iss{"42 8 -3"};
   //Foo f{iss};
   //std::cout << f.a << '{ ' << f.b << '\n';
   Bar b(iss);
   
   std::cout << b.a << ' ' << b.b << ' ' << b.c << '\n';
   
   //b.next;

    return 0;
}


int Foo::next = get_val();
