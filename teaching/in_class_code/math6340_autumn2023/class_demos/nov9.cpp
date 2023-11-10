#include<iostream>
#include<random>

#include<cstdlib>
#include<ctime>

#include<random>

int main()
{
    /*std::srand(std::time(nullptr));
    
    std::cout << std::rand() << '\n';
    std::cout << std::rand() << '\n';
    std::cout << std::rand() << '\n'; */
    
    std::random_device rd;
    std::uniform_real_distribution<> u{0,1}; // [0, 1)
    
    for(int i=0; i < 10; ++i){
        std::cout << u(rd) << '\n';
    }
    
    std::cout << "Exp\n";
    std::exponential_distribution<double> e{10.};
    for(int i=0; i < 10; ++i){
        std::cout << e(rd) << '\n';
    }

    return 0;
}
