#include "Window.h"

Window::Window()
{
	setWindowTitle("Shadow Mapping - Geometric Processing Coursework 2");

	resize(1200, 800);

	m_windowLayout = new QGridLayout();

	m_renderWidgetInstance = new RenderWidget();
	m_windowLayout->addWidget(m_renderWidgetInstance, 0, 0);



	setLayout(m_windowLayout);
}

Window::~Window()
{
	delete m_renderWidgetInstance;
	delete m_windowLayout;
}

RenderWidget * Window::getRenderWidgetInstance() const
{
	return m_renderWidgetInstance;
}

CameraView * Window::getCameraViewInstance() const
{
	return m_renderWidgetInstance->getCameraViewObject();
}
