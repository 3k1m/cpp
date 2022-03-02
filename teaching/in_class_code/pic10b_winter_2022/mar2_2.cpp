#include <iostream>
#include <string>
#include <vector>

/*int get_max(int a, int b) { return a < b ? b : a; }
double get_max(double a, double b) { return a < b ? b : a; }

const std::string& get_max(const std::string& s1, const std::string& s2){
    return s1 < s2 ? s2 : s1;
}*/

template<typename T>
constexpr const T& get_max(const T& s1, const T& s2){
    return s1 < s2 ? s2 : s1;
}

template<typename S>
std::ostream& operator<<(std::ostream& out, const std::vector<S>& vec){
    out << "[";
    for(const auto& s : vec){
        out << s << ' ';
    }
    return out << "]";
}

// std::cout << v2:
// S = std::vector<int>
// S = int 

template<typename T, typename S>
void print_sum(const T& t, const S& s){
    std::cout << t + s << '\n';
}


int main()
{
    constexpr int a = get_max(7,9);
    
    std::cout << get_max(3,20) << '\n';
    std::cout << get_max(4.38,2.2) << '\n';
    
    const std::string& bad = get_max(std::string{"abc"}, std::string{"def"});
    const std::string okay = get_max(std::string{"abc"}, std::string{"def"});
    
    std::cout << bad << "(this is UB)\n";
    
    std::string s1{"hi"};
    std::string s2{"bye"};
    std::cout << get_max(s1,s2) << '\n';
    const std::string& s3 = get_max(s1,s2);
    
    std::cout << bad << "(this is UB)\n";
    std::cout << okay << "(this is safe)\n";
    
    //std::cout << get_max(7.7, 7) << '\n';
    std::cout << get_max<int>(7.7, 7) << '\n'; // T = int 
    std::cout << get_max<double>(7.7, 7) << '\n'; // T = double 
    
    std::vector<int> v1{1,2,3};
    std::cout << v1 << '\n';
    
    std::vector<std::vector<int>> v2{{1,2,3},{4,5},{6}};
    std::cout << v2 << '\n';
    
    print_sum(3,9.8); // T = int, S = double 

    return 0;
}
