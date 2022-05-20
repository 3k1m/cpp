// a simple way to reverse a container 
// in a range for, using CTAD

#include <iostream>
#include <type_traits>
#include <iterator>
#include <set>

template<typename C>
class rev{
  // Iter will be a reverse iterator
  using Iter = decltype( std::rbegin(std::declval<C&>()) );
  
  // should either be a moved version or reference to container 
  C _c;
  Iter _b, _e; // begin and end 
  
public:
  
  Iter begin() const { return _b; }
  Iter end() const { return _e; }
  
  // easy way to handle many possible lvalue/rvalue/constnesses coming in
  template<typename D>
  rev(D&& d) : _c(std::forward<D>(d)), _b(std::rbegin(_c)), _e(std::rend(_c))  {}
};

// deduction guide, may give things like
// rev< int (&)[4] >
// rev< std::set<int> >
// rev< const std::set<int>& >
template<typename D>
rev(D&&) -> rev< D >;

int main()
{
    const int x[] = {1,2,3,4};
    
    for(int i : rev(x)){
        std::cout <<i;
    }    
    std::cout << '\n';
     
    for(int i : rev( std::set<int>{1,2,3,4} ) ){
        std::cout <<i;
    }
    std::cout << '\n';
  
    const std::set<int> s{1,2,3,4};
    for(int i : rev( s ) ){
        std::cout <<i;
    }
    std::cout << '\n';
  
  

    return 0;
}
