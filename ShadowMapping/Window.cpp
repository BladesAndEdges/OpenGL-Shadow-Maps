#include "Window.h"

Window::Window()
{
	/*General window stuff*/
	setWindowTitle("Geometric Processing Coursework 2: Shadow Maps");
	resize(1200, 800);

	m_mainLayout = new QGridLayout();

	m_renderWidget = new RenderWidget();

	/*Add the widget to the layout*/
	m_mainLayout->addWidget(m_renderWidget, 0, 0);

	/*Set the layout as the window's main layout*/
	setLayout(m_mainLayout);
}

Window::~Window()
{
	delete m_renderWidget;
	delete m_mainLayout;
}

/*Getters for renderWidget and CameraView object*/
RenderWidget * Window::getRenderWidgetInstance() const
{
	return m_renderWidget;
}

CameraView * Window::getCameraViewInstance() const
{
	return m_renderWidget->getCameraViewObject();
}
