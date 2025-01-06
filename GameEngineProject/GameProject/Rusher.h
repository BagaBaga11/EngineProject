#pragma once
#include "Enemy.h"
#include "GameEngineProject.h"
class Rusher : public Enemy
{
public:
	Rusher(Level* mylevel, GameEngine engine);
	~Rusher();

	void Update(float deltaTime) override;
	void Hit() override;
};

