#include "SudokuSolver.h"

#include <iostream>
#include <array>
#include <string>

int backtrackCount = 0;

void printGrid(SUDOKU_GRID& grid)
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

SudokuSolver::SudokuSolver()
	: m_solutionCounter(0)
{
}

SudokuSolver::~SudokuSolver()
{
}

void SudokuSolver::solveAndPrint(SUDOKU_GRID grid)
{
	if (solveSudoku(grid))
	{
		printGrid(grid);
	}
}

void SudokuSolver::solve(SUDOKU_GRID& grid)
{
	backtrackCount = 0;
	solveSudoku(grid);
}

int SudokuSolver::countSolutions(SUDOKU_GRID grid)
{
	backtrackCount = 0;
	m_solutionCounter = 0;
	solveSudoku(grid);
	return m_solutionCounter;
}

bool SudokuSolver::findEmptyLocation(SUDOKU_GRID& grid, int& row, int& col)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j] == 0)
			{
				row = i;
				col = j;
				return true;
			}
		}
	}

	return false;
}

bool SudokuSolver::usedInRow(SUDOKU_GRID& grid, int row, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (grid[row][i] == num)
		{
			return true;
		}
	}

	return false;
}

bool SudokuSolver::usedInCol(SUDOKU_GRID& grid, int col, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (grid[i][col] == num)
		{
			return true;
		}
	}

	return false;
}

bool SudokuSolver::usedInBox(SUDOKU_GRID& grid, int row, int col, int num)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (grid[i + row * 3][j + col * 3] == num)
			{
				return true;
			}
		}
	}

	return false;
}

bool SudokuSolver::isLocationValid(SUDOKU_GRID& grid, int row, int col, int num)
{
	bool rowSafe = usedInRow(grid, row, num);
	bool colSafe = usedInCol(grid, col, num);
	bool boxSafe = usedInBox(grid, row / 3, col / 3, num);

	return (!rowSafe and !colSafe and !boxSafe);
}

bool SudokuSolver::solveSudoku(SUDOKU_GRID& grid)
{
	backtrackCount++;
	if (m_solutionCounter > 1)
	{
		return true;
	}

	int row, col;

	if (!findEmptyLocation(grid, row, col))
	{
		m_solutionCounter++;
		return true;
	}

	for (int num = 1; num < 10; num++)
	{
		if (isLocationValid(grid, row, col, num))
		{
			grid[row][col] = num;

			if (solveSudoku(grid))
			{
				return true;
			}

			grid[row][col] = 0;
		}
	}

	return false;
}
