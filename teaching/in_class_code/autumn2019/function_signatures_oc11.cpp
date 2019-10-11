#include<iostream>
#include<string>

// function called foo
// takes in int and double
// outputs double
double foo(int i, double d);
// inputs in foo above are named i and d
// but a function signature does not require naming

// function bar
// takes in 3 int's
// returns nothing
void bar(int, int, int);

// function baz
// takes no inputs
// returns a string
std::string baz();

// more modern syntax...
// function called quuz
// takes in int and double
// outputs double
auto quuz(int, double) -> double;
// trailing return type syntax
// requies the auto keyword as shown

int main(){
    
 return 0;   
}
