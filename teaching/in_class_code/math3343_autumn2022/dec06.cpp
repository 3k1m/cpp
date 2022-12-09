#include<string>
#include<iostream>


void swap_cases(std::string& _s){ // paramter should reference the argument

    // difference in values from uppercase to lower case
    const int upper_to_lower = 'a' - 'A';
   
    for(char& c : _s){
        if('A' <= c and c <= 'Z'){ // it is uppercase
            c += upper_to_lower;
        }
        else if('a' <= c and c <= 'z'){ // it is lowercase
            c -= upper_to_lower;
        }
    }
}

int main(){
    //std::cout << static_cast<char>(('A' + ('a' - 'A'))) << '\n';
    std::string test{"Hello World"};
    swap_cases(test);
    std::cout << test << '\n';
}
