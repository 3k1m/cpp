// Example program
#include <iostream>
#include <string>

int main()
{
  // find the max of 3 values the user enters...
  std::cout << "enter 3 values: ";
  int a = 0, b = 0, c = 0;
  std::cin >> a >> b >> c;
  
  // make code cleaner...
  // need to define this function!!!
  int max = get_max(a,b,c);
  
  
  /*
  int max = 0;
    
  
  if(a > b){
      if(a > c){
         max = a;   
      }
      else{
       max = c;   
      }
  }
  else{
   if(b > c) {
    max = b;   
   }
   else{
    max =c;   
   }
  }
  */
  std::cout << max << '\n';
  
  
}
