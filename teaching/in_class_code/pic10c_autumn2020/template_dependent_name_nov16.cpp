#include<iostream>

template<typename T>
struct Foo{
  template<typename S>
  void bar() const { std::cout << "Foo::bar\n"; }
};

template<typename T>
void call(const T& t){
    // dependent name bar!!!
  t.template bar<int>();  
}

int main(){
    call(Foo<char>{});
    
    Foo<char> f;
    f.bar<int>();
    
    return 0;
}
