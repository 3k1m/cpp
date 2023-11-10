#include<iostream>
#include<random>
#include<cmath>

#include <boost/math/distributions/arcsine.hpp>
#include <boost/math/distributions/exponential.hpp>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/math/tools/roots.hpp>

int main(){
   
  std::random_device rd;
  std::uniform_real_distribution<> u{0,1};
  
  auto get = [&rd,&u] { return u(rd); };
  
  std::cout << "PROBABILITY\n";
  namespace prob = boost::math;
  
  prob::arcsine_distribution<> adist{-1, 5};
  
  std::cout << "arcsine\n";
  for(int i=0; i < 10; ++i){
    std::cout << quantile(adist, get()) << '\n';
  }
  
  prob::exponential_distribution<> edist{5.};
  
  std::cout << "exp dist\n";
  for(int i=0; i < 10; ++i){
    std::cout << quantile(edist, get()) << '\n';
  }  
  
  
  std::cout << "LINEAR ALGEBRA\n";
  namespace ublas = boost::numeric::ublas;
  using matrix = ublas::matrix<double>;
  
  matrix m(2,3);
  double k = 1;
  for(size_t i=0, s1 = m.size1(); i < s1; ++i){
    for(size_t j=0, s2 = m.size2(); j < s2; ++j){
      m(i,j) = k++;
    }
  }  
  
  std::cout << m << '\n';
  std::cout << 2*m << '\n';
  std::cout << trans(m) << '\n';   
  std::cout << prod(m, trans(m)) << '\n';
  
  std::cout << "ROOT FINDING\n";  
  namespace roots = boost::math::tools;
  auto fun = [](double x) { return 3*x*x - 5*x - 20;};
  
  auto sol = roots::bisect(fun, -5., 1., [](double x, double y) { return std::fabs(x-y) < 1.e-6; });
  std::cout << sol.first << ' ' << sol.second << '\n'; 
  
}
