#pragma once

struct GLFWwindow;

class RenderContext
{
public:
	RenderContext(GLFWwindow* pWindow);

	void Init();
	void SwapBuffers();

private:
	GLFWwindow* m_pWindowHandle;
};
