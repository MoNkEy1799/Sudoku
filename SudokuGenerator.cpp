#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include "Random.h"

#include <algorithm>
#include <array>
#include <numeric>

SudokuGenerator::SudokuGenerator()
{
}

SudokuGenerator::~SudokuGenerator()
{
}

void SudokuGenerator::generateRandomUniqueGrid(SUDOKU_GRID& grid)
{
	makeEmptyGrid(grid);
	fillRandomBlocks(grid);
	makeUniqueGrid(grid);
}

void SudokuGenerator::makeEmptyGrid(SUDOKU_GRID& grid)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void SudokuGenerator::fillRandomBlocks(SUDOKU_GRID& grid)
{
	std::array<std::array<int, 9>, 3> numBlocks;
	Random random;
	
	for (int i = 0; i < 3; i++)
	{
		std::iota(numBlocks[i].begin(), numBlocks[i].end(), 1);
		std::shuffle(numBlocks[i].begin(), numBlocks[i].end(), random.getEngine());
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = i + 3 * j;
			grid[i][j] = numBlocks[0][index];
			grid[i + 3][j + 3] = numBlocks[1][index];
			grid[i + 6][j + 6] = numBlocks[2][index];
		}
	}
}

void SudokuGenerator::makeUniqueGrid(SUDOKU_GRID& grid)
{
	SudokuSolver solver;

	//solver.solve(grid);

	solver.solveAndPrint(grid);
}
