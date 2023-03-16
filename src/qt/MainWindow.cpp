#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"
#include "TimerWidget.h"
#include "Tile.h"
#include "Menu.h"

#include <QPushButton>
#include <QWidget>
#include <QGridLayout>

#include <QTimer>
#include <QEvent>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QList>
#include <QHoverEvent>
#include <QApplication>
#include <QIcon>

#include <string>
#include <chrono>

MainWindow::MainWindow()
	: QMainWindow(), m_currentNumber(WHEEL_START), m_visitedTiles({ false }), m_direction(-1), m_scrollSpeed(1)
{
	QWidget* centralWidget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(centralWidget);

	board = new SudokuBoard(centralWidget);
	numbers = new NumberWidget(445, centralWidget);
	timer = new TimerWidget(445, centralWidget);
	timer->startMyTimer();

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

	setStyleSheet(MainStyleSheet().getStyleSheet());
	move(500, 50);
	setMinimumWidth(600);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("resources/icon.png"));
	setWindowTitle("Sudoku Game");

	Menu* menu = new Menu(this, centralWidget);

	for (QPushButton* button : numbers->findChildren<QPushButton*>())
	{
		connect(button, &QPushButton::clicked, timer, [this, button] { selectNumberButton(button, 0); });

		if (button->text().contains("1"))
		{
			selectNumberButton(button);
			button->setChecked(true);
		}
	}
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

void MainWindow::selectNumberButton(QPushButton* pressedButton, int number)
{
	board->removeAllHighlights();

	if (!pressedButton)
	{
		numbers->setNumber(number - 1);
		if (number < 10)
		{
			board->highlightTiles(number);
		}
	}

	else
	{
		if (pressedButton->text().contains("X"))
		{
			number = 10;
		}

		else
		{
			number = std::stoi(pressedButton->text().toStdString());
			board->highlightTiles(number);
		}

		m_currentNumber = WHEEL_START + (number - 1) * m_scrollSpeed;
	}
}

void MainWindow::setMouseType(bool mouse)
{
	if (mouse)
	{
		m_direction = -1;
		m_scrollSpeed = 1;
	}

	else
	{
		m_direction = 1;
		m_scrollSpeed = 20;
	}
}

void MainWindow::processHold(QEvent* event)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
	Qt::MouseButtons buttons = mouseEvent->buttons();

	if (buttons != Qt::RightButton || buttons == Qt::LeftButton)
	{
		return;
	}

	Tile* tile = getTileUnderMouse(mouseEvent);

	if (!tile || tile->getState() == TileState::FIXED)
	{
		return;
	}

	bool visited = m_visitedTiles[tile->getId()];

	if (visited)
	{
		return;
	}

	m_visitedTiles[tile->getId()] = true;

	if (getSelectedNumber() == 9)
	{
		tile->removeAllGuesses();
	}

	else
	{
		tile->addGuess(getSelectedNumber() + 1);
	}
}

void MainWindow::processPress(QEvent* event)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
	Tile* tile = getTileUnderMouse(mouseEvent);

	if (!tile || tile->getState() == TileState::FIXED)
	{
		return;
	}

	switch (mouseEvent->button())
	{
	case Qt::RightButton:
		rightClick(tile);
		break;

	case Qt::LeftButton:
		leftClick(tile);
		break;
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

	if (m_direction * wheelEvent->angleDelta().y() > 0)
	{
		m_currentNumber--;
	}

	else
	{
		m_currentNumber++;
	}

	selectNumberButton(nullptr, getSelectedNumber() + 1);
}

void MainWindow::rightClick(Tile* tile)
{
	m_visitedTiles[tile->getId()] = true;

	if (getSelectedNumber() == 9)
	{
		tile->removeAllGuesses();
	}

	else
	{
		tile->addGuess(getSelectedNumber() + 1);
	}
}

void MainWindow::leftClick(Tile* tile)
{
	if (getSelectedNumber() == 9)
	{
		tile->removeAllGuesses();
	}

	else
	{
		tile->addNumber(getSelectedNumber() + 1);
	}
}

Tile* MainWindow::getTileUnderMouse(QMouseEvent* mouseEvent)
{
	QPoint pos = mouseEvent->globalPos();
	std::array<Tile*, 81>& tiles = board->getTiles();

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
