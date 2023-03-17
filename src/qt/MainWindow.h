#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QEvent>
#include <QObject>
#include <QPushButton>

const uint32_t WHEEL_START = 2147484000;

class SudokuBoard;
class NumberWidget;
class TimerWidget;
class Tile;
class Menu;

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	void setMouseType(bool mouseType);

	SudokuBoard* board;
	NumberWidget* numbers;
	TimerWidget* timer;
	Menu* menu;

private:
	bool m_timerRunning;
	uint32_t m_currentNumber;
	int m_direction, m_scrollSpeed;
	std::array<bool, 81> m_visitedTiles;

	bool eventFilter(QObject* object, QEvent* event) override;
	void selectNumberButton(QPushButton* pressedButton = nullptr, int number = 0);

	void processHold(QEvent* event);
	void processPress(QEvent* event);
	void processRelease(QEvent* event);
	void processWheel(QEvent* event);
	void rightClick(Tile* tile);
	void leftClick(Tile* tile);

	bool checkForWin();

	int getSelectedNumber() { return m_currentNumber % (10 * m_scrollSpeed) / m_scrollSpeed; };

	Tile* getTileUnderMouse(QMouseEvent* mouseEvent);
};

struct MainStyleSheet
{
public:
	const char* getStyleSheet() { return sheet.c_str(); };

private:
	const std::string bgCol = "#0f0f0f";
	const std::string txtCol = "#a5a5a5";
	const std::string hvrCol = "#515b73";
	const std::string highCol = "#757575";
	const std::string bdrCol = "#5a5a5a";

	const std::string sheet =
		"QMainWindow {background: " + bgCol + "; }"
		"QWidget {background: " + bgCol + ";}"
		"QWidget#Tile {background: " + bgCol + ";}"

		"QLabel {background: " + bgCol + "; color: " + txtCol + ";}"

		"QLabel#ThinLine {background: " + bdrCol + ";}"
		"QLabel#ThickLine {background: " + txtCol + ";}"

		"QPushButton#Number {border: 2px solid " + bdrCol + "; color: " + txtCol + "; border-radius: 20;}"
		"QPushButton#Number::hover {background: " + hvrCol + "; color: " + bgCol + ";}"
		"QPushButton#Number::checked {background: " + txtCol + "; color: " + bgCol + ";}"

		"QPushButton#TileOpen {background: " + bgCol + "; color: " + txtCol + "; border-radius: 20;}"
		"QPushButton#TileOpen::hover {background: " + hvrCol + "; color: " + txtCol + ";}"

		"QPushButton#TileHigh {background: " + highCol + "; color: " + bgCol + "; border-radius: 20;}"
		"QPushButton#TileHigh::hover {background: " + hvrCol + "; color: " + txtCol + ";}"

		"QPushButton#TileFixed {background: #303030; color: " + bgCol + "; border-radius: 20;}"
		"QPushButton#TileFixed::hover {background: " + hvrCol + "; color: " + bgCol + ";}"

		"QMenuBar::item {background: " + "#303030" + "}"
		"QMenuBar::item::hover {background: " + hvrCol + "}";
};
