
#include <iostream>
#include <string>

int main()
{
   int a = 108;
   std::cout << a << '\n';
   std::cout << a++ << '\n'; // suffix++: increment a, but returns a copy of the pre-incremented value
   std::cout << a << '\n';
   std::cout << ++a << '\n'; // increments a and returns a itself 
   std::cout << a << '\n';
   
   std::string s{"my cat is happy"};
   size_t N = s.size();
   std::cout << N << '\n';
   // s[N+25] causes UNDEFINED BEHAVIOR 
   std::cout << s[N-1] << s[N] << s[N+25] << '\n';
   std::cout << "not broken\n"[2];
   // at will throw an exception if we access invalid positions
   //std::cout << s.at(N+25) << '\n';
   //std::cout << "...";
   
   //const char* c = "hello world";
   //std::cout << c[3] << '\n';
   
   std::string x(50,'a');
   std::cout << x << '\n';
   
   // gets interpreted as y initially storing 2 chars
   // first char is 50(int) -> '2'
   // second char is 'a'
   std::string y{50,'a'};
   std::cout << y << '\n';
   
   std::string z{ static_cast<char>(50), 'a'};
   std::cout << z << '\n';
   

    return 0;
}
