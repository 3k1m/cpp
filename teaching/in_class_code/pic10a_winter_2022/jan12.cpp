#include <iostream>


int main()
{
   int x = 100;
   std::cout << (++x) << '\n';
   std::cout << x << '\n';
   
   double d = 4.5;
   std::cout << (d--) << '\n';
   std::cout << d << '\n';
   
   std::cout << "=====================\n";
   
   std::cout << 1000000 * 1000000 << '\n';
   
   
   float f = 1.0101010101f;
   float f2 = 1 + 1.f/99;
   std::cout << f - f2 << '\n';
   

    return 0;
}
