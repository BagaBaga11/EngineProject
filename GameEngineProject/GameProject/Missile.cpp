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
	newposX = Firstpos;
	newposY = Secondpos;
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
	sion->SetStartPos(newposX, newposY);
	sion->StartObject();
	GameObject::Hit();
}


