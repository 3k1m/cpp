#include<iostream>

int main(){
 int x = 7;
 x = x+1; // now x is 8
 x+=1; // now x is 9
 
 ++x;
 std::cout << x << '\n';
 
 x++;
 std::cout << x << '\n';
 
 int y = x++;
 std::cout << "y: " << y << " x: " << x << '\n';
 
 y = ++x;
 std::cout << "y: " << y << " x: " << x << '\n';
 
 return 0;  
    
}
