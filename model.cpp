#include <vector>
#include <assert.h>
#include "model.h"


Board::Board(int boardSize) {
    assert (boardSize >= 3);
    size = boardSize;
    grid = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, EMPTY));
}


char& Board::at(int row, int col) {
    return grid.at(row).at(col);
}


void Board::set(int row, int col, char value) {
    grid.at(row).at(col) = value;
}


char Board::has_won() {
    /* Returns the winning player, else EMPTY. */
    
    char diagStart = at(0, 0);
    char antiDiagStart = at(0, size - 1);
    bool diagSame = (diagStart != EMPTY);
    bool antiDiagSame = (antiDiagStart != EMPTY);

    for (int i = 0; i < size; i++) {
        char rowStart = at(i, 0);
        char colStart = at(0, i);
        bool rowSame = (rowStart != EMPTY);
        bool colSame = (colStart != EMPTY);

        for (int j = 1; j < size; j++) {
            if (rowSame) {rowSame = (rowStart == at(i, j));}
            if (colSame) {colSame = (colStart == at(j, i));}
        }

        if (diagSame) {diagSame = (diagStart == at(i, i));}
        if (antiDiagSame) {antiDiagSame = (antiDiagStart == at(i, size - 1 - i));}

        if (rowSame) {return rowStart;}
        if (colSame) {return colStart;}
    }

    if (diagSame) {return diagStart;}
    if (antiDiagSame) {return antiDiagStart;}

    return EMPTY;
}


Game::Game(int boardSize, const char* newP1Name, const char* newP2Name) 
        : board(Board(boardSize)), p1Name(newP1Name), p2Name(newP2Name) {
    xPos = 0;
    yPos = 0;
    currentPlayer = 0;
}


const char*& Game::getCurrentPlayerName() {
    switch (currentPlayer) {
        case 0:
            return p1Name;
            break;
        case 1:
            return p2Name;
            break;
        default:
            throw "Player number invalid";
    }
}


void Game::moveSelection(char wasd) {
    int newY = yPos;
    int newX = xPos;
    switch (wasd) {
        case 'w':
            newY--;
            break;
        case 'a':
            newX--;
            break;
        case 's':
            newY++;
            break;
        case 'd':
            newX++;
            break;
        // default:  // don't really want to do anything if this happens
        //     throw "wasd direction invalid";
    }
    if (0 <= newX && newX < board.size && 0 <= newY && newY < board.size) {
        xPos = newX;
        yPos = newY;
    }
}


void Game::doTurn() {
    if (board.at(yPos, xPos) == EMPTY) {
        switch (currentPlayer) {
            case 0:
                board.set(yPos, xPos, NOUGHT);
                break;
            case 1:
                board.set(yPos, xPos, CROSS);
                break;
            default:
                throw "Player number invalid";
        }
        currentPlayer += 1;
        currentPlayer %= 2;
    }
}