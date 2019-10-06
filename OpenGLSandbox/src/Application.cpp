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
#include "Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_impl_glfw.h"
#include "dependencies/imgui/imgui_impl_opengl3.h"

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

	// ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;		// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;			// Enable Multi-Viewports / Platform Windows

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	ImGui_ImplGlfw_InitForOpenGL(m_pWindow->GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");

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

	// Model Test
	//============
	std::shared_ptr<Model> pModel = std::make_shared<Model>("assets/models/drakefire-pistol/drakefire_pistol_low.obj");
	glm::vec3 modelPosition = glm::vec3(0.0f);
	glm::vec3 modelRotation = glm::vec3(0.0f);
	glm::vec3 modelScale = glm::vec3(1.0f);

	// Textures
	//=========
	Texture pistolAlbedo("assets/models/drakefire-pistol/textures/base_albedo.jpg");
	Texture pistolRoughness("assets/models/drakefire-pistol/textures/base_roughness.jpg");
	
	// Shaders
	//========
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
	pShader->InitFromFile("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");

	// Camera
	//=======
	std::shared_ptr<Camera> pCamera = std::make_shared<Camera>(90, m_pWindow->GetAspectRatio(), 0.1f, 1000.0f);
	std::shared_ptr<CameraController> pCameraController = std::make_shared<CameraController>(pCamera);
	
	auto lastTime = Time::GetTimePoint();
	while (!m_pWindow->ShouldClose())
	{
		const auto currentTime = Time::GetTimePoint();
		Time::Update(lastTime);
		Input::Update();

		// ImGui New Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		pCameraController->Update();

		Renderer::BeginScene(pCamera);
		Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);

		pShader->SetUniformInt("albedo", 0);
		pShader->SetUniformInt("roughness", 1);
		
		// Draw Pistol
		pistolAlbedo.Bind(0);
		pistolRoughness.Bind(1);
		Renderer::Render(pModel, pShader, glm::translate(glm::mat4(1.0f), modelPosition) *
			glm::orientate4(glm::vec3(glm::radians(modelRotation))) *
			glm::scale(glm::mat4(1.0f), modelScale));

		ImGui::ShowDemoWindow();

		ImGuiIO& io = ImGui::GetIO();

		static int renderMode = GL_FILL;
		static int pointSize = 2;
		static int lineWidth = 2;
		if (ImGui::Begin("Rendering Settings"))
		{
			ImGui::RadioButton("Filled", &renderMode, GL_FILL);
			ImGui::RadioButton("Wire frame", &renderMode, GL_LINE);
			ImGui::RadioButton("Points", &renderMode, GL_POINT);

			ImGui::Separator();

			ImGui::SliderInt("Wire frame width", &lineWidth, 1, 10);
			ImGui::SliderInt("Point size", &pointSize, 1, 10);
		}
		ImGui::End();
		glPolygonMode(GL_FRONT_AND_BACK, renderMode);
		glPointSize(float(pointSize));
		glLineWidth(float(lineWidth));

		if (ImGui::Begin("Custom Model Properties"))
		{
			ImGui::Text("Transform");
			ImGui::InputFloat3("Position", glm::value_ptr(modelPosition));
			ImGui::InputFloat3("Rotation", glm::value_ptr(modelRotation));
			ImGui::InputFloat3("Scale", glm::value_ptr(modelScale));

			ImGui::Separator();

			ImGui::Text("Material");
			if (ImGui::Button("Reload Shader"))
			{
				LOG_WARN("Reloading Shaders...");
				pShader->Reload();
			}
		}
		ImGui::End();

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 window_pos = ImVec2(viewport->Pos.x + 10.0f, viewport->Pos.y + 10.0f);
		ImVec2 window_pos_pivot = ImVec2(0.0f, 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::SetNextWindowBgAlpha(0.35f);
		if (ImGui::Begin("Statistics", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Application Statistics");
			ImGui::Separator();
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::Text("DeltaTime: %.3f ms", Time::GetDeltaTime() * 1000.0f);
		}
		ImGui::End();

		// ImGui Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		// Swap buffers etc
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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	m_pWindow->Cleanup();
	delete m_pWindow;
}
