#include <bits/stdc++.h>
using namespace std;

class Position {
public:
    int x, y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class Food {
private:
    Position pos;

public:
    Food(int width, int height) {
        generate(width, height);
    }

    void generate(int width, int height) {
        pos.x = rand() % width;
        pos.y = rand() % height;
    }

    Position getPosition() {
        return pos;
    }
};

class Snake {
private:
    deque<Position> body;

public:
    Snake() {
        body.push_back(Position(5, 5));
    }

    Position getHead() {
        return body.front();
    }

    void move(char direction) {
        Position head = getHead();

        if (direction == 'U') head.y--;
        if (direction == 'D') head.y++;
        if (direction == 'L') head.x--;
        if (direction == 'R') head.x++;

        body.push_front(head);
        body.pop_back();
    }

    void grow() {
        body.push_back(body.back());
    }

    bool selfCollision() {
        Position head = getHead();
        for (int i = 1; i < body.size(); i++) {
            if (body[i] == head)
                return true;
        }
        return false;
    }

    bool occupies(Position p) {
        for (auto& part : body) {
            if (part == p) return true;
        }
        return false;
    }

    deque<Position> getBody() {
        return body;
    }
};

class Board {
private:
    int width, height;

public:
    Board(int w, int h) : width(w), height(h) {}

    bool isWallCollision(Position p) {
        return p.x < 0 || p.y < 0 || p.x >= width || p.y >= height;
    }

    void draw(Snake& snake, Food& food) {
        system("cls"); // use "clear" on Linux/Mac

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Position p(x, y);

                if (p == food.getPosition())
                    cout << "F ";
                else if (snake.occupies(p))
                    cout << "S ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }
};

class Game {
private:
    Board board;
    Snake snake;
    Food food;
    bool gameOver;

public:
    Game() : board(10, 10), food(10, 10) {
        gameOver = false;
    }

    void run() {
        char direction = 'R';

        while (!gameOver) {
            board.draw(snake, food);

            cout << "\nMove (U/D/L/R): ";
            cin >> direction;

            snake.move(direction);

            if (board.isWallCollision(snake.getHead()) || snake.selfCollision()) {
                cout << "Game Over!\n";
                break;
            }

            if (snake.getHead() == food.getPosition()) {
                snake.grow();
                food.generate(10, 10);
            }
        }
    }
};

int main() {
    srand(time(0));
    Game game;
    game.run();
    return 0;
}
