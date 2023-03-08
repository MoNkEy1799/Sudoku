#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>

Tile::Tile(SudokuBoard* board, QWidget* parent)
	: QPushButton(parent), m_board(board)
{
	setMouseTracking(true);
}

Tile::~Tile()
{
}
