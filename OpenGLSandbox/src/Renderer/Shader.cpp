#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <regex>

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
	// Cleanup from previous shader.
	m_UniformLocationCache.clear();
	m_Uniforms.clear();

	// std::vector<std::pair<ShaderType, std::string>> shaders;
	// ASSERT(parser.Parse(m_ShaderSource, shaders), "Failed to parse shaders!");

	GLShaderParser::ShaderParser parser;
	GLShaderParser::ShaderData data;
	if (!parser.Parse(m_SourceLocation, data))
	{
		LOG_ERROR("Error parsing shader!");
		return;
	}

	m_Uniforms = data.parameters;

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, data.vertexShader);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, data.fragmentShader);

	unsigned int reloadedProgram = CreateProgram(vertexShader, fragmentShader);

	if (reloadedProgram)
	{
		glDeleteProgram(m_ProgramId);
		m_ProgramId = reloadedProgram;
	}

#ifdef _DEBUG
	LogUniformVariables();
#endif
}

void Shader::InitFromFile(const std::string& shaderFile)
{
	m_SourceLocation = shaderFile;

	GLShaderParser::ShaderParser parser;
	GLShaderParser::ShaderData data;
	if (!parser.Parse(shaderFile, data))
	{
		LOG_ERROR("Error parsing shader file!");
		return;
	}

	m_Uniforms = data.parameters;
	
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, data.vertexShader);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, data.fragmentShader);
	m_ProgramId = CreateProgram(vertexShader, fragmentShader);
}

#pragma region Uniform Value Setting
void Shader::SetUniformBool(const std::string& name, bool value)
{
	int location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::SetUniformBool2(const std::string& name, const glm::bvec2& value)
{
	int location = GetUniformLocation(name);
	glUniform2i(location, value.x, value.y);
}

void Shader::SetUniformBool3(const std::string& name, const glm::bvec3& value)
{
	int location = GetUniformLocation(name);
	glUniform3i(location, value.x, value.y, value.z);
}

void Shader::SetUniformBool4(const std::string& name, const glm::bvec4& value)
{
	int location = GetUniformLocation(name);
	glUniform4i(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniformInt(const std::string& name, int value)
{
	int location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::SetUniformInt2(const std::string& name, const glm::ivec2& value)
{
	int location = GetUniformLocation(name);
	glUniform2i(location, value.x, value.y);
}

void Shader::SetUniformInt3(const std::string& name, const glm::ivec3& value)
{
	int location = GetUniformLocation(name);
	glUniform3i(location, value.x, value.y, value.z);
}

void Shader::SetUniformInt4(const std::string& name, const glm::ivec4& value)
{
	int location = GetUniformLocation(name);
	glUniform4i(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniformUInt(const std::string& name, unsigned value)
{
	int location = GetUniformLocation(name);
	glUniform1ui(location, value);
}

void Shader::SetUniformUInt2(const std::string& name, const glm::uvec2& value)
{
	int location = GetUniformLocation(name);
	glUniform2ui(location, value.x, value.y);
}

void Shader::SetUniformUInt3(const std::string& name, const glm::uvec3& value)
{
	int location = GetUniformLocation(name);
	glUniform3ui(location, value.x, value.y, value.z);
}

void Shader::SetUniformUInt4(const std::string& name, const glm::uvec4& value)
{
	int location = GetUniformLocation(name);
	glUniform4ui(location, value.x, value.y, value.z, value.w);
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

void Shader::SetUniformDouble(const std::string& name, double value)
{
	int location = GetUniformLocation(name);
	glUniform1d(location, value);
}

void Shader::SetUniformDouble2(const std::string& name, const glm::dvec2& value)
{
	int location = GetUniformLocation(name);
	glUniform2d(location, value.x, value.y);
}

void Shader::SetUniformDouble3(const std::string& name, const glm::dvec3& value)
{
	int location = GetUniformLocation(name);
	glUniform3d(location, value.x, value.y, value.z);
}

void Shader::SetUniformDouble4(const std::string& name, const glm::dvec4& value)
{
	int location = GetUniformLocation(name);
	glUniform4d(location, value.x, value.y, value.z, value.w);
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
#pragma endregion

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

void Shader::LogUniformVariables()
{
	using namespace GLShaderParser; // GLShaderParser::DataType

	for (auto it = m_Uniforms.begin(); it != m_Uniforms.end(); ++it)
	{
		std::string type;
		switch (it->type)
		{
		case DataType::Bool: 		type = "Bool"; break;
		case DataType::Bool2: 		type = "Bool2"; break;
		case DataType::Bool3: 		type = "Bool3"; break;
		case DataType::Bool4: 		type = "Bool4"; break;
		case DataType::Int: 		type = "Int"; break;
		case DataType::Int2: 		type = "Int2"; break;
		case DataType::Int3: 		type = "Int3"; break;
		case DataType::Int4: 		type = "Int4"; break;
		case DataType::UInt: 		type = "UInt"; break;
		case DataType::UInt2: 		type = "UInt2"; break;
		case DataType::UInt3: 		type = "UInt3"; break;
		case DataType::UInt4: 		type = "UInt4"; break;
		case DataType::Float: 		type = "Float"; break;
		case DataType::Float2: 		type = "Float2"; break;
		case DataType::Float3: 		type = "Float3"; break;
		case DataType::Float4: 		type = "Float4"; break;
		case DataType::Double: 		type = "Double"; break;
		case DataType::Double2: 	type = "Double2"; break;
		case DataType::Double3: 	type = "Double3"; break;
		case DataType::Double4: 	type = "Double4"; break;
		case DataType::Mat3: 		type = "Mat3"; break;
		case DataType::Mat4: 		type = "Mat4"; break;
		case DataType::Sampler2D: 	type = "Sampler2D"; break;
		}
		LOG_DEBUG("Uniform: {1} {0}", it->name, type);
	}
}
