// Example program
#include <iostream>
#include <string>
#include <cmath>

int main()
{
  double a = 1.1, b = 2.2;
  
  // want to update a
  a = a + b; // = means ASSIGNMENT
  
  std::cout << a << '\n';
  
  // now a is 5.5... += is shorthand
  // does same here as a = a+b
  a += b; 
  
  std::cout << a << '\n';
  
  // can do this with *, *=, -, -=, /, /=
    
  int total_seconds = 127;  
  int sec_in_min = 60;
  
  // integer division gives 2
  int min = total_seconds/sec_in_min;
  // mod arithmetic gives 7 (remainder)
  int sec = total_seconds % sec_in_min;
  
  // there is also %=
  
  std::cout << total_seconds << "s = " <<
    min << ":" << sec << '\n';
  
  int x = 4;
  
  x = x+1; // now 5
  x += 1; // now 6
  
  //++x; // increment x and give back x
  //x++; // copy x, increment x, give back copy
  
  std::cout << x << " initially\n";
  
  std::cout << "++x: " << ++x << '\n';
  std::cout << x << " after ++x\n";
  
  std::cout << "x++: " << x++ << '\n';
  std::cout << x << " after x++\n";
  
  // same with --: there is a prefix and postfix
  // version
  
  // ++ and -- only increment/decrement by 1
  
  // let's do some math
  
  std::cout << "some math...\n";
  std::cout << "overflow error\n";
  std::cout << 1000000*1000000 << '\n';
  
  // if we overflow or underflow an unsigned value,
  // it "wraps around"
  std::cout << 4u - 8 << '\n';
  
  // roundoff error, don't get exact results
  double sqrt2 = std::sqrt(2);
  std::cout << sqrt2*sqrt2 - 2;
  
  
  
  
  return 0;
}
