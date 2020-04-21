#pragma once
#include <qwidget.h>
#include <qgridlayout.h>

#include "RenderWidget.h"

/*Main window class*/
class Window : public QWidget
{

private:

	QGridLayout* m_windowLayout;
	RenderWidget* m_renderWidgetInstance;

public:

	Window::Window();
	~Window();

	RenderWidget* getRenderWidgetInstance() const;
	CameraView* getCameraViewInstance() const;
};

