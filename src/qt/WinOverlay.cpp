#include "WinOverlay.h"
#include "MainWindow.h"

#include <QFont>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QRect>

WinOverlay::WinOverlay(MainWindow* main, QWidget* parent)
	: QWidget(parent), m_mainWindow(main)
{
	QFont font = QFont("Sans-Serif", 60);
	font.setBold(true);

	QLabel* win = new QLabel(this);
	win->setText("WIN!");
	win->setFont(font);
	win->setObjectName("Win");

	setFixedSize(800, 800);
	move(0, 20);

	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(win);
}
