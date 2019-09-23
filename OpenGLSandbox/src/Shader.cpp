#include "Shader.h"

#include "helpers/Assert.h"
#include <fstream>

#include <glad/glad.h>

Shader::Shader()
{
}

void Shader::Bind()
{
	ASSERT(m_bInitialized, "Shader Not Initialized!");

	glUseProgram(m_ProgramId);
}

void Shader::InitFromSource(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
	CreateProgram(vertexShader, fragmentShader);
}

void Shader::InitFromFile(const std::string& vertexFile, const std::string& fragmentFile)
{
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, ReadFile(vertexFile));
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ReadFile(fragmentFile));
	CreateProgram(vertexShader, fragmentShader);
}

void Shader::SetUniformInt(const std::string& name, int value)
{
	int location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1i(location, value);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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
		LOG_ERROR("Shader Compilation Error: {0}", infoLog);
	}

	return shaderId;
}

void Shader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
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
		LOG_ERROR("Shader Linking Error: {0}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_bInitialized = true;
}

std::string Shader::ReadFile(const std::string& path)
{
	std::string result;
	std::ifstream in(path, std::ios::in | std::ios::binary);
	if (!in)
	{
		LOG_ERROR("Shader: Unable to open file '{0}'", path);
		return result;
	}

	// Write the contents of the file into result
	in.seekg(0, std::ios::end);
	result.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&result[0], result.size());
	in.close();

	return result;
}
