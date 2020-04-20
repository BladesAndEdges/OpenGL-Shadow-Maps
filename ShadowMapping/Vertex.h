#pragma once

#include"Vector3.h" // Nomrals and Cartesian 3D coordinates
#include"Vector2.h" // Texture coordinate
#include"Colour.h" // I could've used Vector3, but it made more sense to create a separate class

/*A Vertex class, holding vertex attributes*/
class Vertex
{

public:

	Vector3 m_position;
	Colour m_colour;
	Vector3 m_normal;
	Vector2 m_textureCoordinate;

	/*Having multiple constructors, that may not set all data members, meant I had to figure out the default values for the other attributes, that are not set.*/
	/*The default values for each one of them is to have all of the uninitialized components set to 0*/
	Vertex(const Vector3& cartesianCoordinate);
	Vertex(const Vector3& cartesianCoordinate, const Vector2& textureCoordiante);
	Vertex(const Vector3& cartesianCoordinate, const Colour& vertexColour, const Vector3& vertexNormal);
	Vertex(const Vector3& cartesianCoordinate, const Colour& vertexColour, const Vector3& vertexNormal, const Vector2& textureCoordinate);
};

