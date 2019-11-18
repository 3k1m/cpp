#include <iostream>
#include <string>
#include <vector>


class user{
private:
  // membervariables for
  // login name, their name, pass code, and friends

  std::string login, display;
  int pin;
  std::vector<const user*> friends;    

public:
  
  // create user with login name, name, and a passcode of 0
  user( const std::string& _login, const std::string& _display) :
    login(_login), display(_display), pin(0) {}
    // the vector will be empty to start with
  
  // create user with login name, name, and a given passcode
  user( const std::string& _login, const std::string& _display,
    int _pin );     
  
  // to update the password...
  void update_pin( int old_pin, int new_pin ) {
    if( old_pin == pin ) { // so know the correct code
      pin = new_pin; // can change the class!
    }
    else{ // gave wrong pass code
        std::cout << "Invalid current password!\n";
    }      
  }
  
  // mark as const b/c checking if a password is correct
  // does not modify the member variables of the class!
  bool check_pin( int pass ) const {
      return pass == pin;
  } 
    
  const std::string& get_name() const{
    return display;   // display here is Lvalue - do not copy it!
  }
  
  void add_friend( user& other );
  
  bool is_friend( const user& other ) const;

};


int main()
{
  user alice("a123", "Alice");
  
  
  // can't update with wrong passcode
  alice.update_pin(1, 4);
  alice.update_pin(0, 4); // now correct passcode
  
  user bob("b456", "Bob", 111);
  user connie("c456", "Connie Foo", 9999);
  
  std::cout << std::boolalpha << alice.check_pin(4) << '\n';
  
  std::cout << alice.get_name() << '\n';
  
  alice.add_friend(bob);
  
  //alice.friends.pop_back();
  
  std::cout << "check friendships: \n";
  
  std::cout << alice.is_friend(bob) << '\n';
  std::cout << bob.is_friend(alice) << '\n';
  std::cout << alice.is_friend(connie) << '\n';
  
}


user::user( const std::string& _login, const std::string& _display,
    int _pin ) :
    login(_login), display(_display), pin(_pin) {}
    
    
void user::add_friend( user& other ){
 // avoid duplicates so check if already there
 
 auto it = std::begin(friends);
 
 for(/* empty */; it != std::end(friends); ++it){
  if( *it == &other ) { // duplicate
      return; // do not add again
  }     
 }
 
 if( it == std::end(friends) ){ // made it through, no duplicates
     friends.push_back( &other );
     
     // add this user to the other's friends     
     other.friends.push_back( this );
 } 
    
}



bool user::is_friend( const user& other ) const{
  
 auto it = std::begin(friends);
 
 for(/* empty */; it != std::end(friends); ++it){
  if( *it == &other ) { // address is found
      return true; // do not add again
  }     
 } 
 
 return false;
    
}
