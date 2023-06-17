#pragma once

#include "../sudoku/SudokuGenerator.h"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <array>
#include <string>
#include <thread>
#include <atomic>

constexpr int TILE_SIZE = 46;
constexpr int BOARD_SIZE = TILE_SIZE * 9 + 7 + 6;

class Tile;

class SudokuBoard : public QWidget
{
	Q_OBJECT

public:
	SudokuBoard(Difficulty difficulty, QWidget* parent = nullptr);

	void highlightTiles(int number);
	void removeAllHighlights();
	bool isBoardFinished();

	std::array<Tile*, 81>& getTiles() { return m_tiles; };

	SUDOKU_GRID currentGrid;
	GridInfo gridInfo;
		
private:
	std::array<Tile*, 81> m_tiles;
	QGridLayout* m_layout;
	std::array<std::thread, 20> m_threads;
	std::array<SUDOKU_GRID, 20> m_threadGrids;
	std::array<GridInfo, 20> m_threadInfos;

	void createTiles();
	void fillBoard();
	
	static std::atomic<int> m_threadID;
	static std::atomic<bool> m_boardFound;
	static void checkForGrid(int id, Difficulty difficulty, SUDOKU_GRID grid, GridInfo gridInfo);
};

enum class LineStyle {HTHIN, VTHIN, HTHICK, VTHICK};

class FillLine : public QLabel
{
public:
	FillLine(QWidget* parent = nullptr, LineStyle lineStyle = LineStyle::HTHIN);
};
