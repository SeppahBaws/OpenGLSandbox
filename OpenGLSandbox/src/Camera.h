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
	inline void SetRotation(const glm::vec3& newRot) { m_Rotation = newRot; CalculateViewMatrix();}

private:
	void CalculateCameraVectors();
	void CalculateViewMatrix(/*const glm::vec3& position, const glm::vec3& rotation*/);
	void CalculateProjectionMatrix(/*float fov, float aspectRatio, float zNear, float zFar*/);

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	
	glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
	glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

	float m_Fov;
	float m_AspectRatio;
	float m_ZNear;
	float m_ZFar;

	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;
};
