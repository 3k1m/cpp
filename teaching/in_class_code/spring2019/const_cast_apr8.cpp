#include<iostream>

// I promise to never change x...
void foo(const int& x){
    // I lied...
    ++const_cast<int&>(x);
}

int main(){
    int a = 100;
 //const int a = 100;
 foo(a);
 std::cout << a;
  return 0;    
}
