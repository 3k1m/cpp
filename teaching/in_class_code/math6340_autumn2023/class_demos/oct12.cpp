#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

// try this with/without the const 
void print_string(const std::string& s){
    std::cout << s << '\n';
}

void print_string(const std::string* sp){
    std::cout << *sp << '\n';
}

void change_string(std::string& s){
    s += s;
}

std::string change_string2(std::string s){
    return s += s;
}


// auto can be used for generic functions 
// secretly this creates a function template 
auto add(auto x, auto y){
    return x+y;
}

auto invoke_lambda(auto lam, auto param){
    return lam(param);
}


class Foo{
private:
  int x, y;
  std::string s;
public:
  Foo(int i, const std::string& _s) : x(i), y(0), s(_s) {}
  
  void inc_x(int val) { x += val; }
  
  int get_x() const { return x; } // only returns copy, can mark as const, no change to member x 
  
  // b/c s is const       // efficient return   // tells compiler that s is const std::string
  const             std::string&      get_s()               const                                     { return s; }
  
};


class pedometer{
private:
//public:
  unsigned steps;
public:
  // parameters   start the ctor init list       initializations       body 
  pedometer()       :                            steps(0)               {}
  
  void take_steps(unsigned num) { steps += num; }
  
  unsigned get_steps() const { return steps; }
};


template<typename T1, typename T2>
struct pair{ // both member variables are public 
    T1 first;
    T2 second; 
};


int main()
{
    {
        // c style array 
        double doubles[] = {1.1, 2.2, 3.3};
        // has no member functions 
        //std::cout << doubles.size();
        
        
        // std::array 
        std::array<int, 5> arr{1,2,3,4,5};
        std::cout << arr.size() << '\n';
        
        
    }
    
    
    return 0;
    
    {
        pair<int,double> p;
        p.first = 8;
        p.second = 3.14;
        std::cout << p.first * p.second << '\n';
    }
    
    
    {
        pedometer p;
        p.take_steps(2000);
        p.take_steps(1000);
        std::cout << p.get_steps() << '\n';
        //p.steps = 10000000;
        std::cout << p.get_steps() << '\n';
    }
    
    
    
    
    {
        std::cout << invoke_lambda(
            [](int i) { return i+1; }, 
            41) << '\n';
    }
    
    
    
    {
        std::cout << add(5,9) << '\n';
        std::cout << add(5.5,9) << '\n';
        std::string a{"a"}, b{"bb"};
        std::cout << add(a,b) << '\n';
        
        std::vector w{1,2,3};
        std::cout << *add(w.begin(), 1) << '\n';
        
        std::cout << add('5', std::string{"this is a string"}) << '\n';
        
        // can't do anything
        //add(5, std::string{"this is a string"});
    }
    
    
    { // auto can avoid explicitly writing brutal data types 
        const std::vector v{1,2,3,4};
        std::vector<int>::const_iterator it = v.begin();
        std::cout << *it << '\n';
        auto it2 = v.begin();
    }
    
    {
        // auto needed to store lambda as variable 
        auto adder = [](int a, int b) { return a+b; };
        std::cout << adder(3,5) << '\n';
    }
    
    {
        std::map<int,int> m;
        m[3] = 3;
        m[8] = 11;
        m[0] = 4;
        m[1] = -2;
        
        // auto used for structured bindings 
        for(const auto& [a,b] : m){
            std::cout << a << ":" << b << '\n';
        }
    }
    
    return 0;
    
    
    {
        const std::string s{"This is a very long string. So long that it should not be copied. Ever!"};
        print_string(s);
        print_string(&s);
        print_string("hello world. I am a string literal getting printed.");
        
        std::string t = "abc";
        change_string(t);
        std::cout << t << '\n';
        
        t = change_string2(t);
        std::cout << t << '\n';
    }
    
    
    
    
    {
        int x = 7;
        int y = 11;
        int *p = &x;
        std::cout << *p << '\n';
        p = &y;
        std::cout << *p << '\n';
        
        const int * p2 = &x;
        std::cout << *p2 << '\n';
        p2 = &y;
        std::cout << *p2 << '\n';
    }
    
    
    
    {
        int x = 42;
        int *xp = &x; // ptr 
        int &xr = x; // ref 
        const int* xpc = &x; // ptr to const int 
        const int& xrc = x; // ref to const int 
        std::cout << x << ' ' << *xp << ' ' << xr  << ' ' << *xpc << ' ' 
           << xrc << '\n';
        --x;
        std::cout << x << ' ' << *xp << ' ' << xr  << ' ' << *xpc << ' ' 
           << xrc << '\n';
        --(*xp);
        std::cout << x << ' ' << *xp << ' ' << xr  << ' ' << *xpc << ' ' 
           << xrc << '\n';
        --xr;
        std::cout << x << ' ' << *xp << ' ' << xr  << ' ' << *xpc << ' ' 
           << xrc << '\n';
        // errors: treated as if pointing to a const int, or referencing a const int 
        // --(*xpc);
        // --xrc;
        //int* xp2 = xpc;
        //int& xr2 = *xpc; 
    }
    
    {
        const int x = 42;
        const int* xpc = &x;
        const int& xrc = x;
        
        // can't reference to non-const or point to non-const from a const variable 
        //int& xr = x; 
        //int* xp = &x;
    }
    
    
    

    return 0;
}
