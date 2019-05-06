#include<iostream>

#define ONE 1
#define seven 7

#define mymax(x,y) ((x<y)?y:x)


union Foo{
  int a;
  double b;
};

struct A{
  bool a;
  int b;
  short c;
};

struct B{
  short a;
  bool b;
  int c;
};

int main(){
    std::cout << sizeof(A) << ' ' << sizeof(B) << '\n';
    
    Foo f;
    std::cout << sizeof(f) << ' ' << sizeof(double) << ' ' << sizeof(int) << '\n';
    
    f.a = 9;
    std::cout << f.a << ' ' << f.b << '\n';
    f.b = 1.1;
    std::cout << f.a << ' ' << f.b << '\n';
    
    std::cout << mymax(ONE,seven) << '\n';
    
 return 0;   
}
