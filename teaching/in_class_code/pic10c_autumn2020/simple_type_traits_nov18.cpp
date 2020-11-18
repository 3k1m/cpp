#include <iostream>
#include <type_traits>

template<typename T>
struct is_lvalue_reference : std::false_type { };

template<typename T>
struct is_lvalue_reference<T&> : std::true_type { };

int main()
{
    
// ...
std::cout << is_lvalue_reference<int>{} << '\n'; // 0
std::cout << is_lvalue_reference<const int&>{} <<'\n'; // 1

    return 0;
}
