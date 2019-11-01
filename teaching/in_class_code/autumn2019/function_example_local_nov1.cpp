// Example program
#include <iostream>
#include <string>

/**
Function returns the max value of 3 int types
@param a the first int
@param b the second int
@param c the third int
@return the max of a, b, and c
*/
int get_max(int a, int b, int c){
    
    int max = 0;    
  
  if(a > b){ //
      if(a > c){ // 
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
  
  return max;
    
}



int main()
{
  // find the max of 3 values the user enters...
  std::cout << "enter 3 values: ";
  int x = 0, y = 0, z = 0;
  std::cin >> x >> y >> z;
  
  // make code cleaner...
  // need to define this function!!!
  int max = get_max(x,y,z);
  
  // alternative without functions
  
  int max2; // not initialized
  
  { // start a local scope
    int a = x; // create local vars a, b, and c
    int b = y; // to store x, y, and z
    int c = z; 
    
    int ret = 0; // return value
    
    if(a > b){
      if(a > c){
         ret = a;   
      }
      else{
       ret = c;   
      }
  }
  else{
   if(b > c) {
    ret = b;   
   }
   else{
    ret =c;   
   }
  }  
      // now ret store the max of a, b, c
      
    max2 = ret;
  } // closing of the scope
  // a, b, c, and ret no longer exist!
  
  std::cout << max << '\n';
  std::cout << max2 << '\n';
  
  return 0;
}
