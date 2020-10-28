// Example program
#include <iostream>
#include <string>


int main()
{
  std::string str("abcdefghijklmn");
  
  const char wanted = 'j';
  
  size_t i = 0;
  
  for(; i < str.size(); ++i){
   if( str[i] == wanted){
     std::cout << "found " << wanted << '\n';
     break;
   }
  }  
  std::cout << i << '\n';
  
  std::string x("bbbaacceeeiaaa");
  
  size_t num_a = 0;
  for(size_t i=0; i < x.size(); ++i){
   if( x[i] != 'a' ){
       continue;
   }   
   ++num_a;   
  }
  
  std::cout << num_a;
    
    
 /* std::string string_num;
  std::cout << "enter a number: ";
  std::cin >> string_num;
    
  // "365"
  // res: 365
    
  unsigned int result = 0u;
  for ( size_t i = 0; i < string_num.size(); ++i ) { //for each digit digit
    result *= 10u; // grow by factor of 10 then...
    // add the next number: for example '6' - '0' is 6
    result += static_cast<unsigned int>( string_num[i] - '0' );
  }
  
  // '0', '1', '2', ... 
  
  std::cout << "the number plus 1 is: " << result + 1; */
  
  return 0;
}
