#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>

#include <string>

Tile::Tile(QWidget* parent, const char* style)
	: QWidget(parent)
{
	m_inner = new QPushButton(this);
	m_inner->setFixedSize(40, 40);
	m_inner->setStyleSheet(style);
	setFixedSize(50, 50);
	setStyleSheet(style);
	setObjectName("Tile");
}

void Tile::addGuess(int guess)
{
	m_guess.push_back(guess);
}

void Tile::setNumber(int number)
{
	m_inner->setText(std::to_string(number).c_str());
}

