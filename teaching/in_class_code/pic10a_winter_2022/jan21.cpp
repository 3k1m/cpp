#include <iostream>
#include <string>

using namespace std;

int main()
{
    string h = "hello world";
    string &x = h; // h has a name, 'h', it is an lvalue 
    
    h[0] = 'H';
    
    cout << x << '\n';
    
    x += '!';
    
    cout << h << '\n';
    
    char& c = h[0]; // a reference to h[0]
    char d = h[0]; // only a copy of the char 
    
    x[0] = 'h';
    
    cout << c << d << '\n';

    return 0;
}
