#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"
#include "TimerWidget.h"
#include "Tile.h"

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QMenuBar>
#include <QTimer>
#include <QEvent>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QList>
#include <QHoverEvent>
#include <QApplication>

#include <string>

std::string bgCol = "#0f0f0f";
std::string txtCol = "#a5a5a5";
std::string hvrCol = "#757575";
std::string bdrCol = "#5a5a5a";

std::string styleSheet =
"QMainWindow {background: " + bgCol + "; }"
"QWidget {background: " + bgCol + ";}"
"QWidget#Tile {background: " + bgCol + ";}"

"QLabel {background: " + bgCol + "; color: " + txtCol + ";}"

"QLabel#ThinLine {background: " + bdrCol + ";}"
"QLabel#ThickLine {background: " + txtCol + ";}"

"QPushButton#Number {border: 2px solid " + bdrCol + "; color: " + txtCol + "; border-radius: 20;}"
"QPushButton#Number:hover {background: " + hvrCol + "; color: " + bgCol + ";}"
"QPushButton#Number:checked {background: " + txtCol + "; color: " + bgCol + ";}"

"QPushButton#TileOpen {background: " + bgCol + "; color: " + txtCol + "; border-radius: 20;}"
"QPushButton#TileOpen:hover {background: " + hvrCol + "; color: " + bgCol + ";}"

"QPushButton#TileFixed {background: #303030; color: " + bgCol + "; border-radius: 20;}"
"QPushButton#TileFixed:hover {background: " + hvrCol + "; color: " + bgCol + ";}";

const char* mainStyleSheet = styleSheet.c_str();

MainWindow::MainWindow()
	: QMainWindow(), m_currentNumber(2147483610), m_visitedTiles({ false })
{
	QWidget* centralWidget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(centralWidget);

	board = new SudokuBoard(centralWidget);
	numbers = new NumberWidget(445, centralWidget);
	timer = new TimerWidget(445, centralWidget);

	for (Tile* tile : board->findChildren<Tile*>())
	{
		tile->getButton()->installEventFilter(this);
	}

	//installEventFilter(this);
	//board->installEventFilter(this);
	//numbers->installEventFilter(this);
	//timer->installEventFilter(this);

	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(timer, 0, 0);
	layout->addWidget(board, 1, 0);
	layout->addWidget(numbers, 2, 0);

	setStyleSheet(mainStyleSheet);
	move(500, 50);
	setMinimumWidth(600);

	for (QPushButton* button : numbers->findChildren<QPushButton*>())
	{
		connect(button, &QPushButton::clicked, timer, &TimerWidget::startMyTimer);
	}

	setCentralWidget(centralWidget);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
	switch (event->type())
	{
	case QEvent::MouseMove:
		processHold(event);
		break;

	case QEvent::MouseButtonPress:
		processPress(event);
		break;

	case QEvent::MouseButtonRelease:
		processRelease(event);
		break;

	case QEvent::Wheel:
		processWheel(event);
		break;
	}

	return false;
}

void MainWindow::processHold(QEvent* event)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

	if (mouseEvent->buttons() != Qt::RightButton)
	{
		return;
	}

	Tile* tile = getTileUnderMouse(mouseEvent);

	if (tile)
	{
		bool visited = m_visitedTiles[tile->getId()];

		if (!visited)
		{
			tile->getButton()->setText(std::to_string(getSelectedNumber()).c_str());
			m_visitedTiles[tile->getId()] = true;
		}
	}
}

void MainWindow::processPress(QEvent* event)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

	if (mouseEvent->buttons() != Qt::RightButton)
	{
		return;
	}

	Tile* tile = getTileUnderMouse(mouseEvent);

	if (tile)
	{
		qDebug() << getSelectedNumber() + 1;
		//tile->addGuess(getSelectedNumber() + 1);
	}
}

void MainWindow::processRelease(QEvent* event)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

	if (mouseEvent->buttons() == Qt::NoButton)
	{
		m_visitedTiles = { false };
	}
}

void MainWindow::processWheel(QEvent* event)
{
	QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

	if (wheelEvent->angleDelta().y() > 0)
	{
		m_currentNumber--;
	}

	else
	{
		m_currentNumber++;
	}

	numbers->setNumber(getSelectedNumber());
}

Tile* MainWindow::getTileUnderMouse(QMouseEvent* mouseEvent)
{
	QPoint pos = mouseEvent->globalPos();
	std::array<Tile*, 81> tiles = board->getTiles();

	for (int i = 0; i < 81; i++)
	{
		QRect local = tiles[i]->geometry();
		QRect global = QRect(board->mapToGlobal(local.topLeft()), local.size());

		if (global.contains(pos))
		{
			return tiles[i];
		}
	}

	return nullptr;
}
