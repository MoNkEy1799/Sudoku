#pragma once
#include "../sudoku/SudokuGenerator.h"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <array>
#include <string>

constexpr int TILE_SIZE = 46;
constexpr int BOARD_SIZE = TILE_SIZE * 9 + 7 + 6;

class Tile;

class SudokuBoard : public QWidget
{
public:
	SudokuBoard(QWidget* parent = nullptr, const char* style = nullptr);
	~SudokuBoard();
	
	void test() { setStyleSheet("backgroud: yellow"); };

private:
	std::array<Tile*, 81> m_tiles;
	QGridLayout* m_layout;
	SudokuGenerator* m_generator;
	Difficulty m_difficulty;
	SUDOKU_GRID m_grid;

	void createTiles(const char* style);
	void fillBoard(const char* style);
};

enum class LineStyle {HTHIN, VTHIN, HTHICK, VTHICK};

class FillLine : public QLabel
{
public:
	FillLine(QWidget* parent = nullptr, LineStyle lineStyle = LineStyle::HTHIN);
};
