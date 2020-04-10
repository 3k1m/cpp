#include<iostream>
#include<memory>
#include<utility>

struct Foo{
  int i;
  Foo(int _i) : i(_i) {}
  ~Foo() { std::cout << i << " gone\n"; }
  operator int() const { return i; }
};


int main(){
 
    {
     Foo *f = new Foo(1);
     delete f;
    }
    
    {
     std::shared_ptr<Foo> f4 ( new Foo(4) );
     std::cout << *f4 << '\n';
     // std::shared_ptr<Foo> bad = new Foo(7); // DOES NOT WORK
     std::shared_ptr<Foo> f8; // f8 points to nullptr
     f8 = f4;  
     std::cout << *f8 << '\n';
        
    }
    
    {
     std::shared_ptr<Foo> f1 = std::make_shared<Foo>(1); 
     f1.reset( new Foo(2) );        
     std::shared_ptr<Foo> f3( new Foo(3) );
     std::swap( f1, f3 ); // they switch where they point   
     std::cout << "f1: " << *f1 << '\n';
     std::cout << "f3: " << *f3 << '\n';
    }
    
    {
     std::unique_ptr<Foo> u7( new Foo(7 ) );
     // auto a7copy = u7;   // cant copy 
     u7.reset(); // will point to null
     
     if( u7 && (*u7 > 6) ){ // lazy evaluation
      std::cout << "bigger than 6\n";   
     }
        
    }
    
    {
     std::unique_ptr<Foo> u = std::make_unique<Foo>(0);
        
     Foo* uraw = u.release();       
    }
 
    
 return 0;   
}
