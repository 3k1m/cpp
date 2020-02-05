#include<iostream>
#include<ctime>
#include<cstdlib>

int main(){
    
    // to "seed" the random function
    // use the current time
    
    // nullptr is a pointer
    // std::time returns #sec since Jan 1, 1970, receives a pointer
    // std::rand takes in an int argument to initialize the seeding
    std::srand( std::time ( nullptr ) );
    
    // generate some random numbers...
    std::cout << std::rand() << '\n';
    std::cout << std::rand() << '\n';
    std::cout << std::rand() << '\n';
    std::cout << RAND_MAX << '\n'; // largest possible
    
    // note they are very big...
    
    // roll of a die...
    const int min = 1;
    const int max = 6;
    
    // +1 for inclusive
    int die_roll = rand() % ( max - min + 1 ) + min;
    
    std::cout << "die rolled a " << die_roll << '\n';
    
    // many applications, want a number from 0 inclusive to 1 exclusive
    // [0, 1)
    
    double x = std::rand() / ( RAND_MAX + 1.0);
    std::cout << x << '\n';
    
    // want range [a,b)
    const double a = 1.3333;
    const double b = 5.26;
    
    double temp = std::rand() / ( RAND_MAX + 1.0);
    double a_to_b = a + (b-a)*temp;
    
    std::cout << a_to_b << '\n';
    
    return 0; 
    
}
