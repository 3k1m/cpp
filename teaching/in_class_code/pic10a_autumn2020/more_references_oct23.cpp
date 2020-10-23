#include<iostream>

using namespace std;

int main(){
    int x = 10;
    int& y = x;
    
    ++y;
    x*=2;
    
    cout << x << ' ' << y << '\n';
    
    const int& z=5;
    
    // error
    // ++z;
    
    cout << z;
    
    // error
    //int& w = z;
    //++w;
    
    int r = z;
    
    
    return 0;
}
