#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::~Shader()
{
	glDeleteProgram(m_ProgramId);
}

void Shader::Bind()
{
	ASSERT(m_bInitialized, "Shader Not Initialized!");

	glUseProgram(m_ProgramId);
}

void Shader::Reload()
{
	// TODO: add ability to reload from source string?
	ASSERT(m_bFromFile, "Cannot reload shaders that aren't stored in a separate file!");

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, ReadFile(m_ShaderSources.first));
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ReadFile(m_ShaderSources.second));

	unsigned int reloadedProgram = CreateProgram(vertexShader, fragmentShader);

	if (reloadedProgram)
	{
		glDeleteProgram(m_ProgramId);
		m_ProgramId = reloadedProgram;
	}

	// Clear the Uniform Location Cache, as this shader is now a new program, and the locations are invalid now.
	m_UniformLocationCache.clear();
}

void Shader::InitFromSource(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	m_bFromFile = false;
	
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
	CreateProgram(vertexShader, fragmentShader);
}

void Shader::InitFromFile(const std::string& vertexFile, const std::string& fragmentFile)
{
	m_bFromFile = true;
	m_ShaderSources.first = vertexFile;
	m_ShaderSources.second = fragmentFile;
	
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, ReadFile(m_ShaderSources.first));
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ReadFile(m_ShaderSources.second));
	m_ProgramId = CreateProgram(vertexShader, fragmentShader);
}

void Shader::SetUniformInt(const std::string& name, int value)
{
	int location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::SetUniformFloat(const std::string& name, float value)
{
	int location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void Shader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
{
	int location = GetUniformLocation(name);
	glUniform2f(location, value.x, value.y);
}

void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
{
	int location = GetUniformLocation(name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
{
	int location = GetUniformLocation(name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	int location = GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
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

unsigned int Shader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	// Create program and attach shaders
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Get linking status
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		LOG_ERROR("Shader Linking Error: {0}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_bInitialized = true;
	// LOG_INFO("Shader program id: {0}", program);
	return program;
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

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	int location = glGetUniformLocation(m_ProgramId, name.c_str());
	m_UniformLocationCache[name] = location;
	return location;
}
