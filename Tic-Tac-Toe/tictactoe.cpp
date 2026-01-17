#include <bits/stdc++.h>
using namespace std;

// ---------- PLAYER ----------
class Player {
private:
    string name;
    char symbol;

public:
    Player(string n, char s) {
        name = n;
        symbol = s;
    }

    char getSymbol() {
        return symbol;
    }

    string getName() {
        return name;
    }
};

// ---------- BOARD ----------
class Board {
private:
    vector<vector<char>> grid;
    int size;

public:
    Board(int n = 3) {
        size = n;
        grid = vector<vector<char>>(size, vector<char>(size, ' '));
    }

    bool placeSymbol(int row, int col, char symbol) {
        if (row < 0 || col < 0 || row >= size || col >= size)
            return false;

        if (grid[row][col] != ' ')
            return false;

        grid[row][col] = symbol;
        return true;
    }

    bool isFull() {
        for (auto &row : grid) {
            for (char cell : row) {
                if (cell == ' ')
                    return false;
            }
        }
        return true;
    }

    bool checkWin(char symbol) {
        // Check rows
        for (int i = 0; i < size; i++) {
            bool win = true;
            for (int j = 0; j < size; j++) {
                if (grid[i][j] != symbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        // Check columns
        for (int j = 0; j < size; j++) {
            bool win = true;
            for (int i = 0; i < size; i++) {
                if (grid[i][j] != symbol) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        // Check main diagonal
        bool win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][i] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;

        // Check anti-diagonal
        win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][size - i - 1] != symbol) {
                win = false;
                break;
            }
        }
        return win;
    }

    void display() {
        cout << "\nBoard:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << grid[i][j];
                if (j < size - 1) cout << " | ";
            }
            cout << endl;
            if (i < size - 1)
                cout << "--+---+--\n";
        }
        cout << endl;
    }
};

// ---------- GAME ----------
class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool gameOver;

public:
    Game(Player* p1, Player* p2) {
        player1 = p1;
        player2 = p2;
        currentPlayer = player1;
        gameOver = false;
    }

    void playTurn(int row, int col) {
        if (!board.placeSymbol(row, col, currentPlayer->getSymbol())) {
            cout << "Invalid move. Try again.\n";
            return;
        }

        board.display();

        if (board.checkWin(currentPlayer->getSymbol())) {
            cout << currentPlayer->getName() << " wins!\n";
            gameOver = true;
            return;
        }

        if (board.isFull()) {
            cout << "Game Draw!\n";
            gameOver = true;
            return;
        }

        switchPlayer();
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }

    bool isGameOver() {
        return gameOver;
    }

    Player* getCurrentPlayer() {
        return currentPlayer;
    }
};

// ---------- MAIN ----------
int main() {
    Player p1("Player 1", 'X');
    Player p2("Player 2", 'O');

    Game game(&p1, &p2);

    cout << "Tic Tac Toe Game Started!\n";
    cout << "Enter row and column (0-based index)\n";

    while (!game.isGameOver()) {
        int row, col;
        cout << game.getCurrentPlayer()->getName()
             << " (" << game.getCurrentPlayer()->getSymbol() << ") turn: ";
        cin >> row >> col;

        game.playTurn(row, col);
    }

    cout << "Game Over.\n";
    return 0;
}
