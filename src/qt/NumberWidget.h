#pragma once

#include "../sudoku/SudokuSolver.h"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include <array>

class NumberWidget : public QWidget
{
	Q_OBJECT

public:
	NumberWidget(int width, QWidget* parent = nullptr);
	void setNumber(int index);
	void initRemaining(SUDOKU_GRID& grid);
	void changeRemaining(int number, bool increase);

private:
	std::array<QPushButton*, 10> m_numbers;
	std::array<QLabel*, 18> m_indicators;
	std::array<int, 9> m_remaining;
	QGridLayout* m_layout;
};
