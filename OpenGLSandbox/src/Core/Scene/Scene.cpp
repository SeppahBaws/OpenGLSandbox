#include "pch.h"
#include "Scene.h"

void Scene::Cleanup()
{
	for (int i = 0; i < m_pActors.size(); ++i)
	{
		delete m_pActors[i];
	}
}

void Scene::Start()
{
	for (int i = 0; i < m_pActors.size(); ++i)
	{
		m_pActors[i]->Start();
	}
}

void Scene::Update()
{
	for (int i = 0; i < m_pActors.size(); ++i)
	{
		m_pActors[i]->Update();
	}
}

void Scene::Render()
{
	for (int i = 0; i < m_pActors.size(); ++i)
	{
		m_pActors[i]->Render();
	}
}

Actor* Scene::CreateActor(const std::string& name)
{
	Actor* pActor = new Actor(name);
	m_pActors.push_back(pActor);

	return pActor;
}
