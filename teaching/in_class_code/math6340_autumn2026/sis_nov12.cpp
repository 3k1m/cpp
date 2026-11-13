#include<print>
#include<cmath>

class SIS{
  double pop;
  int num_contacts;
  double ill, susc;
  double p_recover, p_transmit;
  
  double num_recoveries() const {
      // p_recover = probability of recovering in 1 day 
      // on avg:
      return ill*p_recover;
  }
  
  double num_ill() const {
      const double p_ill = ill/pop;
      const double avg_ill = p_ill*num_contacts;
      
      const double p_not_get_sick = std::pow(1-p_transmit, avg_ill);
      
      return susc*(1-p_not_get_sick);
  }
  
  double susc_change() const {
      return num_recoveries() - num_ill();
  }
  
  void advance();
  
public:
  SIS(double pop_, int num_contacts_, double ill_, double p_recover_, double p_transmit_);
  
  void print_stats() const;
  
  void advance_days(int days=1) {
      for(int i=0; i < days; ++i){
          advance(); // from one day to the next 
      }
  }
};


int main()
{
    const double pop = 1.45e+6;
    const int num_contacts = 50;
    const double ill0 = 20;
    const double p_recover = 0.1;
    const double p_transmit = 0.005;
    
    SIS RGV{pop, num_contacts, ill0, p_recover, p_transmit};
    RGV.print_stats();

    RGV.advance_days(100);
    RGV.print_stats();
}



void SIS::print_stats() const {
      std::println("ill = {}, susceptible = {}, percent ill = {}", ill, susc, ill/pop*100);
  }
  
  SIS::SIS(double pop_, int num_contacts_, double ill_, double p_recover_, double p_transmit_) :
    pop(pop_), num_contacts(num_contacts_), ill(ill_), susc(pop-ill), p_recover(p_recover_), p_transmit(p_transmit_) {}
    
    void SIS::advance(){
      const double d_susc = susc_change();
      const double d_ill = -d_susc; // susc + ill = const 
      susc += d_susc;
      ill += d_ill;
  }
