#include "InputController.h"

#define _USE_MATH_DEFINES
#include <math.h>


InputController::InputController(Window * window) : m_windowWidget(window), m_mouseIsPressed(false)
{
	m_cameraViewObject = m_windowWidget->getCameraViewInstance();
}

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
	QVector3D currentPosition = m_cameraViewObject->getCameraWorldPosition();
	QVector3D translation = QVector3D(0.0f, 0.0f, 0.f);

	QVector3D rightwardVector = QVector3D(1.0f, 0.0f, 0.0f);
	QVector3D upwardVector = QVector3D(0.0f, 1.0f, 0.0f);
	QVector3D forwardVector = QVector3D(0.0f, 0.0f, 1.0f);
	const float cameraSpeed = 0.1f;

	float currentPitchAngle = m_cameraViewObject->getCameraOrientation().getPitchValue();
	float currentYawAngle = m_cameraViewObject->getCameraOrientation().getYawValue();

	/*Convert the angles to radians, as the mathematical functions require it*/
	float currentPitchInRadians = currentPitchAngle * (M_PI / 180.0f);
	float currentYawInRadians = currentYawInRadians * (M_PI / 180.0f);

	/*Sets up the tranlsation for the m_cameraViewObject!*/
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

	/*Since the above translation is set up for the m_cameraViewObject, corresponding matrix,
	that would be applied to the scene, would be the inverse*/
	QVector3D newCameraPosition = currentPosition + translation;
	m_cameraViewObject->setCameraPosition(newCameraPosition);

	m_windowWidget->getRenderWidgetInstance()->repaint();
}

void InputController::mousePressEvent(QMouseEvent * mousePressEvent)
{
	if (mousePressEvent->button() == Qt::LeftButton)
	{
		m_mouseIsPressed = true;
	}

	m_oldXPosition = mousePressEvent->pos().x();
	m_oldYPosition = mousePressEvent->pos().y();
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
		float currentPitch = m_cameraViewObject->getCameraOrientation().getPitchValue();
		float currentYaw = m_cameraViewObject->getCameraOrientation().getYawValue();
		float currentRoll = 0.0f;

		/*Differences between the cursor locations*/
		float differenceAlongX = (newPositionInX - m_oldXPosition);
		float differenceAlongY = (newPositionInY - m_oldYPosition);

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
		m_cameraViewObject->setCameraOrientation(updatedCameraOrientation);

		/*Update the screen*/
		m_windowWidget->getRenderWidgetInstance()->repaint();

		m_oldXPosition = newPositionInX;
		m_oldYPosition = newPositionInY;
	}

}

void InputController::mouseReleaseEvent(QMouseEvent * mouseReleaseEvent)
{
	m_mouseIsPressed = false;
}
