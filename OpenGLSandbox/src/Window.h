#pragma once
#include <string>

#include "RenderContext.h"

struct GLFWwindow;

class Window
{
public:
	struct WindowData
	{
		int width, height;
		std::string title;
		bool resizable = false;
	};
	
public:
	Window();

	void Initialize(const WindowData& data);
	void Update();
	void Cleanup();

	bool ShouldClose() const;

private:
	void CenterWindow();

private:
	GLFWwindow* m_pGLFWWindow;
	RenderContext* m_pRenderContext;
};
