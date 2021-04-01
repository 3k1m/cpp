#include <string>
#include <iostream>


/*template<typename Ret, typename T1, typename T2>
Ret add_stuff(T1&& t1, T2&& t2){
    return std::forward<T1>(t1) + std::forward<T2>(t2);
}*/

template<typename T1, typename T2>
auto add_stuff(T1&& t1, T2&& t2) -> decltype(std::forward<T1>(t1) + std::forward<T2>(t2))   {
    return std::forward<T1>(t1) + std::forward<T2>(t2);
}

template<typename T1, typename T2, typename T3>
void types(T1 t1, T2 t2, T3 t3){
    std::cout << t1 << ' ' << t2 << ' ' << t3;
}

void takes_lrvalue(const std::string &s) { std::cout << "Lvalue\n"; }

void takes_lrvalue(std::string&& s) { std::cout << "Rvalue\n"; }

template<typename T>
struct twins{
    T first, second;
    
    // this is not a universal reference 
    // only rvalue reference
    void set_first(T&& t){
        first = std::move(t);
    }
};


auto main() -> int { 
    std::cout << add_stuff(3.14, 7) << '\n';
    std::cout << add_stuff('x', std::string("y")) << '\n';
    
    std::cout << std::boolalpha;
    types<unsigned, int>(-3, 1.14, false);
    std::cout << '\n';
    
    takes_lrvalue(std::string("hello"));
    
    std::string s;
    takes_lrvalue(s);
    
    twins<std::string> t;
    t.set_first("hello");
    //t.set_first(s);
    t.set_first(std::string("abc"));
    
    return 0; }
