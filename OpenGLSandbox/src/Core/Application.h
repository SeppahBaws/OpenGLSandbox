#pragma once

class Scene;
class Window;

class Application
{
public:
	Application();

	void UseScene(Scene* pScene);
	void Run();

public:
	static void OnError(int error, const char* errorMsg);
	
private:
	void Initialize();
	void Cleanup();

private:
	Window* m_pWindow;
	Scene* m_pScene;

	const int m_MsPerFrame = 16; // hard-lock to 60 fps
};
