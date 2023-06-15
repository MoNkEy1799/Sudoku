#include "Menu.h"
#include "MainWindow.h"
#include "../sudoku/SudokuGenerator.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

Menu::Menu(MainWindow* main, QWidget* parent)
	: QMenuBar(parent), m_mainWindow(main)
{
	m_settings = addMenu("Settings");
	QMenu* mouseType = m_settings->addMenu("Mouse Type");
	QAction* mouse = mouseType->addAction("Mouse");
	QAction* touchpad = mouseType->addAction("Touchpad");

	connect(mouse, &QAction::triggered, this, [this] { changeMouseType(true); });
	connect(touchpad, &QAction::triggered, this, [this] { changeMouseType(false); });

	QMenu* newGame = m_settings->addMenu("New Game");
	QAction* easy = newGame->addAction("Easy");
	QAction* medium = newGame->addAction("Medium");
	QAction* hard = newGame->addAction("Hard");
	QAction* extreme = newGame->addAction("Extreme");

	connect(easy, &QAction::triggered, this, [this] { newBoard(Difficulty::EASY); });
	connect(medium, &QAction::triggered, this, [this] { newBoard(Difficulty::MEDIUM); });
	connect(hard, &QAction::triggered, this, [this] { newBoard(Difficulty::HARD); });
	connect(extreme, &QAction::triggered, this, [this] { newBoard(Difficulty::EXTREME); });
	
	m_highscore = addMenu("Highscores");

	QAction* debug = addAction("Debug");
	connect(debug, &QAction::triggered, m_mainWindow, &MainWindow::debug);

	setMinimumWidth(2000);
}

void Menu::changeMouseType(bool type)
{
	m_mainWindow->setMouseType(type);
}

void Menu::newBoard(Difficulty difficulty)
{
	m_mainWindow->createNewBoard(difficulty);
}
