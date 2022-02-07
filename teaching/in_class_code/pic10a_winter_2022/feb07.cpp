#include <iostream>

// a function can (generally) only return a single data type!

int get_year_born(){
    int y; // y is the year we extract from user 
    std::cin >> y;
    return y;
}

// n is a parameter
// parameters = the entities in the function signature 
unsigned long long factorial(unsigned long long n){
    unsigned long long fact = 1;
    for(unsigned long long i=1; i <=n; ++i){
        fact *= i;
    }
    return fact;
}

/**
 * this function prints the sum of its two inputs
 * @param _a the first input 
 * @param _b the second input
 */
 void print_sum(int _a, int _b){
     int _c = _a + _b;
     std::cout << _c << '\n';
 }
 
 int give_value(int a){
     if(a > 10){
       return 101; // once this is reached, 101 is returned, no more instructions read 
     }
     
     // once this line is reached, the function is done, no more instructions read 
     return 97;
     
     std::cout << "this never gets read!\n";
     
     return 83;
     
     return 0;
 }
 
 
 void print_factorial(int n){
     if(n < 0){ // invalid choice 
         return; // void functions can return with nothing
     }
     
    int fact = 1;
    for(int i=1; i <=n; ++i){
        fact *= i;
    }
    std::cout << fact << '\n';
}

void add_on(int a, int b){
    a += b;
}

// hypothetically: imagine this appears in a .h file ...
void add_on_better(int& a, int b); // -- the declaration of the function 

 

int main()
{
    //std::cout << "In what year were you born? ";
    //const int year_born = 0;
    //std::cin >> year_born;
    
    // get_year_born is a function 
    // returns an int read from the std::cin 
    //const int year_born = get_year_born();
    
    //std::cout << "you were born in " << year_born << '\n';
    
    // now let's compute a factorial for them 
    //std::cout << "Enter an integer: ";
    //unsigned long long int n;
    //std::cin >> n; 
    
    // factorial: clearer semantics, the name says it all 
    // easier to read: less clutter 
    // reusable! -- DRY don't repeat yourself 
    
    //std::cout << n << "! = " << factorial(n) << '\n';
    //std::cout << n+1 << "! = " << factorial(n+1) << '\n';
    
    // factorial(n) -- n is called an argument 
    // what we feed into a function is called an argument 
    
    /*unsigned long long fact = 1;
    for(unsigned long long i=1; i <=n; ++i){
        fact *= i;
    }
    std::cout << n << "! = " << fact << '\n'; */
    
    int a = 5, b = 12;
    { // new scope here!
        int _a = a; // _a and _b and _c local to this scope 
        int _b = b;
        int _c = _a + _b;
        std::cout << _c << '\n';
    }
    
    // order that arguments are passed to a function is 
    // the order the parameters are initialized
    print_sum(a,b); // a --> _a, b--> _b 
    
    std::cout << give_value(500) << '\n';
    std::cout << give_value(0) << '\n';
    
    print_factorial(0);
    print_factorial(-8); // nothing got printed
    print_factorial(5);
    
    std::cout << "========\n";
    
    int i = 42;
    add_on(i,7); // want to add 7 to i 
    std::cout << i << '\n';
    
    // kind of like 
    /*
    {
        int a = i;
        int b = 7;
        a += b;
    }
    */
    
    add_on_better(i,7); // want to add 7 to i 
    std::cout << i << '\n';
    // kind of like 
    /*
    {
        int& a = i;
        int b = 7;
        a += b;
    }
    */

    return 0;
}

// in a separate cpp file...
// this is the definition of the function 
void add_on_better(int& a, int b){
    a += b;
}
