#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
public:
	MainWindow();
	QWidget* wid;
	QGridLayout* lay;
};
