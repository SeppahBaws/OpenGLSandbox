#pragma once
#include <string>

#include <glm/glm.hpp>
#include <unordered_map>
#include <glad/glad.h>

#include <ShaderParser.h>

class Shader
{
public:
	~Shader();

	void Bind();

	void Reload();

	std::vector<GLShaderParser::Parameter> GetUniforms() const { return m_Uniforms; }

	// Do we really need the ability to initialize from source strings?
	void InitFromFile(const std::string& shaderFile);

	void SetUniformBool(const std::string& name, bool value);
	void SetUniformBool2(const std::string& name, const glm::bvec2& value);
	void SetUniformBool3(const std::string& name, const glm::bvec3& value);
	void SetUniformBool4(const std::string& name, const glm::bvec4& value);
	
	void SetUniformInt(const std::string& name, int value);
	void SetUniformInt2(const std::string& name, const glm::ivec2& value);
	void SetUniformInt3(const std::string& name, const glm::ivec3& value);
	void SetUniformInt4(const std::string& name, const glm::ivec4& value);

	void SetUniformUInt(const std::string& name, unsigned int value);
	void SetUniformUInt2(const std::string& name, const glm::uvec2& value);
	void SetUniformUInt3(const std::string& name, const glm::uvec3& value);
	void SetUniformUInt4(const std::string& name, const glm::uvec4& value);
	
	void SetUniformFloat(const std::string& name, float value);
	void SetUniformFloat2(const std::string& name, const glm::vec2& value);
	void SetUniformFloat3(const std::string& name, const glm::vec3& value);
	void SetUniformFloat4(const std::string& name, const glm::vec4& value);

	void SetUniformDouble(const std::string& name, double value);
	void SetUniformDouble2(const std::string& name, const glm::dvec2& value);
	void SetUniformDouble3(const std::string& name, const glm::dvec3& value);
	void SetUniformDouble4(const std::string& name, const glm::dvec4& value);

	void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

	int GetUniformLocation(const std::string& name);

	void LogUniformVariables();

private:
	unsigned int m_ProgramId;
	bool m_bInitialized = false;

	std::string m_SourceLocation;
	
	// Shader Uniform Location Cache.
	// glGetUniformLocation is a pretty costly operation, so we cache the shader uniform locations
	// for faster access the next time.
	std::unordered_map<std::string, int> m_UniformLocationCache;

	// std::unordered_map<std::string, GLShaderParser::DataType> m_Uniforms;
	std::vector<GLShaderParser::Parameter> m_Uniforms;
};
