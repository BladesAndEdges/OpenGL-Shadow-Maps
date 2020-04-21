#pragma once

#include "Colour.h"
#include "Vector2.h"
#include "Vector3.h"

/*An structure which contains all the required attributes we may need for our mesh Vertex*/

struct Vertex
{
	Vector3 m_vertexPosition;
	Colour m_vertexColour;
	Vector3 m_vertexNormal;
	Vector2 m_vertexTextureCoordinate;

	/*Not all meshes will require Colours, normals or texture coordinates. Overloaded versions of the constructor were added to mitigate this*/
	Vertex(const Vector3& cartesianCoordinate);
	Vertex(const Vector3& cartesianCoordinate, const Vector2& texCoord);
	Vertex(const Vector3& cartesianCoordinate, const Colour& rgbaColour, const Vector3& normal);
};