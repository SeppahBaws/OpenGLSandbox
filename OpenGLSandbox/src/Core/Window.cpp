﻿#include "pch.h"
#include "Window.h"

#include "src/Renderer/RenderContext.h"
#include "src/Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window()
	: m_pGLFWWindow(nullptr), m_pRenderContext(nullptr)
{
}

void Window::Initialize(const WindowData& data)
{
	m_WindowData = data;
	
	// Initialize GLFW
	if (!glfwInit())
	{
		LOG_ERROR("Error initializing GLFW!");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, data.resizable);

	m_pGLFWWindow = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
	if (!m_pGLFWWindow)
	{
		LOG_ERROR("Error initializing window!");
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(m_pGLFWWindow, this);

	if (data.resizable)
	{
		glfwSetWindowSizeCallback(m_pGLFWWindow, [](GLFWwindow* pWindow, int width, int height)
		{
			Window* window = (Window*)glfwGetWindowUserPointer(pWindow);
			window->m_pRenderContext->OnWindowResize(pWindow, width, height);
		});
	}
	
	CenterWindow();

	m_pRenderContext = new RenderContext(m_pGLFWWindow);
	m_pRenderContext->Init();

	glfwSwapInterval(1);
}

void Window::Update()
{
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
