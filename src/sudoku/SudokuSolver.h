#pragma once

#include <array>
#include <string>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver
{
public:
	SudokuSolver(uint64_t recursionLimit = 100000);

	void simpleSolve(SUDOKU_GRID& grid, bool& limitHit);
	bool testUniqueness(SUDOKU_GRID grid, bool& limitHit);

	static void printGrid(SUDOKU_GRID& grid);
	static std::string formatGrid(SUDOKU_GRID& grid);

private:
	uint64_t m_backtrackCounter, m_backtrackLimit;

	static bool findEmptyLocation(SUDOKU_GRID& grid, int& row, int& col);
	static bool usedInRow(SUDOKU_GRID& grid, int row, int num);
	static bool usedInCol(SUDOKU_GRID& grid, int col, int num);
	static bool usedInBox(SUDOKU_GRID& grid, int row, int col, int num);
	static bool isLocationValid(SUDOKU_GRID& grid, int row, int col, int num);

	bool solve(SUDOKU_GRID& grid, bool& limitHit);
	int count(SUDOKU_GRID& grid, int count, bool& limitHit);
};
