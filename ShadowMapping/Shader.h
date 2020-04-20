#pragma once

#include<string>
#include<sstream>
#include<fstream>

#include<QMessageBox>
#include<QOpenGLFunctions_4_5_Core>

class Shader : protected QOpenGLFunctions_4_5_Core
{

public:

	GLuint m_programID;

	std::string m_vertexShaderSourceCode;
	std::string m_fragmentShaderSourceCode;

	Shader();

	void readShaderContents(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void compileAndLinkShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	void setUpShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void useShader();

};

