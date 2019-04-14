/**
This demo illustrates the speed gain in using a move constructor by trying two functions, one that makes several copies of an
object, the other that do a proper move of that object.
This requires Timer.h found in the timer/ folder
*/

#include "Timer.h"

#include<iostream>
#include<vector>

/**
@struct No_Moves can be copied but not moved, stores a vector of char
*/
struct No_Moves{
	std::vector<char> s;
	No_Moves() : s(40000,'a') {}
	No_Moves(const No_Moves&) = default;
};

/**
@struct Has_Moves can be moved, stores a vector of char
*/
struct Has_Moves{
	std::vector<char> s;
	Has_Moves() : s(40000,'a') {}
};

/**
This function calls No_Moves copy constructor 100 times
*/
void do_copies(std::vector<No_Moves>&);

/**
This function calls Has_Moves move constructor 100 times
*/
void do_moves(std::vector<Has_Moves>&);

int main(){
    // make a vector that stores 1000 of each type of class
   	std::vector<No_Moves> no_moves(1000);
	std::vector<Has_Moves> has_moves(1000);
    
	// Example 1: copying and moving from this vector
	
	simple_timer::timer<'s',long double> tim; // timer object for seconds with long double precision
	do_copies(no_moves);
	auto time_copies1 = tim.tock(); // time with copy constructors
	
	tim.tick();
	do_moves(has_moves);
	auto time_moves1 = tim.tock(); // time with move constructors
	
	// Example 2: directly copying/moving from a string
	
	std::string s_to_copy(1000,'a');
    	std::string s_to_move(1000,'a');
    
	tim.tick();
	std::string copied = s_to_copy;
	auto time_copies2 = tim.tock(); // time with copy constructors
	
	tim.tick();
	std::string moved = std::move(s_to_move);
	auto time_moves2 = tim.tock(); // time with move constructors
	
	std::cout << "Copy constructors example 1: " << time_copies1 << '\n';
	std::cout << "Move constructors example 1: " << time_moves1 << '\n';
	std::cout << "Copy constructors example 2: " << time_copies2 << '\n';
	std::cout << "Move constructors example 2: " << time_moves2 << '\n';
	
	return 0;
}

void do_copies(std::vector<No_Moves>& v){	
	for(auto& i : v){ // copy each element of v
		No_Moves* m = new No_Moves(std::move(i));
    delete m;
	}	
}

void do_moves(std::vector<Has_Moves>& v){
	for(auto& i : v){ // move from each element of v
		Has_Moves* m = new Has_Moves(std::move(i));
    delete m;
	}		
}
