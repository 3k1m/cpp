#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
    // we can "seed" the random number sequence so it is more random 
    std::srand(std::time(nullptr));
    
    std::cout << "largest possible random int: " << RAND_MAX << '\n';
    
    const int num_rands = 10;
    
    for(int i=1; i <= num_rands; ++i){
        // result will be from 0 to RAND_MAX inclusive
       std::cout << "random number " << i << " is " << std::rand() << '\n';    
    }
    
    // simulate rolling a 20-sided die...
    const int num_sides = 20;
    const int low = 1; // lowest number we allow 
    std::cout << "20 sided die:\n";
    std::cout << std::rand() % num_sides << '\n';
    
    const int rolled = std::rand() % num_sides + low;
    std::cout << "rolled a " << rolled << '\n';
    
    // want from 20-30 inclusive
    const int low2 = 20;
    const int rolled2 = std::rand() % num_sides + low2;
    std::cout << rolled2 << '\n';
    
    std::cout << "floating point stuff..\n";
    // how to generate random floating points on [a,b)?
    
    
    // let's generate on [0,1)
    // can be 0, can't reach 1 
    //double val = static_cast<double>( std::rand() ) / RAND_MAX;
    
    double val = std::rand() / (RAND_MAX + 1.);
    
    // would be more ideal to have RAND_MAX+1 in denominator to avoid ever being 1 
    /*if(val==1){ // value is 1 so we disallow that...
        val -= 1./RAND_MAX;
    }
    std::cout << val << '\n'; // will be on [0,1)*/
    
    const double a = 4.36, b = 9.11;
    const double val_a_b = std::rand() / (RAND_MAX + 1.) * (b-a) + a;
    std::cout << val_a_b << '\n';
    
    // simulate the value of pi 
    const double xmin = 0, ymin = 0, xmax = 1, ymax = 1;
    const double rad = 1.;
    
    const int num_trials = 10000;
    int num_hits = 0; // how many times the random point is in the qtr circle 
    
    for(int i=0; i < num_trials; ++i){
        const double x = std::rand() / (RAND_MAX + 1.) * (xmax-xmin) + xmin;
        const double y = std::rand() / (RAND_MAX + 1.) * (ymax-ymin) + ymin;
        
        // to be within the qtr circle, x^2 + y^2 <= rad^2 
        if(x*x + y*y <= rad*rad){
            ++num_hits;
        }
    }
    
    const double pi_by_4 = static_cast<double>(num_hits)/num_trials;
    const double pi_approx = 4*pi_by_4;
    
    std::cout << "pi is approximately: " << pi_approx << '\n';
    
    

    return 0;
}
