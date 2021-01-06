#include <ncurses.h>
#include "colours.h"


void startColours() {
    start_color();
    init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(WHITE_ON_GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(WHITE_ON_RED, COLOR_WHITE, COLOR_RED);
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(YELLOW_ON_GREEN, COLOR_YELLOW, COLOR_GREEN);
    init_pair(YELLOW_ON_RED, COLOR_YELLOW, COLOR_RED);
    init_pair(CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(CYAN_ON_GREEN, COLOR_CYAN, COLOR_GREEN);
    init_pair(CYAN_ON_RED, COLOR_CYAN, COLOR_RED);
}