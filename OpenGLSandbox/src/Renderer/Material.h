#pragma once
#include <memory>
#include <variant>

#include "Shader.h"

struct Property
{
	std::string name;
	GLShaderParser::DataType dataType;
	std::variant<
		bool, glm::bvec2, glm::bvec3, glm::bvec4,
		int, glm::ivec2, glm::ivec3, glm::ivec4,
		unsigned int, glm::uvec2, glm::uvec3, glm::uvec4,
		float, glm::vec2, glm::vec3, glm::vec4,
		double, glm::dvec2, glm::dvec3, glm::dvec4,
		glm::mat3, glm::mat4
	> data;	// TODO: sampler2D?
};

class Material
{
public:
	Material(const std::shared_ptr<Shader>& pShader);

	void Bind(const glm::mat4& transform, const glm::mat4& viewProjection);
	
	void Render();
	void RenderUniformsImGui();
	void ReloadShader();

private:
	void GenerateProperties();
	
private:
	std::shared_ptr<Shader> m_pShader;
	std::vector<Property> m_Properties;
};