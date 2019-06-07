#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vint){
 for(int i : vint){
  out << i << ' ';   
 }
 return out;
}

template<typename T, typename Compare = std::less<T> >
class generic_less{
private:
  Compare less_than; 
public:
  generic_less( const Compare& _less_than = Compare() ) : less_than(_less_than) {}
  bool operator()(const T& first, const T& second) const {
   return less_than(first, second);   
  }    
};

bool double_greater(double d1, double d2){
 return d1 > d2;   
}

int main(){
 std::vector<int> v{2, 4, -2, -8, 10, 53};
    
 int change = -1;
 std::for_each( std::begin(v), std::end(v), 
               [change](int& i)->void{ i += change;});   
    
 std::cout << v << '\n';
    
 double d1 = 3.14;
 double d2 = 9.999999;
 
 generic_less<double> L1;
 generic_less<double, bool(*)(double,double)> L2(double_greater);
    
 std::cout << std::boolalpha << L1(d1,d2) << '\n' << L2(d1,d2) << '\n';
    
    
 return 0;   
}
