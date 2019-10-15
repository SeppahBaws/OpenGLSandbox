#include "pch.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"

glm::mat4 Renderer::s_ViewProjectionMatrix;

void Renderer::Init(const ViewportData& vp)
{
	glViewport(vp.x, vp.y, vp.width, vp.height);

	
	/*
	// Temporary View Projection Matrices
	const float aspectRatio = float(vp.width) / float(vp.height);
	// glm::mat4 projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	// viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f));
	// viewMatrix = glm::inverse(viewMatrix);
	s_ViewProjectionMatrix = projectionMatrix * viewMatrix;
	*/
	
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
	// pShader->Bind();
	// pShader->SetUniformMat4("u_Model", transform);
	// pShader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
	//
	// pModel->GetMeshes()[0].Bind();
	// glDrawElements(GL_TRIANGLES, pModel->GetMeshes()[0].GetIndexCount(), GL_UNSIGNED_INT, 0);
	
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
