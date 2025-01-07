#pragma once
#include "Collectibles.h"
#include "GameEngineProject.h"
class PowerHealth : public Collectibles
{
public:
	PowerHealth(Level* mylevel, GameEngine engine);
	~PowerHealth();
	void  Hit() override;
	void Update(float deltaTime) override;
};

