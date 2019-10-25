#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
  // make things more random, give a seed to
  // the rand function
  srand(time(nullptr));
  
  // rand returns an int from 0 to RAND_MAX
  cout << "RAND_MAX: " << RAND_MAX << '\n';
  cout << rand() << '\n';
  
  // let's get a random int from 0 to N
  const int N = 6;
  cout << rand() % N << '\n'; // 0 to 5
  
  // now simulate a die: 1-6, not 0 to 5
  int die_roll = rand() % N + 1;
  cout << "die roll: " << die_roll << '\n';
  
  // now get integers from a to b inclusive
  const int a = 4, b = 11;
  const int rng = b - a + 1;
  int result = rand() % rng + a;
  cout << "from " << a << " to " << b << ": " << 
    result << '\n';
  
  // in interval [0, 1)
  double zero_to_one = rand() / ( RAND_MAX + 1.0);
  
  // double in interval [60,100) inclusive?
  const double low = 60, hi = 100;
  double val = low + (hi-low)*zero_to_one;
  cout << val << '\n';
  
  const int num_trials = 100000;
  
  int hits = 0; // number of times the dart is in 
  // circle
  
  // throw many "darts"
  for(int trial = 0; trial < num_trials; ++trial){
    
    // both in [0,1)
    double x = rand() / ( RAND_MAX + 1.0);
    double y = rand() / ( RAND_MAX + 1.0);
    
    if( x*x + y*y <= 1 ) { // in circle?
     ++hits;   
    }      
  }
  
  double pi = 4*static_cast<double>(hits)/num_trials;
  
  cout << "pi ~= " << pi << '\n';
   
  
  return 0;
}
