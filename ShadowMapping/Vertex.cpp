#include "Vertex.h"

Vertex::Vertex(const Vector3 & cartesianCoordinate) : m_position(cartesianCoordinate), 
													  m_colour(Colour(0.0f, 0.0f, 0.0f)), 
													  m_normal(Vector3(0.0f, 0.0f, 0.0f)), 
													  m_textureCoordinate(Vector2(0.0f, 0.0f))
{
}

Vertex::Vertex(const Vector3 & cartesianCoordinate, const Vector2 & textureCoordinate) : m_position(cartesianCoordinate), 
																						 m_colour(Colour(0.0f, 0.0f, 0.0f)),
																						 m_normal(Vector3(0.0f, 0.0f, 0.0f)),
																						 m_textureCoordinate(textureCoordinate)
																					
{
}

Vertex::Vertex(const Vector3 & cartesianCoordinate, const Colour & vertexColour, const Vector3 & vertexNormal) : m_position(cartesianCoordinate),
																												 m_colour(vertexColour), 
																												 m_normal(Vector3(0.0f, 0.0f, 0.0f)), 
																												 m_textureCoordinate(Vector2(0.0f, 0.0f))
																																				
{
}

Vertex::Vertex(const Vector3 & cartesianCoordinate, const Colour & vertexColour, const Vector3 & vertexNormal, const Vector2 & textureCoordinate) 
																											: m_position(cartesianCoordinate), 
																											  m_colour(vertexColour), 
																											  m_normal(vertexNormal), 
																											  m_textureCoordinate(textureCoordinate)
{
}
