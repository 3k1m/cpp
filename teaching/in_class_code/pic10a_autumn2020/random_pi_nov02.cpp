#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

int main()
{
    std::srand( std::time(nullptr) ); // seed the random numbers
    
    const int num_sims = 100000; // how many sims to return
    const double circ_rad = 1.;
    
    int in_circ_count = 0; // how many times in circle

    for(int i=0; i < num_sims; ++i){ // run num_sim trials
    
        
        // x and y are uniformly distributed over [0,1]
        double x = static_cast<double>( std::rand() ) / RAND_MAX;
        double y = static_cast<double>( std::rand() ) / RAND_MAX;
        
        if(x*x + y*y <= circ_rad*circ_rad){ // within the circle 
            ++in_circ_count;
        }
    }
    
    const double quarter_conversion = 4.;
    
    double pi_estimate = quarter_conversion*in_circ_count/num_sims;
    
    std::cout << "pi = " << std::setprecision(10) << std::fixed << pi_estimate;
    

    return 0;
}
