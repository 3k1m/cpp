#include<iostream>

#include "SIS.h"

int main(){
    const double pr = 0.2; // recovery prob/day 
    const double pc = 0.02;  // prob of getting sick from ill contact 
    const double n = 20; // avg number of "close enough" contacts per day 
    
    const double N = 40000; // total population
    const double I0 = 4; // initial number of sick people 
    const double S0 = N-I0;
    
    SIS pop{pr,pc,n,N,S0};
    
	/* REMARK: after deciding at the end to make a history member variable,
	we could consider making this a size_t variable, and updating
	the member function accordingly. */
    const int Tend = 90; 
    
    pop.advance(Tend);
    
    std::cout << "After " << pop.get_t() << " days:\n";
    std::cout << "S: " << pop.get_S() << '\n';
    std::cout << "I: " << pop.get_I() << '\n';
    
    pop.print_history();
}
