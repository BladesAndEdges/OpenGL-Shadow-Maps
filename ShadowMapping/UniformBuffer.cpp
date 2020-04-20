#include "UniformBuffer.h"

void copyMatrix4x4ToFloatArray(const QMatrix4x4 & source, float destination[16])
{
	memcpy(destination, source.data(), 16 * sizeof(float));
}

void copyVector4ToFloatArray(const QVector4D & source, float destination[4])
{
	memcpy(destination, &source, 4 * sizeof(float));
}
