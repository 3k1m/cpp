#include<iostream>
#include<string>
#include<map>
#include <mutex>

extern std::mutex m;

void print_range(int low, int high){
 for(int i=low; i <= high; ++i){
  std::cout << i << '\n';   
 }
}

void foo(int a){
  int asqrd = a*a;
  print_range(a,a*a);
 // for(int i=a; i <= asqrd; ++i){
 //   std::cout << i << '\n';   
 //} 
}
 
void bar(int a){
  int acbd = a*a*a;
  for(int i=a; i <= acbd; ++i){
    std::cout << i << '\n';   
 }     
}

struct X{
    std::string s;
    std::map< std::string, int > m;
    
    virtual ~X() {}
    X(X&&) = default;
    X(const X&) = default;
};

struct array{
    int *a;
    array() : a( new int[7]() ) {} 
    ~array() { std::cout << "!~"; delete[] a; a = nullptr; }
};




int main(){
    
    array arr;
    arr.a[0] = 6;
    {
    array arr2 = arr;
    arr2.a[2] = 0; // bad things will happen after the }
    }
    arr.a[0] = 9;
    
    std::cout << arr.a[0] << '\n';
    
    
    
  foo(3);
  bar(4);
    
    
 return 0;   
}
