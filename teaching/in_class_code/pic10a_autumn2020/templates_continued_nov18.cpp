#include<iostream>
#include<string>
/*
double maxx(double a, double b){
    return (a<b) ? b : a;
}

int maxx(int a, int b){
    return (a<b) ? b : a;
}

const std::string& maxx(const std::string& a, const std::string& b){
     return (a<b) ? b : a;   
}*/

template<typename T>
const T& maxx(const T& a, const T& b){
     return (a<b) ? b : a;   
}

template<typename T>
const T& minn(const T& a, const T& b){
     return (b<a) ? b : a;   
}

int main(){
    
    std::cout << maxx(5,7) << '\n';    
    std::cout << maxx(4.9, 4.8) << '\n';
    
    std::string s1("abc"), s2("def");    
    std::cout << maxx(s1, s2) << '\n';
    
    // ambiguities: int or double for template?
    //std::cout << maxx(8, 7.3) << '\n';
    
    std::cout << maxx<int>(8, 7.3) << '\n';
    std::cout << maxx<double>(8, 7.3) << '\n';
    
    // m references memory that has been repurposed, neither 100 a's nor 500 b's.
    const std::string& m = maxx( std::string(100,'a'), std::string(500, 'b') );
    std::string msg = "The maxx is: ";
    std::cout << msg << m;
    
    return 0;
}
