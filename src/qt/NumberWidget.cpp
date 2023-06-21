#include "NumberWidget.h"
#include "../sudoku/SudokuSolver.h"

#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QFont>
#include <QButtonGroup>
#include <QLabel>

#include <string>

NumberWidget::NumberWidget(int width, QWidget* parent)
	: QWidget(parent), m_numbers({ nullptr }), m_indicators({ nullptr }), m_remaining({ 9 })
{
	m_layout = new QGridLayout(this);
	setMinimumHeight(150);
	setMaximumWidth(width);

	QButtonGroup* group = new QButtonGroup(this);
	for (int i = 0; i < 10; i++)
	{
		QPushButton* button = new QPushButton(std::to_string(i + 1).c_str(), this);
		button->setFont(QFont("Sans-Serif", 16, QFont::Bold));
		button->setFixedSize(50, 50);
		button->setObjectName("Number");
		button->setCheckable(true);
		group->addButton(button);
		m_numbers[i] = button;
		QLabel* indic = new QLabel("I", button);
		indic->setObjectName("Indic");
		indic->setFont(QFont("Sans-Serif", 7, QFont::Bold));
		indic->move(23, 34);
		QLabel* indicHigh = new QLabel("H", button);
		indicHigh->setObjectName("IndicHigh");
		indicHigh->setFont(QFont("Sans-Serif", 7, QFont::Bold));
		indicHigh->move(23, 34);
		indicHigh->hide();

		if (i < 5)
		{
			m_layout->addWidget(button, 0, i);
			m_indicators[2 * i] = indic;
			m_indicators[2 * i + 1] = indicHigh;
		}
		else if (i < 9)
		{
			m_layout->addWidget(button, 1, i - 5);
			m_indicators[2 * i] = indic;
			m_indicators[2 * i + 1] = indicHigh;
		}
		else
		{
			button->setText("X");
			indic->deleteLater();
			indicHigh->deleteLater();
			m_layout->addWidget(button, 1, 4);
		}
	}
}

void NumberWidget::setNumber(int index)
{
	m_numbers[index]->setChecked(true);
	for (int i = 0; i < 9; i++)
	{
		m_indicators[2 * i]->show();
		m_indicators[2 * i + 1]->hide();
	}
	if (index < 9)
	{
		m_indicators[2 * index]->hide();
		m_indicators[2 * index + 1]->show();
	}
}

void NumberWidget::initRemaining(SUDOKU_GRID& grid)
{
	m_remaining = { 9 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (grid[i][j])
			{
				m_remaining[grid[i][j] - 1]--;
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		m_indicators[2 * i]->setText(std::to_string(m_remaining[i]).c_str());
		m_indicators[2 * i + 1]->setText(std::to_string(m_remaining[i]).c_str());
	}
}

void NumberWidget::changeRemaining(int number, bool increase)
{
	int add = -1;
	if (increase)
	{
		add = 1;
	}
	m_remaining[number - 1] += add;
	if (m_remaining[number - 1] <= 0)
	{
		m_indicators[2 * (number - 1)]->setText("");
		m_indicators[2 * (number - 1) + 1]->setText("");
		return;
	}
	m_indicators[2 * (number - 1)]->setText(std::to_string(m_remaining[number - 1]).c_str());
	m_indicators[2 * (number - 1) + 1]->setText(std::to_string(m_remaining[number - 1]).c_str());
}
