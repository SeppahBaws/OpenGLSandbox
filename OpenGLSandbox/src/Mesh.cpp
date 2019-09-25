#include "pch.h"
#include "Mesh.h"
#include <glad/glad.h>

#include "Shader.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
{
	m_Vertices = std::move(vertices);
	m_Indices = std::move(indices);

	SetupMesh();
}

void Mesh::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);
}

uint32_t Mesh::GetIndexCount() const
{
	return uint32_t(m_Indices.size());
}

void Mesh::SetupMesh()
{
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(Vertex), m_Indices.data(), GL_STATIC_DRAW);


	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// TexCoord Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
