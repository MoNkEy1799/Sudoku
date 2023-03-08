#include <QApplication>
#include "qt/MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app = QApplication(argc, argv);
	MainWindow main = MainWindow();

	main.show();

	return app.exec();
}