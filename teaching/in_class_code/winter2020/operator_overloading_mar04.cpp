#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct date{
  int day, month, year;
  date(int _day, int _month, int _year) :
    day(_day), month(_month), year(_year) {}
};

// cout is an ostream object
// streams must always be passed by ref
// and returned by reference
std::ostream& operator<<(std::ostream& out, 
  const date& d){
    out << d.day << "/" << d.month << 
      "/" << d.year;
    return out;
}

bool operator<(const date& d1, const date& d2);

// date is a ref bc we want to change it!
std::istream& operator>>(std::istream& in, date& d){
  in >> d.day >> d.month >> d.year;
  return in;
}

std::ostream& operator<<(std::ostream& out,
  const std::vector<date>& dates){
   out << "[";
   for(const auto& d : dates){
     out << d << " ";  
   }
   out << "]";
   return out;      
  }

int main()
{
    //int i = 5;
    //std::cout << (i << 4) << '\n';    
    
  date d(4,3,2020);
  date d2(11,3,2020);
  date d3(26,2,2020);
  
  std::vector<date> vdate {d, d2, d3};
  std::sort( vdate.begin(), vdate.end() );
  std::cout << vdate << '\n';
  
  
  std::cout << d << '\n'; 
  
  std::cout << std::boolalpha; // true -> "true"
  // false -> "false"
  
  std::cout << "d < d2: " << (d < d2) << '\n';
  
  // allow ourselves to "cin" a date
  std::cin >> d;
  std::cout << "d is now: " << d << '\n';
  
  return 0;
}

bool operator<(const date& d1, const date& d2){
  if(d1.year < d2.year){
      return true;
  }
  else if(d2.year < d1.year){
      return false;   
  }
  else if(d1.month < d2.month){
      return true;
  }
  else if(d2.month < d1.month){
      return false;   
  }
  else if(d1.day < d2.day){
      return true;
  }
  else{
      return false;   
  }    
}
