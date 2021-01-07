#include<iostream>
#include<string>


// imagine this is in Person.h header file

class Person{
private:
  std::string name; // their name
  //int fav_num = 0; -- answering question on ref to const always for getter functions?
  
public:
  Person(const std::string& _name);
  
  void print_name() const; // this function will not change the person's name!
  
  void change_name(const std::string& new_name);     
  
  // & adds efficiency: no copy of name done: just a reference
  // reference to const because member function is an accessor function
  const std::string& get_name() const; // yes, const again!
  
  // get their favourite number
  //int get_favourite_num() const { return fav_num; }
};


// imagine this is in source.cpp - our file with main

int main(){
 std::string persons_name; 
 std::cout << "Give name of Person: ";
 std::getline(std::cin, persons_name);
 
 // now make a Person
 Person p(persons_name);
 
 std::cout << "You gave a name of " << persons_name << '\n';
 
 p.print_name(); // print to console
 
 p.change_name("Alice Foo");
 
 p.print_name(); // print to console
 
 std::cout << p.get_name() << '\n';
    
 return 0;   
}


// imagine this is in Person.cpp 

Person::Person(const std::string& _name) : name(_name) {}
  
void Person::print_name() const{
 std::cout << name << '\n';   
}
  
void Person::change_name(const std::string& new_name){
 name = new_name;   
}

const std::string& Person::get_name() const{
    return name;
}
