#pragma once
#include <memory>
#include <glm/glm.hpp>

class Mesh;
class Model;
class Shader;
class Material;
class Camera;

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
	
	static void BeginScene(const std::shared_ptr<Camera>& pCamera);
	static void Clear(float r, float g, float b, float a);

	static void Render(std::shared_ptr<Mesh> pMesh, std::shared_ptr<Shader> pShader, const glm::mat4& transform);
	static void Render(std::shared_ptr<Model> pModel, std::shared_ptr<Shader> pShader, const glm::mat4& transform);
	static void Render(std::shared_ptr<Model> pModel, std::shared_ptr<Material> pMaterial, const glm::mat4& transform);

private:
	// TODO: This must get set by the camera!
	static glm::mat4 s_ViewProjectionMatrix;
};
