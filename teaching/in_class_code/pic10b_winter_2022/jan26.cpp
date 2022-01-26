#include <iostream>

class Foo{
  using INT = int;    
  static INT x;
  double d = 0;
  
public:
  static INT get_x() { return x; /* d; */ } 
  void inc_x() const { ++x; }
};


int main()
{
    // don't even need a Foo to exist to access the static x 
    std::cout << Foo::get_x() << '\n';
    Foo f;
    // marked as const but can change the static x 
    f.inc_x();
    std::cout << f.get_x() << '\n';
    // the x is shared between all instances of Foo 
    Foo g;
    std::cout << g.get_x() << '\n';
    
    
    {
        int x = 0;
        if(x){
            
        }
        else{
            
        }
    }
    
    
  if(int x = 0){
      int y = 7;
      std::cout << ++x << '\n';
  }
  else{
      //std::cout << y;
      std::cout << --x << '\n';
  }
  
  //std::cout << x << '\n';

    return 0;
}


// have to initialize static member variables 
Foo::INT Foo::x = 0;
