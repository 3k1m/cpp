#include <iostream>
#include <cmath>

// could be in H file...

class SIS{
  double N; // total pop
  double I, S; // number inf/susc  
  double nc; // avg number of contacts/day
  double pr; // probability of recovery/day
  double pc; // probablity of contracting illness
 
  int day; // day = time
 
  // probability any given person is sick, not counting
  // one party in the interaction
  double pr_interact_with_sick() const {
      return I/(N-1); // # infected / (total pop - 1)
  }
 
  // how many sick people on average a person interacts with per day
  double sick_interactions() const {
      return nc*pr_interact_with_sick();
  }
 
  double pr_become_sick() const {
      // (not get sick from sick person 1) * (not get sick from sick person 2)
      double pr_not = std::pow(1-pc, sick_interactions());
      return 1-pr_not;
  }
 
  double get_dS() const {
      double I_to_S = pr*I;
      double S_to_I = pr_become_sick()*S;
      return I_to_S - S_to_I;
  }
 
  double get_dI() const {
      return -get_dS();
  }
 
 

public:
  /**
   * constructor for SIS class
   * @param _N the total population
   * @param _I the initial number infected
   * @param _nc the daily contacts had
   * @param _pr the recovery probability
   * @param _pc the contraction probability
   */
  SIS(double _N, double _I, double _nc, double _pr, double _pc);

  /**
   *  adanved the simulations some number of days
   * @param num the number of days to go forward by    *
   */
  void advance_days(int num);
 
  void print() const {
      std::cout << "On day " << day << " there are " << S << " susceptible  and " <<
         I << " infected.\n";
  }
   
};

int main()
{
    SIS cold{100000, 20, 30, 0.2, 0.02};
    cold.print();
   
    cold.advance_days(200);
    cold.print();

    return 0;
}

// in a cpp file, for example

// should initialize member variables in list in the same order
// as they are listed within the class interface
SIS::SIS(double _N, double _I, double _nc, double _pr, double _pc) :
  N(_N), I(_I), S(N-I), nc(_nc), pr(_pr), pc(_pc), day(0) {}
 
 
void SIS::advance_days(int num){
    for(int i=0; i < num; ++i){
        const double dS = get_dS();
        const double dI = get_dI();
        S += dS; // changes member variables
        I += dI;
        ++day;
    }
} 
