#pragma once
#include <memory>
#include <glm/glm.hpp>

class Shader;
class Mesh;

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

	static void Render(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader, const glm::mat4& transform);

private:
	// TODO: This must get set by the camera!
	static glm::mat4 s_ViewProjectionMatrix;
};
