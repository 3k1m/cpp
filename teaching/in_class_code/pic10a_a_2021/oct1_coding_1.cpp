#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    cout << RAND_MAX << '\n';
    
    // the_number is an integer from 1 to 10 inclusive
    int the_number = rand() % 10 + 1;
    
    bool done_game = false;
    
    cout << "You have to guess a number from 1 to 10 inclusive. Please guess: ";
    
    // ! means not 
    while(!done_game){ // while the game is not done, we do stuff...
        int user_guess = -1;
        cin >> user_guess; // take in their guess 
        
        if(user_guess == the_number){ // they guessed correctly 
            done_game = true;
        }
        else{ // they are wrong
            cout << "Incorrect. Please guess again: ";
        }
    }
    
    cout << "You guessed the number correctly!\n";

    return 0;
}
