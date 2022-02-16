// part 1 of our SIS class

#include <iostream>
#include <cmath>


/**
 * @class SIS is a class to model an S-I-S epidemic spread of disease 
 * 
 */
class SIS{
private:
  // total population, number ill, number susceptible 
  double N, I, S;
  // number of contacts, transmission probability, and recovery prob 
  double n, pc, pr;
  // the time 
  int day; 
  
  
  double get_dI() const { // only returns a value, does not change members
      
      const double nc = n*I/N; // number of sick contacts seen
      
      // probability of each S getting sick 
      const double p_sick = std::pow(1-pc, nc);
      
      const double new_sick = S*p_sick;
      const double num_recovered = I*pr;
      
      return new_sick - num_recovered;
      
      
  }
  
  
  void advance_one_day() {
      
      const double Delta_I = get_dI();
      const double Delta_S = get_dS();
      
      I += Delta_I;
      S += Delta_S;
      
  }
  


public:
  /**
   * constructor for SIS class
   * @param _N the total population 
   * @param _I the initial number infected
   * @param _n the avg number of contacts per day 
   * @param _pc the contraction probability per interaction
   * @param _pr the probability of recovery per day  
   */
  SIS(double _N, double _I, double _n, double _pc, double _pr) :
    N(_N), I(_I), S(N-I), n(_n), pc(_pc), pr(_pr), day(0) {}
    
  
  // some accessor functions
  // within member functions, can access values of 
  // member variables just by their name 
  double get_N() const { return N; }
  
  double get_S() const;
  
  double get_I() const;
  
  
  void advance_days(int num){
      for(int i=0; i < num; ++i){
         advance_one_day();  // if this is a member function, can 
         // call its name just like this 
      }
  }


    
};


int main()
{
   
  const double N = 10000;
  const double I = 53;
  const double n = 12.5;
  const double pc = 0.02;
  const double pr = 0.2;


  SIS population(N, I, n, pc, pr);
  
  std::cout << population.get_S() << ' ' << population.get_I() << ' ' <<
    population.get_N() << '\n';

    return 0;
}



// imagine a separate cpp file 

  double SIS::get_S() const{ return S; }
  
  double SIS::get_I() const { return I; }
