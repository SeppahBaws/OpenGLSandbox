#pragma once
#include <memory>
#include <glm/glm.hpp>

class Shader;

class Renderer
{
public:
	struct ViewportData
	{
		int x;
		int y;
		int width;
		int height;
	};
	
public:
	static void Init(const ViewportData& vp);
	
	static void Clear(float r, float g, float b, float a);

	static void Render(unsigned int VAO, unsigned int EBO, int count, std::shared_ptr<Shader> pShader);

private:
	static glm::mat4 s_ModelMatrix;
	static glm::mat4 s_ViewProjectionMatrix;
};
