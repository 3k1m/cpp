#include <iostream>
#include <string>

using namespace std;

int main()
{
    // a reference is a way to give another name
    // for a block of memory...
    
    int x = 4; // x refers to a block of memory storing 4
    // x is the name 
    
    // references (&) can only be made to Lvalues!
    
    // y is a reference to int 
    int& y = x; // y is now another name for the memory space 
    // that x describes
    
    ++y; // x and y are both changed to 5
    
    cout << "x: " << x << '\n';
    cout << "y: " << y << '\n';
    
    string s("hello");
    
    char& c = s[0]; // c references first char of s 
    c = 'H';
    
    cout << s << '\n';
    
    // promise to keep d const 
    const double d = 3.14;
    
    // don't allow these ordinary references
    // b/c they could change what is stored in d 
    //double& e = d;
    //++e;
    
    const double& e = d; // okay: const promise is kept 
    cout << e << '\n';
    
    // ERROR
    //int& bad = 8; // 8 is Rvalue
    // cannot make a reference from it!

    return 0;
}
