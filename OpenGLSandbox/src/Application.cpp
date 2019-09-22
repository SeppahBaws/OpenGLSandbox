﻿#include "Application.h"

#include <iostream>
#include <sstream>

#include "Window.h"
#include "helpers/Logger.h"
#include "Renderer.h"
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application::Application()
	: m_pWindow(nullptr)
{
}

void Application::Initialize()
{
	Logger::Init();

	glfwSetErrorCallback(OnError);
	
	m_pWindow = new Window();
	m_pWindow->Initialize({ 1280, 720, "Hello World!", true });

	Renderer::Init({ 0, 0, 1280, 720 });
}

void Application::Run()
{
	Initialize();

	float vertices[] = {
		 // Position         // Color
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::string vertexShader = R"(
	#version 460 core
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec3 a_Color;

	out vec3 v_Color;

	void main()
	{
		v_Color = a_Color;
		gl_Position = vec4(a_Position, 1.0);
	})";

	std::string fragmentShader = R"(
	#version 460 core
	layout(location = 0) out vec4 color;

	in vec3 v_Color;

	void main()
	{
		color = vec4(v_Color, 1.0);
	})";

	Shader shader(vertexShader, fragmentShader);

	while (!m_pWindow->ShouldClose())
	{
		Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);

		// Renderer::BeginScene(Camera());
		// Renderer::BeginScene(viewProjectionMatrix);
		// Renderer::Render(Mesh("res/models/some_object.obj"), object_transform);
		// Renderer::EndScene();
		
		Renderer::Render(VAO, EBO, 6, shader);
		
		m_pWindow->Update();
	}

	Cleanup();
}

void Application::OnError(int error, const char* errorMsg)
{
	std::stringstream ss;
	ss << "GLFW Error: [" << error << "] " << errorMsg;
	Logger::LogError(ss.str());
}

void Application::Cleanup()
{
	m_pWindow->Cleanup();
	delete m_pWindow;
}
