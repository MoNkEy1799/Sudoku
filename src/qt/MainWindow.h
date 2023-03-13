#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QEvent>
#include <QObject>

class MainWindow : public QMainWindow
{
public:
	MainWindow();

	void test();
	void rirarun();

private:
	bool eventFilter(QObject* object, QEvent* event) override;
};
