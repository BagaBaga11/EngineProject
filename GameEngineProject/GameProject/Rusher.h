#pragma once
#include <GameObjects.h>
#include "GameEngineProject.h"
class Rusher : public GameObject
{
public:
	Rusher(Level* mylevel, GameEngine engine);
	~Rusher();

	void Update(float deltaTime) override;
	void Hit() override;
};

