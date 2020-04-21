#include "InputController.h"

#define _USE_MATH_DEFINES
#include <math.h>


InputController::InputController(Window * window) : m_windowWidget(window), m_mouseIsPressed(false)
{
	m_cameraObject = m_windowWidget->getCameraViewInstance();
}

/*Filters the type of event being sent to the widget which holds the focus*/
bool InputController::eventFilter(QObject * object, QEvent * theEvent)
{

	if (theEvent->type() == QEvent::Paint)
	{
		return false;
	}
	else if (object == m_windowWidget->getRenderWidgetInstance() && theEvent->type() == QEvent::KeyPress)
	{
		keyPressEvent(static_cast<QKeyEvent*>(theEvent));
		return false;
	}
	else if (object == m_windowWidget->getRenderWidgetInstance() && theEvent->type() == QEvent::MouseButtonPress)
	{
		mousePressEvent(static_cast<QMouseEvent*>(theEvent));
		return false;

	}
	else if (object == m_windowWidget->getRenderWidgetInstance() && theEvent->type() == QEvent::MouseButtonRelease)
	{
		mouseReleaseEvent(static_cast<QMouseEvent*>(theEvent));
		return false;

	}
	else if (object == m_windowWidget->getRenderWidgetInstance() && theEvent->type() == QEvent::MouseMove)
	{
		mouseMoveEvent(static_cast<QMouseEvent*>(theEvent));
		return false;

	}
	/*If it is not one of the events we are interested, pass it down the event system*/
	return QObject::eventFilter(object, theEvent);
}

void InputController::keyPressEvent(QKeyEvent * keyEvent)
{
	/*Get the current position*/
	QVector3D currentPosition = m_cameraObject->getCameraWorldPosition();
	QVector3D translation = QVector3D(0.0f, 0.0f, 0.0f);

	/*The coordinate frame vectors (?)*/
	QVector3D rightwardVector = QVector3D(1.0f, 0.0f, 0.0f);
	QVector3D upwardVector = QVector3D(0.0f, 1.0f, 0.0f);
	QVector3D forwardVector = QVector3D(0.0f, 0.0f, 1.0f);
	const float cameraSpeed = 0.1f;

	/*Extract the current orientation. We don't care about Rolling, so we just get the pitch and yaw*/
	float currentPitchAngle = m_cameraObject->getCameraOrientation().getPitchAngle();
	float currentYawAngle = m_cameraObject->getCameraOrientation().getYawAngle();

	/*Convert the angles to radians, as the mathematical functions require it*/
	float currentPitchInRadians = currentPitchAngle * (M_PI / 180.0f);
	float currentYawInRadians = currentYawInRadians * (M_PI / 180.0f);

	/*Sets up the tranlsation for the CameraObject!*/
	switch (keyEvent->key())
	{
	case Qt::Key_W:
		translation = cameraSpeed * -forwardVector;
		break;
	case Qt::Key_S:
		translation = cameraSpeed * forwardVector;
		break;
	case Qt::Key_A:
		translation = cameraSpeed * -rightwardVector;
		break;
	case Qt::Key_D:
		translation = cameraSpeed * rightwardVector;
		break;
	case Qt::Key_Q:
		translation = cameraSpeed * upwardVector;
		break;
	case Qt::Key_E:
		translation = cameraSpeed * -upwardVector;
		break;
	default:
		OutputDebugStringA("Invalid Key press!");
	}

	/*This will allows us to preserve directions in view space*/
	QMatrix4x4 accountForPitchRotation;
	QMatrix4x4 accountForYawRotation;

	//accountForPitchRotation.rotate(-currentPitchAngle, QVector3D(1.0f, 0.0f, 0.0f)); // This part doesn't work, figure out why
	accountForYawRotation.rotate(currentYawAngle, QVector3D(0.0f, 1.0f, 0.0f));

	translation = accountForPitchRotation * accountForYawRotation * translation;

	/*Since the above translation is set up for the CameraObject, corresponding matrix,
	that would be applied to the scene, would be the inverse*/
	QVector3D newCameraPosition = currentPosition + translation;
	m_cameraObject->setCameraWorldPosition(newCameraPosition);

	m_windowWidget->getRenderWidgetInstance()->repaint();
}

void InputController::mousePressEvent(QMouseEvent * mousePressEvent)
{
	if (mousePressEvent->button() == Qt::LeftButton)
	{
		m_mouseIsPressed = true;
	}

	/*Record the cursor position*/
	m_previousXCoordinate = mousePressEvent->pos().x();
	m_previousYCoordinate = mousePressEvent->pos().y();
}

void InputController::mouseMoveEvent(QMouseEvent * mouseMoveEvent)
{
	const float rotationSpeed = 0.5f;

	if (m_mouseIsPressed)
	{
		float newPositionInX = mouseMoveEvent->pos().x();
		float newPositionInY = mouseMoveEvent->pos().y();

		/*Gets the current orientation of the camera for the yaw and pitch. We will not include roll maneuveres,
		so we leave that out*/
		float currentPitch = m_cameraObject->getCameraOrientation().getPitchAngle();
		float currentYaw = m_cameraObject->getCameraOrientation().getYawAngle();
		float currentRoll = 0.0f;

		/*Differences between the cursor locations*/
		float differenceAlongX = (newPositionInX - m_previousXCoordinate);
		float differenceAlongY = (newPositionInY - m_previousYCoordinate);

		currentPitch = currentPitch + (differenceAlongY * rotationSpeed);
		currentYaw = currentYaw + (-differenceAlongX * rotationSpeed);

		if (currentPitch > 89.0f)
		{
			currentPitch = 89.0f;
		}
		if (currentPitch < -89.0f)
		{
			currentPitch = -89.0f;
		}

		/*Create a new camera orientation*/
		Orientation updatedCameraOrientation(currentPitch, currentYaw, currentRoll);

		/*And set it as the new orientation*/
		m_cameraObject->setCameraOrientation(updatedCameraOrientation);

		/*Update the screen*/
		m_windowWidget->getRenderWidgetInstance()->repaint();

		m_previousXCoordinate = newPositionInX;
		m_previousYCoordinate = newPositionInY;
	}

}

void InputController::mouseReleaseEvent(QMouseEvent * mouseReleaseEvent)
{
	m_mouseIsPressed = false;
}
