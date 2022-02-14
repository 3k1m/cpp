#include <iostream>
#include <string>

void print(int x){
    std::cout << x << '\n';
}

void print(double x){
    std::cout << x << '\n';
}

void print(char x){
    std::cout << x << '\n';
}

void print(const std::string& x){
    std::cout << x << '\n';
}

// S represents any type 
template<typename S>
void print2(const S& x){ 
    std::cout << x << '\n';
}
// it will work as long as << makes sense for whatever is fed into the function 


int main()
{
    print(7);
    print(3.14);
    print('a');
    print("abc");
    
    print2(7);
    print2("abc");

    return 0;
}
