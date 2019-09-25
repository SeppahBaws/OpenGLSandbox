#include "pch.h"
#include "RenderContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

RenderContext::RenderContext(GLFWwindow* pWindow)
	: m_pWindowHandle(pWindow)
{
}

void RenderContext::Init()
{
	glfwMakeContextCurrent(m_pWindowHandle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("RenderContext: Failed to initialize GLAD!");
		glfwTerminate();

		return;
	}
}

void RenderContext::SwapBuffers()
{
	glfwSwapBuffers(m_pWindowHandle);
}

void RenderContext::OnWindowResize(GLFWwindow* pWindow, int width, int height)
{
	glViewport(0, 0, width, height);
}
