#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include "Random.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>

GridInfo SudokuGenerator::generateRandomUniqueGrid(SUDOKU_GRID& grid, bool& success)
{
	success = true;
	grid = { 0 };

	makeRandomGrid(grid, success);
	removePositionsFromGrid(grid, success);

	if (!success)
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

	if (counter <= 22)
	{
		return GridInfo{ Difficulty::EASY, counter };
	}

	else if (counter <= 40)
	{
		return GridInfo{ Difficulty::MEDIUM, counter };
	}

	else if (counter <= 55)
	{
		return GridInfo{ Difficulty::HARD, counter };
	}

	else
	{
		return GridInfo{ Difficulty::EXTREME, counter };
	}
}

void SudokuGenerator::makeRandomGrid(SUDOKU_GRID& grid, bool& success)
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

	SudokuSolver solver;
	solver.solve(grid, 0, success);
}

void SudokuGenerator::removePositionsFromGrid(SUDOKU_GRID& grid, bool& success)
{
	Random random;
	SudokuSolver solver;

	std::array<int, 81> positions;
	std::iota(positions.begin(), positions.end(), 0);
	std::shuffle(positions.begin(), positions.end(), random.getEngine());

	for (int pos : positions)
	{
		int previous = grid[pos / 9][pos % 9];
		grid[pos / 9][pos % 9] = 0;

		if (solver.countSolutions(grid, 1, success) > 1)
		{
			grid[pos / 9][pos % 9] = previous;
			break;
		}
	}
}
