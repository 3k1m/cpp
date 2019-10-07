#include<iostream>
#include<string>
#include<cstddef>

using namespace std;

int main(){
  // make empty string called empty
 string empty; 
 
   // make a string storing "hi"
 string says_hi = "hi";
 
 cout << empty << says_hi << '\n';
 
 // 100 chars, all to be 'a'
 string many_as(100,'a');
 cout << many_as << '\n';
 
 string says_bye("bye");
 cout << says_bye << '\n';
 
 // do math with them?
 cout << says_hi + says_bye << '\n';
 
 // update empty to be a copy of many_as
 empty = many_as;
 
 cout << empty << '\n';
 
 // now says_hi == "hibye"
 says_hi += says_bye;
 
 // ways of adding to the end
 says_bye += '!';
 says_bye += "@@@";
 
 // push_back = "member function"
 // adds a char at end of string
 says_bye.push_back('#');
 
 cout << says_bye << '\n';
 
 // pop_back removes char at end
 says_bye.pop_back();
 
 cout << says_bye << '\n';
 
 // size is a member function to
 // tell us the size (length) of the string
 
 // size_t is a special unsigned integer type
 // that is guaratanteed to have enough bytes
 // to store the largest possible container size
 // (think string) on a given operating system
 
 size_t bye_length = says_bye.size();
 
 cout << bye_length << '\n';
 
 
 
 
    
 return 0;   
}
