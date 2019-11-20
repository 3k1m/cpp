#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

struct date{
  int day, month, year;

  date(int _day, int _month, int _year) :
    day(_day), month(_month), year(_year) {}
};

// streams cannot be copied
// and << >> etc. change the state of
// the stream so no const 
std::ostream& operator<<(std::ostream& out,
  const date& d){
    out << d.day << '/' << d.month << '/' <<
      d.year;
    return out;
  }

std::istream& operator>>(std::istream& in, 
  date& d){
    in >> d.day >> d.month >> d.year;
    return in;
  }

bool operator<(const date& d1, const date& d2);

/*void foo(int& i, const int& j){
  i = 9;
  std::cout << j << '\n';
} */

int main() {
 /* int x = 42;
  foo(x, x);
  std::cout << x << '\n'; */

  // std::cout is an std::ostream object
  date d(20,11,2019);

  std::cout << d << '\n';
  operator<<(std::cout, d);
  std::cout << '\n';

  std::cin >> d;
  std::cout << d << '\n';
  // std::cin is an std::istream object

  std::vector<date> dates;
  dates.push_back( date(21,11,2019));
  dates.push_back( date(10,11,2019));
  dates.push_back( date(21,11,2020));
  dates.push_back( date(21,11,2000));

  for(const auto& d : dates){
    std::cout << d << '\n';
  }

  // sort is an algorithm that can
  // sort elements in order, if
  // there is an operator<

  std::sort( std::begin(dates), std::end(dates));

  for(const auto& d : dates){
    std::cout << d << '\n';
  }

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
  return false;



} 
