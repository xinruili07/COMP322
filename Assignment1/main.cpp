#include <iostream>
#include "functions.cpp"
using namespace std;

int main() {
    // greet and take response
    greetAndInstruct();
    string response;
    cin >> response;

    while (response != "n" && response != "y") {
        cout << "Unrecognized response. Enter y/n: ";
        cin >> response;
    }

    // exits if no
    if (response == "n") {
            return 0;
    }

    // create new board for new game
    char board[27];
    for (int i = 0; i < 27; i++) {
        board[i] = 'n';
    }
    int moves = 0;
    
    // if there are 27 moves, that means the game is a tie
    while (!checkWinner(board) && moves <= 27) {
        int cellNb;
        cout << "Enter the number of the cells you wanna occupy: ";
        cin >> cellNb;
        // if not an integer
        if (cin.fail()){
            cout << "Please enter an integer. ";
            // clear error state
            cin.clear();
            // discard 'bad' character(s)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // reprompt the user while the move stays invalid
        while (!checkIfLegal(cellNb, board)) {
            cin >> cellNb;
            // if not an integer
            if (cin.fail()){
                cout << "Please enter an integer. ";
                // clear error state
                cin.clear();
                // discard 'bad' character(s)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        board[cellNb-1] = 'X';
        moves++;
        displayBoard(board);
        cout << "\n";
        if (checkWinner(board)) {
            cout << "You won!\n";
            break;
        }
        cout << "\n";
        if (moves == 27) {
            cout << "The game ends in a tie! Try again...";
            break;
        }
        computerMove(board);
        moves++;
        cout << "After computer's move:\n";
        displayBoard(board);
        cout << "\n";
        if (checkWinner(board)) {
            cout << "You lost...\n";
            break;
        }
        cout << "\n";
    }
}