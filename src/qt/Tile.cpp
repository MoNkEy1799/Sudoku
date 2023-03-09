#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>

Tile::Tile(QWidget* parent)
	: QPushButton(parent)
{
	setFixedSize(30, 30);
}

Tile::~Tile()
{
}
