#pragma once

#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera(float fov, float aspectRatio, float zNear, float zFar);

	inline glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	inline glm::vec3 GetPosition() const { return m_Position; }
	inline void SetPosition(const glm::vec3& newPos) { m_Position = newPos; CalculateViewMatrix(); }
	inline glm::vec3 GetRotation() const { return m_Rotation; }
	inline void SetRotation(const glm::vec3& newRot) { m_Rotation = newRot; CalculateViewMatrix(); }

	inline glm::vec3 GetFront() const { return m_Front; }
	inline glm::vec3 GetRight() const { return m_Right; }
	inline glm::vec3 GetUp() const { return m_Up; }

	inline void AddYaw(float amount) { m_Yaw += amount; }
	inline void AddPitch(float amount)
	{
		m_Pitch += amount;
		if (m_Pitch >= 89.9f) m_Pitch = 89.9f;
		if (m_Pitch <= -89.9f) m_Pitch = -89.9f;
	}

private:
	void CalculateCameraVectors();
	void CalculateViewMatrix();
	void CalculateProjectionMatrix();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	
	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

	float m_Fov = 0.0f;
	float m_AspectRatio = 0.0f;
	float m_ZNear = 0.0f;
	float m_ZFar = 0.0f;

	glm::vec3 m_Front = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Up = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Right = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_WorldUp = { 0.0f, 0.0f, 0.0f };

	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;
};
