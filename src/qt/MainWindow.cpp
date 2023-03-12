#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"
#include "TimerWidget.h"

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>
#include <QTimer>
#include <iostream>

const char* mainStyleSheet =
"QMainWindow {background: #0f0f0f;}"
"QWidget {background: #0f0f0f;}"
"QWidget#Tile {background: #0f0f0f;}"
"QLabel {color: #b5b5b5;}"
"QLabel#ThinLine {background: #5a5a5a;}"
"QLabel#ThickLine {background: #bfbfbf;}"
"QPushButton#Number {border: 2px solid #5a5a5a; color: #b5b5b5; border-radius: 20;}"
"QPushButton#Number::hover {background: #3d3d3d;}"
"QPushButton#TileOpen {background: #0f0f0f; color: #b5b5b5; border-radius: 20;}"
"QPushButton#TileSet {background: #202020; color: #0f0f0f; border-radius: 20;}"
"QPushButton#TileOpen::hover {background: #3d3d3d; color: #b5b5b5;}"
"QPushButton#TileSet::hover {background: #3d3d3d; color: #b5b5b5;}";

MainWindow::MainWindow()
	: QMainWindow()
{
	QWidget* centralWidget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(centralWidget);

	SudokuBoard* board = new SudokuBoard(centralWidget);
	NumberWidget* numbers = new NumberWidget(centralWidget);
	TimerWidget* timer = new TimerWidget(centralWidget);

	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(timer, 0, 0);
	layout->addWidget(board, 1, 0);
	layout->addWidget(numbers, 2, 0);

	setStyleSheet(mainStyleSheet);
	move(500, 50);

	for (QPushButton* button : numbers->findChildren<QPushButton*>())
	{
		connect(button, &QPushButton::clicked, timer, &TimerWidget::startMyTimer);
	}

	setCentralWidget(centralWidget);
}

void MainWindow::test()
{
	QTimer* tim = new QTimer(this);
	connect(tim, &QTimer::timeout, this, &MainWindow::rirarun);
	tim->start(1000);
}

void MainWindow::rirarun()
{
	std::cout << "run" << std::endl;
}
