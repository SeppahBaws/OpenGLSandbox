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
	const float moveVelocity = m_MoveSpeed * Time::GetDeltaTime();

	if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
	{
		Input::SetCursorMode(CursorMode::Disabled);

		// Movement
		if (Input::IsKeyPressed(KeyCode::KeyW))
			m_Position += m_pCamera->GetFront() * moveVelocity;
		if (Input::IsKeyPressed(KeyCode::KeyS))
			m_Position -= m_pCamera->GetFront() * moveVelocity;
	
		if (Input::IsKeyPressed(KeyCode::KeyA))
			m_Position -= m_pCamera->GetRight() * moveVelocity;
		if (Input::IsKeyPressed(KeyCode::KeyD))
			m_Position += m_pCamera->GetRight() * moveVelocity;

		if (Input::IsKeyPressed(KeyCode::KeyE))
			m_Position += m_pCamera->GetUp() * moveVelocity;
		if (Input::IsKeyPressed(KeyCode::KeyQ))
			m_Position -= m_pCamera->GetUp() * moveVelocity;

		// Look
		const float sensitivity = 0.15f;
		const glm::vec2 mouseMovement = Input::GetCursorMovement() * sensitivity;
		m_pCamera->AddYaw(mouseMovement.x);
		m_pCamera->AddPitch(-mouseMovement.y);
	}

	if (!Input::IsMouseButtonPressed(MouseCode::ButtonRight))
	{
		Input::SetCursorMode(CursorMode::Normal);
	}

	m_pCamera->SetPosition(m_Position);
}
