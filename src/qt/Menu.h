#pragma once

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
	MainWindow* m_mainWindow;

	void changeMouseType(bool type);
};
