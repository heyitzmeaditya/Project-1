#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    int size;
    char currentPlayer;
    string playerXName, playerOName;
    int scoreX, scoreO;
    bool gameRunning;

public:
    TicTacToe(int boardSize) {
        size = boardSize;
        board.resize(size, vector<char>(size));
        initializeBoard();
        scoreX = 0;
        scoreO = 0;
        gameRunning = true;
    }

    // Initialize the board with numbers 1 to size*size
    void initializeBoard() {
        int position = 1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = '0' + position;
                position++;
            }
        }
    }

    // Display the current board state
    void displayBoard() {
        cout << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << " " << board[i][j];
                if (j < size - 1) cout << " |";
            }
            if (i < size - 1) {
                cout << endl;
                for (int k = 0; k < size * 4 - 1; k++) cout << "-";
                cout << endl;
            }
        }
        cout << endl;
    }

    // Make a move based on player's input
    bool makeMove(int position) {
        int row = (position - 1) / size;
        int col = (position - 1) % size;

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
            return true;
        }
        return false;
    }

    // Check if the current player has won
    bool checkWin() {
        // Check rows and columns
        for (int i = 0; i < size; i++) {
            if (checkRow(i) || checkCol(i)) {
                return true;
            }
        }
        // Check diagonals
        if (checkDiagonal() || checkAntiDiagonal()) {
            return true;
        }

        return false;
    }

    bool checkRow(int row) {
        for (int i = 1; i < size; i++) {
            if (board[row][i] != board[row][0]) return false;
        }
        return true;
    }

    bool checkCol(int col) {
        for (int i = 1; i < size; i++) {
            if (board[i][col] != board[0][col]) return false;
        }
        return true;
    }

    bool checkDiagonal() {
        for (int i = 1; i < size; i++) {
            if (board[i][i] != board[0][0]) return false;
        }
        return true;
    }

    bool checkAntiDiagonal() {
        for (int i = 1; i < size; i++) {
            if (board[i][size - i - 1] != board[0][size - 1]) return false;
        }
        return true;
    }

    // Check if the board is full (to determine a draw)
    bool isBoardFull() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    return false;
                }
            }
        }
        return true;
    }

    // Switch to the other player
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Ask if the player wants to start first
    void askStartingPlayer() {
        char choice;
        cout << "Do you want to start first? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            currentPlayer = 'X';
        } else {
            currentPlayer = 'O';
        }
    }

    // Ask the player to make a move or quit
    void askForMove() {
        int move;
        bool validMove = false;

        while (!validMove && gameRunning) {
            cout << (currentPlayer == 'X' ? playerXName : playerOName) << " (" << currentPlayer << "), enter the number of the cell where you want to place your mark (or 0 to quit): ";
            cin >> move;

            if (move == 0) {
                cout << (currentPlayer == 'X' ? playerXName : playerOName) << " has quit the game." << endl;
                gameRunning = false;
                return;
            }
            if (move >= 1 && move <= size * size) {
                validMove = makeMove(move);
                if (!validMove) {
                    cout << "Invalid move. The cell is already occupied. Try again." << endl;
                }
            } else {
                cout << "Invalid move. Please enter a number between 1 and " << size * size << "." << endl;
            }
        }
    }

    // Set player names
    void setPlayerNames() {
        cout << "Enter the name for player X: ";
        cin >> playerXName;
        cout << "Enter the name for player O: ";
        cin >> playerOName;
    }
    // Play the game
    void playGame() {
        bool gameWon = false;
        setPlayerNames();
        askStartingPlayer();

        while (gameRunning) {
            initializeBoard();
            gameWon = false;

            while (!gameWon && !isBoardFull() && gameRunning) {
                displayBoard();
                askForMove();
                if (!gameRunning) break;

                if (checkWin()) {
                    displayBoard();
                    cout << (currentPlayer == 'X' ? playerXName : playerOName) << " wins!" << endl;
                    if (currentPlayer == 'X') scoreX++;
                    else scoreO++;
                    gameWon = true;
                } else if (isBoardFull()) {
                    displayBoard();
                    cout << "The game is a draw!" << endl;
                } else {
                    switchPlayer();
                }
            }

            displayScore();
            if (!askReplay()) break;
        }
    }

    // Display the score
    void displayScore() {
        cout << "\nScore:\n" << playerXName << " (X): " << scoreX << " | " << playerOName << " (O): " << scoreO << endl;
    }
    // Ask the players if they want to play again
    bool askReplay() {
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        return choice == 'y' || choice == 'Y';
    }
};

int main() {
    int boardSize;
    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Enter the board size (e.g., 3 for 3x3, 4 for 4x4): ";
    cin >> boardSize;

    TicTacToe game(boardSize);
    game.playGame();

    return 0;
}
