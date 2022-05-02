#include <iostream>


int (&foo(int (&a)[3][4], size_t i))[4]{
    return a[i];
}

template<typename T>
T bar() { return {}; }

template<>
int bar<int>() { return 3.14; }

int main()
{
    int a[3][4];
    a[0][2] = 1999;
    
    int (&(*p)(int (&)[3][4], size_t))[4] = foo;
    
    auto& r = foo(a,0);
    auto& s = p(a,0);
    
    std::cout << r[2] << '\n';
    std::cout << s[2];
    
    bar<int>();

    return 0;
}
