#include <iostream>
#include <string>

int main()
{
  const double tax_rate = 0.1;
  
  std::cout << "Enter cost $";
  
  double cost;
  // will be error
  //std::cin >> tax_rate; 
  std::cin >> cost;
  
  double total = cost * (1 + tax_rate);
  
  std::cout << "Total cost is: $" << total << '\n';
  
  return 0;  
}
