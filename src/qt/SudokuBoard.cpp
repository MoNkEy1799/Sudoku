#include "SudokuBoard.h"
#include "Tile.h"

#include <QWidget>
#include <QGridLayout>

SudokuBoard::SudokuBoard(QWidget* parent)
	: QWidget(parent)
{
	createTiles();
}

SudokuBoard::~SudokuBoard()
{
}

void SudokuBoard::createTiles()
{
	QGridLayout* layout = new QGridLayout(this);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::unique_ptr<Tile> tile = std::make_unique<Tile>(this, this);
			layout->addWidget(tile.get(), i, j);
			m_tiles.push_back(std::move(tile));
		}
	}
}
