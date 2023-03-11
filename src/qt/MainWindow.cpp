#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>

const char* mainStyleSheet =
"QMainWindow {background: #0f0f0f;}"
"QWidget {background: #0f0f0f;}"
"QWidget#Tile {background: #0f0f0f;}"
"QLabel#ThinLine {background: #5a5a5a;}"
"QLabel#ThickLine {background: #bfbfbf;}"
"QPushButton#Number {border: 2px solid #5a5a5a; color: #b5b5b5; border-radius: 20;}"
"QPushButton#TileOpen {background: #0f0f0f; color: #b5b5b5; border-radius: 20;}"
"QPushButton#TileSet {background: #202020; color: #b5b5b5; border-radius: 20;}"
"QPushButton#TileOpen::hover {background: #3d3d3d; color: #b5b5b5;}"
"QPushButton#TileSet::hover {background: #3d3d3d; color: #b5b5b5;}";

MainWindow::MainWindow()
	: QMainWindow()
{
	SudokuBoard* board = new SudokuBoard(this, mainStyleSheet);
	QGridLayout* layout = new QGridLayout(this);
	QWidget* centralWidget = new QWidget(this);
	NumberWidget* numbers = new NumberWidget(this, mainStyleSheet);

	layout->addWidget(board, 0, 0);
	layout->addWidget(numbers, 1, 0);
	centralWidget->setLayout(layout);

	setCentralWidget(centralWidget);
}