#include <iostream>
#include <string>

template<typename T>
struct Foo{
  struct Bar{
      int i = 7;     
      friend void print_bar_i(const Bar& b){
        std::cout << b.i;
      }
  };    
};

//template<typename T>
//void print_bar_i(const typename Foo<T>::Bar& b){
 //   std::cout << b.i;
//}

int main()
{
  Foo<int>::Bar b;
  print_bar_i(b);
  return 0;
}
