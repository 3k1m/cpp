// Example program
#include <iostream>
#include <vector>

// pos is how many values have been set in the vector
void perm( std::vector<int> &v, size_t pos = 0){
  const size_t N = v.size();
    
  if( pos == N ){ // all values have been set
      for(int i : v ) { std::cout << i << ' '; }
      std::cout << '\n';
      return;
  }
  
  for(size_t other = pos; other < N; ++other){
      std::swap( v[pos], v[other] ); // gives item at index other chance to be at position pos
      perm( v, pos +1);
      std::swap( v[pos], v[other] );
  }
    
}

int main()
{
  std::vector<int> v{1,2,3};
  
  perm(v);

  return 0;
}
