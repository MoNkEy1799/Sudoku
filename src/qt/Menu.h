#pragma once
#include "../sudoku/SudokuGenerator.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>

class MainWindow;

class Menu : public QMenuBar
{
	Q_OBJECT

public:
	Menu(MainWindow* main, QWidget* parent);

private:
	QMenu* m_settings;
	QAction* m_highscore;
	MainWindow* m_mainWindow;

	void changeMouseType(bool type);
	void newBoard(Difficulty difficulty);
};
