#pragma once

#include <QVector3D>
#include "Orientation.h"

/*
We can use this to determine whether a projection uses
an Orthographic-type (i.e. parallel rays) or
a Perspective-type (i.e. uses a frustum, and has a vanishing point)
*/
enum class ProjectionType
{
	Orthographic,
	Perspective
};

/*
	The class represents a Camera Viewpoint.
	What this means is, given a 3D position and and Orientation,
	we can use that information as a means to define how far the camera is
	and what direction it is currently facing.
*/
class CameraView
{

private:

	QVector3D m_cameraWorldPosition;
	Orientation m_cameraOrientation;

	ProjectionType m_cameraProjectionType;

	/*Paramaters I`ll use for the orthographic projection of my shadow view*/
	float m_cameraWidth;
	float m_cameraHeight;
	float m_cameraNearPlane;
	float m_cameraFarPlane;

public:

	CameraView();
	CameraView(const QVector3D& position, const Orientation& orientation, const ProjectionType& projectionType,
		float width, float height, float near, float far);

	QVector3D getCameraWorldPosition() const;
	Orientation getCameraOrientation() const;
	ProjectionType getCameraProjectionType() const;

	void setCameraWorldPosition(const QVector3D& newCameraPosition);
	void setCameraOrientation(const Orientation& newCameraOrientation);

	/*Getters for the orthographic projection*/
	float getCameraWidth() const;
	float getCameraHeight() const;
	float getCameraNearPlane() const;
	float getCameraFarPlane() const;

};

/*For computing shadow map properties*/
Orientation calculateShadowMapViewOrientation(const QVector4D& lightDirection);
float computeLightVectorMagnitude(const QVector4D& vector);


