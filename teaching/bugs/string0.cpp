#include<string>
#include<iostream>

int main(){
  // from what I can tell, it invokes a constructor expecting a const char* and a defaulted allocator
  // but treating the address 0 as a const char* is very bad...
  std::string s(0);
  std::cout << s << "...";
  return 0;
}
