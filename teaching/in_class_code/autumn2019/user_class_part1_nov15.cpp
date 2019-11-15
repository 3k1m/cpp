#include <iostream>
#include <string>
#include <vector>


class user{
private:
  // membervariables for
  // login name, their name, pass code, and friends

  std::string login, name;
  int pass_code;
  std::vector<user*> friends;    

public:
  
  // create user with login name, name, and a passcode of 0
  user( const std::string& _login, const std::string& _name) :
    login(_login), name(_name), pass_code(0) {}
    // the vector will be empty to start with
  
  // create user with login name, name, and a given passcode
  user( const std::string& _login, const std::string& _name,
    int _pass ) :
    login(_login), name(_name), pass_code(_pass) {}      
  
  // to update the password...
  void update_pass( int old_pass, int new_pass ) {
    if( old_pass == pass_code ) { // so know the correct code
      pass_code = new_pass; // can change the class!
    }
    else{ // gave wrong pass code
        std::cout << "Invalid current password!\n";
    }      
  }
  
  // mark as const b/c checking if a password is correct
  // does not modify the member variables of the class!
  bool check_pass( int pass ) const {
      return pass == pass_code;
  } 

};


int main()
{
  user alice("a123", "Alice");
  
  
  // can't update with wrong passcode
  alice.update_pass(1, 4);
  alice.update_pass(0, 4); // now correct passcode
  
  std::cout << std::boolalpha << alice.check_pass(4) << '\n';
  
}
