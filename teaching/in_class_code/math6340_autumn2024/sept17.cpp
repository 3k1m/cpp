#include <iostream>
#include<vector>
#include<string>

int main()
{
    const int x = 42;
    const int* yp = &x;
    std::cout << x << ' ' << *yp << '\n';
    
    ++(*const_cast<int*>(yp)); // evil!
    std::cout << x << ' ' << *yp << '\n';
    
    std::vector<std::string> v {"hello", "world"};
    std::vector<std::string> w;
    
    w.reserve(v.size());
    
    for(const auto& a : v){
        w.push_back(a);
    }
    
    std::vector<std::string> w2(v.begin(), v.end());
    std::cout << w.size() << ' ' << w2.size();
    

    return 0;
}
