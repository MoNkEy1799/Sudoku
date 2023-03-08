#pragma once

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class SudokuBoard;

class Tile : public QPushButton
{
public:
	Tile(SudokuBoard* board, QWidget* parent = nullptr);
	~Tile();

private:
	SudokuBoard* m_board;
	std::vector<int> m_guess;

protected:
};
