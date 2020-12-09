#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>
#include <deque>

int main()
{
    // inserter iterators
  std::deque<int> v;
  // with back_inserter, always call push_back 
  // with front_inserter, always call push_front
  std::generate_n(std::front_inserter(v), 10, [a=1]() mutable { return a++;});
  
  // output stream iterators 
  std::ostream_iterator<int> o(std::cout, " ");
  std::copy(v.begin(), v.end(), o);
  std::cout << '\n';
  
  std::istringstream iss("2 4 6 8");
  
  // input stream iterator 
  std::istream_iterator<int> end;
  std::istream_iterator<int> i(std::cin); // when i fails, will be end 
  
  while(i != end){
      std::cout << *i++ << ' ';
  }

    return 0;
}
