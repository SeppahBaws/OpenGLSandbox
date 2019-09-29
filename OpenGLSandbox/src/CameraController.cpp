#include "pch.h"
#include "CameraController.h"

#include "Input.h"
#include "Time.h"

CameraController::CameraController(std::shared_ptr<Camera> pCamera)
	: m_pCamera(pCamera), m_Position({ 0.0f, 0.0f, 3.0f }), m_MoveSpeed(3.0f)
{
}

void CameraController::Update()
{
	float velocity = m_MoveSpeed * Time::GetDeltaTime();

	const float sensitivity = 0.15f;
	glm::vec2 mouseMovement = Input::GetCursorMovement() * sensitivity;

	if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
	{
		Input::SetCursorMode(CursorMode::Disabled);

		// Movement
		if (Input::IsKeyPressed(KeyCode::KeyW))
			m_Position += m_pCamera->GetFront() * velocity;
		if (Input::IsKeyPressed(KeyCode::KeyS))
			m_Position -= m_pCamera->GetFront() * velocity;
	
		if (Input::IsKeyPressed(KeyCode::KeyA))
			m_Position -= m_pCamera->GetRight() * velocity;
		if (Input::IsKeyPressed(KeyCode::KeyD))
			m_Position += m_pCamera->GetRight() * velocity;

		if (Input::IsKeyPressed(KeyCode::KeyE))
			m_Position += m_pCamera->GetUp() * velocity;
		if (Input::IsKeyPressed(KeyCode::KeyQ))
			m_Position -= m_pCamera->GetUp() * velocity;

		// Look
		m_pCamera->AddYaw(mouseMovement.x);
		m_pCamera->AddPitch(-mouseMovement.y);

		LOG_TRACE("Mouse Movement: {0}, {1}", mouseMovement.x, mouseMovement.y);
	}

	if (!Input::IsMouseButtonPressed(MouseCode::ButtonRight))
	{
		Input::SetCursorMode(CursorMode::Normal);
	}

	m_pCamera->SetPosition(m_Position);
}
