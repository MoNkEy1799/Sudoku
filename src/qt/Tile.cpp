#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QFont>

#include <string>

Tile::Tile(int id, SudokuBoard* board, QWidget* parent)
	: QWidget(parent), m_board(board), m_guess({ false }), m_id(id)
{
	m_inner = new QPushButton(this);
	m_inner->setFixedSize(40, 40);
	m_inner->move(3, 3);
	m_inner->setObjectName("TileOpen");
	m_inner->setCheckable(true);

	m_fontSet = QFont("Sans-Serif", 15);
	m_fontSet.setBold(true);
	m_fontGuess = QFont("Sans-Serif", 10);
	m_fontGuess.setBold(true);

	setFixedSize(TILE_SIZE, TILE_SIZE);
	setObjectName("Tile");
}

void Tile::addGuess(int guess)
{
	m_inner->setFont(m_fontGuess);

	if (inGuess(guess))
	{
		m_guess[guess] = false;
		return;
	}

	m_guess[guess] = true;

	m_inner->setText(std::to_string(guess).c_str());
}

void Tile::addNumber(int number)
{
	m_inner->setFont(m_fontGuess);
	m_inner->setText(std::to_string(number).c_str());
}

void Tile::fixNumber(int number)
{
	m_inner->setFont(m_fontSet);
	m_inner->setObjectName("TileFixed");
	m_inner->setText(std::to_string(number).c_str());
}
