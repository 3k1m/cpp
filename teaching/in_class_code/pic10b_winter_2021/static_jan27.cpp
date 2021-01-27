#include<iostream>

class X{
private:
  static int x; 
public:
  static void inc() { ++x; }
  static int get() /* no const */ { return x; }    
};

int main()
{
  std::cout << X::get() << '\n';
  X x1;
  X x2;
  x1.inc();
  std::cout << x2.get() << '\n';

  return 0;
}

// imagine this in some .cpp file
int X::x = 0;
