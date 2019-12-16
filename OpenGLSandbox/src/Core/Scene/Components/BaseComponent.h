#pragma once

class Actor;

class BaseComponent
{
public:
	BaseComponent(Actor* actor);
	virtual ~BaseComponent() = default;
	
	virtual void Start();
	virtual void Update();
	virtual void Render();

protected:
	Actor* m_pActor;
};
