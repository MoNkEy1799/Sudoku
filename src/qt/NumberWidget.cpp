#include "NumberWidget.h"

#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QFont>

#include <string>

NumberWidget::NumberWidget(QWidget* parent)
	: QWidget(parent), m_numbers()
{
	m_layout = new QGridLayout(this);
	setMinimumHeight(150);

	QFont font = QFont("Sans-Serif", 16);
	font.setBold(true);

	for (int i = 0; i < 9; i++)
	{
		QPushButton* button = new QPushButton(std::to_string(i + 1).c_str(), this);
		m_numbers[i] = button;
		button->setFont(font);
		button->setFixedSize(50, 50);
		button->setObjectName("Number");

		if (i < 5)
		{
			m_layout->addWidget(button, 0, i);
		}

		else
		{
			m_layout->addWidget(button, 1, i - 5);
		}
	}
}
