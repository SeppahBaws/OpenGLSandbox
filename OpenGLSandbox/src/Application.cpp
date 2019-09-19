#include "Application.h"

#include <iostream>

#include "Window.h"
#include "helpers/Logger.h"

Application::Application()
	: m_pWindow(nullptr)
{
}

void Application::Initialize()
{
	Logger::Init();
	
	m_pWindow = new Window();
	m_pWindow->Initialize(1280, 720, "Hello World!");
}

void Application::Run()
{
	Initialize();
	
	while (!m_pWindow->ShouldClose())
	{
		m_pWindow->Update();
	}

	Cleanup();
}

void Application::Cleanup()
{
	m_pWindow->Cleanup();
	delete m_pWindow;
}
