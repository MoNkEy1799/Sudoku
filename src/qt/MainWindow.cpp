#include "MainWindow.h"
#include "SudokuBoard.h"

MainWindow::MainWindow()
	: QMainWindow()
{
	SudokuBoard* board = new SudokuBoard(this);
	setCentralWidget(board);
}

MainWindow::~MainWindow()
{
}