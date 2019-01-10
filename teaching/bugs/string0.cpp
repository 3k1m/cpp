#include<string>
#include<iostream>

struct X{
  std::string s;
  // was a typo, meant to write s()!!!
  X() : s(0) {}
};

int main(){
  // from what I can tell, it invokes a constructor expecting a const char* and a defaulted allocator
  // but treating the address 0 as a const char* is very bad...
  X x;
  std::cout << x.s << "...";
  return 0;
}
