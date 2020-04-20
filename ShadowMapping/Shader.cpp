#include "Shader.h"

Shader::Shader()
{
}

/*Reads the shader files and stores the source code from the files*/
void Shader::readShaderContents(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	/*File stream objects, for reading input*/
	std::ifstream vertexShader;
	std::ifstream fragmentShader;

	/*Link streams to a file*/
	vertexShader.open(vertexShaderPath); // NOTE FOR FUTURE DANIEL: open() is dodgy, if a file does NOT exist, it will create one for you. Meaning that is_open() would always return true
	fragmentShader.open(fragmentShaderPath);

	/*Check if the read was successful */
	bool vShaderReady = vertexShader.is_open();
	bool fShaderReady = fragmentShader.is_open();

	if (!vShaderReady)
	{
		QMessageBox message;
		message.setText("The program failed to read the Vertex Shader correctly!");
		message.exec();
	}

	if (!fShaderReady)
	{
		QMessageBox message;
		message.setText("The program failed to read the Vertex Shader correctly!");
		message.exec();
	}

	/*Gets the range from the start of the stream, until the end, and assigns it to an std::string*/
	m_vertexShaderSourceCode.assign((std::istreambuf_iterator<char>(vertexShader)), (std::istreambuf_iterator<char>()));
	m_fragmentShaderSourceCode.assign((std::istreambuf_iterator<char>(fragmentShader)), (std::istreambuf_iterator<char>()));

	/*As mentioned in the note above, is_open() would return true always, even if the file does nto exist*/
	/*Therefore, we check if after all the reading, the file is empty. This is done as a means to make sure the file actually exist, and it's not being created from scratch*/
	if (m_vertexShaderSourceCode.empty() || m_fragmentShaderSourceCode.empty())
	{
		QMessageBox message;
		message.setText("One or both of the std::strings which should contain the Shader source code after reading is empty!");
		message.exec();
	}
}

/*Compiles and links the shaders, and creates a single Shader program object*/
void Shader::compileAndLinkShader(const std::string & vertexShaderSource, const std::string & fragmentShaderSource)
{
	initializeOpenGLFunctions();

	GLchar errorMessage[512];

	/*COMPILATION OF THE VERTEX SHADER*/

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* vertexCode = (GLchar*)vertexShaderSource.c_str();

	/*Replaces the shader source code. If this is the first time it is called, it technically initializes most likely a nullptr with a pointer to an array of strings(the source code)*/
	glShaderSource(vertexShader, 1, &vertexCode, 0);

	/*Compiles the vertex shader*/
	glCompileShader(vertexShader);

	/*Check if compilation was successful*/
	GLint vShaderCompiled = 0;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

	if (!vShaderCompiled)
	{
		glGetShaderInfoLog(vertexShader, sizeof(errorMessage), NULL, errorMessage);
		//OutputDebugStringA(errorMessage);
	}

	/*COMPILATION OF FRAGMENT SHADER*/

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* fragmentCode = (GLchar*)fragmentShaderSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentCode, 0);

	glCompileShader(fragmentShader);

	/*Check if the fragment shader has compiled*/
	GLint fShaderCompiled = 0;

	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &fShaderCompiled);

	if (!fShaderCompiled)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(errorMessage), NULL, errorMessage);
		OutputDebugStringA(errorMessage);
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
		glGetProgramInfoLog(m_programID, sizeof(errorMessage), NULL, errorMessage);
		OutputDebugStringA(errorMessage);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
/*A single functions sets up the shader module*/
void Shader::setUpShader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	readShaderContents(vertexShaderPath, fragmentShaderPath);
	compileAndLinkShader(m_vertexShaderSourceCode, m_fragmentShaderSourceCode);
}

/*Bind the program for usage*/
void Shader::useShader()
{
	glUseProgram(m_programID);
}
