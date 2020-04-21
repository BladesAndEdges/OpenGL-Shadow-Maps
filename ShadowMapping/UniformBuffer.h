#pragma once

#include <qmatrix4x4.h>

/*The uniform buffer struct which holds our transformation matrices. Both for the main view and the lightSpace matrix*/
struct UniformBuffer
{
	float model[16];
	float viewProjection[16];
	float lightSpaceMatrix[16];
	float toLightDirection[4]; // 3 floats + 1 additional float for padding
};

/*Copies data using memcpy from a Qt class to a normal C-array. This is done in order not to account for the additional data Qt classes may, or may not carry*/
void copyMatrix4x4ToFloat16Array(const QMatrix4x4& src, float dest[16]);
void copyVector4ToFloat4Array(const QVector4D& src, float dest[4]);