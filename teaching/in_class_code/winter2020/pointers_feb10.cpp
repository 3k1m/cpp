#include <iostream>
#include <string>

int main()
{
  int x = 7, y = 111;
  
  // reference definition
  // xr doesn't exist until here
  // when we see int &xr we know it is
  // a refernce to an int
  int &xr = x;
  
  // pointer definition
  // since x already exists,
  // &x means "address of x"
  int *xp = &x;
  
  int *yp; // doesn't point anywhere that we know
  
  std::cout << x << " " << y << '\n';
  std::cout << xp << '\n';
  
  // since xp already exists, *xp means
  // "dereference" xp and access the value it
  // points to
  std::cout << *xp << '\n';
  
  // change where xp points!
  xp = &y;
  // make yp now point to x
  yp = &x;
  
  std::cout << *xp << " " << *yp << '\n';
  
  // xp is pointing to y
  // change y
  ++(*xp);
  
  std::cout << x << " " << y << '\n';
  
  std::string name("Joe Bruin");
  
  std::string *name_pointer = &name;
  
  std::cout << "char count " << (*name_pointer).size()
    << '\n';
    
  std::cout << "char count " << name_pointer->size()
    << '\n';
    
  std::cout << "substr " << name_pointer->substr(1,3)
    << '\n';
  
  // safe way to have a pointer pointing nowhere
  name_pointer = nullptr;
  
  // p is a pointer to a const int
  const int *p = &x;
  // ++(*p); // ERROR
  
  return 0;
}
