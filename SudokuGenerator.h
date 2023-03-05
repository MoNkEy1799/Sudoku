#pragma once

#include <array>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver;

class SudokuGenerator
{
public:
	SudokuGenerator();
	~SudokuGenerator();

	void generateRandomUniqueGrid(SUDOKU_GRID& grid);

private:
	void makeEmptyGrid(SUDOKU_GRID& grid);
	void fillRandomBlocks(SUDOKU_GRID& grid);
	void makeUniqueGrid(SUDOKU_GRID& grid);
};