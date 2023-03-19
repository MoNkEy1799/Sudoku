#include "WinOverlay.h"
#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"
#include "TimerWidget.h"

#include <QFont>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QSize>

WinOverlay::WinOverlay(MainWindow* main, QWidget* parent)
	: QWidget(parent), m_mainWindow(main)
{
	QFont font = QFont("Sans-Serif", 60);
	font.setBold(true);

	QLabel* win = new QLabel(this);
	win->setText("WIN!");
	win->setFont(font);
	win->setObjectName("Win");

	int time = m_mainWindow->timer->geometry().size().height();
	int num = m_mainWindow->numbers->geometry().size().height();
	int board = m_mainWindow->board->geometry().size().height();
	setFixedHeight(time + num + board);

	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(win);
}
