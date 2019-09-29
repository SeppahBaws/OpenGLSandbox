#include "pch.h"
#include "Application.h"

#include <chrono>

#include "Window.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Time.h"
#include "Input.h"
#include "Camera.h"
#include "CameraController.h"

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
	m_pWindow->Initialize({ 1280, 720, "C++ OpenGL Sandbox", true });

	Renderer::Init({ 0, 0, m_pWindow->GetWidth(), m_pWindow->GetHeight() });

	Input::Init(m_pWindow->GetGLFWWindow());

	LOG_INFO("--------------------------------");
	LOG_INFO("OpenGL Info:");
	LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
	LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
	LOG_INFO("--------------------------------");
}

void Application::Run()
{
	auto t = Time::GetTimePoint();
	
	Initialize();

	// Vertex Data
	//============
	// Vertex Data
	//============
	std::vector<Vertex> vertices = {
		// Position           // Texture Coords
	   // Front Face
	   {{ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }}, // Bottom Left
	   {{  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }}, // Bottom Right
	   {{  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }}, // Top Right
	   {{ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }}, // Top Left

	   // Right Face
	   {{  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }}, // Bottom Left
	   {{  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }}, // Bottom Right
	   {{  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }}, // Top Right
	   {{  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }}, // Top Left

	   // Top Face
	   {{ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f }}, // Bottom Left
	   {{  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f }}, // Bottom Right
	   {{  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }}, // Top Right
	   {{ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }}, // Top Left

	   // Back Face
	   {{  0.5f, -0.5f,  0.5f}, { 0.0f, 0.0f }}, // Bottom Left
	   {{ -0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f }}, // Bottom Right
	   {{ -0.5f,  0.5f,  0.5f}, { 1.0f, 1.0f }}, // Top Right
	   {{  0.5f,  0.5f,  0.5f}, { 0.0f, 1.0f }}, // Top Left

	   // Left Face
	   {{ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }}, // Bottom Left
	   {{ -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }}, // Bottom Right
	   {{ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }}, // Top Right
	   {{ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }}, // Top Left

	   // Bottom Face
	   {{ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }}, // Bottom Left
	   {{  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f }}, // Bottom Right
	   {{  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }}, // Top Right
	   {{ -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }}, // Top Left
	};
	std::vector<uint32_t> indices = {
		// Front Face
		0, 1, 3,
		1, 2, 3,

		// Right Face
		4, 5, 7,
		5, 6, 7,

		// Top Face
		8, 9, 11,
		9, 10, 11,

		// Back Face
		12, 13, 15,
		13, 14, 15,

		// Left Face
		16, 17, 19,
		17, 18, 19,

		// Bottom Face
		20, 21, 23,
		21, 22, 23
	};

	// Mesh Data
	//==========
	std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>(vertices, indices);
	glm::vec3 meshPosition = glm::vec3(0.0f);

	// Shaders
	//========
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
	pShader->InitFromFile("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");

	// Textures
	//=========
	Texture tilesTexture("assets/textures/Tiles26/Tiles26_col.jpg");
	tilesTexture.Bind();
	pShader->SetUniformInt("tilesTexture", 0);

	// Camera
	//=======
	std::shared_ptr<Camera> pCamera = std::make_shared<Camera>(90, m_pWindow->GetAspectRatio(), 0.1f, 1000.0f);
	std::shared_ptr<CameraController> pCameraController = std::make_shared<CameraController>(pCamera);
	
	auto lastTime = Time::GetTimePoint();
	while (!m_pWindow->ShouldClose())
	{
		const auto currentTime = Time::GetTimePoint();
		Time::Update(lastTime);

		pCameraController->Update();
		
		Renderer::BeginScene(pCamera);
		Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);
		Renderer::Render(pMesh, pShader, glm::translate(glm::mat4(1.0f), meshPosition));

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
