#include<iostream>
#include<memory>

// behaves like an int but prints a message when destroyed
struct Int{
  int i;
  
  Int(int _i) : i(_i) {}
  
  operator int() const { return i; }
  
  ~Int() { std::cout << i << " destroyed\n"; }

};


int main(){
  
  {
    std::unique_ptr<Int> p( new Int(0) );
    
    // error below: copy unique_ptr
    //auto copy = p;
    
    std::cout << *p << '\n';  
    
    p.reset(new Int(11));
    
    Int *i = p.release();
    
    if(p){ // only print if not pointing to null
        std::cout << *p << "!!!\n";
    }
    
    delete i;
    
    //p = std::make_unique<Int>(11);
    
    auto p2 = std::make_unique<Int>(7);
    
    // swap where p and p2 point
    std::swap(p, p2);
  } // p2 destroyed, then p1
  
  std::cout << "end" << '\n';


  return 0;
}
