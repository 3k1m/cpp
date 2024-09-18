#include <iostream>

#include<vector>

int main()
{
    
    int x = 42;
    int * xp = &     x; // (1)
    std::cout << xp <<'\n'; // (2)
    std::cout << *xp <<'\n'; // (3)
    
    std::vector v{1.9,2.9,3.9,4.9};
    
    // try replacing "auto" with "int", "double", etc.
    for(auto d : v){
        std::cout << d << '\n';
    }
    
    for(size_t i=0, sz = v.size(); i < sz; ++i ){
        auto d = v[i];
        std::cout << d << '\n';
    }


    return 0;
}
