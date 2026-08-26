
#include "scop.hpp"
#include "Shader.hpp"

unsigned int Shader::getID() const
{
	return (_ID);
}

void Shader::use() const
{
	glUseProgram(_ID);
}

unsigned int	Shader::_compilShaderFile(const char* path, GLenum type) const
{
	std::string			code_str;
	unsigned int		id;
	const char*			code;

	code_str = fileLoader::toString(path);
	code = code_str.c_str();

	// Create the OpenGL shader object
	id = glCreateShader(type);
	glShaderSource(id, 1, &code, NULL);
	glCompileShader(id);
	_checkShaderCompil(id);
	glAttachShader(_ID, id);

	return (id);
}

void Shader::_checkShaderCompil(unsigned int shaderID) const
{
	
	int success;
	char infoLog[512];

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION::FAILED\n" << infoLog << std::endl;
		
		clean_exit(true, 4);
	}
}

void Shader::_checkProgramLink(unsigned int programID) const
{
	
	int success;
	char infoLog[512];

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::LINKAGE::FAILED\n" << infoLog << std::endl;
		
		clean_exit(true, 5);
	}
}

// TODO : Could use a bit mask and an array to specify what to load
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	unsigned int	vertex_id;
	unsigned int	fragment_id;

	_ID = glCreateProgram();

	vertex_id = _compilShaderFile(vertexPath, GL_VERTEX_SHADER);
	fragment_id = _compilShaderFile(fragmentPath, GL_FRAGMENT_SHADER);

	glLinkProgram(_ID);
	_checkProgramLink(_ID);

	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

}

// DESTRUCTOR

Shader::~Shader()
{
	glDeleteProgram(_ID);
}
