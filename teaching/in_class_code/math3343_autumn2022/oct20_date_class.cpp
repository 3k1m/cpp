#include <iostream>


struct date{
  int day, month, year;
 
  void print() const { // const here = accessor function
      // the day, month, and year variables are always accessible to
      // the function like function parameters are to free functions
      std::cout << day << "/" << month << "/" << year << '\n';
  }
 
  // write a constructor...
  //                            constructor initializer list  body is empty
  date(int _d, int _m, int _y) : day(_d), month(_m), year(_y)    {}
  // constructor nicely handles cases with three argument supplied
 
  /* need to write a default constructor
  ***IF WE WANT USERS TO BE ABLE TO CONSTRUCT THE CLASS WITH NO ARGUMENTS!!!
  */
  date() : day(1), month(1), year(1970) {}
 
};



int main()
{
 
  //int day, month, year;
  //int day2, month2, year2;
 
  date today; // calls default constructor... starts at 1/1/1970
  today.day = 20;
  today.month = 10;
  today.year = 2022;
 
  std::cout << today.day << "/" << today.month << "/" << today.year << '\n';
 
  date tomorrow = today;
  tomorrow.day = 21;
 
  std::cout << tomorrow.day << "/" << tomorrow.month << "/" << tomorrow.year << '\n';
 
  // cumbersome to print as above, so we wrote the print function ...
 
  date saturday = tomorrow;
  saturday.day = 22;
  saturday.print();
 
 
  // want to be able to specify a construction...
  date sunday{23,10,2022};
  sunday.print();


    return 0;
}
