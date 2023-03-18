#pragma once

#include <array>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver;

enum class Difficulty { NONE, EASY, MEDIUM, HARD };

struct GridInfo
{
	Difficulty difficultly;
	uint32_t openTiles;
};

class SudokuGenerator
{
public:
	static GridInfo generateRandomUniqueGrid(SUDOKU_GRID& grid, bool& success);

private:
	static void makeRandomGrid(SUDOKU_GRID& grid, bool& success);
	static void removePositionsFromGrid(SUDOKU_GRID& grid, bool& success);
};