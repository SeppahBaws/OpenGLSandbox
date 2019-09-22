#pragma once

class Window;

class Application
{
public:
	Application();
	
	void Run();

public:
	static void OnError(int error, const char* errorMsg);
	
private:
	void Initialize();
	void Cleanup();

private:
	Window* m_pWindow;
};
