#include<iostream>
#include<string>

struct X{
  X() { std::cout << "X();\n"; }
  X(int) { std::cout << "X(int);\n"; }     
};

struct Z{
  //Z() { std::cout << "Z();\n"; }
  Z(int) { std::cout << "Z(int);\n"; }     
};

struct Y{
  Z z;
  X x;
  std::string s;
    
  Y(size_t N) : x(3), z(6), s(N, '!') {
    std::cout << s << '\n';
  }  
    
/*  Y(size_t N) {
   std::cout << s.size() << '\n';   
   x = X(3);
   s = std::string(N,'!');   
  } */
}; */




int main(){
 Y y(2);
    
 return 0;   
}




