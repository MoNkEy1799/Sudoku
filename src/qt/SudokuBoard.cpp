#include "SudokuBoard.h"
#include "Tile.h"
#include "../sudoku/SudokuSolver.h"
#include "../sudoku/SudokuGenerator.h"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

SudokuBoard::SudokuBoard(QWidget* parent)
	: QWidget(parent)
{
	setContentsMargins(0, 0, 0, 0);

	m_layout = new QGridLayout(this);
	m_layout->setSpacing(0);
	m_layout->setAlignment(Qt::AlignCenter);

	m_generator = new SudokuGenerator();
	bool success = true;
	while (success)
	{
		m_difficulty = m_generator->generateRandomUniqueGrid(m_grid, success);
	}

	createTiles();
	fillBoard();
}

SudokuBoard::~SudokuBoard()
{
	delete m_generator;
}

void SudokuBoard::createTiles()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Tile* tile = new Tile(this, this);

			if (m_grid[i][j])
			{
				tile->setNumber(m_grid[i][j]);
				tile->installEventFilter(this);
			}

			int index = i * 9 + j;
			m_tiles[index] = tile;
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
			if (i % 2 == 0 and j % 2 == 0)
			{
				m_layout->addWidget(m_tiles[tileIndex], i, j);
				tileIndex++;
			}

			else if ((j == 5 or j == 11) and i == 0)
			{
				FillLine* line = new FillLine(this, LineStyle::VTHICK);
				m_layout->addWidget(line, i, j, 17, 1, Qt::AlignCenter);
			}

			else if (j % 2 == 1 and i % 2 == 0 and !(j == 5 or j == 11))
			{
				FillLine* line = new FillLine(this, LineStyle::VTHIN);
				m_layout->addWidget(line, i, j, Qt::AlignCenter);
			}

			else if ((i == 5 or i == 11) and j == 0)
			{
				FillLine* line = new FillLine(this, LineStyle::HTHICK);
				m_layout->addWidget(line, i, j, 1, 17, Qt::AlignCenter);
			}

			else if (i % 2 == 1 and j % 2 == 0 and !(i == 5 or i == 11))
			{
				FillLine* line = new FillLine(this, LineStyle::HTHIN);
				m_layout->addWidget(line, i, j, Qt::AlignCenter);
			}
		}
	}
}

FillLine::FillLine(QWidget* parent, LineStyle lineStyle)
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
