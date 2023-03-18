#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include <array>

class NumberWidget : public QWidget
{
	Q_OBJECT

public:
	NumberWidget(int width, QWidget* parent = nullptr);

	void setNumber(int index) { m_numbers[index]->setChecked(true); };

private:
	std::array<QPushButton*, 10> m_numbers;
	QGridLayout* m_layout;
};
