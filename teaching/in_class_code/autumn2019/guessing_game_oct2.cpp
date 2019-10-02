// Guessing Game

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(nullptr));
    
  cout << "Hi! What is your name?";
  
  // variable to store their name
  string name;
  
  // use a function to read the user's name
  getline( cin, name );
  
  // greet the user
  cout << "Nice to meet you, " << name << '.';
  
  // variable, will be randomo from 1 to 10
  int rand_number = rand() % 10 + 1;
  
  cout << "I am thinking of a number from 1 to 10. Can you guess it?\n";
  
  // variable: whether they have not guessed it correctly yet
  bool not_guessed = true;
  
  while( not_guessed ) { // until the guess is correct...
      cout << "Guess: ";
      
      int guess = 0; // the guess of the user, a variable
      
      cin >> guess; // read in their guess
      
      // if guess happens to be the random number, this
      // will be false and the game ends
      not_guessed = (guess != rand_number);      
  }
  
  // congratulate the user
  cout << "Yes, the number was in fact: " << rand_number;
  
  return 0;
  
  
}
