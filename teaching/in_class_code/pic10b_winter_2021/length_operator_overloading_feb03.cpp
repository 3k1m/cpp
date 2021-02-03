#include <iostream>
#include <string>

class Length{
private:
  int m, cm;
  constexpr int static cm_in_m = 100;
  
  // 105 cm --> 1m and 5cm
  constexpr void format() {
   int total_cm = cm_in_m * m + cm;
   m = total_cm / cm_in_m;
   cm = total_cm % cm_in_m;
  }
  
public:
  constexpr Length(int _cm = 0) : m(_cm / cm_in_m), cm( _cm % cm_in_m) {}
  
  constexpr Length(int _m, int _cm) : Length( _m * cm_in_m + _cm) {}
  
  constexpr Length operator-() const{
      return Length(-m,-cm);
  }
  
  constexpr Length& operator+=(const Length& right);
  
  // prefix ++ is UNARY
  constexpr Length& operator++(){
      ++cm;
      format();
      return *this;
  }
  
  // suffix ++ is BINARY 
  constexpr Length operator++(int){
      Length copy(*this);
      this->operator++();
      return copy;
  }
  
  friend std::ostream& operator<<(std::ostream& out, const Length& L);
    
};

constexpr Length add_stuff(){
    Length L1, L2;
    return L1 += L2;
}

// should appear in .h file as well
constexpr Length& Length::operator+=(const Length& right){
    m += right.m;
    cm += right.cm;
    format();
    return *this;
}

// now we want binary+
constexpr Length operator+(Length L1, const Length& L2){
    return L1 += L2;
}



int main()
{
  constexpr Length L1;
  constexpr Length L2(5,257);
  
  std::cout << L1 << '\n' << L2 << '\n';
  
  Length L3 = L2;
  std::cout << -L3 << '\n';
  
  L3 += Length(0,44);
  std::cout << L3 << '\n';
  
  constexpr Length L4 = add_stuff(); // uses operator+= in a constexpr setting: requires seeing def first
  
  Length L5(103);
  L5++;
  std::cout << L5 << '\n';
  ++L5;
  std::cout << L5 << '\n';
  
  // crazy
  Length L6; // 0 0 
  L6++++++;
  std::cout << L6 << '\n';
  // Q: why is L6 only 1cm, not 3cm?
  // Q: What would happen if instead, we made Length::operator++(int) a free function, i.e. 
  // Length operator++(Length&, int);
  
  
  
  return 0;
}


std::ostream& operator<<(std::ostream& out, const Length& L){
 return out << L.m << "m, " << L.cm << "cm";
 //return out;
}


