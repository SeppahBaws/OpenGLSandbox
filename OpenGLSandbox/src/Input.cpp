#include "pch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

GLFWwindow* Input::s_pWindow = nullptr;

void Input::Init(GLFWwindow* pWindow)
{
	s_pWindow = pWindow;
}

bool Input::IsMouseButtonPressed(MouseCode mouseButton)
{
	ASSERT(s_pWindow, "GLFW Window is nullptr");

	const int state = glfwGetMouseButton(s_pWindow, static_cast<int>(mouseButton));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsKeyPressed(KeyCode keyCode)
{
	ASSERT(s_pWindow, "GLFW Window is nullptr");

	const int state = glfwGetKey(s_pWindow, static_cast<int>(keyCode));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}
