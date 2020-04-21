#pragma once
#include <qwidget.h>
#include <qgridlayout.h>

#include "RenderWidget.h"

/*A big portion of how to set up proper debugging using Qt5 was referenced from https://www.trentreed.net/blog/qt5-opengl-part-5-debug-logging/ */
class QOpenGLDebugMessage;
class QOpenGLDebugLogger;


class Window : public QWidget
{

private:

	QGridLayout* layout;
	RenderWidget* renderWidget;

public:

	Window::Window();
	~Window();

	RenderWidget* getRenderWidget() const;
	CameraView* getCameraOFRenderWidget() const;
};

