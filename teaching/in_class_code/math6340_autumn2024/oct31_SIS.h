#ifndef _SIS_
#define _SIS_

#include<vector>

struct SIS_stats{
  double S, I;
  int t;
  
  SIS_stats(double _S, double _I, int _t);
};

class SIS{
private:
  double pr, pc, n, N, S, I;
  int t;
  std::vector<SIS_stats> data; // stores the stats day by day 
  
  void step();

public:
  /**
   * constructor for SIS class 
   * @param _pr the ...
   */
  SIS(double _pr, double _pc, double _n, double _N, double _S);
  
  double get_S() const; // const because no changes to member variables here 
  
  double get_I() const;
  
  int get_t() const;
  
  void advance(int days); // this will update member variables, not const 
  
  void print_history() const;
  
};



#endif 
