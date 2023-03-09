#pragma once

#include <QWidget>
#include <QGridLayout>

#include <vector>
#include <string>
#include <memory>

class Tile;

class SudokuBoard : public QWidget
{
public:
	SudokuBoard(QWidget* parent = nullptr);
	~SudokuBoard();

private:
	std::vector<std::unique_ptr<Tile>> m_tiles;

	void createTiles();
};
