#pragma once

#include "Colour.h"
#include "Vector2.h"
#include "Vector3.h"

/*An structure which contains all the required attributes we may need for our mesh Vertex*/

struct Vertex
{
	Vector3 position;
	Colour colour;
	Vector3 normal;
	Vector2 textureCoordinate;

	Vertex(const Vector3& cartesianCoordinate);
	Vertex(const Vector3& cartesianCoordinate, const Vector2& texCoord);
	Vertex(const Vector3& cartesianCoordinate, const Colour& rgbaColour, const Vector3& norm);
};