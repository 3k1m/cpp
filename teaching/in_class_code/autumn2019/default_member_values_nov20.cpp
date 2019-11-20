#include <iostream>
#include <string>

struct X{
  int a = 11, b = 9, c;
  X() : b(14), c(7) {
      std::cout << a << ' ' << b << ' ' << c << '\n';
  }
};

int main()
{
  X x;
  return 0;
}
