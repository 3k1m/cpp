// Example program
#include <iostream>
#include <string>

int main()
{
    std::cout << "with continue: \n";
    // only print *'s according to row number
    // and only for odd numbered rows
  for(int row=1; row <= 10; ++row){
      if( (row % 2) == 0 ) { // even row number
          continue; // go straight to ***
      }
      // print as many *'s as the row number
      for(int col=1; col <= row; ++col){
        std::cout << '*';
      }
      std::cout << '\n'; // next line
      // *** (right before closing loop braces)
  }
  
  std::cout << "with break: \n";
  for(int row=1; row <= 10; ++row){
      if( (row % 2) == 0 ) { // even row number
          break; // exit the immediately enclosing loop
          // go to ###
      }
      // print as many *'s as the row number
      for(int col=1; col <= row; ++col){
        std::cout << '*';
      }
      std::cout << '\n'; // next line      
  }
  // ### go here 
  
  // even if the condition is false
  // a do loop must execute at least once!
  // condition is checked after the body
  char done = 'y';
  
  do{
   std::cout << "are we done? y/n: ";
   std::cin >> done;
  }while( done != 'y' ); // ;!!!!!
  
  // use of break
  std::string msg("hello world how is it going?");
  
  // is h in the msg?
  bool in_string = false;
  
  // look at each char
  for(size_t i = 0; i < msg.size(); ++i){
      if(msg[i] == 'h'){ // found it so done
          in_string = true;
          break;
      }
  }
  
  
  
  
  return 0;
}
