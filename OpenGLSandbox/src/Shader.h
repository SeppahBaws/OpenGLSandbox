#pragma once

#include <string>

class Shader
{
public:
	Shader();

	void Bind();

	void InitFromSource(const std::string& vertexSrc, const std::string& fragmentSrc);
	void InitFromFile(const std::string& vertexFile, const std::string& fragmentFile);
	
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	void CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

	std::string ReadFile(const std::string& path);

private:
	unsigned int m_ProgramId;
	bool m_bInitialized = false;
};
