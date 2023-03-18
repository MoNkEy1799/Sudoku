#include "SudokuBoard.h"
#include "Tile.h"
#include "../sudoku/SudokuGenerator.h"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <set>

SudokuBoard::SudokuBoard(Difficulty difficulty, QWidget* parent)
	: QWidget(parent), currentGrid({ 0 })
{
	setContentsMargins(0, 0, 0, 0);

	m_layout = new QGridLayout(this);
	m_layout->setSpacing(0);
	m_layout->setAlignment(Qt::AlignCenter);

	bool success = false;
	Difficulty currentDifficulty = Difficulty::NONE;

	while (!success || currentDifficulty != difficulty)
	{
		gridInfo = SudokuGenerator::generateRandomUniqueGrid(currentGrid, success);
		currentDifficulty = gridInfo.difficultly;
	}

	createTiles();
	fillBoard();
}

void SudokuBoard::highlightTiles(int number)
{
	for (Tile* tile : m_tiles)
	{
		tile->highlightTile(number);
	}
}

void SudokuBoard::removeAllHighlights()
{
	for (Tile* tile : m_tiles)
	{
		tile->removeHighlight();
	}
}

bool SudokuBoard::isBoardFinished()
{
	for (int i = 0; i < 9; i++)
	{
		std::set<int> row, col, box;

		for (int j = 0; j < 9; j++)
		{
			row.insert(currentGrid[i][j]);
			col.insert(currentGrid[j][i]);
			int index = m_tiles[0]->idLookUp.at(i)[j];
			box.insert(currentGrid[index / 9][index % 9]);
		}

		if (row.size() < 9 || col.size() < 9 || box.size() < 9)
		{
			return false;
		}
	}

	return true;
}

void SudokuBoard::createTiles()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int index = i * 9 + j;
			Tile* tile = new Tile(index, this, this);
			m_tiles[index] = tile;

			if (currentGrid[i][j])
			{
				tile->fixNumber(currentGrid[i][j]);
				tile->installEventFilter(this);
			}
		}
	}
}

void SudokuBoard::fillBoard()
{
	int tileIndex = 0;

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (i % 2 == 0 && j % 2 == 0)
			{
				m_layout->addWidget(m_tiles[tileIndex], i, j);
				tileIndex++;
			}

			else if ((j == 5 || j == 11) && i == 0)
			{
				FillLine* line = new FillLine(this, LineStyle::VTHICK);
				m_layout->addWidget(line, i, j, 17, 1, Qt::AlignCenter);
			}

			else if (j % 2 == 1 && i % 2 == 0 && !(j == 5 || j == 11))
			{
				FillLine* line = new FillLine(this, LineStyle::VTHIN);
				m_layout->addWidget(line, i, j, Qt::AlignCenter);
			}

			else if ((i == 5 || i == 11) && j == 0)
			{
				FillLine* line = new FillLine(this, LineStyle::HTHICK);
				m_layout->addWidget(line, i, j, 1, 17, Qt::AlignCenter);
			}

			else if (i % 2 == 1 && j % 2 == 0 && !(i == 5 || i == 11))
			{
				FillLine* line = new FillLine(this, LineStyle::HTHIN);
				m_layout->addWidget(line, i, j, Qt::AlignCenter);
			}
		}
	}
}

FillLine::FillLine(QWidget* parent, LineStyle lineStyle)
	: QLabel(parent)
{
	switch (lineStyle)
	{
	case LineStyle::HTHIN:
		setFixedSize(TILE_SIZE - 10, 1);
		setObjectName("ThinLine");
		break;

	case LineStyle::HTHICK:
		setFixedSize(BOARD_SIZE, 2);
		setObjectName("ThickLine");
		break;

	case LineStyle::VTHIN:
		setFixedSize(1, TILE_SIZE - 10);
		setObjectName("ThinLine");
		break;

	case LineStyle::VTHICK:
		setFixedSize(2, BOARD_SIZE);
		setObjectName("ThickLine");
		break;
	}
}
