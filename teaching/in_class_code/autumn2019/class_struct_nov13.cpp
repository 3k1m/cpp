// Example program
#include <iostream>
#include <string>

// classes store variables and functions

class C{
    // by default, everything in a class is private
    int z;    
public: // can be accessed outside of C
  // all C's have a function foo
  void foo() const { std::cout << "foo\n"; }
  int x; // all C's have an int member called x
private:
  void bar() const { std::cout << "bar\n"; }
  int y;  
};

struct S{
    // by default, everything in a struct is public
    int z;    
public: // can be accessed outside of S
  // all C's have a function foo
  void foo() const { std::cout << "foo\n"; }
  int x; // all C's have an int member called x
private: // no access
  void bar() const { std::cout << "bar\n"; }
  int y;  
};

struct date{
    // has 3 ints for day and month and year
  int day, month, year;  
};

int main()
{
    // a is a variable of type C
  C a;
  a.foo();
  a.x = 1119;
  std::cout << a.x << '\n';
  
  // because they are private, we cannot access
  // the function or variable of a with . like we could above
  // ERROR
  //a.bar();
  //a.y = 1119;
  //std::cout << a.y << '\n';
  // a.z = 4;
  
  S b;
  b.z = 4;
  b.foo();
  
  // initialization is "dumb"
  // day, month, year need to be set manually in this case
  
  date today;
  
  // before initializing the members
  std::cout << "Today is: " << today.day << "/" <<
    today.month << "/" << today.year << '\n';
  
  // initialize the member variables
  today.day = 13;
  today.month = 11;
  today.year = 2019;
  
  // makes sense
  std::cout << "Today is: " << today.day << "/" <<
    today.month << "/" << today.year << '\n';
    
  // proper initialization of classes/structs
  // usually requires CONSTRUCTORS
  

  return 0;
}
