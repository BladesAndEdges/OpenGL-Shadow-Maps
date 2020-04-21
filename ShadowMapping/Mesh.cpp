#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> data)
{
	initializeOpenGLFunctions();

	m_meshVertexCount = data.size();
	const uint32_t dataRequirementsInBytes = m_meshVertexCount * sizeof(Vertex);

	glGenVertexArrays(1, &m_meshVAO);
	glBindVertexArray(m_meshVAO);

	glGenBuffers(1, &m_meshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_meshVBO);

	glBufferData(GL_ARRAY_BUFFER, dataRequirementsInBytes, &data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_meshVBO);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
}



Mesh* Mesh::createDebugQuadMesh()
{
	/*Note that these coordinates will be in clip space. We want it to be in fron our screen always*/

	std::vector<Vertex> vertices;

	Vector3 topLeft(-1.0f, 1.0f, -1.0f);
	Vector3 bottomLeft(-1.0f, 0.4f, 0.0f);
	Vector3 bottomRight(-0.4f, 0.4f, 0.0f);
	Vector3 topRight(-0.4f, 1.0f, 0.0f);

	Vector2 t0(0.0f, 1.0f);
	Vector2 t1(0.0f, 0.0f);
	Vector2 t2(1.0f, 0.0f);
	Vector2 t3(1.0f, 1.0f);

	Vertex v0(topLeft, t0);
	Vertex v1(bottomLeft, t1);
	Vertex v2(bottomRight, t2);
	Vertex v3(topRight, t3);

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);

	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v0);

	Mesh* mesh = new Mesh(vertices);

	return mesh;
}

Mesh* Mesh::createFloorMesh()
{
	/*Note that these coordinates will be in clip space. We want it to be in fron our screen always*/

	std::vector<Vertex> vertices;

	Vector3 positiveYNormal(0.0f, 1.0f, 0.0f);

	Vector3 topLeft(0.0f, 0.0f, -20.0f);
	Vector3 bottomLeft(0.0f, 0.0f, 0.0f);
	Vector3 bottomRight(20.0f, 0.0f, 0.0f);
	Vector3 topRight(20.0f, 0.0f, -20.0f);

	Colour forestGreen(0.0f, 0.1f, 0.0f);
	Colour purple(1.0f, 0.0f, 1.0f);
	Colour yellow(1.0f, 1.0f, 0.0f);
	Colour cyan(0.5f, 1.0f, 1.0f);

	Vertex v0(topLeft, forestGreen, positiveYNormal);
	Vertex v1(bottomLeft, purple, positiveYNormal);
	Vertex v2(bottomRight, yellow, positiveYNormal);
	Vertex v3(topRight, cyan, positiveYNormal);

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);

	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v0);

	Mesh* mesh = new Mesh(vertices);

	return mesh;
}

Mesh* Mesh::createWallMesh()
{
	/*Note that these coordinates will be in clip space. We want it to be in fron our screen always*/

	std::vector<Vertex> vertices;

	Vector3 positiveZNormal(0.0f, 0.0f, 1.0f);

	Vector3 topLeft(0.0f, 20.0f, 0.0f);
	Vector3 bottomLeft(0.0f, 0.0f, 0.0f);
	Vector3 bottomRight(20.0f, 0.0f, 0.0f);
	Vector3 topRight(20.0f, 20.0f, 0.0f);

	Colour red(1.0f, 0.0f, 0.0f);
	Colour green(0.0f, 1.0f, 0.0f);
	Colour blue(0.0f, 0.0f, 1.0f);
	Colour black(1.0f, 1.0f, 1.0f);

	Vertex v0(topLeft, red, positiveZNormal);
	Vertex v1(bottomLeft, green, positiveZNormal);
	Vertex v2(bottomRight, blue, positiveZNormal);
	Vertex v3(topRight, black, positiveZNormal);

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);

	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v0);

	Mesh* mesh = new Mesh(vertices);

	return mesh;
}

Mesh* Mesh::createCubeMesh()
{
	std::vector<Vertex> vertices;

	/*Normals*/
	Vector3 pointingPositiveX(1.0f, 0.0f, 0.0f);
	Vector3 pointingNegativeX(-1.0f, 0.0f, 0.0f);

	Vector3 pointingPositiveY(0.0f, 1.0f, 0.0f);
	Vector3 pointingNegativeY(0.0f, -1.0f, 0.0f);

	Vector3 pointingPositiveZ(0.0f, 0.0f, 1.0f);
	Vector3 pointingNegativeZ(0.0f, 0.0f, -1.0f);

	/*Vector3s*/
	Vector3 bottomQuadTopLeft(0.0f, 0.0f, -3.0f);
	Vector3 bottomQuadBottomLeft(0.0f, 0.0f, 0.0f);
	Vector3 bottomQuadBottomRight(3.0f, 0.0f, 0.0f);
	Vector3 bottomQuadTopRight(3.0f, 0.0f, -3.0f);

	Vector3 topQuadTopLeft(0.0f, 3.0f, -3.0f);
	Vector3 topQuadBottomLeft(0.0f, 3.0f, 0.0f);
	Vector3 topQuadBottomRight(3.0f, 3.0f, 0.0f);
	Vector3 topQuadTopRight(3.0f, 3.0f, -3.0f);

	Colour cubeColour(0.38f, 0.23f, 0.09f);

	/*DOUBLE CHECK THIS LATER ON, MAY BE WRONG*/

	/*Bottom Quad vertices versions*/
	Vertex bottomFace_bottomQuadTopLeftVertex(bottomQuadTopLeft, cubeColour, pointingNegativeY);
	Vertex backFace_bottomQuadTopLeftVertex(bottomQuadTopLeft, cubeColour, pointingNegativeZ);
	Vertex leftSideFace_bottomQuadTopLeftVertex(bottomQuadTopLeft, cubeColour, pointingNegativeX);

	Vertex bottomFace_bottomQuadBottomLeftVertex(bottomQuadBottomLeft, cubeColour, pointingNegativeY);
	Vertex frontFace_bottomQuadBottomLeftVertex(bottomQuadBottomLeft, cubeColour, pointingPositiveZ);
	Vertex leftSideFace_bottomQuadBottomLeftVertex(bottomQuadBottomLeft, cubeColour, pointingNegativeX);

	Vertex bottomFace_bottomQuadBottomRightVertex(bottomQuadBottomRight, cubeColour, pointingNegativeY);
	Vertex frontFace_bottomQuadBottomRightVertex(bottomQuadBottomRight, cubeColour, pointingPositiveZ);
	Vertex rightSideFace_bottomQuadBottomRightVertex(bottomQuadBottomRight, cubeColour, pointingPositiveX);

	Vertex bottomFace_bottomQuadTopRightVertex(bottomQuadTopRight, cubeColour, pointingNegativeY);
	Vertex backFace_bottomQuadTopRightVertex(bottomQuadTopRight, cubeColour, pointingNegativeZ);
	Vertex rightSideFace_bottomQuadTopRightVertex(bottomQuadTopRight, cubeColour, pointingPositiveX);

	/*Top Quad vertices versions*/
	Vertex topFace_topQuadTopLeftVertex(topQuadTopLeft, cubeColour, pointingPositiveY);
	Vertex backFace_topQuadTopLeftVertex(topQuadTopLeft, cubeColour, pointingNegativeZ);
	Vertex leftSideFace_topQuadTopLeftVertex(topQuadTopLeft, cubeColour, pointingNegativeX);

	Vertex topFace_topQuadBottomLeftVertex(topQuadBottomLeft, cubeColour, pointingPositiveY);
	Vertex frontFace_topQuadBottomLeftVertex(topQuadBottomLeft, cubeColour, pointingPositiveZ);
	Vertex leftSideFace_topQuadBottomLeftVertex(topQuadBottomLeft, cubeColour, pointingNegativeX);

	Vertex topFace_topQuadBottomRightVertex(topQuadBottomRight, cubeColour, pointingPositiveY);
	Vertex frontFace_topQuadBottomRightVertex(topQuadBottomRight, cubeColour, pointingPositiveZ);
	Vertex rightSideFace_topQuadBottomRightVertex(topQuadBottomRight, cubeColour, pointingPositiveX);

	Vertex topFace_topQuadTopRightVertex(topQuadTopRight, cubeColour, pointingPositiveY);
	Vertex backFace_topQuadTopRightVertex(topQuadTopRight, cubeColour, pointingNegativeZ);
	Vertex rightSideFace_topQuadTopRightVertex(topQuadTopRight, cubeColour, pointingPositiveX);

	/*Bottom face*/
	vertices.push_back(bottomFace_bottomQuadTopLeftVertex);
	vertices.push_back(bottomFace_bottomQuadBottomLeftVertex);
	vertices.push_back(bottomFace_bottomQuadBottomRightVertex);

	vertices.push_back(bottomFace_bottomQuadBottomRightVertex);
	vertices.push_back(bottomFace_bottomQuadTopRightVertex);
	vertices.push_back(bottomFace_bottomQuadTopLeftVertex);

	/*Back side face* (The one nearest to the large wall surface)*/
	vertices.push_back(backFace_bottomQuadTopLeftVertex);
	vertices.push_back(backFace_bottomQuadTopRightVertex);
	vertices.push_back(backFace_topQuadTopLeftVertex);

	vertices.push_back(backFace_bottomQuadTopRightVertex);
	vertices.push_back(backFace_topQuadTopRightVertex);
	vertices.push_back(backFace_topQuadTopLeftVertex);

	/*Left Side face*/
	vertices.push_back(leftSideFace_bottomQuadTopLeftVertex);
	vertices.push_back(leftSideFace_bottomQuadBottomLeftVertex);
	vertices.push_back(leftSideFace_topQuadTopLeftVertex);

	vertices.push_back(leftSideFace_bottomQuadBottomLeftVertex);
	vertices.push_back(leftSideFace_topQuadBottomLeftVertex);
	vertices.push_back(leftSideFace_topQuadTopLeftVertex);

	/*Right side face*/
	vertices.push_back(rightSideFace_bottomQuadBottomRightVertex);
	vertices.push_back(rightSideFace_bottomQuadTopRightVertex);
	vertices.push_back(rightSideFace_topQuadBottomRightVertex);

	vertices.push_back(rightSideFace_bottomQuadTopRightVertex);
	vertices.push_back(rightSideFace_topQuadTopRightVertex);
	vertices.push_back(rightSideFace_topQuadBottomRightVertex);

	/*Front face face*/
	vertices.push_back(frontFace_bottomQuadBottomLeftVertex);
	vertices.push_back(frontFace_bottomQuadBottomRightVertex);
	vertices.push_back(frontFace_topQuadBottomLeftVertex);

	vertices.push_back(frontFace_bottomQuadBottomRightVertex);
	vertices.push_back(frontFace_topQuadBottomRightVertex);
	vertices.push_back(frontFace_topQuadBottomLeftVertex);

	/*Top side face*/
	vertices.push_back(topFace_topQuadBottomLeftVertex);
	vertices.push_back(topFace_topQuadBottomRightVertex);
	vertices.push_back(topFace_topQuadTopLeftVertex);

	vertices.push_back(topFace_topQuadBottomRightVertex);
	vertices.push_back(topFace_topQuadTopRightVertex);
	vertices.push_back(topFace_topQuadTopLeftVertex);


	Mesh* mesh = new Mesh(vertices);

	return mesh;
}
