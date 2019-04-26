#include<iostream>

int foo(int end){
  int sum = 2;
  
  for(int i=0; end; ++i){
    ++sum;
  }
  
  return sum;
}

int main(){
  std::cout << "start" << std::endl; // endl to make sure this gets printed
  
  std::cout << foo(5); // finding a bug like this took me more than an hour :(
  
  std::cout << "end!";
  
  return 0;

}
