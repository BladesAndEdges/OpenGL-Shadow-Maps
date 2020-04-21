#pragma once

#include "Window.h"

#include <qevent.h>
#include <qobject.h>

/*This is a special class which is required for Qt to handle events*/
class InputController : public QObject
{

private:

	Window* m_windowWidget;
	CameraView* m_cameraObject;

	float m_previousXCoordinate;
	float m_previousYCoordinate;

	bool m_mouseIsPressed;

	/*Qt event-handling functions*/
	void keyPressEvent(QKeyEvent* keyEvent);
	void mousePressEvent(QMouseEvent* mousePressEvent);
	void mouseMoveEvent(QMouseEvent* mouseMoveEvent);
	void mouseReleaseEvent(QMouseEvent* mouseReleaseEvent);

protected:

	bool eventFilter(QObject* object, QEvent* theEvent) override;

public:

	InputController(Window* window);
};


