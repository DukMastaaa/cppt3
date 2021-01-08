#include <ncurses.h>
#include <iostream>
#include <stdexcept>
#include "colours.h"
#include "model.h"
#include "view.h"


bool stringIsDigit(const std::string& input) {
    // i can't believe i have to write something like this
    // low level scum
    for (char character : input) {
        if (!isdigit(character)) {
            return false;
        }
    }
    return true;
}


int getBoardSize() {
    std::cout << "Enter board size: ";
    std::string input;
    getline(std::cin, input);
    if (!stringIsDigit(input)) {
        throw std::runtime_error("Non-digit entered as input");
    }
    int size = std::stoi(input);
    if (size < 2) {
        throw std::runtime_error("Board size too low; minimum 2");
    }
    return size;
}


std::string getPlayerName(int playerNumber) {
    std::cout << "Enter name for player " << playerNumber << ": ";
    std::string input;
    getline(std::cin, input);
    return input;
}


int main() {
    int boardSize = getBoardSize();

    std::string p1NameString = getPlayerName(1);
    std::string p2NameString = getPlayerName(2);
    const char* p1Name = p1NameString.c_str();
    const char* p2Name = p2NameString.c_str();

    initscr();
    if (!has_colors()) {
        endwin();
        std::cout << "Your terminal does not support colour.\n";
        return 1;
    }

    startColours();
    noecho();
    cbreak();
    curs_set(0);
    
    Game game(boardSize, p1Name, p2Name);
    StatusView statusView(game, 1, 1, 40);
    GameView gameView(game, 3, 1);
    bool gameDrawn = false;

    while (game.board.hasWon() == EMPTY) {
        if (game.board.allCellsFilled()) {  
            // for this to happen, game.board.hasWon() == EMPTY already.
            gameDrawn = true;
            break;
        }

        // draw stuff
        statusView.draw();
        gameView.draw();
        // then refresh internal buffer
        statusView.wnoutrefresh();
        gameView.wnoutrefresh();
        // then refresh the screen
        doupdate();

        int input = wgetch(gameView.viewWindow);
        
        if (input == '\n') {
            game.doTurn();
        } else {
            game.moveSelection(input);
        }

    }

    if (gameDrawn) {
        statusView.gameDrawn();
    } else {
        // display the winner
        char winningPlayerToken = game.board.hasWon();

        switch (winningPlayerToken) {
            case NOUGHT:
                statusView.displayWinner(p1Name);
                break;
            case CROSS:
                statusView.displayWinner(p2Name);
                break;
            default:
                throw std::runtime_error("Board::hasWon() is broken");
        }
    }

    statusView.wnoutrefresh();
    doupdate();

    // wait for input
    wgetch(gameView.viewWindow);

    endwin();
    return 0;
}