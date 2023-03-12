#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include <array>

class NumberWidget : public QWidget
{

	Q_OBJECT

public:
	NumberWidget(QWidget* parent = nullptr);

private:
	std::array<QPushButton*, 9> m_numbers;
	QGridLayout* m_layout;
};
