#pragma once

struct GLFWwindow;

class RenderContext
{
public:
	RenderContext(GLFWwindow* pWindow);

	void Init();
	void SwapBuffers();

	void OnWindowResize(GLFWwindow* pWindow, int width, int height);

private:
	GLFWwindow* m_pWindowHandle;
};
