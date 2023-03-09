#include <QApplication>
#include "qt/MainWindow.h"

#include <QLabel>

int main(int argc, char* argv[])
{
	QApplication app = QApplication(argc, argv);
	MainWindow* main = new MainWindow();
	main->show();

	return app.exec();
}