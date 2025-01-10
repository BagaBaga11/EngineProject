#include "PowerBullet.h"
#include "Player.h"

PowerBullet::PowerBullet(Level* mylevel, GameEngine engine):Collectibles(mylevel)
{
	SetBMP("graphics/PUWeapon.bmp", 4, 2, 2);
	float value = engine.getRandomFloat(0, 460);
	SetStartPos(value, -100.0f);
	SetGravScale(10.0f);
	SetSensor(true);
	animationManager.AddAnimation("Project", { 1,2,3,4,5,6,7,8 }, 0.1f);
	animationManager.SetCurrentAnimation("Project");
}

PowerBullet::~PowerBullet()
{
}

void PowerBullet::Update(float deltaTime)
{
	GetPosition();
	SetPos(Firstpos, Secondpos, 0);
	GameObject::Update(deltaTime);
}

void PowerBullet::Upgrade(GameObject* Object)
{
	if (auto* p = dynamic_cast<Player*>(Object))
	{
		p->ChangeMissile();
	}
	else if (auto* c = dynamic_cast<Companion*>(Object))
	{
		c->ChangeMissile();
	}
	delete this;
}
