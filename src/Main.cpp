#include <QApplication>
#include "qt/MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication* app = new QApplication(argc, argv);
	MainWindow* main = new MainWindow(false);
	main->show();

	int exitCode = app->exec();

	delete app, main;

	return exitCode;
}