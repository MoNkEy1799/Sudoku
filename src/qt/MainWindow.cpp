#include "MainWindow.h"
#include "SudokuBoard.h"

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>

const char* mainStyleSheet =
"QMainWindow {background: #0f0f0f;}"
"QWidget {background: #0f0f0f;}"
"QPushButton {background: #303030; color: #b5b5b5; border-radius: 20;}"
"QPushButton::hover {background: #3d3d3d; color: #b5b5b5;}";

MainWindow::MainWindow()
	: QMainWindow()
{
	SudokuBoard* board = new SudokuBoard(this, mainStyleSheet);
	QGridLayout* layout = new QGridLayout(this);
	QWidget* centralWidget = new QWidget(this);

	layout->addWidget(board);
	centralWidget->setLayout(layout);

	setCentralWidget(centralWidget);
}