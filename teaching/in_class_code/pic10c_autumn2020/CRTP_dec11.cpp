#include <iostream>

template<typename Animal>
struct Pet{
  virtual ~Pet() {}
  void talk_twice() const {
      static_cast<const Animal*>(this)->talk();
      static_cast<const Animal*>(this)->talk();
  }  
};

struct Cat : Pet<Cat>{
    void talk() const { std::cout << "meow\n"; }
};

struct Dog : Pet<Dog>{
    void talk() const { std::cout << "bark\n"; }
};

template<typename Animal>
void greet_owner(const Pet<Animal>& p){
    p.talk_twice();
}



int main()
{
    //Pet<int> p; // int is not a good pet
    //p.talk_twice();
    Cat c;
    Dog d;
    greet_owner(c);
    greet_owner(d);

    return 0;
}
