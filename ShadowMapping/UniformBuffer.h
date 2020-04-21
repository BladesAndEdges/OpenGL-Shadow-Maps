#pragma once

#include <qmatrix4x4.h>

struct ubo
{
	float model[16];
	float viewProjection[16];
	float lightSpaceMatrix[16];
	float toLightDirection[4]; // 3 floats + 1 additional float for padding
};

void copyMatrixIntoFloatArray(const QMatrix4x4& src, float dest[16]);
void copyVector4IntoFloatArray(const QVector4D& src, float dest[4]);