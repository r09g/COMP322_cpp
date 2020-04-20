#include <iostream>
#include <cstring>

using namespace std;

class Utility{
    public:
        int countLetter();
};

int Utility::countLetter(){
    string str;
        char letter;
        int count = 0;

        cout << "Enter a sentence: ";
        cin >> str;

        cout << "\nEnter a letter: ";
        cin >> letter;

        int length = str.length();
        char char_array[length + 1];
        strcpy(char_array, str.c_str());

        for (int i = 0; i < length; i++){
            if(letter == char_array[i]) {
                count++;
            }
        }
        cout << count << endl;
        return count;
}

int main(){
    Utility util;
    util.countLetter();
}