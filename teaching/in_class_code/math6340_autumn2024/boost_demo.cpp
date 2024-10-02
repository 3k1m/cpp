#include <boost/numeric/odeint.hpp> // for ODEs
#include <boost/math/tools/roots.hpp> // for root finding

#include <boost/numeric/ublas/matrix.hpp> // for matrices
#include <boost/numeric/ublas/io.hpp> // to print them...

// so later in the code, we can write ode::euler INSTEAD of boost::numeric::odeinet::euler
namespace ode = boost::numeric::odeint;
namespace roots = boost::math::tools;
namespace ublas = boost::numeric::ublas;

#include<iostream>
#include<cmath>

int main(){
  
  std::cout << "ODEs\n";
  // solve y' = 2 + y + t on [0, 5]
  // y(0) = 2
  // exact: y = 5e^t - 3 - t
  
  // alias for double
  using float_type = double;  
  
  const float_type T = 5;
  const size_t N = 10;
  const double dt = T/N; 
  const double y0 = 2;
  
  // the storage type for our ODE values
  using vec_type = std::vector<double>;
  
  // create some solver variables: these are templated
  // by the type of ODE values they store
  ode::runge_kutta4< vec_type > rk_step;
  ode::euler< vec_type > euler_step;
  
  // initial conditions
  // y_rk4 and y_euler represent the "current" solution value
  vec_type y_rk4{y0}, y_euler{y0};
  
  // first parameter is the current value of the solution
  // second parameter is supposed to be modified -- note the &!!!! -- set the derivative conditions
  // third parameter is the time variable
  auto dydt = [](const vec_type&x, vec_type& dx, double t){
    // derivative is 2 + y + t
    // but y is x[0], since x is the current solution 
    // dx is the y'
    dx[0] = 2 + x[0] + t;    
  };
  
  double t = 0;  // time starts at 0
  
  // these vectors will store the solutions at a series of times
  // the solution types, recall, are vec_type = std::vector<double>
  std::vector<vec_type> rk4_sol{y_rk4}; // initially store the initial data
  std::vector<vec_type> euler_sol{y_euler}; // "" ""
  
  for(size_t i=0; i < N; ++i){ // step forward N times
    
    // advance the rk4 solver forward one step at a time
    // and update the "current" solution, y_rk4
    rk_step.do_step(dydt,y_rk4,t,dt);
    euler_step.do_step(dydt,y_euler,t,dt); // same thing for Euler
    
    // the "current" solution values have been updated from above
    
    t+=dt; // advance time forward
    
    // add the "current" values at the end of the solution vectors
    rk4_sol.push_back(y_rk4);
    euler_sol.push_back(y_euler);
  }
  
  // back = the last solution value 
  // [0] gets the one and only component
  std::cout << "exact: " << 5*std::exp(T) - T - 3 << '\n';
  std::cout << "euler approx: " << euler_sol.back()[0] << '\n';
  std::cout << "rk4 approx: " << rk4_sol.back()[0] << '\n';
  
  
  /*
  y''(t) = -w exp(-y/3) y'(t) |y'(t)| + 1
  y(0) = 0
  y'(0) = 0
  
  releasing a helium balloon, taken up into atmosphere
  this takes into account drag, varying radius, etc., as the air gets thinner
  y(t) = height vs t 
  
  w is a dimensionless number
  */
  // y and y' as variables in 1st order system
  using array_type = std::array<double,2>;  
  ode::runge_kutta4< array_type > solver;
  
  // initial conditions
  array_type z{0,0}; // the values of y(0) and y'(0)  
  std::vector< array_type> zs; // the solutions at the series of times
  zs.push_back(z);
  
  const double w = 1;  
  // y''(t) = -w exp(-y/3) y'(t) |y'(t)| + 1
  auto dzdt = [w](const array_type& z, array_type& dz, double t) {
    // (y)' = y'
    // (y')' = -w exp(-y/3) y' |y'| + 1
    dz[0] = z[1];
    dz[1] = -w*std::exp(-z[0]/3) * z[1] * std::fabs(z[1]) + 1;
  }; 
  
  t = 0; // initial time  
  for(size_t i=0; i < N; ++i){
    solver.do_step(dzdt, z, i*dt, dt);
    t+=dt;
    zs.push_back(z);
  }
  
  std::cout << "t:\ty\ty'\n";
  for(size_t i=0; i < N; ++i){
    std::cout << i*dt << ":\t" << zs[i][0] << '\t' << zs[i][1] << '\n';
  } 
  
   
  std::cout << "ROOT FINDING\n";  
  // find zeros of this: roots ~ -1.8798 and 3.5465
  auto fun = [](double x) { return 3*x*x - 5*x - 20;};
  
  // find root in [-5, 1]
  // arguments are: function to find zero of, lower bound, upper bound, a tolerance function!
  // the tol function, when it returns true, means we are done
  // takes arguments for lower and upper bounds of interval
  const double tol = 1.e-6;
  auto sol = roots::bisect(fun, -5., 1., [tol](double x, double y) { return std::fabs(x-y) < tol; });
  // the return of the bisect has first & second members, the lower and upper bounds
  
  std::cout << sol.first << ' ' << sol.second << '\n'; // solution interval
  
  std::cout << "LINEAR ALGEBRA\n";
  using matrix = ublas::matrix<double>;
  
  matrix m(2,3); // construct matrix with given size: 2x3, all zeros
  double k = 1;
  // size1 gives the number of rows
  // size2 gives the number of cols
  for(size_t i=0, s1 = m.size1(); i < s1; ++i){
    for(size_t j=0, s2 = m.size2(); j < s2; ++j){
      m(i,j) = k++;
    }
  }  
  
  std::cout << m << '\n';
  std::cout << 2*m << '\n';
  std::cout << m + m << '\n'; 
  std::cout << trans(m) << '\n';    // M^T
  std::cout << prod(m, trans(m)) << '\n'; // M M^T   
  
}
