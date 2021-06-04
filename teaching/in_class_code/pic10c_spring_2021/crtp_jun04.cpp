#include <iostream>
#include <cmath>

// CRTP

template<typename Derived>
struct Number{
    virtual ~Number() = default;
    
    auto get_squared() const {
        return std::pow( static_cast<const Derived&>(*this).x, 2  );
    }
};

struct Int : Number<Int> {
  int x = 5;  
};

struct Double : Number<Double> {
  double x = 6.38;  
};

template<typename T>
void print_square(const Number<T>& num){
    std::cout << num.get_squared() << '\n';
}

int main()
{
   std::cout << Int{}.get_squared() << '\n';
   
   Double d;
   print_square(d);

    return 0;
}
