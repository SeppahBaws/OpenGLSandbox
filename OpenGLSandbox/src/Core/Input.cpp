#include "pch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

GLFWwindow* Input::s_pWindow = nullptr;
bool Input::s_bFirstFrame = true;
glm::vec2 Input::s_LastMousePosition = glm::vec2(0.0f, 0.0f);
glm::vec2 Input::s_MouseMovement = glm::vec2(0.0f, 0.0f);

void Input::Init(GLFWwindow* pWindow)
{
	s_pWindow = pWindow;
}

void Input::Update()
{
	ASSERT(s_pWindow, "GLFW Window is nullptr");

	if (s_bFirstFrame)
	{
		s_bFirstFrame = false;
		s_LastMousePosition = GetCursorPosition();
		s_MouseMovement = glm::vec2(0.0f, 0.0f);
		return;
	}

	glm::vec2 prevPos = s_LastMousePosition;
	s_LastMousePosition = GetCursorPosition();

	s_MouseMovement = s_LastMousePosition - prevPos;
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

glm::vec2 Input::GetCursorPosition()
{
	ASSERT(s_pWindow, "GLFW Window is nullptr");

	double xPos, yPos;
	glfwGetCursorPos(s_pWindow, &xPos, &yPos);

	return glm::vec2(float(xPos), float(yPos));
}

glm::vec2 Input::GetCursorMovement()
{
	return s_MouseMovement;
}

void Input::SetCursorMode(CursorMode mode)
{
	ASSERT(s_pWindow, "GLFW Window is nullptr");

	glfwSetInputMode(s_pWindow, GLFW_CURSOR, static_cast<int>(mode));
}
