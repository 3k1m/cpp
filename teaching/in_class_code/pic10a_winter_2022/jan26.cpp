#include <iostream>

using namespace std;

int main()
{ // much bigger scope of main routine

   float f = 1.0101010101f;
   float f2 = 1.f + 1.f/99;
   if( f == f2){
       std::cout << "equal\n";
   }
   
   int y = 7; // y is defined above the scope 
   int z = 100;
   { // start of scope
       int x = 0;
       
       // z hasn't been defined locally yet so z is the z above the scope 
       std::cout << z << '\n';
       
       int z = 50; // this z is local to this scope!
       
       // the z printed is the z local to this scope 
       std::cout << x << ' ' << y << ' ' << z << '\n';
       
       // change a value of a variable not local to the scope 
       // the effect is seen after leaving the scope 
       ++y; // changes the y above the scope 
       
   } // end of scope 
   //std::cout << x << '\n';
   std::cout << y << '\n'; // y can be referenced here, was not only local to 
   //  above scope 
   std::cout << z << '\n'; // this is the z defined above the scope 
   
   bool rep = true;
   while(rep){ // rep is only checked at the start of each iteration 
       std::cout << "keep repeating? y/n";
       char c;
       std::cin >> c;
       
       if(c=='n'){
           rep = false;
       }
       std::cout << "end of loop iteration\n";
   }

    return 0;
}
