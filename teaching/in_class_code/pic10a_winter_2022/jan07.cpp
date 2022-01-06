#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(nullptr));
    
    cout << "I am choosing a number from 1-10. Please guess it!\n";
    
    const int max = 10;
    const int shift = 1; // to shift range 
    
    int num = rand() % max + shift; // the secret number
    
    bool need_more = true;
    
    while(need_more){ // while they are not correct yet
        // make them guess...
        int guess = 0;
        cin >> guess;
        if(guess == num){ // they got it correct 
            need_more = false;
        }
    }
    cout << "Yes, that's right. The number is: " << num << '\n';

    return 0;
}
