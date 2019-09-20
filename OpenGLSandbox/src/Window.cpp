#include "Window.h"

#include "helpers/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window()
	: m_pGLFWWindow(nullptr)
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

	glfwMakeContextCurrent(m_pGLFWWindow);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::LogError("Error initializing GLAD!");
		glfwTerminate();
		return;
	}

	CenterWindow();
}

void Window::Update()
{
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(m_pGLFWWindow);

	glfwPollEvents();
}

void Window::Cleanup()
{
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
