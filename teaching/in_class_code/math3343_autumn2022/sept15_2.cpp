#include<iostream>

int main(){

  int N1, N2;
  std::cout << "Enter two integers to average: ";

  std::cin >> N1 >> N2;

  //std::cout << "The average is: " << static_cast<double>(N1+N2)/2. << '\n';
  std::cout << "The average is: " << static_cast<double>(N1+N2)/2 << '\n';
}
