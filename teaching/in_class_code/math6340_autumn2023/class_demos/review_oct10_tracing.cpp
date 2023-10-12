#include <iostream>

// you can ignore this class definition, it just helps to trace through what's going on
// scroll down to main

template<typename T>
class wrapper{
private:
  T t;
public:
  wrapper() : t() {
      std::cout << "Default constructing wrapper\n";
  }
  
  wrapper(const wrapper& s) : t(s.t) {
      std::cout << "Copy constructing wrapper from other wrapper with value " << s.t << '\n';
  }
  
  wrapper(wrapper&& s) noexcept : t(std::move(s.t))  {
      std::cout << "Move constructing wrapper from other wrapper with value " << t << '\n';
  }

  wrapper(const auto& s) : t(s) {
      std::cout << "Constructing wrapper with " << s << '\n';
  }
  
  ~wrapper() {
      std::cout << "Destructing wrapper with " << t << '\n';;
  }
  
  wrapper& operator=(const auto& s) {
      std::cout << "Assigning to wrapper with " << t << " the value " << s << '\n';
      t = s;
      return *this;
  }
  
  wrapper& operator++() {
      std::cout << "Prefix ++ on wrapper with " << t << '\n';
      ++t;
      return *this;
  }
  
  wrapper operator++(int){
      std::cout << "Suffix ++ on wrapper with " << t << '\n';
      auto cpy{*this};
      ++t;
      return cpy;
  }
  
  operator const T&() const {
      return t;
  }
  
  operator T& () {
      return t;
  }
  
};

using Int = wrapper<int>;

struct Foo{
    Int a, b, c, d;
    Foo(Int i, Int j, Int d) : c(++j), a(i++){
        d = 2*d;
    }
};


void foo(short, long double, float){ std::cout << 1 << '\n'; }
void foo(int, double, double, int*){ std::cout << 2 << '\n'; }
void foo(int, long int, int, int*){ std::cout << 3 << '\n'; }


void bar(int, int) { std::cout << "1"; }
void bar(int, short) { std::cout << "2"; }


int main()
{
    short e = 7;
    bar(e,5);
    
    
    short s = 1;
    int i[] = {1,2,3,4};
    foo(s, 23.L, 1.25f, i);
    
    // no # 1: too few parameters 
    
    // #2: promotion, conversion, promotion, exact 
    // #3: promotion, conversion, conversion, exact  
    // res:   tie          tie      2>3        tie 
    // should call #2 
    
    // f1, f2, f3, ...
    // f1 is the BEST match if:
    // - it is no worse than f2, f3, ... , fn in ALL arg -> param transformations 
    // and 
    // - it is BETTER in at least one 
    
    
    //Int i = 42;
    //i++;
    //++i;
    
    std::cout << "================\n";
    Foo f{1,2,3};

    return 0;
}
