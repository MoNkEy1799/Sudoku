#pragma once

#include <array>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver;

enum class Difficulty { EASY, MEDIUM, HARD };

class SudokuGenerator
{
public:
	SudokuGenerator();

	Difficulty generateRandomUniqueGrid(SUDOKU_GRID& grid, bool& success);

private:
	void makeEmptyGrid(SUDOKU_GRID& grid);
	void makeRandomGrid(SUDOKU_GRID& grid, bool& success);
	void removePositionsFromGrid(SUDOKU_GRID& grid, bool& success);
};