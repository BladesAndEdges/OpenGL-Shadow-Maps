#include "TextureObject.h"

TextureObject::TextureObject(const std::string& file, GLint param) {

	//For loading and converting
	QImage img, glformat;

	if (!img.load(QString::fromStdString(file.c_str()))) {
		OutputDebugStringA("Asdasd");
	}

	initializeOpenGLFunctions();

	/*Qt expects data in a certain format*/
	glformat = QGLWidget::convertToGLFormat(img);

	/*Generate texture object*/
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	/*Retrieve data*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glformat.width(), glformat.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glformat.bits());


	/*Texture paramaters*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

TextureObject::~TextureObject() {
	glDeleteTextures(1, &m_textureID);
}

unsigned int TextureObject::getTextureWidth() {
	return m_textureWidth;
}

unsigned int TextureObject::getTextureHeight() {
	return m_textureHeight;
}

void TextureObject::setActiveTexture() {
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
