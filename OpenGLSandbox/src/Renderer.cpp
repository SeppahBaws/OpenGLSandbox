#include "Renderer.h"

#include "helpers/Logger.h"
#include "Shader.h"

#include <glad/glad.h>
#include <sstream>

void Renderer::Init(const ViewportData& vp)
{
	glViewport(vp.x, vp.y, vp.width, vp.height);
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(unsigned int VAO, unsigned int EBO, int count, Shader shader)
{
	shader.Bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
