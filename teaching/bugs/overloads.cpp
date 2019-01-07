#include<string>
#include<iostream>

class Foo{
private:
  std::string s;
  bool b;
public:
  Foo(bool _b = true) : s("defaulted"), b(_b) {}
  Foo(std::string _s, bool _b = false) : s(std::move(_s)), b(_b) {}
  void print() const {
    std::cout << ( b ? s : "no display"); 
  }
};

int main(){
  Foo f("want this to print"); // but const char* -> bool is a better overload than const char* -> std::string!!!
  f.print();
  return 0;
}
