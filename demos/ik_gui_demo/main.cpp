#include "IKMainWindow.h"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	IKMainWindow mainWindow;
	mainWindow.resize(1200, 800);
	mainWindow.setWindowTitle("IK GUI Demo");
	mainWindow.show();

	return app.exec();
}
