#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

// functions declarations
void greetAndInstruct();
void displayBoard (char board[]);
bool checkIfLegal (int cellNbre, char board[]);
bool checkWinner(char board[]);
void computerMove(char board[]);

// greetings!
void greetAndInstruct() {
    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.\nThe board is numbered from 1 to 27 as per the following:" << endl;
    cout << "1 | 2 | 3        10 | 11 | 12        19 | 20 | 21" << endl;
    cout << "---------        ------------        ------------" << endl;
    cout << "4 | 5 | 6        13 | 14 | 15        22 | 23 | 24" << endl;
    cout << "---------        ------------        ------------" << endl;
    cout << "7 | 8 | 9        16 | 17 | 18        25 | 26 | 27" << endl;
    cout << "Player starts first. Simply input the number of the cell you want to occupy. Player’s move is marked with X. Computer’s move is marked with O." << endl;
    cout << "Start? (y/n): ";
}

// function to print the board with all formatting elements.
void displayBoard(char board[]) {
    for (int i = 0; i < 27; i++) {
        if (board[i] == 'n') {
            cout << i + 1;
            if (i == 20 || i == 23) {
                cout << "\n" << "---------       ------------       ------------\n";
                i -= 18;

            }
            else if ((i + 1) % 3 == 0) {
                cout << "       ";
                i += 6;
            }
            else {
                cout << " | ";
            }
        }

        else {
            if (i > 8) {
                cout << " ";
            }
            if (board[i] == 'X') {
                cout << "\033[1;31mX\033[0m";
            }
            else {
                cout << "\033[1;32mO\033[0m";
            }
            if (i == 20 || i == 23) {
                cout << "\n" << "---------       ------------       ------------\n";
                i -= 18;
            }
            else if ((i + 1) % 3 == 0) {
                cout << "       ";
                i += 6;
            }
            else {
                cout << " | ";
            }
        }
    }
}

bool checkIfLegal(int cellNbre, char board[]) {
    bool valid = true;
    if (cellNbre - 1 < 0 || cellNbre - 1 > 27) {
        valid = false;
        cout << "Illegal cell number for the move because it is out of range. Please input a different cell number: " << endl;
    }

    else if (board[cellNbre-1] != 'n') {
        valid = false;
        cout << "Illegal cell number for the move because it is occupied. Please input a different cell number: " << endl;
    }

    return valid;
}

bool checkWinner(char board[]) {
    bool winner;
    for (int i = 0; i < 27; i += 3) {
        // check for rows win in any table
        if (board[i] != 'n' && board[i] == board[i+1] && board[i] == board[i+2]) {
            winner = true;
        }
    }

    // check for columns win in any table
    for (int i = 0; i < 21; i++) {
        if (board[i] != 'n' && board[i] == board[i+3] && board[i] == board[i+6]) {
            winner = true;
        }

        if ((i + 1) % 3 == 0) {
            i += 6;
        }
    }

    // check for win in same spot from three table
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'n' && board[i] == board[i+9] && board[i] == board[i+18]) {
            winner = true;
        }
    }

    // check for rows win in any table
    for (int i = 0; i < 7; i += 3) {
        if (board[i] != 'n' && board[i] == board[i+10] && board[i] == board[i+20]) {
            winner = true;
        }
    }

    // check for columns win in any table
    for (int i = 0; i < 3; i++) {
        if (board[i] != 'n' && board[i] == board[i+12] && board[i] == board[i+24]) {
            winner = true;
        }
    }

    // check for first diagonal of first table
    if (board[0] != 'n' && board[0] == board[4] && board[0] == board[8]) {
            winner = true;
    }

    // check for second diagonal of first table
    if (board[2] != 'n' && board[2] == board[4] && board[2] == board[6]) {
            winner = true;
    }

    // check for first diagonal of second table
    if (board[9] != 'n' && board[9] == board[13] && board[9] == board[17]) {
            winner = true;
    }

    // check for second diagonal of second table
    if (board[11] != 'n' && board[11] == board[13] && board[11] == board[15]) {
            winner = true;
    }

    // check for first diagonal of third table
    if (board[18] != 'n' && board[18] == board[22] && board[18] == board[26]) {
            winner = true;
    }

    // check for second diagonal of third table
    if (board[20] != 'n' && board[20] == board[22] && board[20] == board[24]) {
            winner = true;
    }

    // check for first diagonal across all table
    if (board[0] != 'n' && board[0] == board[13] && board[0] == board[26]) {
            winner = true;
    }

    // check for second diagonal across all table
    if (board[20] != 'n' && board[20] == board[13] && board[20] == board[6]) {
            winner = true;
    }
    return winner;
}

void computerMove(char board[]) {
    for (int i = 0; i < 27; i++) {
        // initialize a new board to check for potential moves
        char newBoard[27];
        copy_n(board, 27, newBoard);
        if (newBoard[i] == 'n') {
            newBoard[i] = 'O';
        }

        // if new move is valid and a winning move
        if (checkWinner(newBoard)) {
            board[i] = 'O';
            return;
        }
    }

    for (int i = 0; i < 27; i++) {
        // initialize a new board to check for potential defensive moves
        char newBoard[27];
        copy_n(board, 27, newBoard);
        if (newBoard[i] == 'n') {
            newBoard[i] = 'X';
        }
        // if new move is valid and is a winning move for the player
        if (checkWinner(newBoard)) {
            board[i] = 'O';
            return;
        }
    }
    // random computer placement
    srand (time(NULL));
    while(true) {
        // generate secret number between 1 and 27
        int index = rand() % 27 + 1;
        if (board[index] == 'n') {
            board[index] = 'O';
            break;
        }
    }
}