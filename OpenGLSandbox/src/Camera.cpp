#include "pch.h"
#include "Camera.h"

#include "Input.h"
#include "Time.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspectRatio, float zNear, float zFar)
	: m_Position(glm::vec3(0.0f, 0.0f, 3.0f))
	, m_Fov(fov)
	, m_AspectRatio(aspectRatio)
	, m_ZNear(zNear)
	, m_ZFar(zFar)
{
	m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_Front = glm::vec3(0.0f, 0.0f, 1.0f);

	CalculateCameraVectors();
	CalculateProjectionMatrix();
	CalculateViewMatrix();
}

void Camera::CalculateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);
	
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::CalculateViewMatrix()
{
	CalculateCameraVectors();
	
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::CalculateProjectionMatrix()
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov / 2), m_AspectRatio, m_ZNear, m_ZFar);
}
