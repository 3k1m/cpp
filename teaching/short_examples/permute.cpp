#include<vector>
#include<iostream>

/**
This operator allows us to print a vector
@param out an output stream
@param v a vector to print
@return the stream
*/
std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
 for(int i : v){ // print all v elements
  out << i << ' ';   
 }
 return out;
}

/**
This function prints all permuations of a vector
@param v the vector to permute
@param place the position being placed
*/
void perm(std::vector<int>& v, size_t place=0){
 size_t length = v.size();
    
 if(place==length-1){ // last index, so everything placed, just print
  std::cout << v << '\n';   
 }
 else{ // more positioning to do     
     
  // allow all items from current place to end to be used
  for(size_t other=place; other < length; ++other){
   std::swap(v[place],v[other]); // move to place
   perm(v,place+1); // recurse with one more item placed
   std::swap(v[place],v[other]); // undo the placement
  }
 }
}

int main(){
 std::vector<int> v{1,2,3,4,5};
    perm(v);
    return 0;    
}
