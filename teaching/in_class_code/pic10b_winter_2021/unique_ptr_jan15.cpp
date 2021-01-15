#include<iostream>
#include<memory>

class Int{
  int i;
public:
  Int(int _i = 0) : i(_i) {}
  
  // destructor
  ~Int() {
   std::cout << "destroying " << i << '\n';   
  }
  
  int get() const { return i; }
};

int main(){
 // Int a, b(3);
 
 std::cout << "start\n";
 {
     Int* a = new Int;    // acquire memory 
     delete a; // free memory
 }
 std::cout << "with unique\n";
 {
     // make_unique returns an Rvalue
     auto a = std::make_unique<Int>(7); // stores 7
     std::unique_ptr<Int> b( new Int ); // stores 0
     // no calls to delete (that we wrote)
 }
 std::cout << "more features...\n";
 {
     auto a = std::make_unique<Int>(7); // stores 7
     std::unique_ptr<Int> b( new Int ); // stores 0
     std::swap(a,b); // swaps what they own
     
     // what if the pointers are pointing to null?
     if(a && b){
       std::cout << a->get() << ' ' << b->get() << '\n';  
     }
     a.reset(); // a will give up ownership of the 0 and point to null
     std::cout << "...\n";
     
     a.reset( new Int(100) ); // a was pointing null, now a points to an Int w/ 100
 }
 std::cout << "more...\n";
 {
   //  okay
   std::unique_ptr<Int> a ( new Int(-1) );
   
   // ERROR: copy initialization
   // std::unique_ptr<Int> b = new Int;
   
   // ERROR
   //auto b = a; // cannot copy an Lvalue unique_ptr (a is Lvalue)
   
   // a will not free up the memory...
   Int* i = a.release(); // a gives up ownership of object and returns raw pointer to it
   
   // now we must delete i if we want to avoid memory leaks!
   delete i;
     
 }
 
 return 0;
    
}
