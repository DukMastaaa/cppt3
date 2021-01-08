# cppt3

`cppt3` = C++ Tic Tac Toe.

`cppt3` is a program written using `ncurses` which allows two players to play an game of Tic Tac Toe with
arbitrary board size.

## How to play
Enter in the board size (>=2) and usernames of both players. Use wasd or arrow keys to change which cell
is selected, and press enter to make the turn. As usual, the game ends when one row, column or diagonal is
filled with the same token, or when all cells are filled (and there are no matches).

## Build
Make sure you have `ncurses` installed, then run `make` in the repository folder. You can do `make clean` afterwards
to clean up auxillary files. The executable is `main`, at the top level of the repository.
