#include <iostream>
#include <string>

struct Foo{
  // member variables
  int i;
  std::string s1, s2;
  
  // default constructor
  // want i to be 67
  // s1 to be "abc"
  // s2 to be "def"
  Foo() { // constructor body is stuff in {}
    
    // before we get to the body, ALL member variables
    // are initialized
    
    // if values are given in the constructor initializer
    // list, the values are what the programmer wants...
    
    // if no values are given, the compiler default constructs
    // every member variable
    // primitive types int/bool/etc. -> some random bit pattern
    // classes (e.g. string, vector) -> default constructed
  
    std::cout << i << '\n';
    std::cout << s1 << '\n';
    std::cout << s2 << '\n';
    std::cout << "done\n";
  }    
};

// don't do it this way!
struct Bad{
  // member variables
  int i;
  std::string s1, s2;
  
  // default constructor
  // want i to be 67
  // s1 to be "aaa"
  // s2 to be "def"
  Bad() { 
     // inefficient b/c
     // i, s1, s2 were ALREADY initialized
     // now we are just overwriting them...
      
    i = 67;
    s1 = "aaa";
    s2 = "def";
  } 
};

struct Good{
  int i;
  std::string s1, s2;
  
  // more efficient: initialize only once
  Good() : i(67), s1(3, 'a') , s2("def") {}
  
  // s1(3, 'a'): recall a std::string has a constructor that
  // accepts 2 arguments: size and char to repeat... we can call
  // it that way    
};


struct Ord{
  int i, j;
  
  // i will always be initialized before j
  // order of initialization is the order the 
  // member variables are declared in the class interface
  
  Ord(int a) : j(a), i(j) {}    
};

struct date{
  int day, month, year;    
  
  // NO default constructor for date b/c
  // we wrote A constructor that is not a default constructor
  
  date(int _day, int _month, int _year) :
    day(_day), month(_month), year(_year) {}   
};

struct has_date{
    // ctor initializer list is ALWAYS required (even to compile)
    // for members w/o default constructors or
    // members that are const or refence
    
  date d; // has a member of type date
  
  //has_date() /* constructor calls date::date() */ {
//    d.day = 15;
 //   d.month = 11;
  //  d.year = 2019;
 // }
  
  has_date() : d(15,11,2019) { }
};

int main()
{
    // this won't work b/c no def constructor for date
    // date d;
    
    has_date h;
    
  Foo f; // will call default constructor
  
  Bad b;
  std::cout << b.i << ' ' << b.s1 << ' ' << b.s2 << '\n';
  
  Good g;
  std::cout << g.i << ' ' << g.s1 << ' ' << g.s2 << '\n';
  
  Ord o(5);
  std::cout << o.i << ' ' << o.j << '\n';
  
  return 0;
}
