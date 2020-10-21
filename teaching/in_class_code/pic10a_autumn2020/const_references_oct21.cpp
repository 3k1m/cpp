// Example program
#include <iostream>
#include <string>

int main()
{
    std::string h = "hello";
    std::string &hr = h;
    
    hr[0] = 'H';
    h.push_back('!');
    
    std::cout << h << '\n' << hr << '\n';
    
    // Lvalues vs Rvalues
    int x = 40; // x is an Lvalue
    int& y = x; // y references x
    
    // Lvaues have places in memory
    // strings literals are Lvalues
    
    int &z = x + 10; // 10 is an Rvalue, x+10 is an Rvalue
    // 'a' Rvalue
    // h.size() Rvalue
    
    
    
/*  const double tax_rate = 0.1;
  double item_cost = 1.5;
  
  // ... oops
  //tax_rate = 3;
  
  double amount_due = item_cost * (1+tax_rate);
  
  std::cout << amount_due << '\n'; */
  
  return 0;
}
