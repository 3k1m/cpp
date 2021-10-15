#include <iostream>
#include <string>

/*
1. Identify the lines of code below that will not compile. Ignoring those that do not, determine the values of x, y, z, a, b, c, and d.

int x = 7;
const int y = 8;
std::string z = "abc";

int& a = 1; // no! can't make int& out of rvalue
int& b = x; // fine: so b and x are the same entity
int& c = y; // bad: making reference to non-const int out of a const int

const std::string& d = z; // okay: d and z will reference the same std::string. changes to 'd' itself will not be allowed

++a; // a can't be defined -- see above
++b; // b and x both become 8
++c; // c can't be defined -- see above
z[2] = 'C'; // z AND d become "abC"
*/

/*
2. This problem makes use of a cash box class whose interface can be found here: cpp.sh/9xfos

For simplicity we assume that all inputs will be valid.

a) Write a main routine that:

i) Creates a cash box with an initial balance of $0.
ii) Adds $25 to the cash box.
iii) Removes $20 from the cash box.
iv) Computes the amount in the cash box.

b) Repeat the exercise with the cash box starting off with $30 as it is being constructed.
*/

class CashBox{
public:
  /**
   * makes a CashBox starting with a balance of $0    
  */
  CashBox();
  
  /**
   * makes a CashBox starting with an initial balance in dollars
   * @param init_balance the initial balance
  */
  CashBox(double init_balance);
  
  /**
   * deposits value dollars
   * @param value the value to insert
  */
  void deposit(double value);
  
  /**
   *  removes value dollars
   * @param value the value to withdraw
  */
  void withdraw(double value);
  
   /**
   *  gives the balance in the box
   * @return the balance
  */
  double getBalance() const;  
  
private:
  double balance;  
};

int main()
{
   /*
   a) Write a main routine that:

   i) Creates a cash box with an initial balance of $0.
   ii) Adds $25 to the cash box.
   iii) Removes $20 from the cash box.
   iv) Computes the amount in the cash box.
   */
   CashBox box; // (i)
   box.deposit(25); // (ii)
   box.withdraw(20); // (iii)
   
   // (iv)
   std::cout << "There are $" << box.getBalance() << '\n';
   
   /* b) Repeat the exercise with the cash box starting off with $30 as it is being constructed. */
   
   CashBox box2 = 30; // (i) correct but a bit strange
   CashBox box3(30); // (i) a CashBox named box3 is constructed by using the value 30
   CashBox box4 = CashBox(30); // (i) less direct construction than above
   
   //CashBox(30); -- just a CashBox with $30 then it goes away
   //std::string(); -- empty string made and then goes away
   
   box3.deposit(25); // (ii)
   box3.withdraw(20); // (iii)
   
   // (iv)
   std::cout << "There are $" << box3.getBalance() << '\n';
   
  
  return 0;
}

  // definitions that can be ignored for now

  CashBox::CashBox() : balance(0) {}
  
  CashBox::CashBox(double init_balance) : balance(init_balance) {}

  void CashBox::deposit(double value) {
   balance += value;   
  }
  
  void CashBox::withdraw(double value){
    balance -= value;   
  }
  
  double CashBox::getBalance() const{
     return balance;   
  }
