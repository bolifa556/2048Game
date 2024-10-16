#include "../include/GameBoard.h"
#include <algorithm>
#include <random>
#include <chrono>

GameBoard::GameBoard() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator = std::mt19937(seed);
    reset();
}

void GameBoard::reset() {
    // Initialize the board to be 4x4 with all values set to 0
    board = Board(4, std::vector<int>(4, 0));
    std::uniform_int_distribution<int> dist(0, 3);  // [0, 3] uniform distribution
    std::uniform_int_distribution<int> value_dist(0, 1);

    // Add two initial tiles
    for (int i = 0; i < 2; ++i) {
        int x = dist(generator);
        int y = dist(generator);
        while (board[x][y] != 0) { // Ensure we don't place a tile on an occupied cell
            x = dist(generator);
            y = dist(generator);
        }
        board[x][y] = (value_dist(generator) + 1) * 2; // Place either a 2 or a 4
    }
}

int GameBoard::move(Direction direction) {
    // Slide and merge, anyother?
    // TODO 1
    int score = 0;
    score = merge(direction);
    slide(direction);
    // Add a new tile after every move
    // You can refer to the reset() function to see how to add a new tile
    // TODO 2
    std::uniform_int_distribution<int> dist(0, 3);  // [0, 3] uniform distribution
    std::uniform_int_distribution<int> value_dist(0, 1);
    int x = dist(generator);
    int y = dist(generator);
    while (board[x][y] != 0) { // Ensure we don't place a tile on an occupied cell
        x = dist(generator);
        y = dist(generator);
    }
    board[x][y] = (value_dist(generator) + 1) * 2; // Place either a 2 or a 4
    return score;
}

void GameBoard::slide(Direction direction) {
    switch (direction) {
        case Direction::UP:
            for (int col = 0; col < 4; ++col) {
                int target = 3;
                for (int row = 3; row >= 0; --row) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col], board[row][col]);
                        if (target != row) board[row][col] = 0;
                        --target;
                    }
                }
            }
            break;
        case Direction::DOWN:
            // TODO
            for (int col = 0; col < 4; ++col) {
                int target = 0;
                for (int row = 0; row < 4; ++row) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col], board[row][col]);
                        if (target != row) board[row][col] = 0;
                        ++target;
                    }
                }
            }
            break;
        case Direction::LEFT:
            // TODO
            for (int row = 0; row < 4; ++row) {
                int target = 0;
                for (int col = 0; col < 4; ++col) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col], board[row][col]);
                        if (target != row) board[row][col] = 0;
                        ++target;
                    }
                }
            }
            break;
        case Direction::RIGHT:
            // TODO
            for (int row = 0; row < 4; ++row) {
                int target = 3;
                for (int col = 3; col >= 0; --col) {
                    if (board[row][col] != 0) {
                        std::swap(board[target][col], board[row][col]);
                        if (target != row) board[row][col] = 0;
                        --target;
                    }
                }
            }
            break;
    }
}

int GameBoard::merge(Direction direction) {
    int moveScore = 0;
    switch (direction) {
        case Direction::UP:
            for (int col = 0; col < 4; ++col) {
                for (int row = 3; row > 0; --row) {
                    if (board[row][col] != 0 && board[row][col] == board[row - 1][col]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row - 1][col] = 0;
                    }
                }
            }
            break;
        case Direction::DOWN:
            // TODO
            for (int col = 0; col < 4; ++col) {
                for (int row = 0; row < 3; ++row) {
                    if (board[row][col] != 0 && board[row][col] == board[row + 1][col]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row + 1][col] = 0;
                    }
                }
            }
            break;
        case Direction::LEFT:
            // TODO
            for (int row = 0; row < 4; ++row) {
                for (int col = 3; col > 0; --col) {
                    if (board[row][col] != 0 && board[row][col] == board[row][col - 1]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row][col - 1] = 0;
                    }
                }
            }
            break;
        case Direction::RIGHT:
            // TODO
             for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 3; ++col) {
                    if (board[row][col] != 0 && board[row][col] == board[row][col + 1]) {
                        board[row][col] *= 2;
                        moveScore += board[row][col];
                        board[row][col + 1] = 0;
                    }
                }
            }
            break;
    }

    return moveScore;
}

bool GameBoard::isGameOver() const {
    // Check if there are any empty tiles
    // TODO
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if(board[row][col]==0){
                return false;
            }
        }
    }
    // Check if any adjacent tiles can merge
    // TODO
    int rowbefore, rownext, colbefore, colnext;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            rowbefore = row - 1;
            if(rowbefore<0)rowbefore = 0;                
            rownext = row + 1;
            if(rownext>3)rownext = 3;  
            colbefore = col - 1;
            if(colbefore<0)colbefore = 0;   
            colnext = col + 1;
            if(colnext>3)colnext = 3;  
            if(board[row][col]==board[rowbefore][col]||board[row][col]==board[rownext][col]||board[row][col]==board[row][colbefore]||board[row][col]==board[row=][colnext]){
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::hasWinningTile() const {
    // Check if there is a tile with the value 2048
    // TODO
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if(board[row][col]==2048){
                return true;
            }
        }
    }
    return false;
}


const Board &GameBoard::getBoard() const {
    return board;
}