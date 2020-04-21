#include "Orientation.h"

Orientation::Orientation()
{
}

Orientation::Orientation(float pitchAngle, float yawAngle, float rollAngle) : m_pitchAngle(pitchAngle), m_yawAngle(yawAngle), m_rollAngle(rollAngle)
{
}

float Orientation::getPitchAngle() const
{
	return m_pitchAngle;
}

float Orientation::getYawAngle() const
{
	return m_yawAngle;
}

float Orientation::getRollAngle() const
{
	return m_rollAngle;
}

void Orientation::setPitchAngle(float newPitch)
{
	m_pitchAngle = newPitch;
}

void Orientation::setYawAngle(float newYaw)
{
	m_yawAngle = newYaw;
}

void Orientation::setRollAngle(float newRoll)
{
	m_rollAngle = newRoll;
}