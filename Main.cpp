#include <iostream>
#include <array>

#include "SudokuSolver.h"
#include "SudokuGenerator.h"

int main()
{
	SUDOKU_GRID grid;
	SudokuGenerator generator;
	SudokuSolver solver;

	grid = {
		2, 9, 5, 7, 4, 3, 8, 6, 1,
		4, 3, 1, 8, 6, 5, 9, 0, 0,
		8, 7, 6, 1, 9, 2, 5, 4, 3,
		3, 8, 7, 4, 5, 9, 2, 1, 6,
		6, 1, 2, 3, 8, 7, 4, 9, 5,
		5, 4, 9, 2, 1, 6, 7, 3, 8,
		7, 6, 3, 5, 3, 4, 1, 8, 9,
		9, 2, 8, 6, 7, 1, 3, 5, 4,
		1, 5, 4, 9, 3, 8, 6, 0, 0 };

	std::cout << solver.solve(grid, true) << std::endl;

	//generator.generateRandomUniqueGrid(grid);
}