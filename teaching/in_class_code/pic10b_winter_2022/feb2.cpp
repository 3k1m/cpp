// the start of our operator overloading...

#include <iostream>

namespace num{ 
  class ZmodNZ{
    int i; // i is 0, 1, 2, ..., n-1 
    int n; // so the "values" this class can take are 0, 1, 2, ... n-1

  constexpr void format() {
      i %= n; // so now i is -(n-1), -(n-2), ..., -1, 0, 1, 2, ..., n-1 
      if(i<0){ // can't allow this: must be nonnegative 
          i+=n;
      }
  }

  public:
    constexpr ZmodNZ( int _i, int _n = 5) : i(_i), n(_n) {
        format();
    }
    
    // conversion operator turns the class into an int 
    constexpr operator int() const;
    
  };
  
  
  constexpr ZmodNZ::operator int() const{
        return i;
    }

}


int main()
{
  // n = 5 
  // 2+3 = 5 -> 0 
  // 3+3 = 6 -> 1 
  
  num::ZmodNZ x{4};
  std::cout << x << '\n';
  
  constexpr num::ZmodNZ y{12};
  std::cout << y << '\n';
  

    return 0;
}
