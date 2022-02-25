/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

//struct X {
//void foo() const { bar(); } // ERROR: calls bar, not marked as const!
//void bar() { }
//};


struct Foo{
  const int x;
  int &y;
  Foo(int i, int& j) : x(i), y(j) {}
  
  //void bar() { ++x; }
};




int main()
{
    int a = 42;
    
    Foo f(7,a);
    cout << f.x << '\n';
    
    Foo g(9,a);
    
    g.y = 100;
    
    cout << a << '\n';
    
    //f = g; // cannot assign if member variable is const

    return 0;
}
