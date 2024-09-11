#include <iostream>
#include <vector>
#include <string>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
    for(int i : v){
        out << i << ' ';
    }
    return out << '\n';
}

auto main() -> int
{
    std::cout<<"Hello World\n";
    
    std::vector v(4,5);
    std::cout << v;
    std::vector w{4,5};
    std::cout << w;
    
    std::string one_hundred{"100"};
    int i = std::stoi(one_hundred);
    std::cout << i << '\n';
    
    std::string s = std::to_string(i);
    std::cout << s << '\n';

    return 0;
}
