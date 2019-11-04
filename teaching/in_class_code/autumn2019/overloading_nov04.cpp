#include <iostream>
#include <string>

void foo(int, double) { std::cout << "(1): int, double\n"; }
void foo(long int, float) { std::cout << "(2): long int, float\n"; }

int main()
{
    // int and double - perfect match
    foo(3,4.4);
    
    // long int & long double
    // long int matches (2) perfectly
    // convert long double -> float
    // in option (1) need long int -> int AND long double -> double
    // (2) has 1 coercion, but (1) has 2 coercions
    // option (2) is best
    foo(4L, 9.36L);
    
    // long int & double: no best match
    // with (1) convert long int to int, double matches
    // with (2) convert double to float, long int matches
    // ERROR
    //foo(9L, 4.);
  
  return 0;
}
