#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QEvent>
#include <QObject>
#include <QPushButton>

const uint32_t WHEEL_START = 2147483610;

class SudokuBoard;
class NumberWidget;
class TimerWidget;
class Tile;

class MainWindow : public QMainWindow
{
public:
	MainWindow(bool useMouse);

	SudokuBoard* board;
	NumberWidget* numbers;
	TimerWidget* timer;

private:
	uint32_t m_currentNumber;
	std::array<bool, 81> m_visitedTiles;
	bool m_mouseUsed;

	bool eventFilter(QObject* object, QEvent* event) override;
	void selectNumberButton(QPushButton* pressedButton);

	void processHold(QEvent* event);
	void processPress(QEvent* event);
	void processRelease(QEvent* event);
	void processWheel(QEvent* event);

	int getSelectedNumber() { return m_currentNumber % 10; };
	int getSelectedNumberTouch() { return m_currentNumber % 200 / 20; };

	Tile* getTileUnderMouse(QMouseEvent* mouseEvent);
};
