#include "Vertex.h"

Vertex::Vertex(const Vector3& cartesianCoordinate) : position(cartesianCoordinate) {};
Vertex::Vertex(const Vector3& cartesianCoordinate, const Vector2& texCoord) : position(cartesianCoordinate), textureCoordinate(texCoord) {};
Vertex::Vertex(const Vector3& cartesianCoordinate, const Colour& rgbaColour, const Vector3& notNormalizedNormal) : position(cartesianCoordinate),
colour(rgbaColour),
normal(notNormalizedNormal)
{
	// Perhaps normalize the normal
}