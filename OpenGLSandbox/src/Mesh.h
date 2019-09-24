#pragma once
#include <vector>
#include <memory>

#include <glm/glm.hpp>

class Shader;

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

	void Bind();

	uint32_t GetIndexCount() const;

private:
	void SetupMesh();
	
private:
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;

	uint32_t m_VBO, m_VAO, m_EBO;
};
