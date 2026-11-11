#include<print>

struct date{
  int day, month, year; 
  
  void print() const {
      std::println("{}/{}/{}", day, month, year);
  }
};

int main(){
    date d;
    std::println("The date is: {}/{}/{}", d.day, d.month, d.year);
    
    // if everything is public, can do this
    date today{.day = 10, .month = 11, .year=2026};
    std::println("today is: {}/{}/{}", today.day, today.month, today.year);
    
    // if everything is public, can do this
    date today2{10, 11, 2026};
    std::println("today is: {}/{}/{}", today2.day, today2.month, today2.year);
    
    // update
    date tomorrow = today;
    ++tomorrow.day;
    std::println("tomorrow is: {}/{}/{}", tomorrow.day, tomorrow.month, tomorrow.year);
    
    tomorrow.print();
    
    
}
