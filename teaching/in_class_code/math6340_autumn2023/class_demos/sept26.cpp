#include <iostream>
#include <string>

//struct Time{
// // secretly creating a Time::Time() constructor 
//    int hour, minute;
//};

/*struct Time{
  int hour, minute;
  Time(int _hour, int _minute) : // constructor initializer list 
    hour(_hour), minute(_minute) {}
};*/

/*
class Person{
    int birth_year;
    std::string name;
public:
    Person(int year, const std::string& _name) :
        birth_year(year), name(_name) {}
    
    int age(int year_now) const {
        return year_now - birth_year;
    }
    
    void change_name(const std::string& new_name) {
        name = new_name;
    }
    
    const std::string& get_name() const { // const here ==> name ~ const std::string
            return name;
    }
    
    // only declare Person::print()
    void print() const;
}; */

struct Foo{
  int i = 42;  
};

struct S{
  std::string s;
  Foo f;
  
  S() /* no ctor initializer list */ {
      std::cout << s.size() << ' ' << f.i << '\n';
      s = "hello";
      f.i = 0;
      std::cout << s.size() << ' ' << f.i << '\n';
  }
 
};

int main()
{
    S s;
    
    
    //Time t;
    //t.hour = 20;
    //t.minute = 36;
    //std::cout << t.hour << ":" << t.minute << '\n';
    
    // //Time t; // ERROR: no default constructor 
    // Time t{20, 42};
    // std::cout << t.hour << ":" << t.minute << '\n';
    
    /*Person paul{1952, "Paul"};
    std::cout << "Age ~= " << paul.age(2023) << '\n';
    
    Person joseph{1970, "Joseph"};
    joseph.change_name("Joe");
    std::cout << joseph.get_name() << '\n';
    
    joseph.print();
    // joseph.birth_year = 2000; */
    
    

    return 0;
}

     // need the Person:: scope for this function to make sense 
/*void Person::print() const {
  std::cout << name << " was born in " << birth_year << '\n';   
}*/

