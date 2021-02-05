#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

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
  
  // conversion operator: explicit, can only be coverted with static_cast 
  explicit constexpr operator int() const {
      return cm + cm_in_m * m;
  }
  
  
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
  
  int& operator[](const std::string& idx){
     if(idx=="m"){
         return m;
     }
     else if(idx =="cm"){
         return cm;
     }
     else{
         throw std::logic_error("bad index");
     }
  }
  
  int operator[](const std::string& idx) const {
     if(idx=="m"){
         return m;
     }
     else if(idx =="cm"){
         return cm;
     }
     else{
         throw std::logic_error("bad index");
     }
  }
  
  constexpr Length& operator()() {
      m = cm = 0;
      return *this;
  }
  
  // don't need friend here, use []
  //friend std::ostream& operator<<(std::ostream& out, const Length& L);
    
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

std::ostream& operator<<(std::ostream& out, const Length& L);

std::istream& operator>>(std::istream& in, Length& L);

constexpr bool operator<(const Length& L1, const Length& L2) {
    return L1.operator int() < L2.operator int();
}

constexpr bool operator==(const Length& L1, const Length& L2){
    return !(L1 < L2) && !(L2 < L1);
}

constexpr bool operator<=(const Length& L1, const Length& L2){
    return (L1 < L2) || (L1==L2);
}

// user defined literal for cm 
constexpr Length operator"" _cm(unsigned long long u){
    return Length{static_cast<int>(u)};
}

// user defined literal for m 
constexpr Length operator"" _m(unsigned long long u){
    return Length{static_cast<int>(u), 0};
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
  ++++++L6;
  std::cout << L6 << '\n'; 
  
  int x = 7;
  ++++++x;
  // x++++++; this can't work, suffix returns prvalue and can't turn to lvalue 
  
  std::cout << "----\n";
   
  std::cout << L6["m"] << " " << L6["cm"] << '\n';
  std::cout << L6() << '\n';
  
  //std::cin >> L6;
  //std::cout << "updated L6: " << L6 << '\n';
  
  // from conversion operator 
  int tot_cm6 = static_cast<int>(L6);
  std::cout << tot_cm6 << '\n';
  
  constexpr Length L7(0,7), L8(1,9);
  
  std::cout << ( (L7 < L8) ? "L8 bigger\n" : "L8 not bigger\n");
  
  // 1u, 3.14f, 9.999L
  
  constexpr auto L9 = 1_m + 46_cm;
  std::cout << L9 << '\n';
  
  Length L10(0,5);
  Length L11(0,2);
  
  // L11 += L10 done first and result is then +='d to the L10
  L10 += L11 += L10;
  
  std::cout << L10 << '\n';
  std::cout << L11 << '\n';
  
  return 0;
}


std::ostream& operator<<(std::ostream& out, const Length& L){
 return out << L["m"] << "m, " << L["cm"] << "cm";
 //return out;
}

std::istream& operator>>(std::istream& in, Length& L){
    return in >> L["m"] >> L["cm"];
}
