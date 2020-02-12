#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

void greetAndInstruct() {
    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.\n The board is numbered from 1 to 27 as per the following::" << endl;
    cout << "1 | 2 | 3      10 | 11 | 12        19 | 20 | 21" << endl;
    cout << "---------      ------------        ------------" << endl;
    cout << "4 | 5 | 6      13 | 14 | 15        22 | 23 | 24" << endl;
    cout << "---------      ------------        ------------" << endl;
    cout << "7 | 8 | 9      16 | 17 | 18        25 | 26 | 27" << endl;
    cout << "Player starts first. Simply input the number of the cell you want to occupy. Player’s move is marked with X. Computer’s move is marked with O." << endl;
    cout << "Start? (y/n): " << endl;
    cin >> response;

    if response == "n" {
        exit();
    }
}

void displayBoard(char board[]) {
    for (int i = 0; i < 27; i++) {
        if (board[i] == 'n') {
            cout << i + 1
            if ((i + 1) % 3 == 0) {
                cout << "\n"
            }

            if ((i + 1) % 9 == 0) {
                cout << "\n"
            }
            else {
                cout << " | "
            }
        }

        else {
            cout << board[i]
            if ((i + 1) % 3 == 0) {
                cout << "\n"
            }

            if ((i + 1) % 9) {
                cout << "\n"
            }
            else {
                cout << " | "
            }
        }
    }
}

bool checkIfLegal(int cellNbre, char board[]) {
    bool valid = true;
    if (cellNbre - 1 < 0 || cellNbre - 1 > 27) {
        bool valid = false;
        cout << "Illegal cell number for the move because it is out of range. Please input a different cell number: " << endl;
    }

    if (board[cellNbre] != 'n') {
        bool valid = false;
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

    for (int i = 0; i < 21; i++) {
        // check for columns win in any table
        if (board[i] != 'n' && board[i] == board[i+3] && board[i] == board[i+6]) {
            winner = true;
        }

        if ((i + 1) % 3 == 0) {
            i += 6
        }
    }

    // check for win in same spot from three table
    for (int i = 0; i < 9; i++) {
        if (board[i] == board[i+9] && board[i] == board[i+18]) {
            winner = true;
        }
    }

    for (int i = 0; i < 9; i += 3) {
        // check for rows win in any table
        if (board[i] != 'n' && board[i] == board[i+9] && board[i] == board[i+18]) {
            winner = true;
        }
    }

    for (int i = 0; i < 3; i++) {
        // check for columns win in any table
        if (board[i] != 'n' && board[i] == board[i+12] && board[i] == board[i+24]) {
            winner = true;
        }
    }

    // check for first diagonal of first table
    if (board[0] != 'n' && board[0] == board[4] && board[0] == board[8]) {
            winner = true;
    }

    // check for second diagonal of first table
    if (board[2] != 'n' && board[2] == board[4] && board[0] == board[6]) {
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
        char newBoard[27];
        copy_n(board, 27, newBoard);
        if (newBoard[i] == 'n') {
            newBoard[i] = 'O';
        }
        if (checkWinner(newBoard)) {
            board[i] = 'O';
            return;
        }
    }

    for (int i = 0; i < 27; i++) {
        char newBoard[27];
        copy_n(board, 27, newBoard);
        if (newBoard[i] == 'n') {
            newBoard[i] = 'X';
        }
        if (checkWinner(newBoard)) {
            board[i] = 'O'
            return;
        }
    }

    srand (time(NULL));
    while(true) {
        /* generate secret number between 1 and 27: */
        index = rand() % 27 + 1;
        if (board[index] == 'n') {
            board[index] = 'O';
            break;
        }
    }
}