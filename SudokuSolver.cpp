#include "SudokuSolver.h"

#include <iostream>
#include <array>
#include <string>

SudokuSolver::SudokuSolver(SUDOKU_GRID grid)
	: m_grid(grid), m_curRow(0), m_curCol(0)
{
}

SudokuSolver::~SudokuSolver()
{
}

void SudokuSolver::solve()
{
	if (solveSudoku())
	{
		printSolution();
	}
}

bool SudokuSolver::findEmptyLocation(int& row, int& col)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_grid[i][j] == 0)
			{
				row = i;
				col = j;
				return true;
			}
		}
	}

	return false;
}

bool SudokuSolver::usedInRow(int row, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (m_grid[row][i] == num)
		{
			return true;
		}
	}

	return false;
}

bool SudokuSolver::usedInCol(int col, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (m_grid[i][col] == num)
		{
			return true;
		}
	}

	return false;
}

bool SudokuSolver::usedInBox(int row, int col, int num)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_grid[i + row * 3][j + col * 3] == num)
			{
				return true;
			}
		}
	}

	return false;
}

bool SudokuSolver::isLocationValid(int row, int col, int num)
{
	bool rowSafe = usedInRow(row, num);
	bool colSafe = usedInCol(col, num);
	bool boxSafe = usedInBox(row / 3, col / 3, num);

	return (!rowSafe and !colSafe and !boxSafe);
}

bool SudokuSolver::solveSudoku()
{
	int row, col;

	if (!findEmptyLocation(row, col))
	{
		return true;
	}

	for (int num = 1; num < 10; num++)
	{
		if (isLocationValid(row, col, num))
		{
			m_grid[row][col] = num;

			if (solveSudoku())
			{
				return true;
			}

			m_grid[row][col] = 0;
		}
	}

	return false;
}

void SudokuSolver::printSolution()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << m_grid[i][j] << "  ";
		}

		std::cout << std::endl;
	}

	std::cout << "\n" << "- - - - - - - - - - - - -" << "\n" << std::endl;
}
