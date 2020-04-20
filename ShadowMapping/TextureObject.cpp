#include "TextureObject.h"

TextureObject::TextureObject(const std::string & file, GLint textureParameter)
{
	initializeOpenGLFunctions();

	QImage imageFile;
	QImage imageFileInGLFormat;

	if (!imageFile.load(QString::fromStdString(file.c_str())))
	{

	}

	initializeOpenGLFunctions();

	/*Qt expects a certain format*/
	imageFileInGLFormat = QGLWidget::convertToGLFormat(imageFile);

	/*Generate a texture Id*/
	glGenTextures(GL_TEXTURE_2D, &m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageFileInGLFormat.width(), imageFileInGLFormat.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFileInGLFormat.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

TextureObject::~TextureObject()
{
	glDeleteTextures(1, &m_textureID);
}

void TextureObject::setActiveTextureObject()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLuint TextureObject::getWidth() const
{
	return m_textureWidth;
}

GLuint TextureObject::getHeight() const
{
	return m_textureHeight;
}
