#include <iostream>
#include <string>

template<typename T>
const T& maxx(const T& a,
  const T& b){
   return (a<b) ? b : a;   
  }
  
std::string get_A(){
 return "A";   
}

std::string get_B(){
 return "B";   
}

int main()
{
    // DANGER
  const std::string& x = maxx(
      get_B(), get_A() );
      
  int y = 42;
  
  std::cout << y << '\n' <<
    x << '\n' << "...";
    
  return 0;
}
