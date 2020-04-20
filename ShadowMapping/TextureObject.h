#pragma once

#include<QGLWidget>
#include<QImage>
#include<QOpenGLFunctions_4_5_Core>
#include<string>


/*
A texture object class, which will read-in a file, and create a texture object, that 
OpenGL can use.
*/

class TextureObject : protected QOpenGLFunctions_4_5_Core
{

private:
	
	GLuint m_textureID;
	GLuint m_textureWidth;
	GLuint m_textureHeight;

public:

	TextureObject(const std::string& file, GLint textureParameter);
	~TextureObject();
	
	void setActiveTextureObject();

	GLuint getWidth() const;
	GLuint getHeight() const;
};

