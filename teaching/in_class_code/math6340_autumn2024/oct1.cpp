#include <iostream>

int main()
{
    // [] = the capture list 
    // () = the call operation -- think of this like a function call, specifying parameters
    // { } = the body, does the work, can return a value
    auto msg = []() { return "hello\n"; };
    std::cout<< msg() ;
    
    auto double_value = [](double d) { return 2*d; };
    std::cout << double_value(5.5) << '\n';
    
    int x = 0;
    auto inc_val = [](int &i) { ++i; };
    inc_val(x);
    std::cout << x << '\n';
    
    int i = 1, j=2, k=3;
    // list the values to capture in the [] -- they are "frozen" into the lambda
    auto adder = [i,j,k](int a, int b) { return i + j + k + a + b; };
    std::cout << adder(4,5) << '\n';
    
    // captures all by value with =
    auto prod = [=](int a, int b) { return i*j*k*a*b; };
    std::cout << prod(4,5) << '\n';
    

    return 0;
}
