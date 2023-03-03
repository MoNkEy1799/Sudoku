#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

#include "SudokuSolver.h"
#include "Random.h"

void generateEmptyGrid(SUDOKU_GRID& grid)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void generateTestGrid(SUDOKU_GRID& grid)
{
	grid = {
		3, 0, 6, 5, 0, 8, 4, 0, 0,
		5, 2, 0, 0, 0, 0, 0, 0, 0,
		0, 8, 7, 0, 0, 0, 0, 3, 1,
		0, 0, 3, 0, 1, 0, 0, 8, 0,
		9, 0, 0, 8, 6, 3, 0, 0, 5,
		0, 5, 0, 0, 9, 0, 6, 0, 0,
		1, 3, 0, 0, 0, 0, 2, 5, 0,
		0, 0, 0, 0, 0, 0, 0, 7, 4,
		0, 0, 5, 2, 0, 6, 3, 0, 0 };
}

void testFillGrid(SUDOKU_GRID& grid)
{
	Random random;
	std::array<int, 9> numBlock1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::array<int, 9> numBlock2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::array<int, 9> numBlock3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::random_shuffle(numBlock1.begin(), numBlock1.end());
	std::random_shuffle(numBlock2.begin(), numBlock2.end());
	std::random_shuffle(numBlock3.begin(), numBlock3.end());

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = i + 3 * j;
			grid[i][j] = numBlock1[index];
			grid[i + 3][j + 3] = numBlock2[index];
			grid[i + 6][j + 6] = numBlock3[index];
		}
	}
}

void printSolution(SUDOKU_GRID& grid)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << grid[i][j] << "  ";
		}

		std::cout << std::endl;
	}

	std::cout << "\n" << "- - - - - - - - - - - - -" << "\n" << std::endl;
}

int main()
{
	SUDOKU_GRID grid;
	generateEmptyGrid(grid);

	SudokuSolver solver(grid);
	solver.solve();

	for (int i = 0; i < 5; i++)
	{
		SUDOKU_GRID grid;
		generateEmptyGrid(grid);
		testFillGrid(grid);

		SudokuSolver solver(grid);
		solver.solve();
	}
}