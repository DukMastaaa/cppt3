#include <ncurses.h>
#include <iostream>
#include "colours.h"
#include "model.h"
#include "view.h"


int getBoardSize() {
    std::cout << "Enter board size: ";
    int size;
    std::cin >> size;
    return size;
}


const char* getPlayerName(int playerNumber, char* name) {
    std::cout << "Enter name for player " << playerNumber << ": ";
    std::cin >> name;
    std::cout << name;
    return name;
}


int main() {
    int boardSize = getBoardSize();

    char p1Name[30];
    char p2Name[30];
    getPlayerName(1, p1Name);
    getPlayerName(2, p2Name);

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
    StatusView statusView(game, 1, 1, 30);
    GameView gameView(game, 2, 1);

    while (game.board.has_won() == EMPTY) {
        // draw stuff
        statusView.draw();
        gameView.draw();
        // then refresh internal buffer
        statusView.wnoutrefresh();
        gameView.wnoutrefresh();
        // then refresh the screen
        doupdate();

        char input = wgetch(gameView.viewWindow);
        
        if (input == '\n') {
            game.doTurn();
        } else {
            game.moveSelection(input);
        }

    }

    // display the winner
    char winningPlayerToken = game.board.has_won();
    char* winningPlayerName;
    switch (winningPlayerToken) {
        case NOUGHT:
            winningPlayerName = p1Name;
            break;
        case CROSS:
            winningPlayerName = p2Name;
            break;
    }
    statusView.displayWinner(winningPlayerName);
    statusView.wnoutrefresh();
    doupdate();

    // wait for input
    wgetch(gameView.viewWindow);

    endwin();
    return 0;
}