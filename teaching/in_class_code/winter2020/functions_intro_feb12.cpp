// Example program
#include <iostream>

// this declares (signature) and defines (body)
// the function round_to_int

/**
 * will round a double to an int
 * @param val the value to round
 * @return the value rounded to the nearest int * 
 */
int round_to_int(double val){  
  if(val > 0){
     return static_cast<int>(val + 0.5); 
  }
  else{
     return static_cast<int>(val - 0.5);
  }    
}


double return_6(){
    
  // once a return statement is reached, the function is done!
  return 6; // "hello";
    
  // won't be read
  std::cout << "Have a nice day!\n";
  
  return 7;
  
  return 8;
  
  return 9;    
}

const char* return_hello(){
    return "hello";
}


int main()
{
  std::cout << return_6() << '\n';   
    
  double x = 5.9;  
  int xrounded = round_to_int(x);
  
  // simulates
  // int xrounded2 = round_to_int(x);
  int xrounded2;  
  // expanded out...
  // want to make xrounded2...
  { // begin function scope
   double val = x;   
   int return_val; // will be returned
   
   if(val > 0){
     return_val = static_cast<int>(val + 0.5);
     xrounded2 = return_val;
   }
   else{
     return_val = static_cast<int>(val - 0.5);
     xrounded2 = return_val;
   }  
  } // end function scope
  
    
  std::cout << xrounded << '\n';
  std::cout << xrounded2 << '\n';
  
  // this was local to the function
  // not alive anymore - its scope is over
  //std::cout << return_val << '\n';
  

  
  return 0;  
}
