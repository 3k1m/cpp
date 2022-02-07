// plan:
// subscript operator
// user defined literal 
// comparisons operators 


#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

namespace num{ 
  class Zmod11Z{
      
      // friend should not be taken lightly 
    // declared here 
    friend std::istream& operator>>(std::istream& in, Zmod11Z& z);
    
    int i; 

  constexpr void format() {
      i %= n; // so now i is -(n-1), -(n-2), ..., -1, 0, 1, 2, ..., n-1 
      if(i<0){ // can't allow this: must be nonnegative 
          i+=n;
      }
  }

  public:
    static constexpr int n = 11; // so the "values" this class can take are 0, 1, 2, ... 10
  
    constexpr Zmod11Z( int _i) : i(_i) {
        format();
    }
    
    // the unary +
    constexpr Zmod11Z operator+() const{
        return *this;
    }
    
    // +=: binary, member function!
    constexpr Zmod11Z& operator+=(const Zmod11Z& z){
        i += z.i;
        format();
        return *this;
    }
    
    //constexpr Zmod11Z& operator+=(const Zmod11Z& z);
    
    // conversion operator turns the class into an int 
    constexpr explicit operator int() const;
    
    // the prefix -- 
    constexpr Zmod11Z& operator--(){
        --i;
        format();
        return *this;
    }
    
    constexpr Zmod11Z operator--(int){
        auto copy{*this};
        --(*this); // prefix --, defined above 
        return copy;
    }
    
    // call operator: has to be a member function 
    constexpr void operator()(){
        i = 0;
    }
    
    // another overload 
    constexpr void operator()(int j){
        i = j;
        format();
    }
    
    // subscript 
    constexpr int operator[](char c) const {
        // if c is 'i', return the value 
        // otherwise throw exception 
        
        if(c=='i'){
            return i;
        }
        else{
            throw std::logic_error("invalid subscript argument");
        }
    }
    
  };
  
  
  constexpr Zmod11Z::operator int() const{
        return i;
    }
    
    
  constexpr Zmod11Z operator+(Zmod11Z z1, const Zmod11Z& z2){
      return z1 += z2; // z1+=z2, after updating z1, evaluates to z1 (as a reference)
      // z1+z2; -- can't do this because would call itself again and again and again ..
  }    
  
  std::ostream& operator<<(std::ostream& out, const Zmod11Z& z){
        out << z['i'] << " (mod " << Zmod11Z::n << ")";
        return out;
    } 
    
    
    constexpr bool operator<(const Zmod11Z& z1, const Zmod11Z& z2){
        return z1['i'] < z2['i'];
    }
    
    constexpr bool operator==(const Zmod11Z& z1, const Zmod11Z& z2){
        return !(z1<z2) && !(z2<z1);
    }
    
    // nested within num
    namespace literals{
        constexpr Zmod11Z operator""_z(unsigned long long int x){
            return {static_cast<int>(x)};
        }
    }

}


int main()
{
  num::Zmod11Z x{4};
  std::cout << x << '\n';
  
  constexpr num::Zmod11Z y{12};
  std::cout << y << '\n';
  
  // unary +
  std::cout << +y << '\n';
  
  num::Zmod11Z a{2}, b{3};
  a += b; // += operator 
  std::cout << a << '\n';
  
  constexpr auto c = num::Zmod11Z{2} + num::Zmod11Z{9} ;
  std::cout << c << '\n';
  
  num::Zmod11Z d{0};
  --d;
  std::cout << d << '\n';
  d--;
  std::cout << d << '\n';
  
  // d can be treated like a function either 
  // void ()
  // void (int)
  d(12); // call operator with int input 
  std::cout << d << '\n';
  d(); // call operator with no input 
  std::cout << d << '\n';
  
  std::cout << d['i'] << '\n';
  
  try{
      d['b']; 
  }
  catch(const std::exception& e){
      std::cerr << e.what() << '\n';
  }
  
  using namespace num::literals;
  constexpr auto e = 13_z;
  
  std::cout << e << '\n';
  
  std::vector v{1_z, 2_z, 8_z, 4_z, 5_z, 0_z};
  std::sort(std::begin(v), std::end(v));
  
  std::cout << "sorted...\n";
  for(const auto& z : v){
      std::cout << z << '\n';
  }
  
  auto it = std::find(std::begin(v), std::end(v), 6_z);
  
  

    return 0;
}



namespace num{
    // not a member function, it is a free function!
    std::istream& operator>>(std::istream& in, num::Zmod11Z& z){
        in >> z.i;
        if(!in){ // stream is invalidated
            throw std::runtime_error("bad reading");
        }
        z.format();
        return in;
    }
    
   

}
