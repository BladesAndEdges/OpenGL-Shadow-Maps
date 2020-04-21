#pragma once

#include <fstream>
#include <string.h>
#include <sstream>
#include <qmessagebox.h>
#include <qgl.h>
#include <QOpenGLFunctions_4_5_Core>

#include<qmatrix4x4.h>
#include<qvector3d.h>
#include<qvector4d.h>


/*

	This class does three stuff: 

	- It reads in the Shader file, and stores the source code into an std::string object
	- This string is then given to the OpenGL glShaderSource function and compiles it.
	- Once both fragment and vertex shader source code is given to OpenGL and compilation has been done, it links the two shader modules into a program object.
*/
class Shader : protected QOpenGLFunctions_4_5_Core
{

public:

	GLuint m_programID;

	std::string m_vertexShaderSourceCode;
	std::string m_fragmentShaderSourceCode;

	Shader();

	void readShaderContents(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void compileAndLinkShaders(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	void setUpShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void useShader();
};

