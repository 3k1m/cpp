#include<string>
#include<iostream>

// the work and documentation here are very rough
// see course notes for more details

class pet{
private:
  std::string name;
  
public:
  pet(std::string _name) : name(std::move(_name)) {}
  
  // virtual ==> derived classes can give
  // their own rendition of the function
  virtual void talk() const = 0;
  // = 0 ==> derived classes to be 'non-abstract'
  // must define this function  
  
  // always have virt dtor for inheritance base class
  virtual ~pet() = default; // "do the normal thing"
  
  // more efficient to return as ref to const for an object here
  const std::string& get_name() const {
	  return name;
  }
  
  // copy and move ctors
  pet(const pet&) = default;
  pet(pet&&) noexcept = default;
  
  // noexcept tells compiler function will not throw
  // an exception, helps with optimization
  
  // copy and move assignent
  pet& operator=(const pet&) = default;
  pet& operator=(pet&&) noexcept = default;

};

// cat inherits from pet *public*ly
class cat : public pet{
private:
	bool short_hair;
public:	
	cat(std::string _name, bool _short_hair) :
		pet(std::move(_name)), short_hair(_short_hair) {}
	// gotta invoke the base class ctor first!
		
	// giving the cat class its version of talk
	// class is no longer abstract
	void talk() const override {
		std::cout << "meow\n";
	}
	// override ==> tells compiler we intend to be overriding
	// a virtual function
	
	bool has_short_hair() const {
		return short_hair;
	}	
};

class dog : public pet{
public:
	dog(std::string _name) : pet(std::move(_name)) {}
	
	void talk() const override{		
		std::cout << "woof\n";
	} 	
};

// polymorphism: take in pointer or reference to base class
// can pass pointer or reference to derived classes

void make_talk(const pet& p){
	p.talk();
}

void make_talk(const pet* p){
	p->talk();
}

int main(){
	cat c("Molly",true);
	std::cout << c.get_name() << " says "; 
	c.talk();
	std::cout << "it is " << std::boolalpha <<
	 c.has_short_hair() << " that the cat has " <<
	 " short hair ";
	dog d("Achie");
	make_talk(c);
	make_talk(d);
	make_talk(&c);
	make_talk(&d);

	return 0;	
}
