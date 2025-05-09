#include "IKMainWindow.h"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/images/appicon.ico"));

	IKMainWindow mainWindow;
	mainWindow.resize(1200, 800);
	mainWindow.setWindowTitle("Inverse Kinematics");
	mainWindow.show();

	return app.exec();
}
