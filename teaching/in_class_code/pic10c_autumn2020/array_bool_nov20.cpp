#include<iostream>
#include<vector>
#include<climits>

template<typename T>
struct byte_array{
private:
  T data[CHAR_BIT];
public:
  T& operator[](size_t i) { return data[i]; }
  const T& operator[](size_t i) const { return data[i]; }    
};

template<>
struct byte_array<bool>{
private:
  unsigned char data; // takes up 1 byte == CHAR_BIT number of bits 
public:

  byte_array() : data() {}
  
  class proxy{
  friend byte_array<bool>;
  
  unsigned char* p; // the char 
  size_t i; // the index 
  
  proxy(unsigned char* _p, size_t _i) : p(_p), i(_i) {}
  
  public:
    operator bool() const {
        return (*p >> i) & 1;
    }
    
    const proxy& operator=(bool b) const  {
        if(b){ // need to set bit i to true 
            *p = (*p | (1<<i) );
        }
        else{ // set bit i to false 
            *p = (*p & ~(1<<i) );
        }
        
        return *this;
    }
    
    
  };
  
  proxy operator[](size_t i) { return {&data, i}; }
  
};

int main(){
    
   
    byte_array<bool> x;
    x[0] = true;
    x[5] = true;
    
    for(size_t i=0; i < CHAR_BIT; ++i){
        std::cout << x[i] << ' ';
    }
    std::cout << '\n';
    
    // just like with vector<bool>: ERROR
    //bool& y = x[1];
   
   
   
   
    std::vector<double> v {1,2,3,4,5};
    
    for(auto& i : v){ ++i; }
    for(const auto& i : v){ std::cout << i << ' '; }
    std::cout << '\n';
    
    std::vector<bool> b {true, true, false, true};
    
    //for(auto& i : b){ i = !i; } // WHAT IS GOING ON HERE??? 
    for(const auto& i : b){ std::cout << i << ' '; }
    std::cout << '\n';
    
    return 0;
}
