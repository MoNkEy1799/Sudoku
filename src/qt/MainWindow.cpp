#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"
#include "TimerWidget.h"
#include "Tile.h"
#include "Menu.h"
#include "WinOverlay.h"
#include "../sudoku/SudokuSolver.h"

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
#include <QGraphicsBlurEffect>

#include <string>
#include <chrono>

void MainWindow::debug()
{
	winGame();
}

MainWindow::MainWindow()
	: QMainWindow(), m_currentNumber(WHEEL_START), m_direction(-1), m_scrollSpeed(1),
	m_timerRunning(false), m_visitedTiles({ false })
{
	m_centralWidget = new QWidget(this);
	m_layout = new QGridLayout(m_centralWidget);

	numbers = new NumberWidget(445, m_centralWidget);
	timer = new TimerWidget(445, m_centralWidget);
	menu = new Menu(this, m_centralWidget);
	setMenuBar(menu);
	createNewBoard(Difficulty::EASY);

	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->addWidget(timer, 0, 0);
	m_layout->addWidget(numbers, 2, 0);

	setStyleSheet(MainStyleSheet().getStyleSheet());
	move(500, 50);
	setMinimumWidth(600);
	setCentralWidget(m_centralWidget);
	setWindowIcon(QIcon("resources/icon.png"));
	setWindowTitle("Sudoku Game");

	for (QPushButton* button : numbers->findChildren<QPushButton*>())
	{
		connect(button, &QPushButton::clicked, timer, [this, button] { selectNumberButton(button, 0); });
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
		m_scrollSpeed = 10;
	}
}

void MainWindow::createNewBoard(Difficulty difficulty)
{
	if (board)
	{
		delete board;
	}

	if (timer)
	{
		m_timerRunning = false;
		timer->stopTimer();
		timer->resetTimer();
		timer->setGraphicsEffect(nullptr);
	}

	if (win)
	{
		delete win;
		win = nullptr;
	}

	board = new SudokuBoard(difficulty, m_centralWidget);
	m_layout->addWidget(board, 1, 0);

	for (Tile* tile : board->findChildren<Tile*>())
	{
		tile->getButton()->installEventFilter(this);
		tile->getButtonHighlight()->installEventFilter(this);
	}

	selectNumberButton(nullptr, 1);
	numbers->setNumber(0);
	numbers->setGraphicsEffect(nullptr);
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
	if (m_visitedTiles[tile->getId()])
	{
		return;
	}

	int id = tile->getId();
	int selectedNumber = getSelectedNumber();
	m_visitedTiles[id] = true;

	if (selectedNumber == 9)
	{
		tile->removeAllGuesses();
		tile->removeHighlight();
		board->currentGrid[id / 9][id % 9] = 0;
	}
	else
	{
		tile->addGuess(selectedNumber + 1);
		tile->highlightTile(selectedNumber + 1);
		board->currentGrid[id / 9][id % 9] = selectedNumber + 1;
	}
}

void MainWindow::processPress(QEvent* event)
{
	if (!m_timerRunning)
	{
		timer->startTimer();
		m_timerRunning = true;
	}

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
	int id = tile->getId();
	int selectedNumber = getSelectedNumber();
	m_visitedTiles[id] = true;

	if (selectedNumber == 9)
	{
		tile->removeAllGuesses();
		tile->removeHighlight();
		board->currentGrid[id / 9][id % 9] = 0;
	}
	else
	{
		tile->addGuess(selectedNumber+ 1);
		tile->highlightTile(selectedNumber + 1);
		board->currentGrid[id / 9][id % 9] = 0;
	}
}

void MainWindow::leftClick(Tile* tile)
{
	int id = tile->getId();
	int selectedNumber = getSelectedNumber();
	if (selectedNumber == 9)
	{
		tile->removeAllGuesses();
		tile->removeHighlight();
		board->currentGrid[id / 9][id % 9] = 0;
	}
	else
	{
		tile->addNumber(selectedNumber + 1);
		tile->highlightTile(selectedNumber + 1);
		board->currentGrid[id / 9][id % 9] = selectedNumber + 1;
	}

	if (checkForWin())
	{
		winGame();
	}
}

bool MainWindow::checkForWin()
{
	return (countUnfilledTiles() == 0 && board->isBoardFinished());
}

int MainWindow::countUnfilledTiles()
{
	int res = 0;
	for (std::array<int, 9> row : board->currentGrid)
	{
		res += std::count(row.begin(), row.end(), 0);
	}
	return res;
}

void MainWindow::winGame()
{
	win = new WinOverlay(this, m_centralWidget);
	m_layout->addWidget(win, 0, 0, 3, 1, Qt::AlignBottom);
	timer->stopTimer();
	timer->setGraphicsEffect(new QGraphicsBlurEffect(this));
	board->setGraphicsEffect(new QGraphicsBlurEffect(this));
	numbers->setGraphicsEffect(new QGraphicsBlurEffect(this));
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
