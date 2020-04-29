#include<iostream>
#include<stdexcept>
#include<string>
#include<sstream>

class Time{
private:
    int hours, minutes, seconds;
    static constexpr int sec_per_min = 60, sec_per_hour = 3600;
    
    constexpr int total_sec() const {
     return hours*sec_per_hour + minutes*sec_per_min + seconds;   
    }
    
    constexpr void format() {
      int total = total_sec();
      hours = total / sec_per_hour;
      total = total - hours*sec_per_hour; // stores extra sec for min+sec
      minutes = total / sec_per_min;
      seconds = total - minutes*sec_per_min;        
    }
public:
    constexpr Time(int _sec) : hours(0), minutes(0), seconds(_sec) { 
     format();   
    }    
    
      
    constexpr Time& operator+=(const Time& t) {
     hours += t.hours;
     minutes += t.minutes;
     seconds += t.seconds;
     format();
     return *this;
    }
    
    constexpr Time operator+() const;
    
    // prefix: unary
    constexpr Time& operator++() {
     ++seconds;
     format();
     return *this;
    }
    
    // postfix: binary
    constexpr Time operator++(int) {
     Time copy(*this);
     ++seconds;
     format();
     return copy;
    }
    
    // call operator
    constexpr Time& operator()() {
     hours = minutes = seconds = 0;
     return *this;
    }
    
    constexpr Time& operator()(int h, int m, int s) {
     hours = h;
     minutes = m;
     seconds = s;
     format();
     return *this;
    }
    
    // subscript operator
    constexpr int operator[](char c) const{
     switch(c){
         case 'h': return hours; break;
         case 'm': return minutes; break;
         case 's': return seconds; break;
         default: throw std::logic_error("invalid index");             
     }
        
    }
    
    friend std::istream& operator>>(std::istream& in, Time& t){
     in >> t.hours >> t.minutes >> t.seconds;
        
     if(!in){ // in failed state
       throw std::runtime_error("invalid writing to time");
     }
        
     t.format();
        
     return in;
    }
    
    // has to be member: conversion
    //explicit operator std::string() const;
    operator std::string() const;
};


std::ostream& operator<<(std::ostream& out, const Time& t){
       out << t['h'] << ':' << t['m'] << ':' << t['s']; 
        return out;
    }


Time::operator std::string() const {
      std::ostringstream oss;
      oss << *this;
      return oss.str();
    }


constexpr Time operator+(Time t1, const Time& t2){
 return t1 += t2;   
}

constexpr Time Time::operator+() const {
     return *this;   
    }


int main(){
 /*constexpr Time t0 = ( +Time(61) );  
 std::cout << t0 << '\n';
    
 constexpr Time t(119);
 Time t2(1);
 t2 += t;
      
 
 Time t3(50);
 Time t4(60);
    
 (t3 += t4) += t4;
    
 std::cout << t3 << ' ' << t4 << '\n';
   
 std::cout << t3+t4 << '\n'; */
    
 Time t1(60);
 std::cout << ++t1 << '\n';
 std::cout << t1++ << '\n';
 std::cout << t1 << '\n';
    
 t1();
 std::cout << t1 << '\n';
 t1(1,2,3);
 std::cout << t1 << '\n';
 t1.operator()();
 std::cout << t1 << '\n';
    
 std::cout << t1['h'] << ':' << t1['m'] << ':' << t1['s'] << '\n';  
    
 std::cin >> t1;
    
 std::cout << t1 << '\n';
 
    // require cast if explicit conversion
 // std::string t1_as_string = static_cast<std::string> (t1 );
    
 std::string t1_as_string = t1;
    
 std::cout << t1_as_string ;
    
 return 0;
    
}



