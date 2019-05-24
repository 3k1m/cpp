#include<iostream>
#include<string>

template<typename T>
constexpr const T& my_max(const T& x, const T& y){
 return (x<y) ? y : x;   
}

std::string return_hi() { return "hi"; }
std::string return_z() { return "z"; }

int main(){
 
    std::string s1("hello"), s2("goodbye");
    
    std::cout << my_max(s1,s2) << '\n';
    constexpr int maxint = my_max(-8,3);
    std::cout << maxint << '\n';
    
    // line below will not compile
    constexpr std::string bad = my_max( return_hi(), return_z() );
    
    // UNDEFINED BEHAVIOUR!
    const std::string& max = my_max( return_hi(), return_z() );
    
    std::string temp("this is a temp string...");
    
    std::cout << temp;
    
    temp += '!';
    
    std::cout << max << "\n!!!";
    
    return 0;
}
