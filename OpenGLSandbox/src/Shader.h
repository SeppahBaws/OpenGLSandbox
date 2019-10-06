#pragma once
#include <string>

#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
public:
	Shader() = default;
	~Shader();

	void Bind();

	void Reload();

	// Do we really need the ability to initialize from source strings?
	void InitFromSource(const std::string& vertexSrc, const std::string& fragmentSrc);
	void InitFromFile(const std::string& vertexFile, const std::string& fragmentFile);

	void SetUniformInt(const std::string& name, int value);

	void SetUniformFloat(const std::string& name, float value);
	void SetUniformFloat2(const std::string& name, const glm::vec2& value);
	void SetUniformFloat3(const std::string& name, const glm::vec3& value);
	void SetUniformFloat4(const std::string& name, const glm::vec4& value);

	void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

	std::string ReadFile(const std::string& path);

	int GetUniformLocation(const std::string& name);

private:
	unsigned int m_ProgramId;
	bool m_bInitialized = false;

	bool m_bFromFile;
	std::pair<std::string, std::string> m_ShaderSources; // Holds the file paths of the shader sources. Needed for hot-reload

	// Shader Uniform Location Cache.
	// glGetUniformLocation is a pretty costly operation, so we cache the shader uniform locations
	// for faster access the next time.
	std::unordered_map<std::string, int> m_UniformLocationCache;
};
