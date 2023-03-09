#include "MainWindow.h"

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow()
	: QMainWindow()
{
	lay = new QGridLayout(this);
	QLabel* lab = new QLabel("test");
	lay->addWidget(lab);

	wid = new QWidget(this);
	wid->setLayout(lay);

	setCentralWidget(wid);
}