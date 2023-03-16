#pragma once

#include <array>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver
{
public:
	SudokuSolver();

	void solveAndPrint(SUDOKU_GRID grid, bool& success);
	void solve(SUDOKU_GRID& grid, bool& success);
	int countSolutions(SUDOKU_GRID grid, bool& success);

	static void printGrid(SUDOKU_GRID& grid);

private:
	int m_solutionCounter, m_backtrackCounter;

	bool findEmptyLocation(SUDOKU_GRID& grid, int& row, int& col);
	bool usedInRow(SUDOKU_GRID& grid, int row, int num);
	bool usedInCol(SUDOKU_GRID& grid, int col, int num);
	bool usedInBox(SUDOKU_GRID& grid, int row, int col, int num);
	bool isLocationValid(SUDOKU_GRID& grid, int row, int col, int num);
	bool solveSudoku(SUDOKU_GRID& grid, bool& success);
};
