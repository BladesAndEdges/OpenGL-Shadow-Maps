#include "UniformBuffer.h"

void copyMatrix4x4ToFloat16Array(const QMatrix4x4& src, float dest[16])
{
	memcpy(dest, src.data(), 16 * sizeof(float));
}

void copyVector4ToFloat4Array(const QVector4D & src, float dest[4])
{
	memcpy(dest, &src, 4 * sizeof(float));
}
