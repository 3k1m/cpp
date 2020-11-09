#include <iostream>
#include<cstring>

template<typename T>
constexpr const T& maxx(const T& x, const T& y){
    return (x<y) ? y : x;
}

template<>
inline const char * const & maxx(const char * const &x, const char * const & y){
    return (strcmp(x,y) < 0) ? y : x;
}

template<size_t N, size_t M>
const char* maxx(const char (&x)[N], const char (&y)[M]){
    return (strcmp(x,y) < 0) ? y : x;
}

// ordinary, non-tempalte function
//const char* maxx(const char* x, const char* y){
//    return (strcmp(x,y) < 0) ? y : x;
//}

int main()
{
    std::cout << maxx(5,7) << '\n';  
    std::cout << maxx("abc", "def") << '\n';
   // std::cout << maxx<6>("fgh", "abcde") << '\n';

   
    const char* d1 = "defgh";   
     const char* a1 = "abcd";

    
    std::cout << maxx(a1,d1) << '\n';
    
    //const char* a1 = "abc";
    //const char* d1 = "defgh";

    return 0;
}
