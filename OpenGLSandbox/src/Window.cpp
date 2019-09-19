#include "Window.h"

#include "helpers/Logger.h"

#include <GLFW/glfw3.h>

Window::Window()
	: m_pGLFWWindow(nullptr)
{
}

void Window::Initialize(int width, int height, const std::string& title)
{
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
}

void Window::Update()
{
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
