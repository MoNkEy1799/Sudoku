#include "SudokuBoard.h"
#include "Tile.h"
#include "../sudoku/SudokuSolver.h"

#include <QWidget>
#include <QGridLayout>

SudokuBoard::SudokuBoard(QWidget* parent, const char* style)
	: QWidget(parent)
{
	setFixedSize(450, 450);
	setContentsMargins(0, 0, 0, 0);
	setStyleSheet(style);

	m_layout = new QGridLayout(this);
	m_layout->setSpacing(0);
	setLayout(m_layout);

	m_generator = new SudokuGenerator();
	bool success = true;
	m_difficulty = m_generator->generateRandomUniqueGrid(m_grid, success);

	createTiles(style);
}

SudokuBoard::~SudokuBoard()
{
	delete m_generator;
}

void SudokuBoard::createTiles(const char* style)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Tile* tile = new Tile(this, style);
			m_layout->addWidget(tile, i, j);

			if (m_grid[i][j])
			{
				tile->setNumber(m_grid[i][j]);
			}

			int index = i * 9 + j;
			m_tiles[index] = tile;
		}
	}
}
