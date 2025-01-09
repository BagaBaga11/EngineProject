#include "MetalAsteroids.h"
#include "GameEngineProject.h"

MetalAsteroids::MetalAsteroids(Level* mylevel, GameEngine engine) : Asteroids(mylevel)
{
	Engine = engine;
	SetGravScale(1.0f);
	SetSensor(false);
	animationManager.AddAnimation("Asteroid", { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 }, 0.1f);
	animationManager.SetCurrentAnimation("Asteroid");
}

MetalAsteroids::~MetalAsteroids()
{
}

void MetalAsteroids::Update(float deltaTime)
{
	GetPosition();
	SetPos(Firstpos, Secondpos, 0);
	GameObject::Update(deltaTime);
}

void MetalAsteroids::Hit()
{
	delete this;
}
