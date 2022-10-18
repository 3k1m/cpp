#include <iostream>

void print(const auto& x){
    std::cout << x;
}

auto add2(auto a, auto b){
    //std::cout << a[3] << '\n';
    return a+b;
}

auto quad_fun(double a, double b, double c){
    return [a,b,c](double x){ return a*x*x + b*x + c; };
}

// variadic functions
// handle arbitrary number of arguments
auto add(auto ... vals){
    return (vals + ...); // unary left fold
}

void print(const auto& ... params){
    (std::cout << ... << params);
}

int main()
{
    print(7);
    print('\n');
    print(3.14159);
   
    //int arr[] = {1,2,3,4,5};
    //add(arr,3);
   
    std::cout << '\n' << add2(3,4) << '\n';
    std::cout << add2(1.1,2.2) << '\n';
   
    auto poly = quad_fun(2,1,0);
    // 2*3*3 + 1*3 + 0
    std::cout << "poly(3) = " << poly(3) << '\n';
   
    std::cout << "adding...\n";
    std::cout << add(1) << '\n';
    std::cout << add(1,2,3.1,4,5,6,7,8) << '\n';
   
    print("hello", '\n', "world!!!\n", 2.71828);

    return 0;
}
