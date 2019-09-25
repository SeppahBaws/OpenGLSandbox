#pragma once
#include "InputCodes.h"

struct GLFWwindow;

class Input
{
public:
	static void Init(GLFWwindow* pWindow);

	static bool IsMouseButtonPressed(MouseCode mouseButton);
	static bool IsKeyPressed(KeyCode keyCode);

private:
	static GLFWwindow* s_pWindow;
};
