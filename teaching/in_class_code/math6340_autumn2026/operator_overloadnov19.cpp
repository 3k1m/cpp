#include<print>
#include<vector>
#include<iostream>
#include<algorithm>

class date{
private:
  int day, month, year;
  
public:
  date(int day_, int month_, int year_) : day(day_), month(month_), year(year_) {}
  
  date() : day(0), month(0), year(0) {} // this is a default c'tor 
  
  int get_day() const { return day; }
  int get_month() const { return month;} 
  int get_year() const{ return year; }


  void print() const {
      std::println("{}/{}/{}", day, month, year);
  }
  
  void advance() { // ignores leap years
      const int jan = 1, feb = 2, mar = 3, apr = 4, may = 5, jun = 6, jul = 7, aug = 8, sep = 9, oct = 10, nov = 11, dec = 12;
      
      if(month == sep or month == apr or month == jun or month == nov){ // has 30 days 
          if (day == 30){
              day = 1;
              ++month;
          }
          else{
            ++day;
          }
      }
      else if(month == jan or month == mar or month == may or month == jul or month == aug or month == oct){
          if(day == 31){
              day = 1;
              ++month;
          }
          else{
            ++day;
          }
      }
      else if(month==dec){
          if(day==31){
              day = 1;
              month = 1;
              ++year;
          }
          else{
              ++day;
          }
      }
      else if(month==feb){
          if(day==28){
              day = 1;
              ++month;
          }
          else{
            ++day;
          }
      }
      
  }
};

std::ostream& operator<<(std::ostream& out, const date& d){
       return out << d.get_day() << '/' << d.get_month() << '/' << d.get_year();
   }
   
bool operator<(const date& d1, const date& d2){
    if(d1.get_year()<d2.get_year()){
        return true;
    }
    if(d1.get_year()>d2.get_year()){
        return false;
    }
    if(d1.get_month()<d2.get_month()){
        return true;
    }
    if(d1.get_month()>d2.get_month()){
        return false;
    }
    return d1.get_day() < d2.get_day();
}

bool operator==(const date& d1, const date& d2){
    return d1.get_day() == d2.get_day() and d1.get_month() == d2.get_month() and 
      d1.get_year() == d2.get_year();
}

std::istream& operator>>(std::istream& in, date& d){
    int day, month, year;
    in >> day >> month >> year;
    d = {day,month,year};
    return in;
}

int main(){
    date today{19,11,2026};
    std::cout << today << '\n';
    operator<<(operator<<(std::cout, today),'\n');
    
    std::vector<date> dates{{19,11,2026},{18,11,2026},{20,11,2026},{19,11,2025}};
    for(const auto& d: dates){
        std::cout << d << '\n';
    }
    std::sort(dates.begin(),dates.end());
    std::cout << "sorted dates\n";
    for(const auto& d: dates){
        std::cout << d << ' ';
    }
    std::cout << '\n';
    
    date d{19,11,2026};
    // check if d is in the vector 
    if(auto i = std::find(dates.begin(), dates.end(), d); i != dates.end()){
        std::cout << "found " << d << " among the dates\n";
    }
    else{
        std::cout << " did not find it\n";
    }
    
    
    date d2{30,11,2026};
    // check if d is in the vector 
    if(auto i = std::find(dates.begin(), dates.end(), d2); i != dates.end()){
        std::cout << "found " << d2 << " among the dates\n";
    }
    else{
        std::cout << " did not find it\n";
    }
    
    std::cout << "Set a date";
    date d3;
    std::cin >> d3;
    std::cout << "you entered " << d3 << '\n';
    
}
