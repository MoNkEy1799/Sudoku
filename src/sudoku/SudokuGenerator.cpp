#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include "Random.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>

GridInfo SudokuGenerator::generateRandomUniqueGrid(SUDOKU_GRID& grid)
{
	bool limitHit = false;
	grid = { 0 };

	makeRandomGrid(grid, limitHit);
	removePositionsFromGrid(grid, limitHit);

	if (limitHit)
	{
		return GridInfo{ Difficulty::NONE, 0 };
	}

	uint32_t counter = 0;
	for (int i = 0; i < 81; i++)
	{
		if (grid[i / 9][i % 9] == 0)
		{
			counter++;
		}
	}
	if (counter <= 10)
	{
		return GridInfo{ Difficulty::NONE, 0 };
	}
	if (counter <= 25)
	{
		return GridInfo{ Difficulty::EASY, counter };
	}
	else if (counter <= 43)
	{
		return GridInfo{ Difficulty::MEDIUM, counter };
	}
	else
	{
		return GridInfo{ Difficulty::HARD, counter };
	}
}

void SudokuGenerator::scrambleSeedGrid(SUDOKU_GRID& grid)
{
	reshuffleNumber(grid);
	rotate90(grid);
	flipAxis(grid);
}

void SudokuGenerator::reshuffleNumber(SUDOKU_GRID& grid)
{
	Random random;
	std::array<int, 9> shuffle;
	std::iota(shuffle.begin(), shuffle.end(), 1);
	std::shuffle(shuffle.begin(), shuffle.end(), random.getEngine());
	
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			int number = grid[row][col];
			if (number)
			{
				grid[row][col] = shuffle[number - 1];
			}
		}
	}
}

void SudokuGenerator::rotate90(SUDOKU_GRID& grid)
{
	Random random;
	SUDOKU_GRID temp;
	int times = random.randInt(0, 3);
	for (int i = 0; i < times; i++)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				temp[col][8 - row] = grid[row][col];
			}
		}
		grid = temp;
	}
}

void SudokuGenerator::flipAxis(SUDOKU_GRID& grid)
{
	Random random;
	SUDOKU_GRID temp;
	int axes = random.randInt(0, 3);
	if (!axes)
	{
		return;
	}
	if (axes == 1 or axes == 3)
	{
		for (int row = 0; row < 4; row++)
		{
			temp[row] = grid[8 - row];
			temp[8 - row] = grid[row];
		}
		temp[4] = grid[4];
		grid = temp;
	}
	if (axes == 2 or axes == 3)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				temp[row][col] = grid[row][8 - col];
				temp[row][8 - col] = grid[row][col];
			}
			temp[row][4] = grid[row][4];
		}
		grid = temp;
	}
}

void SudokuGenerator::makeRandomGrid(SUDOKU_GRID& grid, bool& limitHit)
{
	Random random;
	std::array<std::array<int, 9>, 3> numBlocks;
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
	SudokuSolver solver;
	solver.simpleSolve(grid, limitHit);
}

void SudokuGenerator::removePositionsFromGrid(SUDOKU_GRID& grid, bool& limitHit)
{
	Random random;
	SudokuSolver solver(0);

	std::array<int, 81> positions;
	std::iota(positions.begin(), positions.end(), 0);
	std::shuffle(positions.begin(), positions.end(), random.getEngine());
	for (int pos : positions)
	{
		int previous = grid[pos / 9][pos % 9];
		grid[pos / 9][pos % 9] = 0;
		if (!solver.testUniqueness(grid, limitHit))
		{
			grid[pos / 9][pos % 9] = previous;
			break;
		}
	}
}