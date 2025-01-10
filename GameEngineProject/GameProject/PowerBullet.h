#pragma once
#include "Collectibles.h"
#include "GameEngineProject.h"
class PowerBullet : public Collectibles
{
public:
	PowerBullet(Level* mylevel, GameEngine engine);
	~PowerBullet();
	void Update(float deltaTime) override;
	void Upgrade(GameObject* Object) override;
};

