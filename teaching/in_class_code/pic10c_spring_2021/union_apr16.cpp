#include <iostream>

union stuff{
  int x;
  double d;
  char c;
};

struct Out{
  union{
    int i;
    float f;
  };  
};

int main()
{
  std::cout << sizeof(stuff) << '\n';
  
  stuff s;
  s.x = 7; // ACTUALLY THIS IS THE BELL SOUND AS A CHAR!!!! :)
  std::cout << s.x << ' ' << s.d << ' ' << s.c << '\n';
  s.d = 3.14;
  std::cout << s.x << ' ' << s.d << ' ' << s.c << '\n';
  s.c = '!';
  std::cout << s.x << ' ' << s.d << ' ' << s.c << '\n';
  
  Out o;
  o.f = 9.11f;
  std::cout << o.f << '\n';
  
  
  
  return 0;
}
