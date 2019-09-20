#include "Renderer.h"

#include <glad/glad.h>

void Renderer::Init()
{
	// Nothing for now
}

void Renderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
