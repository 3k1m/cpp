#include<iostream>
#include<vector>



void double_value(int& x){ x *= 2; }
void triple_value(int& x){ x *= 3; }

void transform(std::vector<int>& v,
  void (*f)(int&) ){
      for(int& i: v){
          f(i);
      }
  }


int main(){
    std::vector<int> v {2,4,6};
    
    transform(v, double_value);
    
    for(int i: v){
        std::cout << i << ' ';
    }
    
    return 0;
    
}
