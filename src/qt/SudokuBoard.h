#pragma once
#include "../sudoku/SudokuGenerator.h"

#include <QWidget>
#include <QGridLayout>

#include <array>
#include <string>

class Tile;

class SudokuBoard : public QWidget
{
public:
	SudokuBoard(QWidget* parent = nullptr, const char* style = nullptr);
	~SudokuBoard();

private:
	std::array<Tile*, 81> m_tiles;
	QGridLayout* m_layout;
	SudokuGenerator* m_generator;
	Difficulty m_difficulty;
	SUDOKU_GRID m_grid;

	void createTiles(const char* style);
};
