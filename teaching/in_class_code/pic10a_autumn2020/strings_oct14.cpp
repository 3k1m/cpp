#include <iostream>
#include <string>

int main()
{
    char n = '\n';
    
    //int x;
  std::string s;
  std::cout << s << '\n';
  
  std::string s2 = "hello";
  std::cout << s2 << '\n';
  
  std::string s3("world");
  std::cout << s3 << n;
  
  std::string s4 = s3;
  std::cout << s4 << n;
  
  std::string s5 = s3 + ' ' + s4;
  std::cout << s5 << n;
  
  //std::cout << "hello " + " world";
  
  size_t s5_length = s5.size();
  std::cout << "s5 has " << s5_length << " number of chars\n";
  
  s3 = "...";
  s3.push_back('!');
  s4.pop_back();
  std::cout << s3 << ' ' << s4 << n;
  
  std::string s6("0123456789");
  std::string s7 = s6.substr(3);
  std::string s8 = s6.substr(1,4);
  std::cout << s7 << ' ' << s8 << n;
  
  return 0;
}
