#pragma once
#include <string>

#include "RenderContext.h"

struct GLFWwindow;

class Window
{
public:
	Window();

	void Initialize(int width, int height, const std::string& title);
	void Update();
	void Cleanup();

	bool ShouldClose() const;

private:
	void CenterWindow();
	
private:
	GLFWwindow* m_pGLFWWindow;
	RenderContext* m_pRenderContext;
};
