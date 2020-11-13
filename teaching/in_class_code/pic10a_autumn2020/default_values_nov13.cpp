#include <iostream>

using namespace std;

void print_vals(int x=0, int y=3, int z=14){
    cout << x << ", " << y << ", " << z << '\n';
}

void bar(int x=7);


int main()
{
    bar();
    
    print_vals(1,2,3);
    print_vals(4,5);
    print_vals(7);
    print_vals();
    
    

    return 0;
}



void bar(int x){
    std::cout << x << '\n';
}
