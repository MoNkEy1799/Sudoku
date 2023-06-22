#include "MainWindow.h"
#include "SudokuBoard.h"
#include "NumberWidget.h"
#include "TimerWidget.h"
#include "Tile.h"
#include "Menu.h"
#include "WinOverlay.h"
#include "Highscores.h"
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
#include <QTabWidget>
#include <QTabBar>

#include <string>
#include <chrono>
#include <numbers>
#include <cmath>

MainWindow::MainWindow()
	: QMainWindow(), m_currentNumber(WHEEL_START), m_direction(-1), m_scrollSpeed(1),
	board(nullptr), numbers(nullptr), timer(nullptr), menu(nullptr), win(nullptr), highscore(nullptr),
	m_timerRunning(false), m_visitedTiles({ false }), m_highscoreWidget(nullptr)
{
	m_centralWidget = new QWidget(this);
	m_layout = new QGridLayout(m_centralWidget);

	highscore = new Highscores(this);
	numbers = new NumberWidget(445, m_centralWidget);
	timer = new TimerWidget(445, highscore, m_centralWidget);
	menu = new Menu(this, m_centralWidget);
	makeHighscoreWidget();
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
		int time = timer->stopTimer();
		highscore->addStat(Stats::TIME, time, true);
		timer->resetTimer();
		timer->setGraphicsEffect(nullptr);
	}
	if (win)
	{
		delete win;
		win = nullptr;
	}

	board = new SudokuBoard(difficulty, m_centralWidget);
	highscore->addStat(Stats::BOARDS, 1, true);
	m_layout->addWidget(board, 1, 0);

	for (Tile* tile : board->findChildren<Tile*>())
	{
		tile->getButton()->installEventFilter(this);
		tile->getButtonHighlight()->installEventFilter(this);
	}

	selectNumberButton(nullptr, 1);
	numbers->setGraphicsEffect(nullptr);
	numbers->initRemaining(board->currentGrid);
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
		numbers->setNumber(number - 1);
	}
}

void MainWindow::makeHighscoreWidget()
{
	if (m_highscoreWidget)
	{
		m_highscoreWidget->deleteLater();
		highscore->scoreStatChanged = false;
	}

	m_highscoreWidget = new QWidget();
	m_highscoreWidget->setMinimumSize(400, 400);
	m_highscoreWidget->setWindowTitle("Highscores & Stats");
	m_highscoreWidget->setWindowIcon(QIcon("resources/icon.png"));
	m_highscoreWidget->setStyleSheet(MainStyleSheet().getStyleSheet());
	QGridLayout* layout = new QGridLayout(m_highscoreWidget);

	QTabWidget* tabWidget = new QTabWidget();
	tabWidget->tabBar()->setExpanding(true);
	tabWidget->tabBar()->setDocumentMode(true);
	layout->addWidget(tabWidget);
	std::array<std::string, 4> diffNames = { "EASY", "MEDIUM", "HARD", "EXTREME" };
	for (int diff = 0; diff < 4; diff++)
	{
		QWidget* widget = new QWidget();
		QGridLayout* tabLayout = new QGridLayout();
		widget->setLayout(tabLayout);
		tabWidget->addTab(widget, diffNames[diff].c_str());

		for (int place = 0; place < 10; place++)
		{
			std::string score = highscore->formattedScore((Difficulty)(diff + 1), place, false);
			QLabel* qlabel = new QLabel((std::to_string(place + 1) + ". " + score).c_str());
			QLabel* line = new QLabel();
			line->setObjectName("ThinLine");
			line->setFixedHeight(1);
			if (place < 5)
			{
				tabLayout->addWidget(qlabel, (place % 5) * 2, 0);
				tabLayout->addWidget(line, (place % 5) * 2 + 1, 0);
			}
			else
			{
				tabLayout->addWidget(qlabel, (place % 5) * 2, 1);
				tabLayout->addWidget(line, (place % 5) * 2 + 1, 1);
			}
		}
	}
	QWidget* statsWidget = new QWidget();
	layout->addWidget(statsWidget);
	QGridLayout* statsLayout = new QGridLayout();
	statsWidget->setLayout(statsLayout);

	QLabel* head = new QLabel("- RANDOM GAME STATS -");
	QFont stdFont = QApplication::font();
	stdFont.setBold(true);
	stdFont.setPointSizeF(12);
	head->setFont(stdFont);
	statsLayout->addWidget(head, 0, 0, 1, 2, Qt::AlignCenter);
	QLabel* game = new QLabel("Sudokus generated: ");
	statsLayout->addWidget(game, 1, 0);
	QLabel* won = new QLabel("Games won: ");
	statsLayout->addWidget(won, 2, 0);
	QLabel* time = new QLabel("Total time played: ");
	statsLayout->addWidget(time, 3, 0);
	QLabel* left = new QLabel("Numbers set: ");
	statsLayout->addWidget(left, 4, 0);
	QLabel* right = new QLabel("Guesses added: ");
	statsLayout->addWidget(right, 5, 0);
	QLabel* wheel = new QLabel("Distance scrolled: ");
	statsLayout->addWidget(wheel, 6, 0);
	for (int stat = 0; stat < 6; stat++)
	{
		statsLayout->addWidget(new QLabel(highscore->getStat((Stats)stat).c_str()), stat + 1, 1, Qt::AlignRight);
	}
}

void MainWindow::showHighscore()
{
	if (highscore->scoreStatChanged)
	{
		makeHighscoreWidget();
	}
	m_highscoreWidget->show();
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
	if (!tile || tile->getState() == TileState::FIXED || tile->getState() == TileState::SET)
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
	highscore->addStat(Stats::GUESS, 1);

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
	float angle = wheelEvent->angleDelta().y() / 8.0f;
	highscore->addStat(Stats::WHEEL, std::abs(angle / 360.0f * 2 * std::numbers::pi * 2.54f * 10.0f));
	if (m_direction * angle > 0)
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
	highscore->addStat(Stats::GUESS, 1);
	int id = tile->getId();
	int selectedNumber = getSelectedNumber();
	m_visitedTiles[id] = true;

	if (tile->getState() == TileState::SET)
	{
		numbers->changeRemaining(tile->getButton()->text().toInt(), true);
	}

	if (selectedNumber == 9)
	{
		tile->setState(TileState::GUESS);
		tile->removeAllGuesses();
		tile->removeHighlight();
		board->currentGrid[id / 9][id % 9] = 0;
	}
	else
	{
		tile->addGuess(selectedNumber + 1);
		tile->highlightTile(selectedNumber + 1);
		board->currentGrid[id / 9][id % 9] = 0;
	}
}

void MainWindow::leftClick(Tile* tile)
{
	highscore->addStat(Stats::SET, 1);
	int id = tile->getId();
	int selectedNumber = getSelectedNumber();
	if (selectedNumber == 9)
	{
		if (tile->getState() == TileState::SET)
		{
			numbers->changeRemaining(tile->getButton()->text().toInt(), true);
		}
		tile->setState(TileState::GUESS);
		tile->removeAllGuesses();
		tile->removeHighlight();
		board->currentGrid[id / 9][id % 9] = 0;
	}
	else
	{
		numbers->changeRemaining(selectedNumber + 1, false);
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
	timer->updateLabel(false);
	win = new WinOverlay(this, m_centralWidget);
	m_layout->addWidget(win, 0, 0, 3, 1, Qt::AlignBottom);
	int time = timer->stopTimer();
	highscore->addStat(Stats::TIME, time);
	highscore->addStat(Stats::WON, 1);
	highscore->addScore(board->gridInfo.difficultly, time);
	timer->setGraphicsEffect(new QGraphicsBlurEffect(this));
	board->setGraphicsEffect(new QGraphicsBlurEffect(this));
	numbers->setGraphicsEffect(new QGraphicsBlurEffect(this));
}

int MainWindow::getSelectedNumber()
{
	return m_currentNumber % (10 * m_scrollSpeed) / m_scrollSpeed;
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
