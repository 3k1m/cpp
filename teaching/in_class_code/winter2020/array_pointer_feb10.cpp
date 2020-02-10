#include <iostream>
#include <string>

int main()
{
  int i_array[5] = {2, 4, 6, 8, 10};
  
  // how many bytes an int gets
  std::cout << sizeof(int) << '\n';
  
  // see how these differ by 4 ==> 4 bytes
  std::cout << i_array << '\n';
  std::cout << i_array + 1 << '\n';
  
  // these two should be the same
  std::cout << i_array + 2 << '\n';
  std::cout << &(i_array[2]) << '\n';
  
  std::cout << i_array[2] << '\n';
  std::cout << *(i_array + 2) << '\n';
  
  // this is pointing to the last value
  int *i = i_array + 4;
  *i = 153;
  
  --i; // i now points to 2nd last element
  *i = -8;
  
  for(size_t i= 0; i < 5; ++i){
   std::cout<< i_array[i] << ' ';   
  }
  
    
  return 0;  
}
