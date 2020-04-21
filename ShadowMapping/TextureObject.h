#pragma once

#include <string>
#include <QGLWidget>
#include <QImage>
#include <GL/glu.h>
#include <iostream>
#include <cstdio>

#include "TextureObject.h"
#include <qopenglfunctions_4_5_core.h>

/*
A class capable of handling texture draw calls
*/
class TextureObject : protected QOpenGLFunctions_4_5_Core 
{

private:

	GLuint m_textureWidth;
	GLuint height;

	GLuint textureID;

public:

	TextureObject(const std::string& file, GLint param);

	~TextureObject();

	void setActiveTexture();

	GLuint getWidth();
	GLuint getHeight();
};
