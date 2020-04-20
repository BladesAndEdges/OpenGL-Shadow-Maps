#pragma once

#include<qevent.h>

#include "Window.h"
#include "CameraView.h"


/*This is a special class which is required for Qt to handle events*/

class InputController : public QObject
{

private:

	Window* m_windowWidget;
	CameraView* m_cameraViewObject;

	float m_oldXPosition;
	float m_oldYPosition;

	bool m_mouseIsPressed;

	/*Event-handling functions*/
	void keyPressEvent(QKeyEvent* keyPress);
	void mousePressEvent(QMouseEvent* mousePress);
	void mouseMoveEvent(QMouseEvent* mouseMove);
	void mouseReleaseEvent(QMouseEvent* mouseRelease);

protected:

	bool eventFilter(QObject* object, QEvent* theEvent) override;

public:

	InputController(Window* window);

};

