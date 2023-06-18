#include "SudokuSolver.h"

#include <iostream>
#include <array>
#include <string>

SudokuSolver::SudokuSolver(uint64_t recursionLimit)
	: m_backtrackCounter(0), m_backtrackLimit(recursionLimit)
{
	if (recursionLimit == 0)
	{
		m_backtrackLimit = ~0;
	}
}

void SudokuSolver::simpleSolve(SUDOKU_GRID& grid, bool& limitHit)
{
	m_backtrackCounter = 0;
	limitHit = false;
	solve(grid, limitHit);
}

bool SudokuSolver::testUniqueness(SUDOKU_GRID grid, bool& limitHit)
{
	m_backtrackCounter = 0;
	limitHit = false;
	if (count(grid, 0, limitHit) > 1)
	{
		return false;
	}
	return true;
}

void SudokuSolver::printGrid(SUDOKU_GRID& grid)
{
	std::cout << "\n- - - - - - - - - - - - -\n";
	for (int i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
		{
			std::cout << "- - - - - - - - - - - - -\n";
		}
		std::cout << "| ";
		for (int j = 0; j < 9; j++)
		{
			if (j == 3 || j == 6)
			{
				std::cout << "| ";
			}
			if (grid[i][j] == 0)
			{
				std::cout << ". ";
			}
			else
			{
				std::cout << grid[i][j] << " ";
			}
		}
		std::cout << "|\n";
	}
	std::cout << "- - - - - - - - - - - - -\n" << std::endl;
}

std::string SudokuSolver::formatGrid(SUDOKU_GRID& grid)
{
	std::string temp;
	temp += "\n- - - - - - - - - - - - -\n";
	for (int i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
		{
			temp += "- - - - - - - - - - - - -\n";
		}
		temp += "| ";
		for (int j = 0; j < 9; j++)
		{
			if (j == 3 || j == 6)
			{
				temp += "| ";
			}
			if (grid[i][j] == 0)
			{
				temp += ". ";
			}
			else
			{
				temp += std::to_string(grid[i][j]) + " ";
			}
		}
		temp += "|\n";
	}
	temp += "- - - - - - - - - - - - -\n";
	return temp;
}

bool SudokuSolver::findEmptyLocation(SUDOKU_GRID& grid, int& row, int& col)
{
	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			if (grid[row][col] == 0)
			{
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
	bool rowUnsafe = usedInRow(grid, row, num);
	bool colUnsafe = usedInCol(grid, col, num);
	bool boxUnsafe = usedInBox(grid, row / 3, col / 3, num);

	return (!rowUnsafe && !colUnsafe && !boxUnsafe);
}

bool SudokuSolver::solve(SUDOKU_GRID& grid, bool& limitHit)
{
	m_backtrackCounter++;
	if (m_backtrackCounter > m_backtrackLimit)
	{
		limitHit = true;
		return true;
	}

	int row, col;
	if (!findEmptyLocation(grid, row, col))
	{
		return true;
	}

	for (int num = 1; num < 10; num++)
	{
		if (isLocationValid(grid, row, col, num))
		{
			grid[row][col] = num;
			if (solve(grid, limitHit))
			{
				return true;
			}
			grid[row][col] = 0;
		}
	}
	return false;
}

int SudokuSolver::count(SUDOKU_GRID& grid, int solutions, bool& limitHit)
{
	m_backtrackCounter++;
	if (m_backtrackCounter > m_backtrackLimit)
	{
		limitHit = true;
		return 2;
	}

	int row, col;
	if (!findEmptyLocation(grid, row, col))
	{
		return solutions + 1;
	}

	for (int num = 1; num < 10 && solutions < 2; num++)
	{
		if (isLocationValid(grid, row, col, num))
		{
			grid[row][col] = num;
			solutions = count(grid, solutions, limitHit);
		}
	}
	grid[row][col] = 0;
	return solutions;
}
