#pragma once

class Window;

class Application
{
public:
	Application();
	
	void Run();

private:
	void Initialize();
	void Cleanup();

private:
	Window* m_pWindow;
};
