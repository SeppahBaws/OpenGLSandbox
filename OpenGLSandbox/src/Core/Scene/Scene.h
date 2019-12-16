#pragma once
#include "Actor.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Cleanup() final;
	
	virtual void Start();
	virtual void Update();
	virtual void Render();

protected:
	Actor* CreateActor(const std::string& name);

private:
	std::vector<Actor*> m_pActors;
};
