#include <ncurses.h>
#include <iostream>
#include "model.h"
#include "view.h"
#include "colours.h"


BaseView::BaseView(Game& newGame) : game(newGame) {}


void BaseView::wnoutrefresh() {
    ::wnoutrefresh(viewWindow);
}


GameView::GameView(Game& newGame, int topLeftY, int topLeftX) :
        BaseView(newGame) { 
    viewWindow = newwin(game.board.size, game.board.size, topLeftY, topLeftX);
    keypad(viewWindow, true);  // allows special chars e.g. arrow keys to be captured
}


void GameView::draw() {
    werase(viewWindow);
    for (int row = 0; row < game.board.size; row++) {
        for (int col = 0; col < game.board.size; col++) {
            char thisChar = game.board.at(row, col);
            int colourPair;

            switch (thisChar) {
                case EMPTY:
                    colourPair = WHITE_ON_BLACK;
                    break;
                case NOUGHT:
                    colourPair = YELLOW_ON_BLACK;
                    break;
                case CROSS:
                    colourPair = CYAN_ON_BLACK;
                    break;
                default:
                    throw std::runtime_error("Board contains invalid chars");
            }

            if (row == game.yPos && col == game.xPos) {
                // yes i know if statement inefficient just for an event
                // that happens once, but otherwise i have to duplicate the 
                // whole switch statement. nuh uh.

                // changes the background colour of the selected cell
                // based on the current player number. see the order 
                // of the enum in `colours.h` for why this works.
                colourPair += (game.currentPlayer + 1);
            }
            
            wattron(viewWindow, COLOR_PAIR(colourPair));
            mvwaddch(viewWindow, row, col, thisChar);
            wattroff(viewWindow, COLOR_PAIR(colourPair));
        }
    }
}

StatusView::StatusView(Game& newGame, int topLeftY, int topLeftX, int cols) : 
        BaseView(newGame) {
    viewWindow = newwin(2, cols, topLeftY, topLeftX);
}


void StatusView::draw() {
    werase(viewWindow);
    const char* currentPlayerName = game.getCurrentPlayerName();
    mvwprintw(viewWindow, 0, 0, "%s's turn", currentPlayerName);
    mvwprintw(viewWindow, 1, 0, "wasd/arrow to move, enter to place");
}


void StatusView::displayWinner(const char* winningPlayerName) {
    werase(viewWindow);
    mvwprintw(viewWindow, 0, 0, "%s wins!", winningPlayerName);
    mvwprintw(viewWindow, 1, 0, "Press any key to exit");
}


void StatusView::gameDrawn() {
    werase(viewWindow);
    mvwprintw(viewWindow, 0, 0, "Game drawn!");
    mvwprintw(viewWindow, 1, 0, "Press any key to exit");
}