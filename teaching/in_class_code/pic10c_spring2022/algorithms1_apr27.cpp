#include <iostream>
#include<algorithm>
#include<vector>
#include<numeric>

int main()
{
    constexpr size_t sz = 10;
    std::vector<int> v;
    v.resize(sz);
    //std::iota(v.begin(), v.end(), 0);
    std::generate(v.begin(), v.end(),
    [cnt=0]() mutable { return cnt++;});
    
    std::for_each(v.begin(), v.end(),
    [](int i){ std::cout << i << '\n';});
    
    std::stable_sort(v.begin(), v.end(),
    [](int i, int j){ return i/2 >= j/2;});
    
    std::for_each(v.begin(), v.end(),
    [](int i){ std::cout << i << '\n';});
    
    

    return 0;
}
