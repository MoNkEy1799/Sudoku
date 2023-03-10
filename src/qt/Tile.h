#pragma once

#include <QWidget>
#include <QPushButton>

#include <string>

class Tile : public QWidget
{
public:
	Tile(QWidget* parent = nullptr, const char* = nullptr);

	void addGuess(int guess);
	void setNumber(int number);

private:
	std::vector<int> m_guess;
	QPushButton* m_inner;
};
