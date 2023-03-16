#include "Menu.h"
#include "MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

Menu::Menu(MainWindow* main, QWidget* parent)
	: QMenuBar(parent), m_mainWindow(main)
{
	m_settings = addMenu("Settings");
	QMenu* mouseType = m_settings->addMenu("Mouse Type");
	QAction* acm = mouseType->addAction("Mouse");
	QAction* act = mouseType->addAction("Touchpad");

	connect(acm, &QAction::triggered, this, [this] {changeMouseType(true); });
	connect(act, &QAction::triggered, this, [this] {changeMouseType(false); });

	setStyleSheet("QMenu::item {background: #505050}");
}

void Menu::changeMouseType(bool type)
{
	m_mainWindow->setMouseType(type);
}
