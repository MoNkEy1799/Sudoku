#include "SudokuSolver.h"

#include <iostream>
#include <array>
#include <string>

SudokuSolver::SudokuSolver()
	: m_solutionCounter(0)
{
}

SudokuSolver::~SudokuSolver()
{
}

void SudokuSolver::solveAndPrint(SUDOKU_GRID& grid)
{
	if (solveSudoku(grid))
	{
		printSolution(grid);
	}
}

int SudokuSolver::solve(SUDOKU_GRID& grid, bool count)
{
	if (count)
	{
		m_solutionCounter = 0;
		solveSudoku(grid, true);
		return m_solutionCounter;
	}

	else
	{
		solveSudoku(grid);
		return 1;
	}
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

bool SudokuSolver::solveSudoku(SUDOKU_GRID& grid, bool countSoltuions)
{
	int row, col;

	if (!findEmptyLocation(grid, row, col))
	{
		m_solutionCounter++;
		return false;
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

void SudokuSolver::printSolution(SUDOKU_GRID& grid)
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