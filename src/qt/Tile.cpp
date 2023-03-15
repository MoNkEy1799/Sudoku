#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QFont>

#include <string>
#include <algorithm>
#include <tuple>

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
	m_fontGuess = QFont("Sans-Serif", 8);
	m_fontGuess.setBold(true);

	setFixedSize(TILE_SIZE, TILE_SIZE);
	setObjectName("Tile");
}

void Tile::addGuess(int guess)
{
	m_inner->setFont(m_fontGuess);
	m_inner->setStyleSheet("text-align: bottom");

	int numberOfGuesses = std::count(m_guess.begin(), m_guess.end(), true);
	int index = guess - 1;

	if (inGuess(index))
	{
		m_guess[index] = false;
	}

	else if (!inGuess(index) && numberOfGuesses < 8)
	{
		m_guess[index] = true;
	}

	else
	{
		return;
	}

	displayGuess();
}

void Tile::removeGuesses()
{
	m_guess = { false };
	displayGuess();
}

void Tile::addNumber(int number)
{
	removeGuesses();

	m_inner->setFont(m_fontSet);
	m_inner->setStyleSheet("text-align: center");
	m_inner->setText(std::to_string(number).c_str());
}

void Tile::fixNumber(int number)
{
	m_inner->setFont(m_fontSet);
	m_inner->setObjectName("TileFixed");
	m_inner->setText(std::to_string(number).c_str());
}

void Tile::displayGuess()
{
	int numberOfGuesses = std::count(m_guess.begin(), m_guess.end(), true);

	if (numberOfGuesses == 0)
	{
		m_inner->setText("");
		return;
	}

	std::array<int, 2> alignment;

	if (numberOfGuesses <= 2)
	{
		alignment = { 0, 0};
	}

	else if (numberOfGuesses >= 3 && numberOfGuesses <= 6)
	{
		alignment = { 0, numberOfGuesses - 2};
	}

	else
	{
		alignment = { numberOfGuesses - 6, 4};
	}

	std::string text;

	for (int i = 0; i < 9; i++)
	{
		if (!m_guess[i])
		{
			continue;
		}

		text += std::to_string(i + 1) + " ";
	}

	text.erase(text.size() - 1);
	size_t lastPos = 0;

	for (int a : alignment)
	{
		if (!a)
		{
			continue;
		}

		lastPos += 2 * a;
		text.replace(lastPos - 1, 1, "\n");
	}

	m_inner->setText(text.c_str());
}
