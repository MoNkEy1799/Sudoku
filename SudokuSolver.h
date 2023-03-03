#pragma once

#include <array>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver
{
public:
	SudokuSolver(SUDOKU_GRID grid);
	~SudokuSolver();

	void solve();

private:
	SUDOKU_GRID m_grid;
	int m_curRow, m_curCol;

	bool findEmptyLocation(int& row, int& col);
	bool usedInRow(int row, int num);
	bool usedInCol(int col, int num);
	bool usedInBox(int row, int col, int num);
	bool isLocationValid(int row, int col, int num);
	bool solveSudoku();

	void printSolution();
};
