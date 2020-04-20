#include "Orientation.h"

Orientation::Orientation()
{
}

Orientation::Orientation(float pitch, float yaw, float roll) : m_pitch(pitch), m_yaw(yaw), m_roll(roll)
{
}

float Orientation::getPitchValue() const
{
	return m_pitch;
}

float Orientation::getYawValue() const
{
	return m_yaw;
}

float Orientation::getRollValue() const
{
	return m_roll;
}

void Orientation::setPitchValue(float newPitchValue)
{
	m_pitch = newPitchValue;
}

void Orientation::setYawValue(float newYawValue)
{
	m_yaw = newYawValue;
}

void Orientation::setRollValue(float newRollValue)
{
	m_roll = newRollValue;
}