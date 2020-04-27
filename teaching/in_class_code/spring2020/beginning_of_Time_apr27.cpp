#include<iostream>

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
    
    friend std::ostream& operator<<(std::ostream& out, const Time& t){
       out << t.hours << ':' << t.minutes << ':' << t.seconds; 
        return out;
    }
    
    constexpr Time& operator+=(const Time& t) {
     hours += t.hours;
     minutes += t.minutes;
     seconds += t.seconds;
     format();
     return *this;
    }
};

constexpr Time operator+(Time t1, const Time& t2){
 return t1 += t2;   
}


int main(){
 constexpr Time t(119);
 Time t2(1);
 t2 += t;
 
 Time t3(50);
 Time t4(60);
   
 std::cout << t3+t4 << '\n';
    
 return 0;
    
}


