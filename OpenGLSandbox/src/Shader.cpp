#include "Shader.h"

#include "helpers/Logger.h"
#include <sstream>

#include <glad/glad.h>

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

	// Create program and attach shaders
	m_ProgramId = glCreateProgram();
	glAttachShader(m_ProgramId, vertexShader);
	glAttachShader(m_ProgramId, fragmentShader);
	glLinkProgram(m_ProgramId);

	// Get linking status
	int success;
	char infoLog[512];
	glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ProgramId, 512, nullptr, infoLog);
		std::stringstream ss;
		ss << "Shader Link Error: " << infoLog;
		Logger::LogError(ss.str());
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Bind()
{
	glUseProgram(m_ProgramId);
}

unsigned int Shader::CompileShader(unsigned type, const std::string& source)
{
	// Create shader and attach sources
	unsigned int shaderId = glCreateShader(type);
	const char* sourceCstr = source.c_str();
	glShaderSource(shaderId, 1, &sourceCstr, nullptr);
	glCompileShader(shaderId);

	// Check for shader compile status
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
		std::stringstream ss;
		ss << "Shader Compile Error: " << infoLog;
		Logger::LogError(ss.str());
	}

	return shaderId;
}