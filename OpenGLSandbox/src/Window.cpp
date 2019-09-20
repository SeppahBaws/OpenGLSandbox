#include "Window.h"

#include "helpers/Logger.h"
#include "RenderContext.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window()
	: m_pGLFWWindow(nullptr), m_pRenderContext(nullptr)
{
}

void Window::Initialize(int width, int height, const std::string& title)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		Logger::LogError("Error initializing GLFW!");
		return;
	}

	m_pGLFWWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_pGLFWWindow)
	{
		Logger::LogError("Error initializing window!");
		glfwTerminate();
		return;
	}
	
	CenterWindow();


	m_pRenderContext = new RenderContext(m_pGLFWWindow);
	m_pRenderContext->Init();
}

void Window::Update()
{
	Renderer::Clear(0.2f, 0.3f, 0.8f, 1.0f);

	m_pRenderContext->SwapBuffers();
	
	glfwPollEvents();
}

void Window::Cleanup()
{
	delete m_pRenderContext;
	
	glfwTerminate();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_pGLFWWindow);
}

void Window::CenterWindow()
{
	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
	if (!pMonitor)
		return;

	const GLFWvidmode* pMode = glfwGetVideoMode(pMonitor);
	if (!pMode)
		return;

	int monitorX, monitorY;
	glfwGetMonitorPos(pMonitor, &monitorX, &monitorY);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_pGLFWWindow, &windowWidth, &windowHeight);

	glfwSetWindowPos(m_pGLFWWindow,
		monitorX + (pMode->width - windowWidth) / 2,
		monitorY + (pMode->height - windowHeight) / 2);
}
