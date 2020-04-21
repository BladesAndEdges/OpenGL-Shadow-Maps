#include "Vertex.h"

Vertex::Vertex(const Vector3& cartesianCoordinate) : m_vertexPosition(cartesianCoordinate) {};
Vertex::Vertex(const Vector3& cartesianCoordinate, const Vector2& texCoord) : m_vertexPosition(cartesianCoordinate), m_vertexTextureCoordinate(texCoord) {};
Vertex::Vertex(const Vector3& cartesianCoordinate, const Colour& rgbaColour, const Vector3& notNormalizedNormal) : m_vertexPosition(cartesianCoordinate),
m_vertexColour(rgbaColour),
m_vertexNormal(notNormalizedNormal)
{
	// Perhaps normalize the normal
}