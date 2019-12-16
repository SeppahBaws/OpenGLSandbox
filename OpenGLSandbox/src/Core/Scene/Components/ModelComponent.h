#pragma once

#include "BaseComponent.h"
#include "src/Renderer/Model.h"
#include "src/Renderer/Shader.h"

class ModelComponent : public BaseComponent
{
public:
	ModelComponent(Actor* pActor);

	void Render() override;

	void SetModel(const std::string& path);
	void SetShader(const std::string& vertPath, const std::string& fragPath);

private:
	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Shader> m_pShader;
};
