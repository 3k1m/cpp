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
    
	simple_timer::timer<'s',long double> tim; // timer object for seconds with long double precision
	do_copies(no_moves);
	auto time_copies = tim.tock(); // time with copy constructors
	
	tim.tick();
	do_moves(has_moves);
	auto time_moves = tim.tock(); // time with move constructors
	
	std::cout << "Copy constructors: " << time_copies << '\n';
	std::cout << "Move constructors: " << time_moves << '\n';
	
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
