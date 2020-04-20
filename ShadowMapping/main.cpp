#include<QApplication>

#include "Window.h"
#include "InputController.h"

int main(int argc, char* argv[])
{
	/*The QApplication object manages all Qt widget-based application*/
	QApplication app(argc, argv);

	/*Creat main window instance*/
	Window* window = new Window();

	InputController controller(window);

	app.installEventFilter(&controller);

	window->show();

	/*Begins the main event loop. Terminates upon exit*/
	return app.exec();
}