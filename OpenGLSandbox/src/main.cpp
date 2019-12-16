#include "pch.h"
// ReSharper Disable Once CppUnusedIncludeDirective
#include <vld.h>

#include "src/Core/Application.h"

#include "src/Core/Scene/Scene.h"
#include "src/Core/Scene/Actor.h"
#include "src/Core/Scene/Components/ModelComponent.h"

class GameScene : public Scene
{
public:
	GameScene()
	{
		Actor* pGun = CreateActor("Gun");
		ModelComponent* pModelComp = pGun->AttachComponent<ModelComponent>();
		pModelComp->SetModel("assets/models/drakefire-pistol/drakefire_pistol_low.obj");
		pModelComp->SetShader("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");
		pGun->SetPosition({ 1.0f, 1.0f, 1.0f });
		pGun->SetRotation({ 0.0f, 0.0f, 45.0f });

		Actor* pCube = CreateActor("Cube");
		pModelComp = pCube->AttachComponent<ModelComponent>();
		pModelComp->SetModel("assets/models/default-shapes/cube.fbx");
		pModelComp->SetShader("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");
		pCube->SetScale(glm::vec3(0.5f));

		Actor* pMonkey = CreateActor("Monkey");
		pModelComp = pMonkey->AttachComponent<ModelComponent>();
		pModelComp->SetModel("assets/models/default-shapes/suzan-monkey.fbx");
		pModelComp->SetShader("assets/shaders/simpleShader.vert", "assets/shaders/simpleShader.frag");
		pMonkey->SetPosition({ -2.0f, 0.0f, 0.0f });
		pMonkey->SetRotation({ -90.0f, 0.0f, 30.0f });

		Actor* pSphere = CreateActor("Light");
		pModelComp = pSphere->AttachComponent<ModelComponent>();
		pModelComp->SetModel("assets/models/default-shapes/uv-sphere.fbx");
		pModelComp->SetShader("assets/shaders/unlit.vert", "assets/shaders/unlit.frag");
		pSphere->SetPosition({ 0.0f, 2.0f, 2.5f });
		pSphere->SetScale(glm::vec3(0.25f));
	}

	~GameScene()
	{
	}
};

int main()
{
	Application* pApplication = new Application();
	pApplication->UseScene(new GameScene());
	pApplication->Run();
	
	delete pApplication;
}
