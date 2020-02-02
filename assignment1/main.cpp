#include <iostream>
#include <cstdlib>
#include <ctime>
#include "functions.cpp"
#include "header.h"

using namespace std;

// Records the previous move in index (cellnumber - 1). This will be used to check for
// winners and find optimal strategy for computer's next move
volatile int lastmove = -1;

// Constructed graph of all possible winning configurations based on the previous move. 
// This graph is used in determining whether there is a winner and the computer's next
// move. With this graph, it is much faster to traverse it and find optimal strategy or
// check for winner, at the cost of more memory. The comment on the right indicates the
// previous cell occupied
int graph[27][13][2] = {
    {{2,3},{5,9},{4,7},{10,19},{11,21},{14,27},{13,25}},    // 1
    {{1,3},{5,8},{11,20},{14,26}},                          // 2
    {{2,1},{5,7},{6,9},{12,21},{11,19},{14,25},{15,27}},    // 3
    {{1,7},{5,6},{13,22},{14,24}},                          // 4
    {{1,9},{2,8},{3,7},{4,6},{14,23}},                      // 5
    {{4,5},{3,9},{15,24},{14,22}},                          // 6
    {{1,4},{3,5},{8,9},{13,19},{14,21},{17,27},{16,25}},    // 7
    {{2,5},{7,9},{16,25},{14,20}},                          // 8
    {{7,8},{3,6},{1,5},{18,27},{17,25},{15,21},{14,19}},    // 9
    {{13,16},{11,12},{14,18},{1,19}},                       // 10
    {{10,12},{14,17},{2,20},{1,21},{3,19}},                 // 11
    {{10,11},{14,16},{15,18},{3,21}},                       // 12
    {{10,16},{14,15},{4,22},{1,25},{7,19}},                 // 13
    {{10,18},{11,17},{12,16},{13,15},{5,23},{2,26},{8,20},
    {4,24},{6,22},{1,27},{3,25},{7,21},{9,19}},             // 14
    {{13,14},{12,18},{6,24},{3,27},{9,21}},                 // 15
    {{10,13},{12,14},{17,18},{7,25}},                       // 16
    {{16,18},{11,14},{8,26},{7,27},{9,25}},                 // 17
    {{16,17},{10,14},{12,15},{9,27}},                       // 18
    {{22,25},{23,27},{20,21},{1,10},{14,9},{13,7},{11,3}},  // 19
    {{19,21},{23,26},{2,11},{8,14}},                        // 20
    {{19,20},{23,25},{24,27},{7,14},{1,11},{9,15},{3,12}},  // 21
    {{19,25},{23,24},{4,13},{14,6}},                        // 22
    {{19,27},{20,26},{21,15},{22,24},{5,14}},               // 23
    {{21,27},{22,23},{6,15},{4,14}},                        // 24
    {{19,22},{21,23},{26,27},{7,16},{1,13},{9,17},{3,14}},  // 25
    {{25,27},{20,23},{8,17},{2,14}},                        // 26
    {{21,24},{19,23},{25,26},{9,18},{7,17},{3,15},{1,14}}   // 27  
};

// Main function
int main() {
    
    // initializes the random number generator by providing it a seed based on the 
    // current time
    srand(time(NULL));

    greetAndInstruct();  // greet player

    // Initialize board. The board is a 1 x 27 character array to represent cell
    // numbers from 1 to 27. Alphabetical letter are used as they can represent 
    // two digit numbers in 1 char. Note that "z" has ASCII code 122 and "{" has 
    // ASCII code 123. "{" is used for ease of coding the functions. 
    char board[] = "abcdefghijklmnopqrstuvwxyz{";
    
    int turn = 0;  // records the number of turn
    
    // while loop to run the game and alternate turns between player and computer
    while(true) {
        // player's turn
        turn++;
        playerMove(board);  // player places 'X'
        cout << "At turn " << turn << ": Player played 'X' on cell " << lastmove + 1 << endl << endl;
        displayBoard(board);  // display the updated state of the board
        if(checkWinner(board) == true) {  // check if game ended
            break;  // exit the infinite while loop if game ended
        }
        // computer's turn
        turn++;
        computerMove(board);  // computer places 'O'
        cout << "At turn " << turn << ": Computer played 'O' on cell " << lastmove + 1 << endl << endl;
        displayBoard(board);  // display the updated state of the board
        if(checkWinner(board) == true) {  // check if game ended
            break;  // exit the infinite while loop if game ended
        }
    }
    
    return EXIT_SUCCESS;
}