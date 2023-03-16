#include "NumberWidget.h"

#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QFont>
#include <QButtonGroup>

#include <string>

NumberWidget::NumberWidget(int width, QWidget* parent)
	: QWidget(parent), m_numbers()
{
	m_layout = new QGridLayout(this);
	setMinimumHeight(150);
	setMaximumWidth(width);

	QFont font = QFont("Sans-Serif", 16);
	font.setBold(true);

	QButtonGroup* group = new QButtonGroup(this);

	for (int i = 0; i < 10; i++)
	{
		QPushButton* button = new QPushButton(std::to_string(i + 1).c_str(), this);
		m_numbers[i] = button;
		button->setFont(font);
		button->setFixedSize(50, 50);
		button->setObjectName("Number");
		button->setCheckable(true);
		group->addButton(button);

		if (i < 5)
		{
			m_layout->addWidget(button, 0, i);
		}

		else if (i < 9)
		{
			m_layout->addWidget(button, 1, i - 5);
		}

		else
		{
			button->setText("X");
			m_layout->addWidget(button, 1, 4);
		}
	}

	m_numbers[0]->setChecked(true);
}
