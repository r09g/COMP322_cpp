#include <iostream>
#include <vector>
#include <iomanip>
#include "header.h"

using namespace std;

// This is a helper function that checks whether a cell is empty or not
// Input: 
//   int cellNbre: the cell number to check
//   char board[]: char pointer to pass in the board
// Output: boolean value with "true" for empty and "false" for occupied
bool cellEmpty(int cellNbre, char board[]) {
    // Occupied cells would either have "X" or "O"
    if(board[cellNbre] == 'X' || board[cellNbre] == 'O') {
        return false;
    } else {
        return true;
    }
}

// This is a helper function that plays a move and can be used by both
// the player and the computer. The board and the "lastmove" variable
// are both updated. This helps alleviate chances of forgetting to 
// update "lastmove".
// Input:  
//   int cellNbre: the cell number to place
//   char board[]: char pointer to pass in the board
//   bool player: "true" if the move is made by the player and "false"
//                if the move is made by the computer
// Output: None    
void makeMove(int cellNbre, char board[], bool player) {
    if(player == true){
        board[cellNbre] = 'X';
    } else {
        board[cellNbre] = 'O';
    }
    lastmove = cellNbre;
    return;
}

// This function is ran at the start of the program. It explains the
// instructions for playing the game to the player, and asks the 
// player whether they want to play. Upon receiving a response, the
// program either exits or runs.
// Input: None
// Output: None
void greetAndInstruct() {
    char space[] = "       ";  // used to separate the boards
    char play;  // stores the player's response

    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer." << endl << endl;
    cout << "The board is numbered from 1 to 27 as per the following:" << endl << endl;
    cout << " 1 |  2 |  3" << space << "10 | 11 | 12" << space << "19 | 20 | 21" << endl;
    cout << "------------" << space << "------------" << space << "------------" << endl;
    cout << " 4 |  5 |  6" << space << "13 | 14 | 15" << space << "22 | 23 | 24" << endl;
    cout << "------------" << space << "------------" << space << "------------" << endl;
    cout << " 7 |  8 |  9" << space << "16 | 17 | 18" << space << "25 | 26 | 27" << endl << endl;
    cout << "Player starts first. Simply input the number of cell you want to occupy. Player's move is marked with X. Computer's move is marked with O." << endl << endl;
    cout << "Start? (y/n): ";
    cin >> play;  // accepts player input indicating whether they want to play

    // Exits program if player selects anything other than "y" (not playing)
    if(play != 'y') {
        cout << endl;
        exit(EXIT_SUCCESS);
    }

    cout << endl;
}

// This function shows the updated board.
// Input:
//   char board[]: char pointer to pass in the board
// Output: None
void displayBoard(char board[]) {
    char space[] = "       ";  // used to separate the boards
    char divider[] = " | ";  // used as the inner border of each board
    
    // Iterates over all the values in board[] to print them out
    for(int i = 0; i < 27; i++) {   
        // sets the width of each element for better appearance
        cout << setw(2); // with of 2 characters

        // If the element is an "X" or "O" then print out as is
        // if it is a letter other than "X" or "O" then perform
        // ASCII conversion to obtain cell number. Note that "a"
        // corresponds to 96.
        if(board[i] == 'X' || board[i] == 'O'){
            cout << board[i];
        } else {
            cout << (int)(board[i]) - 96;
        }
        
        // Depending on certain cell numbers, space or newline may need to be
        // inserted.
        i++;  // cell number = index + 1. This helps in figuring out the logic
        if(i % 3 == 0) {  // cells that can mod 3 are on the right edge of board
            if(i == 21 || i == 24) {  // requires a newline and separation
                cout << endl;
                cout << "------------" << space << "------------" << space << "------------" << endl;
                i = i - 18;  // adjust cell number
            } else {  // cells other than 21 and 24 only need space and not newline
                cout << space;
                i = i + 6;  // adjust cell number
            } 
        } else {
            cout << divider;  // add divider to separate elements
        }
        i--;  // restore index
    }  
    cout << endl << endl;
}

// This function checks if the player's choice is legal. The function checks
// both the cell number and the cell's availability
// Input:
//   int cellNbre: the cell number the player selected
//   char board[]: char pointer to pass in the board
// Output: boolean value with "true" indicating the player's selection is 
//         legal and "false" indicating the selection is not legal
bool checkIfLegal(int cellNbre, char board[]) {
    cellNbre--;  // cell number = array index + 1
    // check if cell number is out of range
    if(cellNbre > 26 || cellNbre < 0) {
        cout << "Warning: invalid cell number." << endl << endl;
        return false;
    }
    // check if cell is already occupied
    if(cellEmpty(cellNbre, board) == false) {
        cout << "Warning: cell already occupied." << endl << endl;
        return false;
    }
    return true;
}

// This function uses the graph to determine whether there is a winner or
// tie that caused the game to end.
// Input:
//   char board[]: char pointer to pass in the board
// Output: boolean value with "true" indicating that the game has finished
//         and "false" indicating that there is no winner yet.
bool checkWinner(char board[]) {
    // based on the previous move, check the possible winning combinations
    int i = 0;
    for(auto e: graph[lastmove]) {  // iterate over combinations 
        if(*e == 0) {  // end of possible combinations
            break;
        } else {
            // cell that needs to be checked based on the constructed graph
            int index = graph[lastmove][i][0] - 1;  // array index of cell
            // check if the marker is the same at a possible cell
            if(board[index] == board[lastmove]) {  // check for second marker
                // note that for each combination, three markers need to be 
                // in a straight line. Thus, for each combination, with one 
                // checked, there is still another cell to check.
                index = graph[lastmove][i][1] - 1;  // update index
                if(board[index] == board[lastmove]) {  // check for third marker
                    // Passing both "if" statements mean that there are three
                    // markers in a straight line. Determine who won by marker.
                    if(board[index] == 'X') {
                        cout << "The game is over and the player won!" << endl;
                    } else {
                        cout << "The game is over and the computer won!" << endl;
                    }
                    return true;
                }
            }

        }
        i++;  // move to next combination if no result
    }

    // Tie is also a possibility. Iterate over board to see if all elements
    // are occupied. If so, then a tie results.
    bool finished = true;
    for(int i = 0; i < 27; i++) {
        if(board[i] != 'X' && board[i] != 'O') {
            finished = false;
            break;
        }
    }
    if(finished == true) {
        cout << "The game is over and resulted in a tie." << endl << endl;
        return true;
    }
    
    return false;
}

// This function implements the computer's strategy for making the next move.
// For the computer, there are 6 different types of ordered in terms of priority:
// 1. Initial move (if computer goes first): if cell 14 is not occupied, occupy 14
// 2. Winning move: if there is 1 move that allows computer to win
// 3. Imminent move: if there is 1 move that allows player to win
// 4. Cell 14: if the computer is not the first to go and cell 14 is unoccupied
// 5. Preferred Move: A winning combination where 2 out of 3 cells are still free
// 6. Random move: randomly choose an available cell
// Input:
//   char board[]: char pointer to pass in the board
// Output: None
void computerMove(char board[]) {
    
    // Type 1.
    if(lastmove == -1) {
        makeMove(13, board, false);  // array index = cell number - 1
        return;
    }

    // Type 2.
    vector<int> nextMove;  // stores preferred possible moves 
    // All current "O" markers are used as a starting point to traverse the graph
    // in order to find winning move
    for(int k = 0; k < 27; k++) {
        if(board[k] == 'O') {
            int i = 0;
            for(auto e: graph[k]) {  // iterate over all combinations for winning
                if(*e == 0) {
                    break;
                } else {
                    // Used for evaluation of non-winning moves. If in a straight
                    // line there is only 1 cell occupied and 2 empty, either of
                    // 2 cells are preferred if there is no winning move.
                    int score = 0;
                    // Check the first cell of the 2 possible cells that could 
                    // achieve 3 cells in a straight line (winning combination)
                    if(cellEmpty(graph[k][i][0] - 1, board) == true) {
                        // if it is available, check the third cell to see whether
                        // there is an "O" marker already. If so, then this is a 
                        // winning move and has the highest precedence.  
                        if(board[graph[k][i][1] - 1] == 'O') {
                            makeMove(graph[k][i][0] - 1, board, false);
                            return;
                        } else {
                            // if the third cell is occupied by opponent (player)
                            // then do not add score; otherwise add score
                            if(board[graph[k][i][1] - 1] == 'X') {
                                // No score added as it is already occupied by 
                                // opponent (player)
                            } else {
                                score++;  // if both cells are empty, 
                            }
                        }
                    }
                    // Perform the same check done above but in the reversed 
                    // sequence in case the first cell checked happens to be
                    // occupied
                    if(cellEmpty(graph[k][i][1] - 1, board) == true) {
                        if(board[graph[k][i][0] - 1] == 'O') {
                            makeMove(graph[k][i][1] - 1, board, false);
                            return;
                        } else {
                            if(board[graph[k][i][0] - 1] == 'X') {
                                
                            } else {
                                score++; 
                            }
                        }
                    }
                    // With a score of two, then in this winning combination,
                    // only 1 out of 3 cells are occupied. This is recommended
                    // and are stored.
                    if(score == 2) {
                        nextMove.push_back(graph[k][i][0] - 1);
                        nextMove.push_back(graph[k][i][1] - 1);
                    }
                }
                i++;  // next combination for the cell
            }
        }
    }

    // cout << endl << "Not winning move" << endl;

    // Type 3.
    // Based on previous move, iterate over all possible winning combinations
    // to check if there are any moves that allow the player to win directly,
    // that must be blocked.
    int i = 0;
    for(auto e: graph[lastmove]) {
        if(*e == 0) {
            break;
        } else {
            // Check if 1 out of the 2 possible cells in a winning combination
            // is occupied with "X".
            if(board[graph[lastmove][i][0] - 1] == board[lastmove]) {
                // 2 out of the 3 cells in a winning combination are occupied
                // by the player with "X". Check if the 3rd cell is available
                // to occupy and block the player
                if(cellEmpty(graph[lastmove][i][1] - 1, board) == true) {
                    makeMove(graph[lastmove][i][1] - 1, board, false);
                    return;
                }
            }
            // Perform the same check as above but on the other cell of the 2
            // possible cells in a winning combination
            if(board[graph[lastmove][i][1] - 1] == board[lastmove]) {
                if(cellEmpty(graph[lastmove][i][0] - 1, board) == true) {
                    makeMove(graph[lastmove][i][0] - 1, board, false);
                    return;
                }
            }

        }
        i++;  // next combination for the cell
    }

    // cout << endl << "Not imminent move" << endl;

    // Type 4.
    // Choosing the center cell is more advantageous than choosing a preferred
    // or random cell as there are 13 possible combinations to win for cell 14.
    if(cellEmpty(13, board) == true) {
        makeMove(13, board, false);
        return;
    }

    // Type 5.
    // If there is a preferred move available in the vector.
    if(nextMove.size() > 0) {
        int move = rand() % nextMove.size();  // any of the preferred move works
        if(move < 0 || move > nextMove.size() - 1) {  // ensure index in range
            move = 0;
        }
        makeMove(nextMove[move], board, false);
        return;
    } else {
        // Type 6.
        // No preferred move available. Look for unoccupied cells.
        for(int i = 0; i < 27; i++) {
            if(board[i] != 'X' && board[i] != 'O') {
                nextMove.push_back(i);
            }
        }
        // Randomly select one from vector.
        int move = rand() % nextMove.size();  // any of the preferred move works
        if(move < 0 || move > nextMove.size() - 1) {  // ensure index in range
            move = 0;  
        }
        makeMove(nextMove[move], board, false);
        return;
    }

    return;
}

// This function is for the player to make a move.
// Input: 
//   char board[]: char pointer to pass in the board
// Output: None
void playerMove(char board[]) {
    int move;  // store move
    // Ask for player to enter their move
    cout << "Player's turn to make a move. Please enter a valid cell number: ";
    cin >> move;  // store in variable
    cout << endl;
    
    bool legal = false;
    do {  // check and repeat until player input is legal
        if(checkIfLegal(move, board) == true) {
            legal = true;
        } else {
            // Ask again for player choice
            cout << "Please enter a valid cell number: ";
            cin >> move;
            cout << endl;
        }
    } while(legal == false);
    
    makeMove(move - 1, board, true);  // array index = cell number - 1;
}