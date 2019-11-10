#include "pch.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"

glm::mat4 Renderer::s_ViewProjectionMatrix;

void Renderer::Init(const ViewportData& vp)
{
	glViewport(vp.x, vp.y, vp.width, vp.height);
}

void Renderer::BeginScene(const std::shared_ptr<Camera>& pCamera)
{
	s_ViewProjectionMatrix = pCamera->GetViewProjectionMatrix();
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader, const glm::mat4& transform)
{
	pShader->Bind();
	pShader->SetUniformMat4("u_Model", transform);
	pShader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
	
	pMesh->Bind();

	glDrawElements(GL_TRIANGLES, pMesh->GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::Render(std::shared_ptr<Model> pModel, std::shared_ptr<Shader> pShader, const glm::mat4& transform)
{
	for (Mesh& mesh : pModel->GetMeshes())
	{
		pShader->Bind();
		pShader->SetUniformMat4("u_Model", transform);
		pShader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
		
		mesh.Bind();
		glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Renderer::Render(std::shared_ptr<Model> pModel, std::shared_ptr<Material> pMaterial, const glm::mat4& transform)
{
	for (Mesh& mesh : pModel->GetMeshes())
	{
		pMaterial->Bind(transform, s_ViewProjectionMatrix);

		mesh.Bind();
		glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
