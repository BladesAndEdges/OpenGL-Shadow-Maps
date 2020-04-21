#include "Window.h"

Window::Window()
{
	setWindowTitle("Shadow Mapping - Geometric Processing Coursework 2");

	resize(1200, 800);

	//The layout of our window. It will only contain a single RenderWidget in it
	layout = new QGridLayout();

	renderWidget = new RenderWidget();
	layout->addWidget(renderWidget, 0, 0);



	setLayout(layout);
}

Window::~Window()
{
	delete(layout);
}

RenderWidget * Window::getRenderWidget() const
{
	return renderWidget;
}

CameraView * Window::getCameraOFRenderWidget() const
{
	return renderWidget->getCameraViewObject();
}
