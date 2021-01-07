#pragma once
#include <ncurses.h>
#include "model.h"


class BaseView {
    protected:
        Game& game;
    
    public:
        WINDOW* viewWindow;
        BaseView(Game& newGame);
        virtual void draw() = 0;
        void wnoutrefresh();
};


class GameView : public BaseView {
    public:
        GameView(Game& newGame, int topLeftY, int topLeftX);
        void draw();
};


class StatusView : public BaseView {
    public:
        StatusView(Game& newGame, int topLeftY, int topLeftX, int cols);
        void draw();
        void displayWinner(const char* winningPlayerName);
        void gameDrawn();  // if players come to a draw
};