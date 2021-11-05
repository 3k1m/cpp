#include <iostream>
#include <vector>

/*
1. Write an overloaded 'square' function that for inputs of type int, 
unsigned int, and double, returns the square of that input with the same 
return type as the input.

2. Write a 'pow' function that can raise a double value 
to any integer power, returning a double. If the user calls the function with 
only one argument, it should return the square of the number:

pow(7); // 49
pow(0.25, -1); // 4

3. Write a make_unique_vector function that accepts an std::vector<int>, 
possibly storing duplicates. It should then remove all duplicates from that vector.
Do not worry about the order of the elements after the removal process.

It should return the number of elements removed.

std::vector<int> v{1,8,8,3,8,2,2};
size_t rem = make_unique_vector(v); // rem == 3
// now v=={1,2,3,8} -- or some other ordering 
*/

using namespace std;

size_t make_unique_vector( vector<int>& myVec ){
    // 1 8 8 3 8 2 2
    if(myVec.empty()){
        return 0;
    }
    
    // until the current spot is past the end, need to examine for duplicates
    for(auto curr = myVec.begin(); curr != myVec.end(); ++curr){
        bool erase_more = true;
        while(erase_more){ // more erasure
            // other position we are looking at
            auto comp_pos = curr+1;
            for(; comp_pos != myVec.end(); ++comp_pos){
                if(*comp_pos == *curr){ // duplicate 
                    myVec.erase(comp_pos);
                    break;
                }
            }
            if(comp_pos == myVec.end()){ // enver found a dupicate to curr 
                erase_more = false;
            }
        }
    }
    
}


/**
 * This function returns the square of a number
 * @param num the number to square
 * @return the number squared
 */
int square(int num);

unsigned square(unsigned num);

double square(double num);


/**
 * This function raises a number to a power
 * @param base the base of the exponentiation
 * @param exp the exponent to raise the base by --
 * by default this will be 2 if a value is not given
 * @return the base to the exponent 
 */
double pow(double base, int exp = 2);

int main()
{
    vector<int> v{1,8,8,3,8,2,2};
    size_t rem = make_unique_vector(v); // rem == 3
    
    
    /*
    1.
    
    int x = 3;
    unsigned u = 12u;
    double d = 3.14;
    
    std::cout << square(x) << ' ' << square(u) << ' ' << square(d) << '\n';
    */
    
    /*
    2. 
    std::cout << pow(3,4) << '\n';
    std::cout << pow(1,5) << '\n';
    std::cout << pow(2,-3) << '\n';
    std::cout << pow(1000,0) << '\n';
    std::cout << pow(0,0) << '\n';
    */
    
    return 0;
}

int square(int num){
    return num*num;
}

unsigned square(unsigned num){
    return num*num;
}

double square(double num){
    return num*num;
}

double pow(double base, int exp){
    double res = 1; // result
    if(exp > 0){ // positive power -- multiply
        for(int i = 1; i <= exp; ++i){ // do this exp times 
            res *= base;
        }
    }
    else if(exp < 0){ // negative power so divide
        for(int i = 1; i <= (-exp); ++i){ // sign switch b/c exp<0 
            res /= base;
        }        
    }
    else{ // exp is 0 
        if(base==0){ // bad case
            std::cout << "bad decision. 0^0 is undefined\n";
        }
    }
    
    return res;
}




