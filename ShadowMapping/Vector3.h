#pragma once

/*A general-purpose structure for a 3-component object.*/

/*
	This sturcture is used for:
	- Cartesian positions
	- Normals
*/

class Vector3
{

public:

	float m_x;
	float m_y;
	float m_z;

	Vector3();
	Vector3(float x, float y, float z);

};

