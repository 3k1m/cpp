// Example program
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
  srand(time(nullptr));      
    
  const int Num_Iterations = 100000;
  
  const double radius = 1.;
  
  int in_circle = 0; // how many in the circle
  
  // do it many times
  for(int i = 0; i < Num_Iterations; ++i){ 
      
     // pick two random x and y in [0,1] 
     double x = static_cast<double>( rand() ) / RAND_MAX;
     double y = static_cast<double>( rand() ) / RAND_MAX;
     
     // if point is in circle, increase hit count
     if( x*x + y*y <= radius*radius){
       ++in_circle;   
     }     
  }
  
  double pi_by_4 = static_cast<double>(in_circle)/
    Num_Iterations;
    
  cout << "pi = " << pi_by_4 * 4 << '\n';    
    
  
  
  return 0;
}
