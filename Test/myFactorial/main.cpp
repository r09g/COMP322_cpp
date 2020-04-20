#include <iostream>
#include <exception>

using namespace std;

class user_exception: public exception {
    virtual const char* what() const throw() {
        return "Negative number"; 
    }
};

user_exception negativeException;

class myFactorial{
    public:
        void factorial() {
            unsigned int num;
            cout << "Enter a non-negative number: ";
            cin >> num;
            unsigned int num_cpy = num;

            try{
                if(num < 0) {
                    throw negativeException;
                }
            } catch (exception& e) {
                cout << e.what() << endl;
                return;
            }

            unsigned int  result = 1;
            while(num > 0) {
                result *= num;
                num--;
            }
            cout << "The factorial of " << num_cpy << " is " << result << endl;
            return;
        }
};

class myEnhancedFactorial: public myFactorial {
    private:
        int values [6];

    public:
        void myEnhancedFactorial() {
            values[0] = 1;
            values[1] = 2;
            values[2] = 6;
            values[3] = 24;
            values[4] = 120;
            values[5] = 720;
        }

        void factorial() {
            unsigned int num;
            cout << "Enter a non-negative number: ";
            cin >> num;
            unsigned int num_cpy = num;

            try{
                if(num < 0) {
                    throw negativeException;
                }
            } catch (exception& e) {
                cout << e.what() << endl;
                return;
            }

            if(num <= 6) {
                // CONTINUE TO IMPLEMENT
            }

            unsigned int  result = 1;
            while(num > 0) {
                result *= num;
                num--;
            }
            cout << "The factorial of " << num_cpy << " is " << result << endl;
            return;
        }
}

int main(){

    myFactorial instance;
    instance.factorial();

}