#include "Tile.h"
#include "SudokuBoard.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QFont>

#include <string>
#include <algorithm>
#include <tuple>
#include <unordered_map>

const std::unordered_map<int, std::array<int, 9>> Tile::m_idLookUp =
{
	{ 0, { 0, 1, 2, 9, 10, 11, 18, 19, 20 } },
	{ 1, { 3, 4, 5, 12, 13, 14, 21, 22, 23 } },
	{ 2, { 6, 7, 8, 15, 16, 17, 24, 25, 26 } },
	{ 3, { 27, 28, 29, 36, 37, 38, 45, 46, 47 } },
	{ 4, { 30, 31, 32, 39, 40, 41, 48, 49, 50 } },
	{ 5, { 33, 34, 35, 42, 43, 44, 51, 52, 53 } },
	{ 6, { 54, 55, 56, 63, 64, 65, 72, 73, 74 } },
	{ 7, { 57, 58, 59, 66, 67, 68, 75, 76, 77 } },
	{ 8, { 60, 61, 62, 69, 70, 71, 78, 79, 80 } },
};

Tile::Tile(int id, SudokuBoard* board, QWidget* parent)
	: QWidget(parent), m_board(board), m_guess({ false }), m_id(id), m_state(TileState::GUESS)
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
	m_state = TileState::GUESS;
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
	m_state = TileState::SET;
	removeGuesses();
	updateInvolvedGuesses();

	m_inner->setFont(m_fontSet);
	m_inner->setStyleSheet("text-align: center");
	m_inner->setText(std::to_string(number).c_str());
}

void Tile::updateInvolvedGuesses()
{
	int col = m_id % 9;
	int row = m_id / 9;
	int block = col / 3 + row / 3 * 3;

	std::array<Tile*, 81>& tiles = m_board->getTiles();
	const std::array<int, 9>& tilesInBlock = Tile::m_idLookUp.at(block);

	for (int i = 0; i < 81; i++)
	{
		if (i == m_id || tiles[i]->getState() == TileState::SET || tiles[i]->getState() == TileState::FIXED)
		{
			continue;
		}

		if (i % 9 == col || i / 9 == row || Tile::contains(tilesInBlock, i))
		{
			tiles[i]->removeGuesses();
		}
	}
}

void Tile::fixNumber(int number)
{
	m_state = TileState::FIXED;
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
