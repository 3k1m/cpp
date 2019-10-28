#include <iostream>
#include <string>
#include <vector>

int main()
{
    // an empty vector OF vector of int
    
    // long winded way of making the vector ...
    std::vector< std::vector<int> > vec_ints;
    
    const size_t num_vecs = 10;
    
    for(size_t i=0; i < num_vecs; ++i){ // push back 10 vectors
      vec_ints.push_back( std::vector<int>(3)   );   
    }
    
    for(size_t i=0; i < num_vecs; ++i){ // for each vector
        for(size_t j =0; j < vec_ints[i].size(); ++j){
          std::cout << vec_ints[i][j] << ' ';   
        }
        std::cout << '\n';
    }
    
    // quicker way
    
    std::vector< std::vector<int> > vec_ints2( num_vecs, 
        std::vector<int>(3, 5) );
        
    for(size_t i=0; i < num_vecs; ++i){ // for each vector
        for(size_t j =0; j < vec_ints2[i].size(); ++j){
            // want 1 2 3 ... 4 5 6 ... 7 8 9 ...
          int val = static_cast<int>( i*3 + j + 1 );   
          vec_ints2[i][j] = val;
        }       
    }
    
    vec_ints2.push_back( std::vector<int>(20) );
    
    for(size_t i=0; i < vec_ints2.size(); ++i){ // for each vector
        for(size_t j =0; j < vec_ints2[i].size(); ++j){
          std::cout << vec_ints2[i][j] << ' ';   
        }
        std::cout << '\n';
    }
    
    
    const size_t array_cap = 5;    
    size_t array_size = 5;    
    
    // bunch of doubles [2. | 4. | ... | 10.]    
    //double d[array_cap] = {2,4,6,8,10};
    
    //double d[5]; // none of the values were specified... - could be anything    
    //double d[5] = {1,2,3}; // extra values are value initialized    
    double d[] = {2,4,6,8,10};
        
    std::cout << d[3] << '\n';    
    d[0] = 8;
    std::cout << d[0] << '\n';
    
    
    if(array_size == 0){ // size is zero... don't do anything
     std::cout << "cannot pop back... to small!\n";   
    }
    else{        // safe to "pop back"
        // pop_back on d...
    --array_size;
    }
    
    for(size_t i=0; i < array_size; ++i){
     std::cout << d[i] << '\n';   
    }
    
    double e[4][5];
    
    for(size_t i=0; i < 4; ++i){
        for(size_t j =0; j < 5; ++j){
            e[i][j] = 10;       
        }
    }
    
    
    // cat_mood is a data type with categories: HAPPY/SAD
    enum class cat_mood{
      HAPPY,
      SAD
    };
    
    cat_mood c = cat_mood::HAPPY;
    
    if(c == cat_mood::HAPPY){ // happy
     std::cout << "purrr...\n";   
    }
    else{ // must be sad
     std::cout << "hiss...\n";   
    }   
    
    
  
  return 0;
}
