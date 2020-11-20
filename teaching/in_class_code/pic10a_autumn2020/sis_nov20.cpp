#include<iostream>
#include<cmath>

class SIS{
private:
  double pr, pc, n; // disease stats 
  double I, S; // infected and susceptibles 
  double N; // total population
  double t; // current time in days 
  
  double get_S_change() const {
      // some recover, some get ill
      return pr*I - (1 - std::pow(1-pc, n*I/N))*S;
  }
  
  void advance_day(){
      double dS = get_S_change(); // how much S will change by 
      S += dS;
      I -= dS; // changes in opposite direction 
      ++t; 
  }
  
public:
  /**
   * construct for SIS class
   * @param _pr probability of recovery in day
   * @param _pc probability contracting from ill person
   * @param _n avg number of daily contacts
   * @param I0 initial number ill
   * @param S0 initial number susceptible
   */
  SIS(double _pr, double _pc, double _n, double I0, double S0) :
    pr(_pr), pc(_pc), n(_n), I(I0), S(S0), N(I+S), t(0) {}
    
  double get_t() const { return t; }
  double get_N() const { return N; }
  double get_S() const { return S; }
  double get_I() const { return I; }
  
  
  
  void advance_days(int step = 1) {
      for(int i=1; i <= step; ++i){
          advance_day();
      }
  }
  
  
    
};


int main(){
 SIS pop(0.2, 0.01, 20, 10, 990);
 
 std::cout << pop.get_N() << '\n';
 std::cout << pop.get_t() << '\n';
 
 const double end_day = 100;
 
 //while(pop.get_t() < end_day) {
 //    pop.advance_day();
 //}
 
 pop.advance_days();
 
 std::cout << "on day " << pop.get_t() << ":\n";
 std::cout << "I: " << pop.get_I() << '\n';
 std::cout << "S: " << pop.get_S() << '\n';
    
    
 return 0;   
}
