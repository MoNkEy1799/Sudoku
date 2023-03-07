#include "SudokuSolver.h"
#include "SudokuGenerator.h"

#include <iostream>
#include <array>
#include <chrono>
#include <thread>


int main()
{
	while (true)
	{
		bool suc = true;

		int succCounter = 0;

		SUDOKU_GRID grid;
		SudokuGenerator gen;

		Difficulty diff = gen.generateRandomUniqueGrid(grid, suc);

		if (suc)
		{
			succCounter++;
		}

		std::cout << succCounter << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}