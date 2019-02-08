#include<iostream>
#include<stdexcept>

class Time{
private:
  // members
  int hours, minutes, seconds;
  static constexpr int sec_per_hr=3600, sec_per_min=60;
   
  constexpr void format(){
    hours = total_seconds() / sec_per_hr;
	minutes = (total_seconds() % sec_per_hr) / sec_per_min;
	seconds = total_seconds() % sec_per_min;  
  }
public:
  constexpr int total_seconds() const{
    return hours*sec_per_hr + minutes*sec_per_min + seconds;
  }
  
  friend std::istream& operator>>(std::istream& in, Time& t){
	  in >> t.hours >> t.minutes >> t.seconds;
	  
	  t.format();
	  
	  if(in.fail()){ // if stream failed
		  throw std::runtime_error("fail to read");
	  }
	  
	  return in;	  
  }

  constexpr Time(int _hours = 0, int _minutes = 0, int _seconds = 0) : hours(_hours), minutes(_minutes), seconds(_seconds) {
    format();
  }
  
  constexpr int operator[](char i) const{
    switch(i){
	case 'h': return hours; break;
	case 'm': return minutes; break;
	case 's': return seconds; break;
	default: throw std::logic_error("bad index");	
	}
  }
  
  constexpr operator int() const{
	  return total_seconds();
  }
  
  constexpr Time &operator+=(const Time& right);
  
  constexpr Time operator+() const{
	  return *this;
  }
  
  // prefix ++
  constexpr Time& operator++() {
	  ++seconds;
	  format();
	  return *this;
  }
  
  // postfix ++
  constexpr Time operator++(int){
	  Time copy(*this);
	  ++seconds;
	  format();
	  return copy;
  }
  
  // call operator
  constexpr void operator()(int h=0, int m=0, int s = 0){
	  hours = h;
	  minutes = m;
	  seconds = s;
	  format();
  }
};

constexpr Time operator+(Time left, const Time& right);


std::ostream& operator<<(std::ostream& out, const Time& t);


constexpr Time& Time::operator+=(const Time& right){
	hours += right.hours;
	minutes += right.minutes;
	seconds += right.seconds;
	format();
	return *this; // returns updated time
}

constexpr Time operator+(Time left, const Time& right){
	return left += right;
}

constexpr Time operator""_sec(unsigned long long u){
	return Time{0,0,static_cast<int>(u)};
}

int main(){
	
  Time t{};
  std::cin >> t;
  std::cout << t << '\n';
  
  Time t2 = 68_sec;
  std::cout << t2 << '\n';
  
  /*
  ++t;
  std::cout << t << '\n';
  t++;
  std::cout << t << '\n';
  t();
  std::cout << t << '\n';
  t(1,62);
  std::cout << t << '\n';
  
  int x = static_cast<int>(t);
  std::cout << x << '\n';
  */
  
/*  constexpr Time t2{1,2,3};
  constexpr Time t3 = t2 + t2;
  Time t4{0,0,1};
  Time t5{0,0,3};
  std::cout << +t2 << '\n' <<
    (t4 += t5) << '\n' <<
	t3 << '\n';
  */
  
  /*std::cout << t2 << '\n';
  try{
    t2['r'];
  }
  catch(...){ std::cout << "bad"; }
  
  constexpr int total = t2.total_seconds();
  std::cout << t.total_seconds() << '\n' << t2.total_seconds() << '\n' << total << '\n'; */
  
  return 0;
}


std::ostream& operator<<(std::ostream& out, const Time& t){
	out << t['h'] << ":" << t['m'] << ":" <<
	  t['s'];
	return out;	
}

