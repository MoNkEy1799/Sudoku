#include "SudokuBoard.h"
#include "Tile.h"

#include <QWidget>
#include <QGridLayout>

const char* mainStyleSheet =
"QPushButton {background: #3d3d3d; color: #b5b5b5;}"
"QPushButton::hover {background: #3d3d3d; color: #b5b5b5;}"
"QWidget {background: #050505;}";

SudokuBoard::SudokuBoard(QWidget* parent)
	: QWidget(parent)
{
	setFixedSize(270, 270);
	setStyleSheet(mainStyleSheet);
	createTiles();
}

SudokuBoard::~SudokuBoard()
{
	m_tiles.clear();
}

void SudokuBoard::createTiles()
{
	QGridLayout* layout = new QGridLayout(this);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::unique_ptr<Tile> tile = std::make_unique<Tile>(this);
			m_tiles.push_back(std::move(tile));
		}
	}
}
