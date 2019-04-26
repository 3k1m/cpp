#include<iostream>
#include<vector>

double mean(const std::vector<int>& v){
  if(v.empty()){
   throw std::logic_error("empty vector");   
  }
    
 double sum = 0;
 for(int i : v){
  sum += i;   
 }
 return sum / v.size();
}

double sum(const std::vector<int>& v){
 double total = 0;
 for(int i : v){
  total += i;   
 }
  return total;
}

void do_stuff(const std::vector<int>& v, double (*f)(const std::vector<int>&)){
 //std::cout << f(v) << '\n';
 std::cout << (*f)(v) << '\n';
}

int main(){
    std::vector<int> v{1,2,3};
    do_stuff(v, mean);
    do_stuff(v, sum);
    
    typedef double (*fun_type)(const std::vector<int>&);
    using fun_type2 = double (*)(const std::vector<int>&);
    
    fun_type f1 = mean;
    fun_type2 f2 = sum;
    
    do_stuff(v, f1);
    do_stuff(v, f2);
    
    double (*f3)(const std::vector<int>&) = mean;
    double (*f4)(const std::vector<int>&) = sum;
    
    do_stuff(v,f3);
    do_stuff(v,f4);     
    
    return 0;
    
    
}
