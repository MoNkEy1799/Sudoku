#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include "Random.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <iostream>

SudokuGenerator::SudokuGenerator()
{
}

SudokuGenerator::~SudokuGenerator()
{
}

Difficulty SudokuGenerator::generateRandomUniqueGrid(SUDOKU_GRID& grid)
{
	makeEmptyGrid(grid);
	makeRandomGrid(grid);
	removePositionsFromGrid(grid);

	int counter = 0;

	for (int i = 0; i < 81; i++)
	{
		if (grid[i / 9][i % 9] == 0)
		{
			counter++;
		}
	}

	if (counter <= 22)
	{
		return Difficulty::EASY;
	}

	else if (counter <= 43)
	{
		return Difficulty::MEDIUM;
	}

	else
	{
		return Difficulty::HARD;
	}
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

void SudokuGenerator::makeRandomGrid(SUDOKU_GRID& grid)
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
	solver.solve(grid);
}

void SudokuGenerator::removePositionsFromGrid(SUDOKU_GRID& grid)
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

		if (solver.countSolutions(grid) > 1)
		{
			grid[pos / 9][pos % 9] = previous;
			break;
		}
	}
}
