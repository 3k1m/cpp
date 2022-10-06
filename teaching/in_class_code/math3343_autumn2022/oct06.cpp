#include <iostream>
#include <map>

int main()
{
    std::map<int, double> map;
    map[3] = 3.14;
    map[0] = 0.96;
    map[7] = 0.1111;
    map[300] = -90;
   
    map[7] = 0.222;
   
    for(const auto& [i, d] : map){
        std::cout << i << " -> " << d << '\n';
    }
   

    return 0;
}
