

#include <qapplication.h>
#include <qdebug.h>
#include "RenderWidget.h"
#include "Shader.h"
#include <string.h>


#include "Window.h"
#include "InputController.h"

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);

	Window* window = new Window();

	InputController controller(window);

	app.installEventFilter(&controller);


	window->show();

	/*Starts up the main Qt loop*/
	return app.exec();
}