#pragma once
#include "Enemy.h"
#include "GameEngineProject.h"
class Drone : public Enemy
{
public:
	Drone(Level* mylevel, GameEngine engine);
	~Drone();

	void Update(float deltaTime) override;
	void Hit() override;
private:
	float timer;
};

