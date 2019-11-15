#include <iostream>
#include <string>

struct date{
  int day, month, year;    
  
  /**
   * Constructor for date objects
   * @param _day the day
   * @param _month the month
   * @param _year the year
   */
  date(int _day, int _month, int _year) :
    day(_day), month(_month), year(_year) {}
  // this syntax is called a CONSTRUCTOR INITIALIZER LIST    
};

int main()
{
    // thing of the past
  //date d;
  //d.day = 15; d.month = 11; d.year = 2019;
  
  date d(15, 11, 2019);
  
  std::cout << d.day << "/" << d.month << "/" << d.year << '\n';
  
  return 0;
}
