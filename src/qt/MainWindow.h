#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QEvent>
#include <QObject>

class SudokuBoard;
class NumberWidget;
class TimerWidget;
class Tile;

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	SudokuBoard* board;
	NumberWidget* numbers;
	TimerWidget* timer;

	int getSelectedNumber() { return m_currentNumber % 200 / 20; };

private:
	uint32_t m_currentNumber;
	std::array<bool, 81> m_visitedTiles;

	bool eventFilter(QObject* object, QEvent* event) override;

	void processHold(QEvent* event);
	void processPress(QEvent* event);
	void processRelease(QEvent* event);
	void processWheel(QEvent* event);

	Tile* getTileUnderMouse(QMouseEvent* mouseEvent);
};
