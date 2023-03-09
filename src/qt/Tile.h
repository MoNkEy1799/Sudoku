#pragma once

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class Tile : public QPushButton
{
public:
	Tile(QWidget* parent = nullptr);
	~Tile();

private:
	std::vector<int> m_guess;

protected:
};
