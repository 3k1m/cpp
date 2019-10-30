// Example program
#include <iostream>
#include <string>

int main()
{
    int x = 7, y = 10;
    std::cout << "address x: " << &x << '\n';
    std::cout << "address y: " << &y << '\n';
    
    // & for reference
    int &xr = x;
    int &yr = y; // cannot leave unitialized
    
    yr = xr;
    yr = 4;
    
    // references are stuck with regards to
    // the memory they reference forever
    // assignment changes the value in the
    // location they reference
    // but not the location where they reference
    std::cout << "xr and yr\n" << xr 
        << '\n' << yr << '\n';
    
    //  * for pointer!
    int *xp = &x; // xp points to x
    int *yp; // not initialized!!! but can point to int
    
    // dereferencing operator to get value from ptr
    //           * before variable name
    std::cout << *xp << '\n';
    //std::cout << *yp << '\n'; // VERY BAD: yp not set
    
    // change where points point...
    yp = xp; // yp should point where xp points
    std::cout << *yp << '\n';
    
    // modify x!!!
    ++(*yp);
    
    std::cout << "now x is: " << x << '\n';
    
    // make yp point to y...
    yp = &y;
    
    std::cout << *yp << '\n';
    
    // the pointers have addresses too
    std::cout << &yp << '\n';
    
    std::string message = "hello";
    std::string* messagep = &message;
    
    std::cout << (*messagep).substr(1) << '\n';
    // shorthand for above
    std::cout << messagep->substr(1) << '\n';
    
    // (*foo). ~ foo->
    
    
    // reference ~ automatically dereferenced pointer
    
    
    
    
    
    
    
    /*
    // "loop" with goto
    
    int i = 1;
    
    print_i: // this is called print_i
      std::cout << i << '\n';
    
    if(i < 10) { // not yet 10
        ++i;
        goto print_i; // go back to the line print_i
    }
    
    
  int x = 1;
  
  switch(x) { // x has to be an INTEGER type
      case 1: std::cout << "one\n"; //break;
      case 2: std::cout << "two\n"; //break;
      case 3: std::cout << "three\n"; //break;
      default: std::cout << "else\n";      
  }
  */
  return 0;
  
}
