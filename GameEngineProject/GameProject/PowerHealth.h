#pragma once
#include "Collectibles.h"
#include "GameEngineProject.h"
class PowerHealth : public Collectibles
{
public:
	PowerHealth(Level* mylevel, GameEngine engine);
	~PowerHealth();
	void Update(float deltaTime) override;
	void Upgrade(GameObject* Object) override;
};

