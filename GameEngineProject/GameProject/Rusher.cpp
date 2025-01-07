#include "Rusher.h"

Rusher::Rusher(Level* mylevel, GameEngine engine) : Enemy(mylevel)
{
	SetBMP("graphics/rusher.bmp", 4, 6, 4);
	float value = engine.getRandomFloat(0, 460);
	SetStartPos(value, -100.0f);
	SetGravScale(10.0f);
	SetSensor(false);
	animationManager.AddAnimation("Rusher", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 }, 0.1f);
	animationManager.SetCurrentAnimation("Rusher");
}
Rusher::~Rusher()
{
}

void Rusher::Update(float deltaTime)
{
	GetPosition();
	SetPos(Firstpos, Secondpos, 0);
	GameObject::Update(deltaTime);
}

void Rusher::Hit()
{
	delete this;
}

