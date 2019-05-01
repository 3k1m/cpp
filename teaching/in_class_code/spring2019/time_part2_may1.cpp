#include<iostream>
#include<stdexcept>

class Time{
private:
  int hours, minutes, seconds;
  static constexpr int sec_per_min = 60, sec_per_hr = 3600;
    
  constexpr int total_seconds() const {
   return seconds + sec_per_min * minutes + sec_per_hr * hours;   
  }
    
  constexpr void reduce() {
    int total = total_seconds(); // sum all the seconds
    hours = total / sec_per_hr;
    minutes = (total % sec_per_hr) / sec_per_min;
    seconds = total % sec_per_min;  
  }
public:
  
    // must initialize in initializer list!
  constexpr Time(int _hours, int _minutes, int _seconds) : hours(_hours), minutes(_minutes), seconds(_seconds) {
    reduce(); // format it   
  }
    
  // note this is a NON MEMBER FUNCTION
  friend std::ostream& operator<<(std::ostream& out, const Time& t){
    out << t.hours << ":" << t.minutes << ":" << t.seconds;
    return out;
  }
    
  // unary -
  constexpr Time operator-() const {
    return Time(-hours,-minutes,-seconds);   
  }
    
  constexpr Time&operator+=(const Time& right) {
    hours += right.hours;
    minutes += right.minutes;
    seconds += right.seconds;
    reduce();
    return *this;
  }
    
    // prefix version! increments & returns reference to new time!
  constexpr Time& operator++() {
   ++seconds;
   reduce();
   return *this;
  }
    
    // take in an unused int value: this ++ is binary
    // note it returns a copy of the pre-incremented time but still increments thetime
  constexpr Time operator++(int){
     Time copy(*this); // copy current Time
     ++(*this); // call the other ++
     return copy;
  }
    // only takes one arg
  constexpr int operator[](char c) const {
      switch(c){
          case 'h': return hours; break;
          case 'm': return minutes; break;
          case 's': return seconds; break;
          default: throw std::logic_error("bad index");              
      }
  }
    
  // call operator
  constexpr void operator()(int h=0, int m=0, int s=0);
    
  // conversion operator
  constexpr explicit operator int() const{
    return total_seconds();   
  }
    
  friend std::istream& operator>>(std::istream& in, Time& t){
    in >> t.hours >> t.minutes >> t.seconds;
    t.reduce();
    if(in.fail()){
      throw std::runtime_error("bad inputs for reading");   
    }
    return in;  
  }  
    
};

// call operator
  constexpr void Time::operator()(int h, int m, int s) {
    hours = h;
    minutes = m;
    seconds = s;
    reduce();
  }

  // take in a copy on left, ref to const on right
  constexpr Time operator+(Time left, const Time& right); 

  constexpr Time operator+(Time left, const Time& right){
     return left += right;   // update the copy & return it!
  }

  // user defined literal: in C++ 11 and beyond
  // can accept unsigned long long int, lon double, char, string literals...

  constexpr Time operator""_sec( unsigned long long int s  ){
      return Time{0,0, static_cast<int>(s)};
  }

  constexpr bool operator<(const Time& left, const Time& right){
     return static_cast<int>(left) < static_cast<int>(right);   
  }

  constexpr bool operator==(const Time& left, const Time& right){
     return static_cast<int>(left) == static_cast<int>(right);   
  }

  // needto havae defined a constexpr function before
  // it can be used in a constexpr context!

int main(){
 constexpr Time t1{0,65,5};   
    
 std::cout << t1 << '\n';   
 std::cout << -t1 << '\n';
    
 Time t2(0,0,7);
 Time t3(0,0,4);
    
 t2 += t3;
  std::cout << t2 << '\n';
  std::cout << t2 + t2 << '\n';
    
  constexpr Time ttest = Time(0,0,1) + Time(0,1,0);  
    
  Time t4(0,0,0);
    
  std::cout << t4 << '\n';
  std::cout << ++t4 << '\n';
  std::cout << t4 << '\n';
  std::cout << t4++ << '\n';
  std::cout << t4 << '\n';
    
  std::cout << ++++++t4 << '\n';
  std::cout << t4 << '\n';
  std::cout << t4++++++ << '\n';
  std::cout << t4 << '\n';
    
   Time t5(1,2,3);
   t5();  // call call operator no arguments - h, m, s = 0
   std::cout << t5 << '\n';
    
   int a = static_cast<int>(t5);
   std::cout << a << '\n';
    
   std::cout << 128_sec << '\n'; 
    
   std::cin >> t5;
   std::cout << t5 << '\n';
    
   std::cout << std::boolalpha << (0_sec < 43_sec) << '\n' <<
       (14_sec == 14_sec) << '\n';
    
   std::cout << t4['r'] << '\n'; 
    

    
    // different from fundamental types
  int x = 9;
  ++++x;
   // x++++;
    
  return 0;   
}
