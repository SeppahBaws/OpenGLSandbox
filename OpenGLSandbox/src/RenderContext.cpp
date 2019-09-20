#include "RenderContext.h"

#include "helpers/Logger.h"

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
		Logger::LogError("RenderContext: Failed to initialize GLAD!");
		glfwTerminate();

		return;
	}
}

void RenderContext::SwapBuffers()
{
	glfwSwapBuffers(m_pWindowHandle);
}
