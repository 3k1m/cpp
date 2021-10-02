#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(){
    // magic to make the randomness better 
    srand(time(nullptr));
    
    // can add this const keyword to say a value shouldn't change 
    const int num_prints = 30; // how many times to print a random number 
    const int max_rand_val = 20; // numbers should be from 1 to this value inclusive 
    
    int counter = 0;
    
    while(counter < num_prints){ // until we have printed enough 
        cout << rand() % max_rand_val + 1 << '\n';
        counter = counter + 1;
    }
    
    return 0;
}
