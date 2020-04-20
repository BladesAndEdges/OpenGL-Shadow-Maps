#pragma once

#include<QWidget>
#include<QGridLayout> // Allows Qt grid layout structure for widgets

#include "RenderWidget.h"

/*
	This class represents our main window.
*/

class Window : public QWidget
{

private:

	QGridLayout* m_mainLayout;
	RenderWidget* m_renderWidget;

public:

	Window();
	~Window();

	RenderWidget* getRenderWidgetInstance() const;
	CameraView* getCameraViewInstance() const;
};

