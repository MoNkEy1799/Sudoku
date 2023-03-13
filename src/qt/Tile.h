#pragma once

#include <QWidget>
#include <QPushButton>

#include <string>

class SudokuBoard;

class Tile : public QWidget
{
	Q_OBJECT

public:
	Tile(SudokuBoard* board = nullptr, QWidget* parent = nullptr);

	void addGuess(int guess);
	void addNumber(int number);
	void fixNumber(int number);

	QPushButton* getButton() { return m_inner; };

private:
	std::vector<int> m_guess;
	QPushButton* m_inner;
	SudokuBoard* m_board;
	QFont m_font;
};
