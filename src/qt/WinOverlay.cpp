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
	int time = m_mainWindow->timer->geometry().size().height();
	int num = m_mainWindow->numbers->geometry().size().height();
	int board = m_mainWindow->board->geometry().size().height();
	setFixedHeight(time + num + board - 14);

	QFont font = QFont("Sans-Serif", 60);
	font.setBold(true);

	QLabel* win = new QLabel(this);
	win->setText("WIN!");
	win->setFont(font);
	win->setObjectName("Win");
	win->setAlignment(Qt::AlignCenter);

	QPushButton* newGame = new QPushButton("New Game", this);
	newGame->setObjectName("Win");
	connect(newGame, &QPushButton::clicked, this, [this] { m_mainWindow->createNewBoard(Difficulty::HARD); });

	QPushButton* highscore = new QPushButton("Highscores", this);
	highscore->setObjectName("Win");
	connect(highscore, &QPushButton::clicked, this, [this] { qDebug() << "click"; });

	QWidget* topSpacer = new QWidget(this);
	topSpacer->setFixedHeight(240);
	topSpacer->setObjectName("Win");
	QWidget* bottomSpacer = new QWidget(this);
	bottomSpacer->setFixedHeight(250);
	bottomSpacer->setObjectName("Win");

	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(topSpacer, 0, 0, 1, 2);
	layout->addWidget(win, 1, 0, 1, 2);
	layout->addWidget(newGame, 2, 0);
	layout->addWidget(highscore, 2, 1);
	layout->addWidget(bottomSpacer, 3, 0, 1, 2);
	setLayout(layout);
}
