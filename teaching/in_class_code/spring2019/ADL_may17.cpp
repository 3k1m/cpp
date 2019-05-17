#include<iostream>
#include<string>

namespace bah{
    
    class X{
      int i = 0;
        
      friend void foo(X& x) { std::cout << ++x.i; }
        
    };
    
    // try with and without this declaration below
    void foo(X& x);
    
}


int main(){
    std::string s("hello\n");
    for(auto it = begin(s), end = std::end(s); it != end; ++it){
     std::cout << *it;   
    }
    
    bah::X x;
    
    // try with and without the bah:: below
    bah::foo(x);
    
    endl(std::cout);
    
    return 0;
}
