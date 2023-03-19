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
	int timeHeight = m_mainWindow->timer->geometry().size().height();
	int numHeight = m_mainWindow->numbers->geometry().size().height();
	int boardHeight = m_mainWindow->board->geometry().size().height();
	setFixedHeight(timeHeight + numHeight + boardHeight - 14);

	QLabel* win = new QLabel(this);
	win->setText("WIN!");
	win->setFont(QFont("Sans-Serif", 60, QFont::Bold));
	win->setObjectName("Win");
	win->setAlignment(Qt::AlignCenter);

	QLabel* time = new QLabel(this);
	time->setText(m_mainWindow->timer->getTime().c_str());
	time->setFont(QFont("Sans-Serif", 30, QFont::Bold));
	time->setObjectName("Win");
	time->setAlignment(Qt::AlignCenter);

	QPushButton* newGame = new QPushButton("New Game", this);
	newGame->setFont(QFont("Sans-Serif", 12));
	newGame->setMinimumHeight(24);
	newGame->setObjectName("Win");
	connect(newGame, &QPushButton::clicked, this, [this] { m_mainWindow->createNewBoard(Difficulty::HARD); });

	QPushButton* highscore = new QPushButton("Highscores", this);
	highscore->setFont(QFont("Sans-Serif", 12));
	highscore->setMinimumHeight(24);
	highscore->setObjectName("Win");
	connect(highscore, &QPushButton::clicked, this, [this] { qDebug() << "click"; });

	QWidget* topSpacer = new QWidget(this);
	topSpacer->setMinimumHeight(240);
	topSpacer->setObjectName("Win");

	QWidget* bottomSpacer = new QWidget(this);
	bottomSpacer->setMinimumHeight(200);
	bottomSpacer->setObjectName("Win");

	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(topSpacer, 0, 0, 1, 2);
	layout->addWidget(win, 1, 0, 1, 2);
	layout->addWidget(time, 2, 0, 1, 2);
	layout->addWidget(newGame, 3, 0);
	layout->addWidget(highscore, 3, 1);
	layout->addWidget(bottomSpacer, 4, 0, 1, 2);
	setLayout(layout);
}
