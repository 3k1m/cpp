#include<iostream>

namespace X{
    
  template<typename T>
  struct Out{
    class In{
      int x;
      friend void okay(const In&) {}  
      friend void not_okay(const In&);
    };  
  };
    
  template<typename T>
  void not_okay(const typename Out<T>::In& i) { i.x; }
  
  template<typename T>
  void still_not_okay(const typename Out<T>::In& i) {}
}

int main()
{
  // make an inner class
  X::Out<double>::In a;
  okay(a);
  //X::okay(a); // cannot be fully qualified

  // friend not_okay is not a templated function
  //X::not_okay<double>(a);    
    
  //X::still_not_okay(a); // cannot deduce type!
  X::still_not_okay<double>(a); 


  std::cout << "ran";
    
  return 0;
}
