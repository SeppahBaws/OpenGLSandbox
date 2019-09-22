#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

	void Bind();

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);

private:
	unsigned int m_ProgramId;
};
