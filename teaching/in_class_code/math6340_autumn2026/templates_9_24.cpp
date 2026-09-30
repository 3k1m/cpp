#include <iostream>

template<typename T>
T sum(const T& a, const T& b){ return a+b; }

auto add(const auto& a, const auto& b) { return a+b; }

int main()
{
   std::cout << sum(3,4) << '\n';
   
   std::cout << sum(1.1,2.2) << '\n';
   
   std::cout << sum<double>(7,4.99) << '\n';
   
   std::cout << add(7,4.99) << '\n';
   
   

    return 0;
}
