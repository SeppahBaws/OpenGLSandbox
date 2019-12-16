#pragma once

#include "Components/BaseComponent.h"
#include <glm/glm.hpp>

class Actor
{
public:
	Actor(const std::string& name);
	~Actor();

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const glm::vec3& scale);

	glm::mat4 GetTransform();

	virtual void Start();
	virtual void Update();
	virtual void Render();

	template<typename T>
	T* AttachComponent()
	{
		T* t = new T(this);
		m_pComponents.push_back(t);

		return t;
	}

private:
	void CalculateTransform();

private:
	std::string m_Name;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	glm::mat4 m_Transform;

	std::vector<BaseComponent*> m_pComponents;
};
