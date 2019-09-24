#include "Renderer.h"

#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Renderer::s_ModelMatrix;
glm::mat4 Renderer::s_ViewProjectionMatrix;

void Renderer::Init(const ViewportData& vp)
{
	glViewport(vp.x, vp.y, vp.width, vp.height);

	// Temporary View Projection Matrices
	const float aspectRatio = float(vp.width) / float(vp.height);
	glm::mat4 projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);
	// glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), vp.width);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f));
	viewMatrix = glm::inverse(viewMatrix);
	s_ViewProjectionMatrix = projectionMatrix * viewMatrix;

	s_ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0f));
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(unsigned int VAO, unsigned int EBO, int count, std::shared_ptr<Shader> pShader)
{
	pShader->Bind();
	pShader->SetUniformMat4("u_Model", s_ModelMatrix);
	pShader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
