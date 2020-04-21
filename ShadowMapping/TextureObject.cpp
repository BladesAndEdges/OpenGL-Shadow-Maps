#include "TextureObject.h"

TextureObject::TextureObject(const std::string& file, GLint param) {

	//For loading and converting
	QImage img, glformat;

	if (!img.load(QString::fromStdString(file.c_str()))) {
		OutputDebugStringA("Asdasd");
	}

	initializeOpenGLFunctions();

	//If file could not be loaded

	//Convert to accepted GL format
	glformat = QGLWidget::convertToGLFormat(img);

	//Generate name/id
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Apply texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glformat.width(), glformat.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glformat.bits());


	//Wrap modes, min-mag filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

//Destructor(???) test
TextureObject::~TextureObject() {
	glDeleteTextures(1, &textureID);
}

unsigned int TextureObject::getWidth() {
	return m_textureWidth;
}

unsigned int TextureObject::getHeight() {
	return height;
}

void TextureObject::setActiveTexture() {
	glBindTexture(GL_TEXTURE_2D, textureID);
}
