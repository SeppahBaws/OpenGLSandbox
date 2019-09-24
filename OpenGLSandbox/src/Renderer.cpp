#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"

glm::mat4 Renderer::s_ViewProjectionMatrix;

void Renderer::Init(const ViewportData& vp)
{
	glViewport(vp.x, vp.y, vp.width, vp.height);

	// Temporary View Projection Matrices
	const float aspectRatio = float(vp.width) / float(vp.height);
	glm::mat4 projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);
	// glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f));
	viewMatrix = glm::inverse(viewMatrix);
	s_ViewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader, const glm::mat4& transform)
{
	pShader->Bind();
	pShader->Bind();
	pShader->SetUniformMat4("u_Model", transform);
	pShader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
	
	pMesh->Bind();

	glDrawElements(GL_TRIANGLES, pMesh->GetIndexCount(), GL_UNSIGNED_INT, 0);
}
