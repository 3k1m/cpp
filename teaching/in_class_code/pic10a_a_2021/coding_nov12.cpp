#include <iostream>

/*
1. Write...
a) A function compound_interest compounds interest upon a balance owing from one month to the next. It should:
- take in a balance b,
- and an annual interest rate r based on 12 compounding periods per year 
- and updates b to b*(1+r/12) 
(the argument b should be updated)
*/
void compound_interest(double& b, const double r){
    const int compounds_per_yr = 12;
    b *= (1+r/compounds_per_yr);
}

/*
b) A function pay_installment that updates a balance owing through making a payment. It should:
- take in a balance b 
- a payment amount p 
- and decreases b by p 
(the argumennt b should be updated)
*/
void pay_installment(double& balance, const double payment){
    balance -= payment;
}

/*
c) A function advance_month that updates a balance owing from one month to the next. It should:
- take in a balance b 
- an annual interest rate r 
- a payment amount p 
- and update the balance by first compounding the interest and then deducting for the payment 
(the argument b should be updated)
*/
void advance_month(double& b, const double r, const double p){
    compound_interest(b,r);
    pay_installment(b,p);
}

/*
d) A function compute_payment_plan that illustrates the amount to be paid monthly to pay off a loan.
It should:
- take in a balance b 
- an annual interest rate r 
- a monthly payment amount p 
- and print, month by month, how much is paid and owed until the balance is paid off 
- and it should return the total amount paid over all months

$70 payments...
100->101->31
31->31.31 < 70 (final payment should be 31.31)
*/
double balance_from_interest_next_month(const double b, const double r){
    const int compounds_per_yr = 12;
    return b*(1+r/compounds_per_yr);
}

double compute_payment_plan(double balance, const double rate, const double payment){
    double total_amount_paid = 0;
    int month = 0;
    std::cout << "Month " << month << ". Balance: $" << balance << '\n';
    ++month;
    while(balance>0){ // until it is fully paid off...
        std::cout << "Month " << month << ": ";
        
        advance_month(balance, rate, payment);
        double amount_paid = payment;
        if(balance<0){ // so fully paid off...
            amount_paid = payment + balance;
            balance = 0;
        }
        total_amount_paid += amount_paid;
        
        std::cout << "Balance: " << balance << ". Paid: $" << amount_paid
            << '\n';
        ++month;
    }
    return total_amount_paid;
}


class Loan{
private:
  double balance;
  double rate, payments;

public:
};

int main()
{
    const double loan = 100;
    const double rate = 0.12;
    const double payments = 70;
    
    double total_paid = compute_payment_plan(loan,rate,payments);
    
    std::cout << "paid a total of: " << total_paid << '\n';
    
    //Loan computer(1500, 0.2);
    // work towards having a class taht can 
    // produce hypothetical total payments for a given 
    // loan situation which can be used in a function 
    // to evaluate different loan options ...
    //double tot_paid = computer.payment_plan();
    
    //double bal = 100;
    //const double r = 0.12;
    //compound_interest(bal,r);
    
    //std::cout << bal << '\n'; // 101

    return 0;
}
