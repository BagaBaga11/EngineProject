#include "Missile.h"
#include <iostream>

Missile::Missile(Level* mylevel) : GameObject(mylevel)
{

}
Missile::~Missile()
{

}

void Missile::Update(float deltaTime)
{
	GetPosition();
	SetPos(Firstpos, Secondpos,0);
	mytimer += deltaTime;
	GameObject::Update(deltaTime);
	if (mytimer > 5)
	{
		Hit();
	}
}

void Missile::Hit()
{
	Explo* sion = new Explo(mylevel);
	sion->SetStartPos(Firstpos, Secondpos);
	sion->StartObject();
	delete this;
}


