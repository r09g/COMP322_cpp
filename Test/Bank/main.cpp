#include <iostream>
#include <exception>

using namespace std;

class NA_exception: public exception {
    virtual const char* what() const throw() {
        return "Amount cannot be negative";
    }
};

class NB_exception: public exception {
    virtual const char* what() const throw() {
        return "Balance cannot be negative after withdrawal";
    }
};

NA_exception negativeAmount;
NB_exception negativeBalance;

class BankAccount {
    public:
        double balance;

        virtual void deposit(double amount) = 0;
        virtual void withdrawal(double amount) = 0;
        void getBalance(){
            cout << "The current balance is: " << balance << endl;
        }
};

class ChequingAccount: public BankAccount {
    public:
        ChequingAccount() {
            this->balance = 0;
        }
        void deposit(double amount) {
            try{
                if(amount < 0){
                    throw negativeAmount;
                }
            } catch(exception& e) {
                cout << e.what() << endl;
                return;
            }

            if(this->balance + amount < 3000) {
                this->balance = this->balance + amount - 5;
                if(this->balance < 0){
                    this->balance = 0;
                    cout << "Deposit complete. Transaction fee: $5" << endl;
                }
            } else {
                this->balance += amount;
                cout << "Deposit complete. Transaction fee waived" << endl;
            }

        }
        void withdrawal(double amount) {
            try{
                if(this->balance - amount < 0 || (this->balance - amount - 5 < 0 && this->balance - amount < 3000)){
                    throw negativeBalance;
                }
            } catch(exception& e) {
                cout << e.what() << endl;
                return;
            }

            if(this->balance - amount < 3000) {
                this->balance = this->balance - amount - 5;
                if(this->balance < 0){
                    this->balance = 0;
                }
                cout << "withdrawal complete. Transaction fee: $5" << endl;
            } else {
                this->balance -= amount;
                cout << "withdrawal complete. Transaction fee waived" << endl;
            }

        }
};

class SavingsAccount: public BankAccount {
    public:
        SavingsAccount() {
            this->balance = 0;
        }
        void deposit(double amount) {
            try{
                if(amount < 0){
                    throw negativeAmount;
                }
            } catch(exception& e) {
                cout << e.what() << endl;
                return;
            }

            if(amount > 1000) {
                this->balance = this->balance + 1.03 * amount;
                cout << "Deposit complete. Cashback: 3%" << endl;
            } else {
                this->balance += amount;
                cout << "Deposit complete." << endl;
            }

        }
        void withdrawal(double amount) {
            try{
                if(this->balance - amount < 3000){
                    throw negativeBalance;
                }
            } catch(exception& e) {
                cout << e.what() << endl;
                return;
            }

            this->balance -= amount;
            cout << "Withdrawal complete." << endl;
        
        } 
};

int main() {

    ChequingAccount acc1;
    acc1.deposit(5000);
    acc1.withdrawal(1000);
    acc1.getBalance();

    SavingsAccount acc2;
    acc2.deposit(5000);
    acc2.getBalance();
    
}