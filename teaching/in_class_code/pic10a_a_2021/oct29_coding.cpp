/*
1. Consider the array of int, vals, and the pointer to int, x. Write code so that, in the end, x will either:
a) point to an element of vals with value 8 if such a value exists or 
b) point to nullptr if no such value can be found.

int vals[25];

// stuff

int* x = nullptr;

// our code 

2. We repeat this exercise with a 3-dimensional array, vals.

int vals[20][30][40];

// stuff

int* x = nullptr;

// code to write 


*/

#include<iostream>
#include<ctime>
#include<cstdlib>

int main(){
    // 1. 
    
    /*const size_t val_sz = 250u;
    
    int vals[val_sz];
    
    std::srand(std::time(nullptr));
    
    for(size_t i=0; i < val_sz; ++i){
        vals[i] = std::rand() % 20;
    }
    
    // stuff 
    
    int* x = nullptr;
    
    for(size_t i=0; i < val_sz; ++i){
        if(vals[i] == 8){
            x = &vals[i];
            //x = vals + i;
            break; // we found it!
        }
    }
    
    if(x==nullptr){
        std::cout << "not found\n";
    }
    else{
        std::cout << "found an 8\n";
    }*/
    
    // 2. 
    /*
    
    const size_t xdim = 20, ydim=30, zdim=40;
    const int wanted = 8;
    
    int vals[xdim][ydim][zdim];

    // stuff

    int* x = nullptr;
    
    bool done = false;

    for(size_t i =0; i < xdim; ++i){
        for(size_t j=0; j < ydim; ++j){
            for(size_t k=0; k < zdim; ++k){
                if(vals[i][j][k]==wanted){
                    x = &vals[i][j][k];
                    goto finish;
                    //done = true;
                    //break;
                }
            }
            //if(done){
             //   break;
            //}
        }
        //if(done){
         //   break;
        //}
    }
    
    finish:
    
    if(x==nullptr){
        std::cout << "not found\n";
    }
    else{
        std::cout << "found an 8\n";
    } */
    
    /*
    3. Consider a little game simulating fighting a monster. 
    In the game, the player and the monster both start with 10 hit points. 
    The player starts.

   In each turn, the player and monster can either attack
   (and lessen the other's hit points by a uniformly random integer from 0-2)
   or recover (gain 0-2 hit points, again uniformly at random, 
   without exceeding 10 total).

  The player gets to choose 'a' for attack and anything else for recover.

  The monster always randomly chooses between attack and recover.

  The game ends when either party reaches 0 hit points.

  Do this where the turns always alternate.
    
    
    */
    std::srand(std::time(nullptr));
    
    std::cout << "A monster is coming to attack you!\n";
    int player_hp = 10, monster_hp = 10;
    
    bool player_attack = false, monster_attack = false;
    
    bool player_turn = true;
    
    const int attack_range = 3, recover_range = 3;
    const int hp_max = 10;
    
    while((player_hp>0) && (monster_hp>0)){ // this runs until player or monster have 0 hp 
        if(player_turn){
            std::cout << "Attack (a) or recover (else): ";
            
            char choice;
            std::cin >> choice;
            
            player_attack = (choice=='a');
            
            if(player_attack){ // player does the attack 
                int damage = std::rand() % attack_range;
                monster_hp -= damage;
                if(monster_hp<0){ // can't be more than dead 
                    monster_hp = 0;
                }
                std::cout << "You attack. Monster now has: " << monster_hp << '\n';
            }
            else{ // player recovers 
                int recovery = std::rand() % recover_range;
                player_hp += recovery;
                if(player_hp>hp_max){ // can't have more hp  
                    player_hp = hp_max;
                }
                std::cout << "Player recovers. You now has: " << player_hp << '\n';
            }
            player_turn = false;
        }
        else{ // monster's turn 
            monster_attack = (std::rand() % 2 == 0);
            if(monster_attack){ // monster does the attack 
                int damage = std::rand() % attack_range;
                player_hp -= damage;
                if(player_hp<0){ // can't be more than dead 
                    player_hp = 0;
                }
                std::cout << "Monster attacks. You now have: " << player_hp << '\n';
            }
            else{ // monster recovers 
                int recovery = std::rand() % recover_range;
                monster_hp += recovery;
                if(monster_hp>hp_max){ // can't have more hp  
                    monster_hp = hp_max;
                }
                std::cout << "Monster recovers. Monster now has: " << monster_hp << '\n';
            }
            player_turn = true;
        }
    }
    
    if(player_hp > 0){
        std::cout << "You defeated the monster!\n";
    }
    else{
        std::cout << "Monster defeated you!\n";
    }
    
    return 0;
}
