#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <set>
#include <list>
#include<array>


bool reverse_compare(const std::string& s1, const std::string& s2){
    return s2 < s1;
}

bool has_size_5(const std::string& s){
    return s.size() == 5;
}

struct Int{
  int i;
  Int(int _i) : i(_i) {}
};

bool operator==(const Int& i1, const Int& i2){
    return i1.i == i2.i;
}


//void print(const std::string& s){
//    std::cout << s << ' ';
//}

template<typename T>
void print(const T& s){
    std::cout << s << ' ';
}

void first_to_lower(std::string& s){
    if(s.size()>0){ // only do stuff if it has characters!
        if(('A' <= s[0]) && (s[0] <= 'Z')){ // then a capital letter 
            auto A_to_a = 'a' - 'A';
            s[0] += A_to_a;
        }
    }
}


int main()
{
  std::vector<std::string> names{"Connie", "Elise", "Alice", "Bob", "Doug" };
  std::sort( names.begin(), names.end() ); // default is to use operator<
  
  for(const auto& n : names){
      std::cout << n << '\n';
  }
  std::cout << "-----\n";
  
  std::sort( names.begin(), names.end(), reverse_compare ); // now "a < b" means "b < a"
  
  for(const auto& n : names){
      std::cout << n << '\n';
  }
  std::cout << "-----\n";
  
  // other data type 
  std::deque<std::string> names2{"Connie", "Elise", "Alice", "Bob", "Doug" };
  std::sort( names2.begin(), names2.end() ); // default is to use operator<
  
  for(const auto& n : names2){
      std::cout << n << '\n';
  }
  
  std::vector<Int> v;
  for(size_t i =0; i < 10; ++i){
      v.push_back( Int ( static_cast<int>(i)  ) );
  } 
  Int q(5);
  
  // if found, returns iterator there
  // if not found, returns past-the-end
  auto it5 = std::find(std::begin(v), std::end(v), q);
  
  if(it5 != std::end(v)){
      // (*it5).i
      std::cout << it5->i << '\n';
  }
  
  // now we will look to find if there is a name with a length of 5 ...
  std::string names3[] = {"Connie", "Elise", "Alice", "Bob", "Doug"};
  
  // find first position where name has 5 chars 
  auto name_it = std::find_if(std::begin(names3), std::end(names3), has_size_5 );
  
  // alternatively
  auto name_it2 = std::begin(names3);
  while(name_it2 != std::end(names3)){
      if(name_it2->size() == 5){
          break;
      }
      ++name_it2;
  }
  
  
  if(name_it != std::end(names3)){
      std::cout << *name_it;
  }
  
  std::cout << "-----\n";
  
  std::for_each(std::begin(names3), std::end(names3), first_to_lower);
  std::for_each(std::begin(names3), std::end(names3), print<std::string>);
  
  std::cout << "-----\n";
  
  std::set<int> ints;
  for(size_t i =0; i < 10; ++i){
      ints.insert( static_cast<int>(i) );
  } 
  std::for_each(std::begin(ints), std::end(ints), print<int>);
  
  std::cout << "-----\n";
  
  std::list<double> doubles;
  doubles.push_back(3000.14);
  doubles.push_front(1.111);
  std::for_each(std::begin(doubles), std::end(doubles), print<double>);
  
  std::array<int,5> arr;
  arr[3] = 7;
  std::for_each(std::begin(arr), std::end(arr), print<int>);
  

    return 0;
}
