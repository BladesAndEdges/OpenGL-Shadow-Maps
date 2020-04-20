#include "CameraView.h"
#define _USE_MATH_DEFINES
#include <math.h>


CameraView::CameraView()
{
}

CameraView::CameraView(const QVector3D& position, const Orientation& orientation, const ProjectionType& projectionType,
	float width, float height, float near, float far) : m_cameraWorldPosition(position),
														m_cameraOrientation(orientation),
														m_cameraProjectionType(projectionType),
														m_cameraWidth(width),
														m_cameraHeight(height),
														m_cameraNearPlane(near),
														m_cameraFarPlane(far)



{

}

QVector3D CameraView::getCameraWorldPosition() const
{
	return m_cameraWorldPosition;
}

Orientation CameraView::getCameraOrientation() const
{
	return m_cameraOrientation;
}

ProjectionType CameraView::getCameraProjectionType() const
{
	return m_cameraProjectionType;
}

void CameraView::setCameraPosition(const QVector3D & newCameraPosition)
{
	m_cameraWorldPosition = newCameraPosition;
}

void CameraView::setCameraOrientation(const Orientation & newCameraOrientation)
{
	m_cameraOrientation = newCameraOrientation;
}

float CameraView::getCameraWidth() const
{
	return m_cameraWidth;
}

float CameraView::getCameraHeight() const
{
	return m_cameraHeight;
}

float CameraView::getCameraNearPlane() const
{
	return m_cameraNearPlane;
}

float CameraView::getCameraFarPlane() const
{
	return m_cameraFarPlane;
}

float computeLightVectorMagnitude(const QVector4D & lightVector)
{
	return sqrtf(powf(lightVector.x(), 2.0f) + powf(lightVector.y(), 2.0f) + powf(lightVector.z(), 2.0f));
}


Orientation calculateShadowMapViewOrientation(const QVector4D & lightDirection)
{
	/*Get the magnitude of the toLightVector*/
	float hypotenuse = computeLightVectorMagnitude(lightDirection);

	/*Get the angle for the pitch*/
	float ratioForPitch = lightDirection.x() / hypotenuse;

	/*The angle would be arcos(ratioForPitch)*/
	float pitchAngle = (acos(ratioForPitch) * 180.0f) / M_PI;

	/*Compute the yaw angle*/
	float ratioForYaw = lightDirection.z() / hypotenuse;

	/*Compute yaw angle*/
	float yawAngle = (acos(ratioForYaw) * 180.0f) / M_PI;

	/*Hard code the roll value*/
	float rollAngle = 0.0f;

	/*Compute */
	return Orientation(pitchAngle, yawAngle, rollAngle);
}
