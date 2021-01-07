# cppt3

`cppt3` = C++ Tic Tac Toe.

`cppt3` is a program written using `ncurses` which allows two players to play an game of Tic Tac Toe with
arbitrary board size.

## Build
Make sure you have `ncurses` installed, then run `make` in the repository folder. You can do `make clean` afterwards
to clean up auxillary files. The executable is `main`, at the top level of the repository.

## Known bugs
- There is an `n` character shown after the winning player message is displayed. Not sure where this comes from.
  I tried looking for a stray `\n` or `std::cout` but couldn't find any.
- The game can't detect a draw.
