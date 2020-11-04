#include <iostream>
#include <string>

int main()
{
  int x = 10;
  // & before variable name -- address
  std::cout << &x << '\n';
  
  int &xr = x; // xr is reference to x 
  
  int *xp = &x; // xp is a pointer, pointing to x
  
  std::cout << x << '\n';
  std::cout << xr << '\n';
  std::cout << *xp << '\n'; // dereference a pointer with * -- gives the pointed-to value
  
  (*xp)*=7;
  
  std::cout << x << '\n';
  std::cout << xp << '\n';
  
  //int *p; // p could point anywhere!!! -- dangerous uninitialized pointers!!!
  int *p = nullptr; // better initialization if don't know where to point 
  
  int y = 401;
  xp = &y; // xp points to y now!
  std::cout << *xp << '\n';
  
  const int *yp = &y; // yp is a pointer to const int, initialized from &y 
  std::cout << *yp << '\n'; // okay...
  //++(*yp); // bad --- changing what yp points to 
  
  // in parallel with references...
  const double d = 0.0;
  // double& dr = d; // bad 
  const double& cdr = d; // okay ...
  
  //double *dp = &d; // error ...
  const double *cdp = &d; // okay 
  
  std::string s("hello world");
  std::string* sp = &s;
  (*sp).push_back('!');
  sp->push_back('!'); // pointer-> same as (*pointer).
  std::cout << s << '\n';
  
  int arr[] = {1,2,3,4};
  
  std::cout << arr << ' ' << *arr << ' ' << *(arr+1) << ' ' << arr[1] << '\n';
  
  return 0;
}
