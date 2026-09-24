#include<print>
#include<vector>

int main()
{
    std::vector v{1,2,3,4,5};
    
    /*for(size_t i=0, sz = v.size(); i < sz; ++i){
        std::println("{}",v[i]);
    }*/
    
    for(int i : v){
        std::println("{}",i);
    }
    
    for(size_t j=0, sz = v.size(); j < sz; ++j){
        int i = v[j];
        std::println("{}",i);
    }
    
    // printing in reverse
    for(size_t i = v.size()-1; i != -1; --i){
        std::print("{}",v[i]);
    }
    

    return 0;
}
