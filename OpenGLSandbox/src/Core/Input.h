#pragma once
#include "InputCodes.h"

#include <glm/vec2.hpp>

struct GLFWwindow;

class Input
{
public:
	static void Init(GLFWwindow* pWindow);
	static void Update();

	static bool IsMouseButtonPressed(MouseCode mouseButton);
	static bool IsKeyPressed(KeyCode keyCode);

	static glm::vec2 GetCursorPosition();
	static glm::vec2 GetCursorMovement();

	static void SetCursorMode(CursorMode mode);

private:
	static GLFWwindow* s_pWindow;
	static bool s_bFirstFrame;
	static glm::vec2 s_LastMousePosition;
	static glm::vec2 s_MouseMovement;
};
