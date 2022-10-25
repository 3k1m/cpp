#include <iostream>

/* could all be in one header file from here --> */
struct Mult{
  Mult(int _i) : i(_i) {}
 
  auto times(auto p) const;
 
  int i;
};


auto Mult::times(auto p) const {
    return p*i;
}

/* <-- to here */

int main(){
   
    Mult m{7};
   
    std::cout << m.times(3) << '\n';
    std::cout << m.times(3.14) << '\n';
   
}
