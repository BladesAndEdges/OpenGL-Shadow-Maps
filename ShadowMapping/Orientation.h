#pragma once

#include<QMatrix4x4>

/*
	This class represents a CameraView orientation.
	It uses Euler angles to express which way the CameraView
	object is currently facing in the scene.
*/
class Orientation
{

private:

	float m_pitch;
	float m_yaw;
	float m_roll;

public:

	Orientation();
	Orientation(float pitch, float yaw, float roll);

	/*Getters*/
	float getPitchValue() const;
	float getYawValue() const;
	float getRollValue() const;

	/*Setters*/
	void setPitchValue(float newPitchValue);
	void setYawValue(float newYawValue);
	void setRollValue(float newRollValue);
};

