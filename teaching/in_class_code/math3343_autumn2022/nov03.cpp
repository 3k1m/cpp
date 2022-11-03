#include <iostream>
#include<string>
#include<vector>

unsigned factorial(unsigned n){
    if(n <= 1) { return 1; }
    return n*factorial(n-1);
}

struct Y{
  int a = 0;
 
  // parameter a masks the member variable a
  void set_a(int a) { a = a; } // a = a assigns parameter to itself, member a unchanged
 
  void set_a2(int a) { this->a = a; } // this->a is the member variable
 
  void set_a3(int _a) { a = _a; } // no masking
 
  void print() const { std::cout << a << '\n'; }
   
};


class Z{
  std::string s;
  std::vector<int> v;
  int i;
  std::string t;
public:
  Z(const std::string& _s, size_t N, int v_val, int i_val) :
    s(_s), v(N,v_val), i(i_val) {} /* t is "" */
   
};

int main()
{
    Y y{};
    y.print();
    y.set_a(1);
    y.print();
   
   
  std::cout << "5! =" << factorial(5) << '\n';
 
  int x = 42;
 
  // xp starts to exist here so xp is defined as type int*
  int* xp = &x; // x already exists so &x = address of x
 
  // xr starts to exist here, so xr is defined as type int&
  int& xr = *xp; // xp already exists so *xp is dereferencing, gets to x
 
  int& xr2 = x; //  
 
  ++xr;
  (*xp)*=2;
 
  std::cout << x << '\n';
 

    return 0;
}
