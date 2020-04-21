#pragma once

#include <qmatrix4x4.h>

/*
	This class represents a CameraView orientation.
	It uses Euler angles to express which way the CameraView
	object is currently facing in the scene.
*/
struct Orientation
{

private:

	float m_pitchAngle;
	float m_yawAngle;
	float m_rollAngle;

public:

	Orientation();
	Orientation(float pitchAngle, float yawAngle, float rollAngle);

	float getPitchAngle() const;
	float getYawAngle() const;
	float getRollAngle() const;

	void setPitchAngle(float newPitch);
	void setYawAngle(float newYaw);
	void setRollAngle(float newRoll);
};

