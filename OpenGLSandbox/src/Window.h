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

	inline int GetWidth() const { return m_WindowData.width; }
	inline int GetHeight() const { return m_WindowData.height; }
	inline float GetAspectRatio() const { return float(m_WindowData.width) / float(m_WindowData.height); }

	inline GLFWwindow* GetGLFWWindow() const { return m_pGLFWWindow; }

private:
	void CenterWindow();

private:
	GLFWwindow* m_pGLFWWindow;
	RenderContext* m_pRenderContext;
	WindowData m_WindowData;
};
