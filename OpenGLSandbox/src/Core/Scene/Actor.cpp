#include "pch.h"
#include "Actor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

Actor::Actor(const std::string& name)
{
	m_Name = name;
	m_Position = glm::vec3(0.0f);
	m_Rotation = glm::vec3(0.0f);
	m_Scale = glm::vec3(1.0f);
	CalculateTransform();
}

Actor::~Actor()
{
	for (int i = 0; i < m_pComponents.size(); ++i)
	{
		delete m_pComponents[i];
	}
}

void Actor::SetPosition(const glm::vec3& position)
{
	m_Position = position;

	CalculateTransform();
}

void Actor::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;

	CalculateTransform();
}

void Actor::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;

	CalculateTransform();
}

glm::mat4 Actor::GetTransform()
{
	return m_Transform;
}

void Actor::Start()
{
	for (int i = 0; i < m_pComponents.size(); ++i)
	{
		m_pComponents[i]->Start();
	}
}

void Actor::Update()
{
	for (int i = 0; i < m_pComponents.size(); ++i)
	{
		m_pComponents[i]->Update();
	}
}

void Actor::Render()
{
	for (int i = 0; i < m_pComponents.size(); ++i)
	{
		m_pComponents[i]->Render();
	}
}

void Actor::CalculateTransform()
{
	m_Transform = glm::translate(glm::mat4(1.0f), m_Position) *
		glm::orientate4(glm::vec3(glm::radians(m_Rotation))) *
		glm::scale(glm::mat4(1.0f), m_Scale);
}
