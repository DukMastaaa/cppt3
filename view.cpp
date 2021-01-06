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
}


void GameView::draw() {
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
                    throw "what";
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
    viewWindow = newwin(1, cols, topLeftY, topLeftX);
}


void StatusView::draw() {
    const char* currentPlayerName = game.getCurrentPlayerName();
    mvwprintw(viewWindow, 0, 0, "%s's turn", currentPlayerName);  // length check?!
}


void StatusView::displayWinner(const char* winningPlayerName) {
    mvwprintw(viewWindow, 0, 0, "%s wins!", winningPlayerName);  // length check?!
    mvwprintw(viewWindow, 1, 0, "press any key to exit");
}