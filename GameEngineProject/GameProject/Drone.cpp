#include "Drone.h"

Drone::Drone(Level* mylevel, GameEngine engine) : Enemy(mylevel)
{
	SetBMP("graphics/drone.bmp", 8, 2, 4);
	float value = engine.getRandomFloat(100, 400);
	SetStartPos(value, -300.0f);
	SetGravScale(10.0f);
	SetSensor(false);
	animationManager.AddAnimation("Drone", { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, 0.1f);
	animationManager.SetCurrentAnimation("Drone");
}

Drone::~Drone()
{
}

void Drone::Update(float deltaTime)
{
	float gravMultiplier;
	timer += deltaTime;
	if (timer > 1)
	{
		gravMultiplier = 1;
		if (timer> 2)
		{
			timer = 0;
		}
	}
	else
	{
		gravMultiplier = -1;
	}
	ApplyForce(10000000 * gravMultiplier, 0, deltaTime);
	ResetXForce();
	GetPosition();
	SetPos(Firstpos, Secondpos, 0);
	GameObject::Update(deltaTime);
}

void Drone::Hit()
{
	delete this;
}
