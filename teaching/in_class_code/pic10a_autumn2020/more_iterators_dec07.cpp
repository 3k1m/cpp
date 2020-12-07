#include <iostream>
#include <iterator>


int main()
{
    int x[] = {1,2,3,4,5};
    
    for(int i : x){ std::cout << i << ' '; }
    std::cout << '\n';
    
    // need C++17
    for(auto it = std::cbegin(x); it != std::cend(x); ++it)
    { 
        std::cout << *it << ' ';
    }
    std::cout << '\n';
    for(auto it = std::crbegin(x); it != std::crend(x); ++it)
    { 
        std::cout << *it << ' ';
    }
    
}
