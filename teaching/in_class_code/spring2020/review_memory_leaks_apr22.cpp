// Example program
#include <iostream>
#include <string>
#include <memory>

struct A{
  static int a;
  int id;
  A (): id(a++) {}
  ~A() { std::cout << id << " gets destroyed\n"; }
};

int main()
{
    {
  A* ap = new A;
  A* ap2 = new A;
  
  delete ap2; // manual deletes
  delete ap;
    }
    
    
    { // no need for deletes
     std::unique_ptr<A> ap{ new A };
     std::unique_ptr<A> ap2 = std::make_unique<A>();        
    }
    
    { 
     std::unique_ptr<A> ap{ new A };
     std::unique_ptr<A> ap2 = std::make_unique<A>();  
     
     A* ap2copy = ap2.release();
     
     // bad b/c a2copy doesn't delete
     //delete ap2copy;
    }
  
  
  return 0;
}

int A::a = 0;
