#include<iostream>
#include<vector>

// place = the position where we want to place a #
void permute(std::vector<int>& v, size_t place = 0){
    if(place == v.size()-1){ // placing at the end
        // everything already placed
        for(int i : v) { std::cout << i << ' '; }
        std::cout << '\n';
        return; // done!
    }
    
    // other values we can swap with
    for(size_t i = place, sz = v.size(); i < sz; ++i){
        std::swap(v[place], v[i]); // now i has chance at place
        permute(v, place+1); // move on to next slot
        std::swap(v[place], v[i]); // undo the placement
    }    
}

int main(){
    
   std::vector<int> v{1,2,3};
    permute(v);
    
 return 0;   
}
