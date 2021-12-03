#include <iostream>


template<typename Derived>
struct scalable{
  virtual ~scalable() = default;
  
  Derived times(unsigned u) const {
      Derived tot{};
      for(unsigned i=0; i < u; ++i){
          tot += static_cast<const Derived&>(*this);
      }
      return tot;
  }  
    
};


template<typename T>
struct Num : scalable<Num<T>> {
    T t;
    Num() : t{} {}
    
    Num& operator+=(const Num& other){
        t += other.t;
        return *this;
    }
};

int main()
{
   Num<int> n;
   n.t = 7;
   auto res = n.times(4);
   std::cout << res.t << '\n';

    return 0;
}
