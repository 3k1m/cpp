#include <iostream>
#include <deque>
#include <map>
#include <utility>

template<typename T, typename S>
struct Pair{
    T foo;
    S bar;
};

template<typename T, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<T,S>& p){
    return out << "[" << p.first << ',' << p.second << "]";
}

template<typename T>
void print_container(const T& t){
    std::cout << "[";
    for(const auto& e : t){
        std::cout << e << ' ';
    }
    std::cout << "]" << '\n';
}


int main()
{
  std::deque<int> d;
  
  for(int i=0; i < 10; ++i){
      d.push_front(i);
  }
  
  for(int i : d){
      std::cout << i << ' ';
  }
  std::cout << '\n';
  
  for(size_t i=0; i < d.size(); ++i){
      std::cout << d[i] << ' ';
  }
  std::cout << '\n';
  
  std::pair<int, char> p;
  std::cout << p.first << ' ' << p.second << '\n';
  p.first = 10;
  p.second = 'a';
  std::cout << p.first << ' ' << p.second << '\n';
  
  
  // object = count unique characters in a sentence 
  std::map<char, size_t> char_counts;
  // map will sort things by key: by char 
  // [] either creates a new key with value-initialized value 
  // or accesses the value at that key 
  char_counts['r'];
  std::cout << char_counts['r'] << '\n';
  char_counts['r']++;
  char_counts['t']++;
  std::cout << char_counts['r'] << ' ' << char_counts['t'] << '\n';
  char_counts.clear();
  

  std::cout << "Enter a sentence to analyze: ";
  std::string sentence;
  std::getline(std::cin, sentence);
  
  // for every character in the sentence, we want to 
  // increase the count for that character by 1...
  for(char c : sentence){
      char_counts[c]++;
  }
  
  std::cout << "There were " << char_counts.size() << " unique chars\n";
  
  std::cout << "The chars and counts are as follows:\n";
  
  //for(const std::pair<const char, size_t>& pair : char_counts){
      // first = key 
      // second = its value 
//      std::cout << pair.first << '-' << pair.second << '\n';
  //}
  
  for(const auto& pair : char_counts){
      std::cout << pair.first << '-' << pair.second << '\n';
  }
  
  print_container(d);
  print_container(char_counts);

    return 0;
}
