// Example program
#include <iostream>
#include <string>

class A{
private:
 int arr[5];   
public:
  // but return by value here gives error on the a.get(2) = 7 line
 int& get(size_t i) { return arr[i]; } 
};

int main()
{
  A a;
  a.get(2) = 7;
  std::cout << a.get(2) << '\n';
  return 0;
}
