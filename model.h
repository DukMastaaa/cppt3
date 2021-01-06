#pragma once
#include <vector>
#include <iostream>


const static char EMPTY = '.';
const static char NOUGHT = 'O';
const static char CROSS = 'X';


class Board {
    private:
        std::vector<std::vector<char>> grid;
    
    public:
        int size;
        Board(int boardSize);
        char& at(int row, int col);
        void set(int row, int col, char value);
        char has_won();
};


class Game {
    public:
        Board board;
        int yPos;
        int xPos;
        int currentPlayer;
        const char* p1Name;
        const char* p2Name;
        Game(int boardSize, const char* p1Name, const char* p2Name);
        const char*& getCurrentPlayerName();
        void moveSelection(char wasd);
        void doTurn();
};