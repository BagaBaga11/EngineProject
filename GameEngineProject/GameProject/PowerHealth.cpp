#include "PowerHealth.h"
#include "Levels.h"
#include "Player.h"

PowerHealth::PowerHealth(Level* mylevel, GameEngine engine) : Collectibles(mylevel)
{
	SetBMP("graphics/PUShield.bmp", 4, 2, 2);
	float value = engine.getRandomFloat(0, 460);
	SetStartPos(value, -100.0f);
	SetGravScale(10.0f);
	SetSensor(true);
	animationManager.AddAnimation("Project", { 1,2,3,4,5,6,7,8 }, 0.1f);
	animationManager.SetCurrentAnimation("Project");
}

PowerHealth::~PowerHealth()
{
}

void PowerHealth::Hit()
{
	if(auto* player = dynamic_cast<Player*>(mylevel->GetPawn()))
	{
		player->ChangeHealh(1);
		delete this;
	}
}

void PowerHealth::Update(float deltaTime)
{
	GetPosition();
	SetPos(Firstpos, Secondpos, 0);
	GameObject::Update(deltaTime);
}
