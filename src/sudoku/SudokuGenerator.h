#pragma once

#include <array>

typedef std::array<std::array<int, 9>, 9> SUDOKU_GRID;

class SudokuSolver;

enum class Difficulty { NONE, EASY, MEDIUM, HARD, EXTREME };

struct GridInfo
{
	Difficulty difficultly;
	uint32_t openTiles;
};

class SudokuGenerator
{
public:
	static GridInfo generateRandomUniqueGrid(SUDOKU_GRID& grid);
	static void scrambleSeedGrid(SUDOKU_GRID& grid);

private:
	static void reshuffleNumber(SUDOKU_GRID& grid);
	static void rotate90(SUDOKU_GRID& grid);
	static void flipAxis(SUDOKU_GRID& grid);
	static void makeRandomGrid(SUDOKU_GRID& grid, bool& limitHit);
	static void removePositionsFromGrid(SUDOKU_GRID& grid, bool& limitHit);
};