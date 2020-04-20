#include <iostream>
#include <exception>

using namespace std;

class sizeException: public exception {
    virtual const char* what() const throw() {
        return "Size less than 1 not allowed";
    }
};

sizeException size_exception;

template <typename T>
class SmartAllocator {
    private:
        int memory_addr;
        int allocateMemory(int size){
            try{
                if(size < 1){
                    throw size_exception;
                }
                T* memory_addr = new T[size];
                return (int)memory_addr;
            } catch (exception& e) {
                cout << e.what() << endl;
            }
            return -1;
        }

    public:
        SmartAllocator() {
            this->memory_addr = allocateMemory(1);
        }

        SmartAllocator(int size) {
            this->memory_addr = allocateMemory(size);
        }

        ~SmartAllocator() {
            delete [] (T*)memory_addr;
        }

        getAddress() {
            return memory_addr;
        }
};

int main(){

    SmartAllocator<int> smart(-1);
    cout << smart.getAddress() << endl; 


}