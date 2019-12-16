#include "pch.h"
#include "ModelComponent.h"

#include "src/Renderer/Renderer.h"
#include "src/Core/Scene/Actor.h"

ModelComponent::ModelComponent(Actor* pActor)
	: BaseComponent(pActor)
{
}

void ModelComponent::Render()
{
	Renderer::Render(m_pModel, m_pShader, m_pActor->GetTransform());
}

void ModelComponent::SetModel(const std::string& path)
{
	m_pModel = std::make_shared<Model>(path);
}

void ModelComponent::SetShader(const std::string& vertPath, const std::string& fragPath)
{
	m_pShader = std::make_shared<Shader>();
	m_pShader->InitFromFile(vertPath, fragPath);
}
