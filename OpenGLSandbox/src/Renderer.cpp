#include "Renderer.h"

#include "helpers/Logger.h"

#include <glad/glad.h>
#include <sstream>

unsigned int Renderer::s_DemoShader;

void Renderer::Init(const ViewportData& vp)
{
	glViewport(vp.x, vp.y, vp.width, vp.height);

	// demo shaders
	const char* vertexShaderSource = R"(
	#version 460 core
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec3 a_Color;

	out vec3 v_Color;

	void main()
	{
		v_Color = a_Color;
		gl_Position = vec4(a_Position, 1.0);
	})";

	const char* fragmentShaderSource = R"(
	#version 460 core
	layout(location = 0) out vec4 color;

	in vec3 v_Color;

	void main()
	{
		color = vec4(v_Color, 1.0);
	})";

	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::stringstream ss;
		ss << "[Vertex Shader Compile Error]: " << infoLog;
		Logger::LogError(ss.str());
	}

	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::stringstream ss;
		ss << "[Fragment Shader Compile Error]: " << infoLog;
		Logger::LogError(ss.str());
	}

	// link shaders
	s_DemoShader = glCreateProgram();
	glAttachShader(s_DemoShader, vertexShader);
	glAttachShader(s_DemoShader, fragmentShader);
	glLinkProgram(s_DemoShader);
	glGetProgramiv(s_DemoShader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(s_DemoShader, 512, nullptr, infoLog);
		std::stringstream ss;
		ss << "[Shader Program Linking Error]: " << infoLog;
		Logger::LogError(ss.str());
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(unsigned int VAO, unsigned int EBO, int count)
{
	glUseProgram(s_DemoShader);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
