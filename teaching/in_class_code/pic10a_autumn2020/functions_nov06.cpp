#include<iostream>

// valid declaration of a function
unsigned long long int factorial(unsigned long long int);

// also a valid declaration of a function: named argument 
//unsigned long long int factorial(unsigned long long int N);

void print_sum(int i, int j){
    std::cout << i+j << '\n';
}

int foo(){
    return 5;
    
    std::cout << "running...\n";
    
    return 6;
    return 10;
    return 100;
}

double prod(double a, double b){
    return a*b;  // don't use x... not declared in this scope 
}

int bar(bool b){
  if(b){
      return 63;
  }   

}

int main(){
    std::cout << bar(true) << '\n';
    //std::cout << bar(false) << '\n'; // could be dangerous since bar won't return a value!
    
    
    // this line of code here...
    double p = prod(1.1, 1.1);
    
    double x = 1.25;
    
    // is "equivalent" to ...
    
    double q;
    {
        double a = 1.1;
        double b = 1.1;
        q = a*b;
    }
    std::cout << q << '\n';
    
    //std::cout << a;
    
    
    
   /* std::cout << foo() << '\n';
    
    
    std::cout << "Enter a number, N: ";
    
    unsigned long long int N = 0;
    std::cin >> N;
    
    std::cout << "N! = " << factorial(N) << '\n';
    
    print_sum(3,4); */
    
    return 0;
    
}

unsigned long long int factorial(unsigned long long int N){
    unsigned long long int Nfact = 1;
    for(unsigned long long int i=1; i <= N; ++i){
        Nfact *= i;
    }
    return Nfact;
}

/* unsigned long long int Nfact = 1;
    for(unsigned long long int i=1; i <= N; ++i){
        Nfact *= i;
    }
    std::cout << "N! = " << Nfact; */
