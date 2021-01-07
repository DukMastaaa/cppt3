#include <vector>
#include <ncurses.h>
#include <stdexcept>
#include "model.h"


Board::Board(int boardSize) {
    size = boardSize;
    grid = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, EMPTY));
}


char& Board::at(int row, int col) {
    return grid.at(row).at(col);
}


void Board::set(int row, int col, char value) {
    grid.at(row).at(col) = value;
}


char Board::hasWon() {
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


bool Board::allCellsFilled() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (at(i, j) == EMPTY) {
                return false;
            }
        }
    }
    return true;
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
            throw std::runtime_error("Player number invalid");
    }
}


void Game::moveSelection(int input) {
    int newY = yPos;
    int newX = xPos;
    switch (input) {
        case 'w':
        case KEY_UP:
            newY--;
            break;
        case 'a':
        case KEY_LEFT:
            newX--;
            break;
        case 's':
        case KEY_DOWN:
            newY++;
            break;
        case 'd':
        case KEY_RIGHT:
            newX++;
            break;
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
                throw std::runtime_error("Player number invalid");
        }
        currentPlayer += 1;
        currentPlayer %= 2;
    }
}