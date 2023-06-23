# Sudoku
Sudoku game made with Qt. All Sudokus are generated using a backtracking algorithm to first solve a randomized "seed" and then subsequently removing one number from the board until the solution would no longer be unique.

## How to play
Use the big number buttons below the board to select a number, or use the scroll wheel/ touchpad to scroll through them (there is an extra setting for touchpads since the scroll sensitivity changes. By **right-clicking** you can add a guess to that tile. A **left-click** on a tile the number will set number of that tile and remove all guesses. The board will also automatically update all guesses in the same block/ row/ column when you set a number. It is also possible to hold **right-click** and set guesses to all tiles that the mouse moves over. The rest is just normal Sudoku.

## Difficulties
The difficulties ***Easy***, ***Medium*** and ***Hard*** are generated on the fly by the generator algorithm. The difficulty ***Extreme*** would take too long to generate in real time. That's why around 700 extreme Sudokus where generated beforehand and saved in a file. One of these is randomly selected and scrambled by: rotating it 0-3 times by 90°, flipping around no/ horizontal/ vertical/ both axes, reshuffle/ encode all numbers (i.e. 1->3, 2->6, 3->2, ...). This results in 4 ⋅ 4 ⋅ 9! = 5,806,080 combinations for one Sudoku or around 4 billion overall.

## Highscores & stats
The game automatically keeps track of the 10 best times in each difficulty. The scores are saved in `saves\highscores.txt` with the date and time (UTC+1). All stats are also automatically saved every 10s, so most of the miscellaneous stats should be rather accurate.
