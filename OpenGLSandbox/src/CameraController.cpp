#include "pch.h"
#include "CameraController.h"

#include "Input.h"
#include "Time.h"

CameraController::CameraController(std::shared_ptr<Camera> pCamera)
	: m_pCamera(pCamera), m_Position({ 0.0f, 0.0f, 3.0f }), m_MoveSpeed(3), m_Yaw(0), m_Pitch(0)
{
}

void CameraController::Update()
{
	if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
	{
		if (Input::IsKeyPressed(KeyCode::KeyA))
			m_Position.x -= m_MoveSpeed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(KeyCode::KeyD))
			m_Position.x += m_MoveSpeed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(KeyCode::KeyE))
			m_Position.y += m_MoveSpeed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(KeyCode::KeyQ))
			m_Position.y -= m_MoveSpeed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(KeyCode::KeyW))
			m_Position.z -= m_MoveSpeed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(KeyCode::KeyS))
			m_Position.z += m_MoveSpeed * Time::GetDeltaTime();
	}

	m_pCamera->SetPosition(m_Position);
}
