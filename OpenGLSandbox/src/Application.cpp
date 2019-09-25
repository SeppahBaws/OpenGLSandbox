#include "Application.h"

#include <chrono>

#include "helpers/Logger.h"

#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Time.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.inl>

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

	Renderer::Init({ 0, 0, m_pWindow->GetWidth(), m_pWindow->GetHeight() });

	LOG_INFO("--------------------------------");
	LOG_INFO("OpenGL Info:");
	LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
	LOG_INFO("--------------------------------");
}

void Application::Run()
{
	auto t = Time::GetTime();
	
	Initialize();

	// Vertex Data
	//============
	std::vector<Vertex> vertices = {
		 // Position           // Texture Coords
		{{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }}, // Bottom Left
		{{  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }}, // Bottom Right
		{{  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f }}, // Top Right
		{{ -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f }}  // Top Left
	};
	std::vector<uint32_t> indices = {
		0, 1, 3,
		1, 2, 3
	};

	// Mesh Data
	//==========
	std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>(vertices, indices);
	glm::mat4 meshTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));

	// Shaders
	//========
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
	pShader->InitFromFile("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");

	// Textures
	//=========
	Texture tilesTexture("assets/textures/Tiles26/Tiles26_col.jpg");
	tilesTexture.Bind();
	pShader->SetUniformInt("tilesTexture", 0);
	
	auto lastTime = Time::GetTime();
	while (!m_pWindow->ShouldClose())
	{
		const auto currentTime = Time::GetTime();
		Time::Update(lastTime);
		
		Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);
		Renderer::Render(pMesh, pShader, meshTransform);

		m_pWindow->Update();

		t = lastTime + std::chrono::milliseconds(m_MsPerFrame);
		lastTime = currentTime;
		std::this_thread::sleep_until(t);
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
