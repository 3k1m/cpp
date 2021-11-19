#include <iostream>
#include <thread>
#include <chrono>


int main()
{
  
  /*const int x = 100;
  while(x==100){
      std::cout << "x is 100\n";
      std::this_thread::sleep_for( std::chrono::seconds(1));
      ++const_cast<int&>(x);
      const int* y = &x;
      std::cout << "*y is: " << *y << '\n';
  }
  std::cout << x << '\n';*/
  
  const volatile int x = 100;
  while(x==100){
      std::cout << "x is 100\n";
      std::this_thread::sleep_for( std::chrono::seconds(1));
      ++const_cast<int&>(x);
      const volatile int* y = &x;
      std::cout << "*y is: " << *y << '\n';
  }
  std::cout << x << '\n';


    return 0;
}
