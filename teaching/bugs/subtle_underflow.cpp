#include<iostream>
#include<type_traits>

template<
  typename Int, 
  typename Float,
  std::enable_if_t< std::is_floating_point_v<Float> &&
    std::is_unsigned_v<Int> , void* > = nullptr >
  Float do_math(Int i, Float f){
   return i-1+f;   
  }

int main()
{
  // sure would be nice if this returned 1.5...
  // but it won't! underflow happens first :(
  std::cout << do_math(0u, 2.5) << '\n';
  return 0;
}
