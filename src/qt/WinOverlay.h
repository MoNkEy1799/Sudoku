#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class MainWindow;

class WinOverlay : public QWidget
{
	Q_OBJECT

public:
	WinOverlay(MainWindow* main, QWidget* parent = nullptr);

private:
	MainWindow* m_mainWindow;
};

