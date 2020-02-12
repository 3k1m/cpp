/*
This is an illustration only. In practice, goto should almost never be used.
But it's nice to see that it exists and what it does.
*/

#include<iostream>

int main(){
 
 int i = 1;
 
 // can label lines
 begin:
 
 if(i < 11){
   goto print;   // go to the line labelled print
 }
 else{
   goto done; // go to the line labelled done
 }
 
 print:
   std::cout << i << '\n';
   ++i; // and INCREASE or bad things happen ;)
   goto begin;
   
 done:
   std::cout << "done!";
    
    
    
 return 0;   
}
