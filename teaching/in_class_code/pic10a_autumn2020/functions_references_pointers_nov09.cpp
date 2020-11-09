#include <iostream>
#include <string>


void times_two(int i){
    i *= 2;
}

void times_two_ref(int& i){
    i *= 2;
}

void times_two_ptr(int* i){
    (*i) *= 2;
}

// always ask: should i be changing the argument? --- n: make const 
// especially for references!
void foo(const std::string& s){
    // check the size of s...
    if(s.size()==3){
        // oops we should have done
        //if(s == "hello world"){
        //    std::cout << s << '\n';
        //}
      //s = "hello world";
    }
}

void print(const char* c){
    std::cout << c << '\n';
}

int main()
{
    const char* hello = "hello";
    std::cout << hello << '\n';
    print(hello);
    
    
   std::string msg("123");
   foo(msg);
   std::cout << msg << '\n';
   
 
 
    int x = 4;
    //times_two(x);
    {
        int i = x;
        i *= 2;
    }
    std::cout << x<< '\n';
    
    times_two_ref(x);
    std::cout << x<< '\n';
    
    times_two_ptr(&x);
    std::cout << x<< '\n';

    return 0;
}
