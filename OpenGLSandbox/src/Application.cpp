#include "Application.h"

#include <iostream>
#include <sstream>

#include "Window.h"
#include "helpers/Logger.h"
#include "Renderer.h"

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
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
	while (!m_pWindow->ShouldClose())
	{
		Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);

		// Renderer::BeginScene(Camera());
		// Renderer::BeginScene(viewProjectionMatrix);
		// Renderer::Render(Mesh("res/models/some_object.obj"), object_transform);
		// Renderer::EndScene();
		
		Renderer::Render(VBO, EBO, 6);
		
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
