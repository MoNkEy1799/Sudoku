#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QEvent>
#include <QObject>

class SudokuBoard;
class NumberWidget;
class TimerWidget;

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	SudokuBoard* board;
	NumberWidget* numbers;
	TimerWidget* timer;

private:
	uint32_t m_currentNumber;

	bool eventFilter(QObject* object, QEvent* event) override;

	void processHold(QEvent* event);
	void processClick(QEvent* event);
	void processWheel(QEvent* event);
};
