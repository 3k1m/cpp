#include<iostream>

void foo(int y){ // only makes a copy 
    ++y;
}

void bar(int& y){
    ++y;
}

void baz(int *y){
    (*y)+=1;
}

int main()
{
    int x = 7;
    //foo(x);
    {
        int y = x; // copy!
        ++y;
    } // y==8, then it dies 
    std::cout << x << '\n';
    
    {
        int& y = x;
        ++y;
    }
    std::cout << x << '\n';
    bar(x);
    std::cout << x << '\n';
    baz(&x); 
    std::cout << x << '\n';

    return 0;
}
