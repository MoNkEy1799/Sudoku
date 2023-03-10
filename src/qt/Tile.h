#pragma once

#include <QWidget>
#include <QPushButton>

#include <string>
#include <array>

class SudokuBoard;

class Tile : public QWidget
{
	Q_OBJECT

public:
	Tile(int id, SudokuBoard* board = nullptr, QWidget* parent = nullptr);

	void addGuess(int guess);
	void addNumber(int number);
	void fixNumber(int number);
	int getId() { return m_id; };

	QPushButton* getButton() { return m_inner; };

private:
	int m_id;
	std::array<bool, 9> m_guess;
	QPushButton* m_inner;
	SudokuBoard* m_board;
	QFont m_fontGuess, m_fontSet;

	bool inGuess(int number) { return m_guess[number]; };
};
