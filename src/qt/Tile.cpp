#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QFont>
#include <QMouseEvent>

#include <string>

Tile::Tile(SudokuBoard* board, QWidget* parent)
	: QWidget(parent), m_board(board)
{
	m_inner = new QPushButton(this);
	m_inner->setFixedSize(40, 40);
	m_inner->move(3, 3);
	m_inner->setObjectName("TileOpen");

	QFont font = QFont("Sans-Serif", 15);
	font.setBold(true);
	m_inner->setFont(font);

	setFixedSize(TILE_SIZE, TILE_SIZE);
	setObjectName("Tile");
}

void Tile::addGuess(int guess)
{
	m_guess.push_back(guess);
}

void Tile::setNumber(int number)
{
	m_inner->setText(std::to_string(number).c_str());
	m_inner->setObjectName("TileSet");
}
