#pragma once
#include "Camera.h"

class CameraController
{
public:
	CameraController(std::shared_ptr<Camera> pCamera);

	void Update();

	inline glm::vec3 GetPosition() const { return m_Position; }

private:
	std::shared_ptr<Camera> m_pCamera;

	glm::vec3 m_Position;
	float m_MoveSpeed;
};
