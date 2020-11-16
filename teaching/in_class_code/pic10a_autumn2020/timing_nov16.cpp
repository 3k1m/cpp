#include<ctime>
#include<iostream>

int main(){
    
    //std::cout << ( false ? 1 : ( true ? 11 : 4  ));
    
    std::cout << "to start/stop timing, press ENTER! ";
    std::cin.get(); // user presses ENTER
    time_t start = std::time(nullptr), end = 0;
    std::cin.get(); // user presses ENTER
    std::time(&end);
    std::cout << end - start << " seconds elapsed.";
    
    return 0;
}
