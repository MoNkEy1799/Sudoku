#include "SudokuSolver.h"
#include "SudokuGenerator.h"

#include <iostream>
#include <array>
#include <chrono>
#include <thread>

void createGrid()
{
	SUDOKU_GRID grid;
	SudokuGenerator generator;

	Difficulty diff = generator.generateRandomUniqueGrid(grid);
	printGrid(grid);
	std::cout << (int)diff << std::endl;
}

int main()
{
	while (true)
	{
		SUDOKU_GRID grid;
		SudokuGenerator gen;

		int tries = 0;

		while (gen.generateRandomUniqueGrid(grid) != Difficulty::HARD)
		{
			tries++;
		}

		std::cout << tries << std::endl;

		//std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}