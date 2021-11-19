/******************************************************************************
0. Write a struct PaymentTime that represents the total amount paid on a loan and the number of months 
to pay it off. It should simply store two member variables for the total payment and the number of months.
*******************************************************************************/

#include <iostream>

struct PaymentTime{
  double paid;
  int months;
};

/*
1. Write a Loan class that represents a loan. It should:
- store member variables for the balance owing, annual interest rate, monthly
payment, current month in the schedule, and the total amount paid
- have a constructor to initialize the member variables
- have a function to increase the balance through one month of interest 
- have a function to decrease the balance through a payment 
- have a function to advance a month (interest plus payment) 
- have a function to pay the loan that can be passed a bool (true to print 
the plan) and will compute the total amount paid on the loan and the total number of months, 
returning these as a PaymentTime
*/
class Loan{
private:
  double balance;
  double annual_interest_rate;
  double monthly_payment;
  double total_paid;
  int month;
  
  void print() const {
      std::cout << "month: " << month << 
        " --- balance: " << balance << '\n';
  }
  
  void accrue_interest(){
      const int compounds_per_year = 12;
      balance *= (1+annual_interest_rate/12);
  }
  
  void make_payment(){
      balance -= monthly_payment;
      total_paid += monthly_payment;
  }
  
  void advance_month(){
      accrue_interest();
      make_payment();
      
      if(balance<0){
          total_paid += balance;
          balance = 0;
      }
      
      ++month;
  }
  
public:
  Loan(double _balance, double _annual_interest_rate, double _monthly_payment) :
    balance(_balance), annual_interest_rate(_annual_interest_rate),
    monthly_payment(_monthly_payment), total_paid(0), month(0) {}
    
  PaymentTime pay_loan(bool print_payments=true) {
      while(balance>0){ // until loan is paid off 
          if(print_payments){
              print();
          }
          advance_month(); // interest + payment cycle 
      }
      if(print_payments){
        print();
      }
      PaymentTime res;
      res.paid = total_paid;
      res.months = month;
      return res;
  }
};

/*
2. Write a LoanSimulator class that simulates paying off a loan in various situations. It should:
- store member variables for the initial balance and annual interest rate
- have a constructor to initialize the member variables 
- have a function to compute the total payment and time, a PaymentTime, 
to pay off the loan given a monthly payment amount 
- have a function to change the annual interest rate 
- have a function to change the initial balance
- have a function to return the current annual interest rate 
- have a function to return the current initial balance
*/
class LoanSimulator{
private:
  double initial_balance;
  double annual_interest_rate;
  
public:
  LoanSimulator(double _initial_balance, double _annual_interest_rate) :
    initial_balance(_initial_balance), annual_interest_rate(_annual_interest_rate) {}
    
  void set_annual_interest(double r){
      annual_interest_rate = r;
  }
  
  void set_initial_balance(double b){
      initial_balance = b;
  }
  
  double get_annual_interest() const {
      return annual_interest_rate;
  }
  
  double get_initial_balance() const {
      return initial_balance;
  }
  
  /**
   * This computes a total paid and time for a loan situation
   * @param monthly_payment the amount paid per month
   * @return a PaymentTime for the loan based on the rate and balance of the class 
   */ 
  PaymentTime compute_total_payment(double monthly_payment) const {
      Loan current(initial_balance, annual_interest_rate, monthly_payment);
      return current.pay_loan(false); // no printing, returns the value needed 
  }
  
};


int main()
{
    //  double _balance, double _annual_interest_rate, double _monthly_payment
    const double balance = 1000;
    const double rate = 0.05;
    const double payment = 200;
    
   Loan joe(balance, rate, payment);
    
   PaymentTime p = joe.pay_loan();
   
   std::cout << p.paid << ' ' << p.months << '\n';
   
   const double balance2 = 2000;
    const double rate2 = 0.07;
    const double payment2 = 350;
    
    LoanSimulator sim(balance2, rate2);
    
    sim.set_initial_balance(2500);
    
    PaymentTime p2 = sim.compute_total_payment(payment2);
    
    std::cout << p2.paid << ' ' << p2.months << '\n';

    return 0;
}
