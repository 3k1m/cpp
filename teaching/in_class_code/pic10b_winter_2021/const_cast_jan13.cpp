#include<iostream>

void i_promise( const int& u){
    // the function lied!
    int& r = const_cast<int&>(u);
    r = 0;
}



int main(){
 int x = 1;    
 
 i_promise(x);
 
 std::cout << x << '\n';
    
 return 0;   
}
