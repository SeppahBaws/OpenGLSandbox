#include "pch.h"
#include "Material.h"
#include "dependencies/imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

Material::Material(const std::shared_ptr<Shader>& pShader)
	: m_pShader(pShader)
{
	GenerateProperties();
}

void Material::Bind(const glm::mat4& transform, const glm::mat4& viewProjection)
{
	m_pShader->Bind();
	m_pShader->SetUniformMat4("u_Model", transform);
	m_pShader->SetUniformMat4("u_ViewProjection", viewProjection);

	for (auto it = m_Properties.begin(); it != m_Properties.end(); ++it)
	{
		switch (it->dataType)
		{
			// Booleans
		case GLShaderParser::DataType::Bool:
			m_pShader->SetUniformBool(it->name, std::get<bool>(it->data));
			break;
		// case GLShaderParser::DataType::Bool2:
		// 	m_pShader->SetUniformBool2(it->name, std::get<glm::bvec2>(it->data));
		// 	break;
		// case GLShaderParser::DataType::Bool3:
		// 	m_pShader->SetUniformBool3(it->name, std::get<glm::bvec3>(it->data));
		// 	break;
		// case GLShaderParser::DataType::Bool4:
		// 	m_pShader->SetUniformBool4(it->name, std::get<glm::bvec4>(it->data));
		// 	break;

			// Integers
		case GLShaderParser::DataType::Int:
			m_pShader->SetUniformInt(it->name, std::get<int>(it->data));
			break;
		case GLShaderParser::DataType::Int2:
			m_pShader->SetUniformInt2(it->name, std::get<glm::ivec2>(it->data));
			break;
		case GLShaderParser::DataType::Int3:
			m_pShader->SetUniformInt3(it->name, std::get<glm::ivec3>(it->data));
			break;
		case GLShaderParser::DataType::Int4:
			m_pShader->SetUniformInt4(it->name, std::get<glm::ivec4>(it->data));
			break;

			// Unsigned Integers
		// case GLShaderParser::DataType::UInt:
		// 	m_pShader->SetUniformUInt(it->name, std::get<unsigned int>(it->data));
		// 	break;
		// case GLShaderParser::DataType::UInt2:
		// 	m_pShader->SetUniformUInt2(it->name, std::get<glm::uvec2>(it->data));
		// 	break;
		// case GLShaderParser::DataType::UInt3:
		// 	m_pShader->SetUniformUInt3(it->name, std::get<glm::uvec3>(it->data));
		// 	break;
		// case GLShaderParser::DataType::UInt4:
		// 	m_pShader->SetUniformUInt4(it->name, std::get<glm::uvec4>(it->data));
		// 	break;

			// Floats
		case GLShaderParser::DataType::Float:
			m_pShader->SetUniformFloat(it->name, std::get<float>(it->data));
			break;
		case GLShaderParser::DataType::Float2:
			m_pShader->SetUniformFloat2(it->name, std::get<glm::vec2>(it->data));
			break;
		case GLShaderParser::DataType::Float3:
			m_pShader->SetUniformFloat3(it->name, std::get<glm::vec3>(it->data));
			break;
		case GLShaderParser::DataType::Float4:
			m_pShader->SetUniformFloat4(it->name, std::get<glm::vec4>(it->data));
			break;

			// Doubles
		// case GLShaderParser::DataType::Double:
		// 	m_pShader->SetUniformDouble(it->name, std::get<double>(it->data));
		// 	break;
		// case GLShaderParser::DataType::Double2:
		// 	m_pShader->SetUniformDouble2(it->name, std::get<glm::dvec2>(it->data));
		// 	break;
		// case GLShaderParser::DataType::Double3:
		// 	m_pShader->SetUniformDouble3(it->name, std::get<glm::dvec3>(it->data));
		// 	break;
		// case GLShaderParser::DataType::Double4:
		// 	m_pShader->SetUniformDouble4(it->name, std::get<glm::dvec4>(it->data));
		// 	break;

			// The material editor in-game isn't going to be able to edit these values.
		case GLShaderParser::DataType::Mat3:
		case GLShaderParser::DataType::Mat4:
		case GLShaderParser::DataType::Sampler2D:
			break;
			
		default: LOG_CRITICAL("Data type for Uniform {0} not implemented yet!", it->name);
		}
	}
}

void Material::Render()
{
}

void Material::RenderUniformsImGui()
{
	for (auto& property : m_Properties)
	{
		switch (property.dataType)
		{
			// Booleans
		case GLShaderParser::DataType::Bool:
			ImGui::Checkbox(property.name.c_str(), &std::get<bool>(property.data));
			break;

			// Integers
		case GLShaderParser::DataType::Int:
			ImGui::InputInt(property.name.c_str(), &std::get<int>(property.data));
			break;
		case GLShaderParser::DataType::Int2:
			ImGui::InputInt2(property.name.c_str(), glm::value_ptr(std::get<glm::ivec2>(property.data)));
			break;
		case GLShaderParser::DataType::Int3:
			ImGui::InputInt3(property.name.c_str(), glm::value_ptr(std::get<glm::ivec3>(property.data)));
			break;
		case GLShaderParser::DataType::Int4:
			ImGui::InputInt4(property.name.c_str(), glm::value_ptr(std::get<glm::ivec4>(property.data)));
			break;

			// Floats
		case GLShaderParser::DataType::Float:
			ImGui::InputFloat(property.name.c_str(), &std::get<float>(property.data));
			break;
		case GLShaderParser::DataType::Float2:
			ImGui::InputFloat2(property.name.c_str(), glm::value_ptr(std::get<glm::vec2>(property.data)));
			break;
		case GLShaderParser::DataType::Float3:
			ImGui::InputFloat3(property.name.c_str(), glm::value_ptr(std::get<glm::vec3>(property.data)));
			break;
		case GLShaderParser::DataType::Float4:
			ImGui::InputFloat4(property.name.c_str(), glm::value_ptr(std::get<glm::vec4>(property.data)));
			break;

		case GLShaderParser::DataType::Mat3:
		case GLShaderParser::DataType::Mat4:
		case GLShaderParser::DataType::Sampler2D:
			break;
			
		default:;
		}
	}
}

void Material::ReloadShader()
{
	m_pShader->Reload();
	GenerateProperties();
}

void Material::GenerateProperties()
{
	m_Properties.clear();
	
	auto uniforms = m_pShader->GetUniforms();

	for (auto& uniform : uniforms)
	{
		switch (uniform.type)
		{
			// Booleans
		case GLShaderParser::DataType::Bool:
			m_Properties.push_back(Property{ uniform.name, uniform.type, false });
			break;
		// case GLShaderParser::DataType::Bool2:
		// 	m_Properties.push_back(Property{ uniform.name, uniform.type, glm::bvec2(false, false) });
		// 	break;
		// case GLShaderParser::DataType::Bool3:
		// 	m_Properties.push_back(Property{ uniform.name, uniform.type, glm::bvec3(false, false, false) });
		// 	break;
		// case GLShaderParser::DataType::Bool4:
		// 	m_Properties.push_back(Property{ uniform.name, uniform.type, glm::bvec4(false, false, false, false) });
		// 	break;

			// Integers
		case GLShaderParser::DataType::Int:
			m_Properties.push_back(Property{ uniform.name, uniform.type, 0 });
			break;
		case GLShaderParser::DataType::Int2:
			m_Properties.push_back(Property{ uniform.name, uniform.type, glm::ivec2(0, 0) });
			break;
		case GLShaderParser::DataType::Int3:
			m_Properties.push_back(Property{ uniform.name, uniform.type, glm::ivec3(0, 0, 0) });
			break;
		case GLShaderParser::DataType::Int4:
			m_Properties.push_back(Property{ uniform.name, uniform.type, glm::ivec4(0, 0, 0, 0) });
			break;

			// Unsigned Integers

			// Floats
		case GLShaderParser::DataType::Float:
			m_Properties.push_back(Property{ uniform.name, uniform.type, 0.0f });
			break;
		case GLShaderParser::DataType::Float2:
			m_Properties.push_back(Property{ uniform.name, uniform.type, glm::vec2(0.0) });
			break;
		case GLShaderParser::DataType::Float3:
			m_Properties.push_back(Property{ uniform.name, uniform.type, glm::vec3(0.0) });
			break;
		case GLShaderParser::DataType::Float4:
			m_Properties.push_back(Property{ uniform.name, uniform.type, glm::vec4(0.0) });
			break;

			// Doubles
			
		default:
			m_Properties.push_back(Property{ uniform.name, uniform.type, {} });
		}
	}
}
