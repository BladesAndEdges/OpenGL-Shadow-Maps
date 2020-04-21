#include "Shader.h"

Shader::Shader()
{
}


void Shader::readShaderContents(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	std::ifstream vertexStream;

	std::ifstream fragmentStream;

	vertexStream.open(vertexShaderPath);
	fragmentStream.open(fragmentShaderPath);

	bool vShaderIsReady = vertexStream.is_open();
	bool fShaderIsReady = fragmentStream.is_open();

	if (!vShaderIsReady)
	{
		QMessageBox message;
		message.setText("The program failed to read the Vertex Shader correctly!");
		message.exec();
	}

	if (!fShaderIsReady)
	{
		QMessageBox message;
		message.setText("The program failed to read the Fragment Shader correctly!");
		message.exec();
	}

	/*Gets the range from the start of the stream, until the end, and assigns it to an std::string*/
	m_vertexShaderSourceCode.assign((std::istreambuf_iterator<char>(vertexStream)), (std::istreambuf_iterator<char>()));
	m_fragmentShaderSourceCode.assign((std::istreambuf_iterator<char>(fragmentStream)), (std::istreambuf_iterator<char>()));

	/*Checks if the shader files were empty*/
	if (m_vertexShaderSourceCode.empty() || m_fragmentShaderSourceCode.empty())
	{
		QMessageBox message;
		message.setText("One or both of the std::strings which should contain the Shader source code after reading is empty!");
		message.exec();
	}
}

void Shader::compileAndLinkShaders(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
	initializeOpenGLFunctions();

	GLchar error[512];

	/*COMPILING VERTEX SHADER*/

	/*Create empty shader objects*/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	/*Make things consistent with GL code*/
	const GLchar* vertexCode = (GLchar*)vertexShaderCode.c_str();

	/*Sets the source code in the shader object*/
	glShaderSource(vertexShader, 1, &vertexCode, 0);

	/*Compile the shader*/
	glCompileShader(vertexShader);

	/*Check if compilation was successful*/
	GLint vertShaderCompiled = 0;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertShaderCompiled);

	if (!vertShaderCompiled)
	{
		glGetShaderInfoLog(vertexShader, sizeof(error), NULL, error);
		OutputDebugStringA(error);
	}

	/*COMPILING FRAGMENT SHADER*/

	/*The process is the same, so I've not commented it*/

	/*Create empty shader objects*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	/*Make things consistent with GL code*/
	const GLchar* fragmentCode = (GLchar*)fragmentShaderCode.c_str();

	/*Sets the source code in the shader object*/
	glShaderSource(fragmentShader, 1, &fragmentCode, 0);

	/*Compile the shader*/
	glCompileShader(fragmentShader);

	/*Check if compilation was successful*/
	GLint fragmentShaderCompiled = 0;

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);

	if (!fragmentShaderCompiled)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(error), NULL, error);
		OutputDebugStringA(error);
	}

	/*PROGRAM CREATION AND LINKING*/
	m_programID = glCreateProgram();

	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);

	glLinkProgram(m_programID);


	GLint hasLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &hasLinked);

	if (!hasLinked)
	{
		glGetProgramInfoLog(m_programID, sizeof(error), NULL, error);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::setUpShader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	readShaderContents(vertexShaderPath, fragmentShaderPath);
	compileAndLinkShaders(m_vertexShaderSourceCode, m_fragmentShaderSourceCode);
}

void Shader::useShader()
{
	glUseProgram(m_programID);
}

