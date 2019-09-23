#include "Application.h"

#include "helpers/Logger.h"

#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

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

	LOG_INFO("--------------------------------");
	LOG_INFO("OpenGL Info:");
	LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
	LOG_INFO("--------------------------------");
}

void Application::Run()
{
	Initialize();

	// Vertex Data
	//============
	float vertices[] = {
		 // Position         // Color           // Texture Coords
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Bottom Left
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Bottom Right
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // Top Right
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f  // Top Left
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

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// TexCoord Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Shaders
	//========
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
	pShader->InitFromFile("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");

	// Textures
	//=========
	Texture tilesTexture("assets/textures/Tiles26/Tiles26_col.jpg");
	tilesTexture.Bind();
	pShader->SetUniformInt("tilesTexture", 0);

	while (!m_pWindow->ShouldClose())
	{
		Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);

		// Renderer::BeginScene(Camera());
		// Renderer::BeginScene(viewProjectionMatrix);
		// Renderer::Render(Mesh("res/models/some_object.obj"), object_transform);
		// Renderer::EndScene();

		Renderer::Render(VAO, EBO, 6, pShader);
		
		m_pWindow->Update();
	}

	Cleanup();
}

void Application::OnError(int error, const char* errorMsg)
{
	LOG_ERROR("GLFW Error: [{0}] {1}", error, errorMsg);
}

void Application::Cleanup()
{
	m_pWindow->Cleanup();
	delete m_pWindow;
}
