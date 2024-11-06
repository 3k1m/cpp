#include "SIS.h"

#include<cmath>
#include<iostream>

SIS_stats::SIS_stats(double _S, double _I, int _t) : S(_S), I(_I), t(_t) {}

SIS::SIS(double _pr, double _pc, double _n, double _N, double _S) :
  pr(_pr), pc(_pc), n(_n), N(_N), S(_S), I(N-S), t(0), data{SIS_stats{S,I,t}} {}
 
  
double SIS::get_S() const{
    return S;
}
  
double SIS::get_I() const{
    return I;
}
  
int SIS::get_t() const{
    return t;
}

void SIS::advance(int days){
    for(int i = 0; i < days; ++i){
        step(); // advance one day
        ++t;
        data.emplace_back(S,I,t); // instead of data.push_back(SIS_stats(S,I,t));
    }
}

void SIS::step(){
    const double num_recover = pr*I;
    const double num_get_sick = (1-std::pow(1-pc,n*I/N))*S;
    
    const double dI = num_get_sick - num_recover; // in - out 
    
    I += dI;
    S -= dI;
}


void SIS::print_history() const{
    for(const auto& [s,i,t] : data){
        std::cout << t << ":\t" << s << '\t' << i << '\n';
    }
}
