#include <iostream>
#include <memory>
#include <stdexcept>


template<typename T>
class iterator;

template<typename T>
class node{
public:
    T val;
    node* left;
    node* right;
    

    node(T t) : val(std::move(t)), left(nullptr), right(nullptr) {}
    
friend iterator<T>;
};

template<typename T>
class iterator{
private:
   node<T>* curr;
public:
   iterator(node<T>* n = nullptr) : curr(n) {}

   iterator& operator++(){
       curr = curr->right;
       return *this;
   }
   
   iterator operator++(int){
       auto copy(*this);
       curr = curr->right;
       return copy;
   }
   
   T* operator->() const{
       return &curr->val;
   }
   
   T& operator*() const{
       return curr->val;
   }
   
   friend bool operator==(const iterator& first, const iterator& second){
       return first.curr == second.curr;
   }
   
   friend bool operator!=(const iterator& first, const iterator& second){
       return !(first==second);
   }
};

template<typename T>
void type();

struct Tracer{
  ~Tracer() { std::cout << "~Tracer()\n"; }  
};


int main()
{
    std::unique_ptr<Tracer> U (new Tracer);
    //auto W = U;
    
    std::shared_ptr<Tracer> X (new Tracer);
    auto Y = X;
    
    //Tracer *t = nullptr;
    try{
        
  Tracer* t = new Tracer;
  
  //t = new Tracer;
  //auto t2 = std::make_unique<Tracer>();
  // complicated logic... stuff that could throw exceptions 
  throw std::runtime_error("something bad");
  //delete t;
    }
    catch(const std::exception& E){
        delete t;
        t = nullptr;
        std::cerr << E.what() << '\n';
    }
    delete t;


/*    int x = 7;
    int& xr = x;
    const int& xcr = x;
    
    auto a = 4;
    auto& ar = a; // int&
    const auto& acr = a; // const int& 
    
    const auto b = 4; // const int 
    auto& br = b; // const int&
    const auto& bcr = b; // const int& 
    
    auto d = 4;
    auto&& drr = d; // int&
    
    const auto e = 4;
    auto&& err = d; // const int&
    
    auto&& f = 8; // int&&
    
    const auto&& g = e;
    
    
    // <- a -> <- b -> <- c ->
    node n1('a'), n2('b'), n3('c');
    n1.right = &n2;
    n2.left = &n1;
    n2.right = &n3;
    n3.left = &n2;
    
    iterator<char> end;
    
    for(iterator<char> i = iterator<char>(&n1); i != end; ++i){
        std::cout << *i;
    }
    */
    
    
    

    return 0;
}
