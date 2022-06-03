#include<vector>
#include<iostream>

template<typename Derived>
struct features{
    
    size_t size() const {
        return std::size( static_cast<const Derived*>(this)->data );
    }
    
    void square_values() {
        for(auto& e : static_cast<Derived*>(this)->data){
            e *= e;
        }
    }
    
};


struct Ints : features<Ints> {
  int data[3] { 1,2,3};  
};

struct Doubles : features<Doubles> {
  std::vector<double> data{1,2,3};  
};


template<typename C>
size_t print_sz(const features<C>& c){
    return c.size();
}


int main(){
    
    Doubles d;
    
    std::cout << d.size() << '\n';
    d.square_values();
    
    for(const auto& e : d.data){
        std::cout << e << '\n';
    }
    
    Ints i;
    std::cout << print_sz(i) << '\n';
    
    return 0;
}
