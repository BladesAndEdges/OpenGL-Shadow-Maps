#include "UniformBuffer.h"

void copyMatrixIntoFloatArray(const QMatrix4x4& src, float dest[16])
{
	memcpy(dest, src.data(), 16 * sizeof(float));
}

void copyVector4IntoFloatArray(const QVector4D & src, float dest[4])
{
	memcpy(dest, &src, 4 * sizeof(float));
}
