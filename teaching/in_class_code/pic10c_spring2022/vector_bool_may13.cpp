#include <iostream>
#include <vector>


int main()
{
   std::vector vint{1,2,3,4};
   
   for(int& i : vint){
       ++i;
   }
   
   for(int i : vint){ std::cout << i << '\n'; }
   
   std::vector vool{true,true,false,true,false};
   
   for(auto&& b : vool){ // "auto b" also works, but not "bool&"
       b = !b;
   }
   
   for(bool b : vool){ std::cout << b << '\n'; }
   
   

    return 0;
}
