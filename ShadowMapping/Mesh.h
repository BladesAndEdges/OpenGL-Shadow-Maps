#pragma once

#include<QOpenGLFunctions_4_5_Core>
#include<vector>

#include "Vertex.h"

/*Represents a Mesh instance. It can be used for any type of mesh, if you supply Vertex Attribute data to it */
class Mesh : protected QOpenGLFunctions_4_5_Core
{
	
public:

	GLuint m_meshVAO;
	GLuint m_meshVBO;
	GLuint m_vertexCount;

	Mesh(const std::vector<Vertex>& data);

	static Mesh* createDebugQuadMesh();
	static Mesh* createFloorMesh();
	static Mesh* createWallMesh();
	static Mesh* createCubeMesh();
};

