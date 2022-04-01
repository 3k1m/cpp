#include <iostream>

void foo(int &i){
    ++i;
}

void bar(int& i, void (*p)(int&)){
    p(i);
}

int main()
{
   int x = 7;
   bar(x, foo);
   std::cout << x << '\n';

    return 0;
}
