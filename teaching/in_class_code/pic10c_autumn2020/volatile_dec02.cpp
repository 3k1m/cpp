#include <iostream>



int main()
{
    //const int x = 42;
    //const int* xp = &x;
    
    const volatile int x = 42;
    const volatile int* xp = &x;
    
    ++const_cast<int&>(x);
    
    std::cout << x << '\n';
    std::cout << *xp << '\n';

    return 0;
}
