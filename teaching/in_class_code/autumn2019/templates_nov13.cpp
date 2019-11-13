#include <iostream>
#include <string>
#include <vector>

// very generic with templates!
template<typename T> // T represents ANY type
T get_max_inefficient(T a, T b){
 return a < b ? b : a;   
}

/**
 This templated function returns the "max" of two arguments
 @tparam X the type of both arguments
 @param a the first value
 @param b the second value
 @return the max of the two based on <
  */
template<typename X> // T represents ANY type
// output is a reference: no copying
const X& get_max(const X& a, const X& b){ // inputs are references
 return a < b ? b : a;   
}

// these functions return Rvalues

std::string get_bob(){
    std::string b = "Bob";
 return b;   
}

std::string get_alice(){
 return "Alice";   
}

// becomes redundant... 
/*
double get_max(double a, double b){
 return a < b ? b : a;   
}

int get_max(int a, int b){
 return a < b ? b : a;   
} */

template<typename T>
void print_vec( const std::vector<T>& vec){
 for(const auto& t : vec){
  std::cout << t << ' ';   
 }
 std::cout << '\n';
}

template<typename Container>
void print( const Container& c){
 for(const auto& e : c){
  std::cout << e << ' ';   
 }
 std::cout << '\n';
}

int main()
{
    std::vector<int> v{1,2,4,8};
    print_vec(v);
    
    print(v);
    print("hey");
    
    std::cout << get_max_inefficient(3,4) << '\n';
    std::cout << get_max_inefficient(3.2,0.4) << '\n';
    std::cout << get_max_inefficient(3L,4L) << '\n';
    
    std::cout << get_max(3,4) << '\n';
    std::cout << get_max(3.2,0.4) << '\n';
    std::cout << get_max(3L,4L) << '\n';
    
    std::string x("apple");
    std::string y("bear");
    
    std::cout << get_max(x,y) << '\n';
    
    std::cout << get_max( get_alice(), get_bob() ) << '\n';
    
    // seg fault
    //const std::string& s = get_max( get_alice(), get_bob() );    
    //std::cout << s << '\n';
    
    const std::string s = get_max( get_alice(), get_bob() );    
    std::cout << s << '\n';
    
    
  return 0;
}
