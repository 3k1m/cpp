#include <iostream>
#include <algorithm>
#include <iterator>


struct Item{
  double price;
  constexpr Item(double _p) : price(_p) {}
  
  constexpr operator double() const { return price; } 
};


constexpr bool rev_double(double x, double y){
    return y < x;
}

// this function needs one input and returns a bool 
constexpr bool more_than_10(double x){
 return x > 10;
}

// much more general: can work for any lower bound!
struct Exceeds_Lower{
  double low;  
    
  constexpr Exceeds_Lower(double _low) : low(_low) {}
  
  // this call operator takes one input and returns a bool 
  constexpr bool operator()(double x) const {
      return x > low;
  }
};



int main()
{
    auto hello = [](){ std::cout << "Hello world\n"; };
    hello();
    
    
    
   Item items[] = {Item(10.50), Item(12.25), Item(8.67), Item(3.42), Item(25.25)};
   
   for(const auto& i : items){
    std::cout << i << ' ';   
   }
   std::cout << '\n';
   
   // put in ascending order 
   // uses operator<
   std::sort(std::begin(items), std::end(items));
   
   for(const auto& i : items){
    std::cout << i << ' ';   
   }
   std::cout << '\n';
   
   // switches the notion of "<"
   // custom comparison...
    std::sort(std::begin(items), std::end(items), rev_double);
   
   for(const auto& i : items){
    std::cout << i << ' ';   
   }
   std::cout << '\n';
   
   // want to know if an item costs more than $10...
   auto it_gtr_10 = std::find_if(std::begin(items), std::end(items), more_than_10);
   
   // will point to first element where predicte is true or past the end if none meet criteria 
   if(it_gtr_10 != std::end(items)){
       std::cout << "found an item > $10: " << *it_gtr_10 << '\n';
   }
   
   double lower_bound;
   std::cout << "Enter a lower bound: ";
   std::cin >> lower_bound;
   
   // want to know if an item costs more than lower_bound 
   auto it_gtr_lower = std::find_if(std::begin(items), std::end(items), Exceeds_Lower(lower_bound));
   
   // will point to first element where predicte is true or past the end if none meet criteria 
   if(it_gtr_lower != std::end(items)){
       std::cout << "found an item: " << *it_gtr_lower << '\n';
   }
   
   double low, up;
   std::cout << "Enter a price range separated by space: ";
   std::cin >> low >> up;
   
   // want to know if an item costs between low and up inclusive...
   // used a lambda expression 
   auto it_range = std::find_if(std::begin(items), std::end(items), 
     [low,up](double x){
         return (low <= x) && (x <= up);
     }
   );
   
   // will point to first element where predicte is true or past the end if none meet criteria 
   if(it_range != std::end(items)){
       std::cout << "found an item: " << *it_range << '\n';
   }

    return 0;
}
